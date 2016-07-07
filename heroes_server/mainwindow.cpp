#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    path = "/Users/Alexander/Desktop/heroes_game/data_folder/";
    cellSize = QSize(70, 70);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionStart_triggered()
{
    stop = false;
    Field f(path + "field.txt");

    while (!f.isGameEnd())
    {
        // Execute programm
        QPoint move, attack;
        executeProgramm(f, move, attack);
        validateInput(f, move, attack);

        // Process model and render
        QString log;
        QList<QPoint> motinPath;
        bool attackSuccess = false;
        int damage = 0, died = 0;
        f.actionMove(move, log, motinPath);

        for (int i = 0; i < motinPath.length(); i++)
        {
            if (i == motinPath.length() - 1)
            {
                f.actionAttack(attack, log, attackSuccess, damage, died);
            }
            QImage img = renderField(f, motinPath, i, attackSuccess, attack, damage, died);
            ui->label->setPixmap(QPixmap::fromImage(img));
            sleep(200);
        }

        ui->textEdit_log->insertPlainText(log);

        updateTroopsInfo(f);

        if (stop) { break; }
        sleep(1000);
    }
}

void MainWindow::on_actionStop_triggered()
{
    stop = true;
}

void MainWindow::executeProgramm(const Field &f, QPoint &move, QPoint &attack)
{
    QFile::remove("input.txt");
    QFile::remove("output.txt");

    writeInput(f);

    QString programmName = path + f.getActionQueue().first().getOwner();
//    if (programmName.indexOf("anton") != -1)
//    {
//        programmName = "/usr/local/Cellar/mono/4.2.3.4/bin/mono " + programmName;
//    }

    QProcess p(this);
    p.start(programmName);
    p.waitForFinished(500);

    readOutput(move, attack);
}

QImage MainWindow::renderField(const Field &f, QList<QPoint> motionPath, int motionStep,
                               bool attackSuccess, QPoint attack, int damage, int died)
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
            p.drawRect(pointToFrameRect(QPoint(i, j)));
        }
    }

    // Motion path
    p.setPen(Qt::black);
    for (int i = 0; i < motionPath.length() - 1; i++)
    {
        p.drawLine(pointToFrameRect(motionPath.at(i)).center(), pointToFrameRect(motionPath.at(i + 1)).center());
    }

    // Troops
    for (int i = 0; i < f.getTroops().length(); i++)
    {
        Troop curTroop = f.getTroops().at(i);
        QPoint troopPosition = curTroop.getPosition();

        if (troopPosition == motionPath.last())
        {
            troopPosition = motionPath.at(motionStep);
        }

        if (curTroop.getOwner() == "alex")
        {
            p.setPen(Qt::red);
        }
        if (curTroop.getOwner() == "anton")
        {
            p.setPen(Qt::green);
        }

        // Border
        p.drawRect(pointToFrameRect(troopPosition));

        // Picture
        QImage img(path + "pictures/" + curTroop.getUnit().picture);
        QImage imgScaled = img.scaled(cellSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        p.drawImage(pointToFrameRect(troopPosition), imgScaled, imgScaled.rect());

        // Count
        p.setFont(QFont("Arial", 20));
        p.drawText(pointToFrameRect(troopPosition).bottomLeft(), QString::number(curTroop.getCount()));
    }

    // Attack
    if (motionStep == motionPath.length() - 1 && attackSuccess)
    {
        p.setPen(Qt::yellow);
        p.drawLine(pointToFrameRect(motionPath.last()).center(), pointToFrameRect(attack).center());
        p.drawEllipse(pointToFrameRect(attack).adjusted(-10, -10, 10, 10));

        p.setFont(QFont("Arial", 20));
        p.drawText(pointToFrameRect(attack).topLeft() - QPoint(0, 20), "-" + QString::number(damage) + "/-" + QString::number(died));
    }

    p.end();

    return frame;
}

void MainWindow::updateTroopsInfo(const Field &f)
{
    ui->textEdit_info->clear();

    ui->textEdit_info->append("Troops:");
    for (int i = 0; i < f.getTroops().length(); i++)
    {
        ui->textEdit_info->append(f.getTroops().at(i).toStringFull());
    }
    ui->textEdit_info->append("");

    ui->textEdit_info->append("Action queue:");
    ui->textEdit_info->append("");
    for (int i = 0; i < f.getActionQueue().length(); i++)
    {
        int index = f.getTroops().indexOf(f.getActionQueue().at(i));
        ui->textEdit_info->insertPlainText(QString::number(index) + " ");
    }
}

void MainWindow::sleep(int msecs)
{
    qApp->processEvents();
    QThread::msleep(msecs);
}

void MainWindow::validateInput(const Field &f, QPoint &move, QPoint &attack)
{
    move.rx() = qMax(0, move.x());
    move.ry() = qMax(0, move.y());

    move.rx() = qMin(f.getSize().width() - 1, move.x());
    move.ry() = qMin(f.getSize().height() - 1, move.y());

    attack.rx() = qMax(0, attack.x());
    attack.ry() = qMax(0, attack.y());

    attack.rx() = qMin(f.getSize().width() - 1, attack.x());
    attack.ry() = qMin(f.getSize().height() - 1, attack.y());
}

void MainWindow::writeInput(const Field &f)
{
    QFile file("input.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

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

    file.close();
}

void MainWindow::readOutput(QPoint &move, QPoint &attack)
{
    QFile file("output.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    int x, y;
    in >> x >> y;
    move = QPoint(x, y);

    in >> x >> y;
    attack = QPoint(x, y);

    file.close();
}

QRect MainWindow::pointToFrameRect(QPoint p)
{
    return QRect(p.x() * cellSize.width(), p.y() * cellSize.height(), cellSize.width(), cellSize.height());
}
