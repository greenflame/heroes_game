#include "session.h"


Session::Session(QString fieldFile, QString firstProgramm, QString secondProgramm, QString picturesPath, QObject *parent)
{
    f = Field(fieldFile);
    cellSize = QSize(60, 60);
    motionPathStep = 0;

    this->firstProgram = firstProgramm;
    this->secondProgramm = secondProgramm;
    this->picturesPath = picturesPath;

    this->parent = parent;
}

QImage Session::nextFrame()
{
    if (motionPathStep == motionPath.length())   // Path complete
    {
        // Run
        QString curProgramm = (f.getActionQueue().first().getOwner() == FIRST_PALYER ? firstProgram : secondProgramm);
        QString output = executeProgramm(curProgramm, generateInput(), 500);

        // Save output
        QTextStream ts(&output);
        int x, y;
        ts >> x >> y;
        move = QPoint(x, y);
        ts >> x >> y;
        attack = QPoint(x, y);

        // Move
        f.actionMove(move, log, motionPath);
        motionPathStep = 0;
        attackSuccess = false;
    }

    if (motionPathStep == motionPath.length() - 1)    // Last frame
    {
        f.actionAttack(attack, log, attackSuccess, damage, died);
    }

    QImage frame = renderField();

    motionPathStep++;

    return frame;
}

bool Session::isEnd()
{
    return f.isGameEnd() && motionPathStep == motionPath.length();
}

Player Session::winner()
{
    return f.getActionQueue().first().getOwner();
}

QImage Session::renderField()
{
    QImage frame(f.getSize().width() * cellSize.width(),
             f.getSize().height() * cellSize.height(),
             QImage::Format_ARGB32);

    QPainter p;
    p.begin(&frame);

    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.fillRect(frame.rect(), Qt::white);

    // Border
    p.setPen(Qt::gray);
    for (int i = 0; i < f.getSize().width(); i++)
    {
        for (int j = 0; j < f.getSize().height(); j++)
        {
            p.drawRect(posToFrameRect(QPoint(i, j)));
        }
    }

    // Motion path
    p.setPen(Qt::black);
    for (int i = 0; i < motionPath.length() - 1; i++)
    {
        p.drawLine(posToFrameRect(motionPath.at(i)).center(), posToFrameRect(motionPath.at(i + 1)).center());
    }

    // Troops
    for (int i = 0; i < f.getTroops().length(); i++)
    {
        Troop curTroop = f.getTroops().at(i);
        QPoint troopPosition = curTroop.getPosition();

        if (troopPosition == motionPath.last())
        {
            troopPosition = motionPath.at(motionPathStep);
        }

        if (curTroop.getOwner() == FIRST_PALYER)
        {
            p.setPen(Qt::green);
        }
        if (curTroop.getOwner() == SECOND_PLAYER)
        {
            p.setPen(Qt::red);
        }

        // Border
        p.drawRect(posToFrameRect(troopPosition));

        // Picture
        QImage img(picturesPath + curTroop.getUnit().picture);
        QImage imgScaled = img.scaled(cellSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        p.drawImage(posToFrameRect(troopPosition), imgScaled, imgScaled.rect());

        // Count
        p.setFont(QFont("Arial", 20));
        p.drawText(posToFrameRect(troopPosition).bottomLeft(), QString::number(curTroop.getCount()));
    }

    // Attack
    if (motionPathStep == motionPath.length() - 1 && attackSuccess)
    {
        p.setPen(Qt::yellow);
        p.drawLine(posToFrameRect(motionPath.last()).center(), posToFrameRect(attack).center());
        p.drawEllipse(posToFrameRect(attack).adjusted(-10, -10, 10, 10));

        p.setFont(QFont("Arial", 20));
        p.drawText(posToFrameRect(attack).topLeft() - QPoint(0, 20), "-" + QString::number(damage) + "/-" + QString::number(died));
    }

    p.end();

    return frame;
}

QRect Session::posToFrameRect(QPoint pos)
{
    return QRect(pos.x() * cellSize.width(), pos.y() * cellSize.height(), cellSize.width(), cellSize.height());
}

QString Session::executeProgramm(QString programmName, QString input, int timeOut)
{
    // Remove old files
    QFile::remove("input.txt");
    QFile::remove("output.txt");

    // Write input
    QFile fileOut("input.txt");
    fileOut.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&fileOut);
    out << input;
    fileOut.close();

    // Run programm
    QProcess p(parent);
    p.start(programmName);
    p.waitForFinished(timeOut);

    // Read output
    QFile fileIn("output.txt");
    fileIn.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&fileIn);
    QString result = in.readAll();
    fileIn.close();

    return result;
}

QString Session::generateInput()
{
    QString result;
    QTextStream out(&result);

    // Troops
    out << f.getTroops().length();
    endl(out);

    for (int i = 0; i < f.getTroops().length(); i++)
    {
        Troop troop = f.getTroops().at(i);

        out << troop.getPosition().x();
        endl(out);
        out << troop.getPosition().y();
        endl(out);
        out << troop.getUnit().name;
        endl(out);
        out << troop.getCount();
        endl(out);
        out << troop.getHealth();
        endl(out);
    }

    QList<Troop> playerTroops, enemyTroops;

    for (int i = 0; i < f.getTroops().length(); i++)
    {
        if (f.getTroops().at(i).getOwner() == f.getActionQueue().first().getOwner())
        {
            playerTroops.append(f.getTroops().at(i));
        }
        else
        {
            enemyTroops.append(f.getTroops().at(i));
        }
    }

    // Player troops
    out << playerTroops.length();
    endl(out);

    for (int i = 0; i < playerTroops.length(); i++)
    {
        out << f.getTroops().indexOf(playerTroops.at(i));
        endl(out);
    }

    // Enemy troops
    out << enemyTroops.length();
    endl(out);

    for (int i = 0; i < enemyTroops.length(); i++)
    {
        out << f.getTroops().indexOf(enemyTroops.at(i));
        endl(out);
    }

    // Action queue
    out << f.getActionQueue().length();
    endl(out);

    for (int i = 0; i < f.getActionQueue().length(); i++)
    {
        out << f.getTroops().indexOf(f.getActionQueue().at(i));
        endl(out);
    }

    return result;
}

QString Session::getLog() const
{
    return log;
}

QString Session::troopsInfo() const
{
    QString result;
    QTextStream ts(&result);

    ts << "Troops:";
    endl(ts);
    for (int i = 0; i < f.getTroops().length(); i++)
    {
        ts << f.getTroops().at(i).toStringFull();
        endl(ts);
    }
    endl(ts);

    ts << "Action queue:";
    endl(ts);
    for (int i = 0; i < f.getActionQueue().length(); i++)
    {
        int index = f.getTroops().indexOf(f.getActionQueue().at(i));
        ts << index << " ";
    }
    endl(ts);

    return result;
}

QSize Session::getCellSize() const
{
    return cellSize;
}

void Session::setCellSize(const QSize &value)
{
    cellSize = value;
}
