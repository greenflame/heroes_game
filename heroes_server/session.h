#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <QPainter>
#include <QString>
#include <QTextStream>
#include <QProcess>

#include <field.h>

class Session
{
public:
    Session(QString fieldFile, QString firstProgramm, QString secondProgramm, QString picturesPath, QObject *parent);
    QImage nextFrame();
    bool isEnd();
    Player winner();

    QSize getCellSize() const;
    void setCellSize(const QSize &value);

    QString getLog() const;
    QString troopsInfo() const;

private:
    QImage renderField();
    QRect posToFrameRect(QPoint pos);

    QString executeProgramm(QString programmName, QString input, int timeOut);
    QString generateInput();

    // Field input
    QPoint move;
    QPoint attack;

    // Field output
    QString log;
    QList<QPoint> motionPath;
    bool attackSuccess;
    int damage;
    int died;

    // Temporary data
    int motionPathStep;

    //
    QString firstProgram;
    QString secondProgramm;
    QString picturesPath;

    Field f;
    QSize cellSize;

    QObject *parent;
};

#endif // SESSION_H
