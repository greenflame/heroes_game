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

    void writeInput(const Field &f);
    void readOutput(Field &f);


    void updateUi(const Field &f);
    void updateTroopsInfo(const Field &f);
    void renderField(const Field &f);
private:
    Ui::MainWindow *ui;

    QString path;
    QSize cellSize;
};

#endif // MAINWINDOW_H
