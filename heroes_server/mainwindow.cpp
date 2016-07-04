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
    Field f(path + "field.txt");

    while (!f.isGameEnd())
    {
        // Write input
        writeInput(f);

        // Start programm
        QString programmName = f.getTroops().at(f.getActionQueue().first()).getOwner();

        QProcess p(this);
        p.start(path + programmName);
        p.waitForStarted(1000);

        if (p.state() == QProcess::Running)
        {
            p.waitForFinished(2000);
        }

        // Read output
        readOutput(f);

        // Render state
        updateUi(f);

        // Sleep
        QThread::msleep(1000);
        qApp->processEvents();
    }
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
                Troop curTroop = f.getTroops().at(f.getTroopIndex(QPoint(i, j)));

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
        ui->textEdit_info->insertPlainText(QString::number(f.getActionQueue().at(i)) + " ");
    }
}

void MainWindow::writeInput(const Field &f)
{
    QFile file(path + "input.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    // Troops
    out << f.getTroops().length();
    endl(out);

    for (int i = 0; i < f.getTroops().length(); i++)
    {
        out << f.getTroops().at(i).toString();
        endl(out);
    }
    endl(out);

    // Action queue
    out << f.getActionQueue().length();
    endl(out);

    for (int i = 0; i < f.getActionQueue().length(); i++)
    {
        if (i)
        {
            out << " ";
        }
        out << f.getActionQueue().at(i);
    }
    endl(out);

    file.close();
}

void MainWindow::readOutput(Field &f)
{
    QFile file(path + "output.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    int x, y;
    in >> x >> y;
    QPoint move(x, y);

    in >> x >> y;
    QPoint attack(x, y);

    QString log;
    f.action(move, attack, log);

    file.close();
}

void MainWindow::updateUi(const Field &f)
{
    renderField(f);
    updateTroopsInfo(f);
}
