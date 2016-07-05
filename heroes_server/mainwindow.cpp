#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    path = "/Users/Alexander/Desktop/heroes_game/data_folder/";
    cellSize = QSize(50, 50);
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
        // Write input
        QFile::remove(path + "input.txt");
        QFile::remove(path + "output.txt");
        QFile::copy("input.txt", path + "input.txt");
        QFile::copy("output.txt", path + "output.txt");
        QFile::remove("input.txt");
        QFile::remove("output.txt");

        writeInput(f);

        // Start programm
        QString programmName = path + f.getActionQueue().first().getOwner();

        QProcess p(this);
//        if (programmName.indexOf("anton") != -1)
//        {
//            p.start("/usr/local/Cellar/mono/4.2.3.4/bin/mono", QStringList() << programmName);
//        }
//        else
        {
            p.start(programmName);
        }
        p.waitForFinished(2000);

        // Read output
        readOutput(f);

        // Render state
        updateUi(f);

        // Sleep
        QThread::msleep(1000);
        qApp->processEvents();

        // Interrupt
        if (stop)
        {
            break;
        }
    }
}

void MainWindow::on_actionStop_triggered()
{
    stop = true;
}

void MainWindow::renderField(const Field &f)
{
    QImage img(f.getSize().width() * cellSize.width(),
             f.getSize().height() * cellSize.height(),
             QImage::Format_ARGB32);

    QPainter p;
    p.begin(&img);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.fillRect(img.rect(), Qt::white);

    for (int i = 0; i < f.getSize().width(); i++)
    {
        for (int j = 0; j < f.getSize().height(); j++)
        {
            QRect curCell(i * cellSize.width(), j * cellSize.height(), cellSize.width(), cellSize.height());

            // Border
            p.setPen(Qt::gray);
            p.drawRect(curCell);

            if (f.troopExists(QPoint(i, j)))
            {
                Troop curTroop = f.getTroop(QPoint(i, j));

                // Miniature
                QImage img(path + "pictures/" + curTroop.getUnit().picture);
                QImage imgScaled = img.scaled(cellSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                p.drawImage(curCell, imgScaled, imgScaled.rect());

                // Text
                p.setPen(Qt::white);

                if (curTroop.getOwner() == "alex")
                {
                        p.setPen(Qt::red);
                }
                if (curTroop.getOwner() == "anton")
                {
                        p.setPen(Qt::blue);
                }

                p.setFont(QFont("Arial", 30));
                p.drawText(curCell.bottomLeft(), QString::number(curTroop.getCount()));
            }
        }
    }

    p.end();

    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::updateTroopsInfo(const Field &f)
{
    ui->textEdit_info->clear();

    ui->textEdit_info->append("Troops:");
    for (int i = 0; i < f.getTroops().length(); i++)
    {
        ui->textEdit_info->append(f.getTroops().at(i).toString());
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

void MainWindow::readOutput(Field &f)
{
    QFile file("output.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    int x, y;
    in >> x >> y;
    QPoint move(x, y);

    in >> x >> y;
    QPoint attack(x, y);

    QString log;
    f.action(move, attack, log);
    ui->textEdit_log->insertPlainText(log);

    file.close();
}

void MainWindow::updateUi(const Field &f)
{
    renderField(f);
    updateTroopsInfo(f);
}
