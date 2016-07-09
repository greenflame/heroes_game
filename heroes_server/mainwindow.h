#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QString>
#include <QDebug>
#include <QTime>
#include <QSet>
#include <QThread>
#include <QProcess>
#include <QFile>
#include <QDir>

#include "unit.h"
#include "troop.h"
#include "field.h"
#include "session.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    // View
    void on_actionStart_triggered();
    void on_actionStop_triggered();
    void on_actionPlay_fast_10_games_triggered();

    QString programm1();
    QString programm2();

    void sleep(int msecs);

private:
    Ui::MainWindow *ui;

    QString path;
    bool stop;
};

#endif // MAINWINDOW_H
