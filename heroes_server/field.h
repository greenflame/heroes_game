#ifndef FIELD_H
#define FIELD_H

#include <QSize>
#include <QList>
#include <QSet>
#include <QFile>
#include <QRect>

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

    void action(QPoint move, QPoint attack, QString &log);
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

    bool moveTroop(Troop &troop, QPoint destination, QString &log);

    QSize size;
    QList<Troop> troops;
    QList<Troop*> actionQueue;
    int actionQueueLength;
};

#endif // FIELD_H
