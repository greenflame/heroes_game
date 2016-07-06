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

    void executeProgramm(const Field &f, QPoint &move, QPoint &attack);
    void writeInput(const Field &f);
    void readOutput(QPoint &move, QPoint &attack);


    void renderMotion(const Field &f, const QList<QPoint> &motionPath);

    void renderField(const Field &f);
    void updateTroopsInfo(const Field &f);
private:
    Ui::MainWindow *ui;

    QString path;
    QSize cellSize;

    bool stop;
};

#endif // MAINWINDOW_H
