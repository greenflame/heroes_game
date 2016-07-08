#ifndef FIELD_H
#define FIELD_H

#include <QSize>
#include <QList>
#include <QSet>
#include <QFile>
#include <QRect>
#include <QQueue>

#include "unit.h"
#include "troop.h"

class Field
{
public:
    Field();
    Field(QString fileName);

    void addTroop(Troop troop);

    void action(QPoint actionMove, QPoint actionAttack, QString &log, QList<QPoint> &motionPath, bool &attackSuccess, int &damage, int &died);
    void actionMove(QPoint destination, QString &log, QList<QPoint> &motionPath);
    void actionAttack(QPoint aim, QString &log, bool &attackSuccess, int &damage, int &died);

    bool isGameEnd() const;

    QSize getSize() const;
    QList<Troop> getTroops() const;
    QList<Troop> getActionQueue() const;    // For externall use

private:
    void init();

    bool troopExists(QPoint position) const;
    Troop *getTroop(QPoint position);

    void regenerateActionQueue();
    void updateActionQueue();
    void checkForDeath();   // Troops + queue

    void loadFromFile(QString fileName);
    bool cellExists(QPoint cell);
    static QPoint validatePoint(QPoint p, QSize s);

    QSize size;
    QList<Troop> troops;
    QList<Troop*> actionQueue;
    int actionQueueLength;

    // Wave algorithm + path search
    QList<QPoint> searchWalkingPath(QPoint start, QPoint destination, int maxLength);
    QList<QPoint> searchFlyingPath(QPoint start, QPoint destination, int maxLength);

    void doWave(QPoint waveCenter);

    int wave[15][10];
    int obstacles[15][10];
    int visited[15][10];
    int waveMax;
    QList<QPoint> neibours;
};

#endif // FIELD_H
