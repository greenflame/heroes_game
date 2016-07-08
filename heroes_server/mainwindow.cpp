#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    path = "/Users/Alexander/Desktop/heroes_game/data_folder/";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionStart_triggered()
{
    stop = false;

    Session s(path + "field.txt",
              ui->lineEdit_programm_1->text(),
              ui->lineEdit_programm_2->text(),
              path + "pictures/",
              this);

    while(!s.isEnd())
    {
        ui->label->setPixmap(QPixmap::fromImage(s.nextFrame()));
        ui->textEdit_log->setText(s.getLog());
        ui->textEdit_info->setText(s.troopsInfo());
        sleep(50);
        sleep(50);
        sleep(50);
        sleep(50);
        sleep(50);
        sleep(50);
        if (stop) { break; }
    }
}

void MainWindow::on_actionStop_triggered()
{
    stop = true;
}

void MainWindow::on_actionPlay_fast_10_games_triggered()
{
    ui->textEdit_log->clear();
    QMap<Player, int> results;
    stop = false;

    for (int i = 0; i < 10; i++)
    {
        Session s(path + "field.txt",
                  ui->lineEdit_programm_1->text(),
                  ui->lineEdit_programm_2->text(),
                  path + "pictures/",
                  this);

        while(!s.isEnd())
        {
            ui->label->setPixmap(QPixmap::fromImage(s.nextFrame()));
            ui->textEdit_info->setText(s.troopsInfo());
            sleep(50);
            if (stop) { break; }
        }

        results[s.winner()]++;

        QString winner = (s.winner() == FIRST_PALYER ? "First" : "Second");
        ui->textEdit_log->append(QString("Round %1. %2 player win.")
                                 .arg(i + 1)
                                 .arg(winner));

        if (stop) { break; }
    }

    ui->textEdit_log->append(QString("First: %1, second: %2.")
                              .arg(results[FIRST_PALYER])
                              .arg(results[SECOND_PLAYER]));
}

void MainWindow::sleep(int msecs)
{
    qApp->processEvents();
    QThread::msleep(msecs);
}
