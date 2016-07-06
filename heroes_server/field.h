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

    bool troopExists(QPoint position) const;
    Troop getTroop(QPoint position) const;

    void action(QPoint move, QPoint attack, QString &log, QList<QPoint> &motionPath, bool &attackSuccess, int &damage, int &died);
    bool isGameEnd() const;

    QSize getSize() const;
    QList<Troop> getTroops() const;
    QList<Troop> getActionQueue() const;    // For externall use

private:
    void init();

    void regenerateActionQueue();
    void updateActionQueue();

    void checkForDeath();
    void loadFromFile(QString fileName);

    void moveTroop(Troop &troop, QPoint destination, QString &log, QList<QPoint> &motionPath);
    bool cellExists(QPoint cell);

    void initWaveMaps();
    QPoint findReachableDestination(QPoint destination);
    void doWave(QPoint destination);
    QList<QPoint> restorePath(QPoint start, int maxLength);

    QSize size;
    QList<Troop> troops;
    QList<Troop*> actionQueue;
    int actionQueueLength;

    // Maps for wave algo
    int wave[15][10];
    int obstacles[15][10];
    int visited[15][10];
    QList<QPoint> neibours;
};

#endif // FIELD_H
