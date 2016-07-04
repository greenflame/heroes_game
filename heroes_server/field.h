#ifndef FIELD_H
#define FIELD_H

#include <QSize>
#include <QList>
#include <QSet>
#include <QFile>

#include "unit.h"
#include "troop.h"

class Field
{
public:
    Field();
    Field(QString fileName);

    void addTroop(Troop troop);

    bool troopExists(QPoint position) const;
    int getTroopIndex(QPoint position) const;
    bool troopExists(int id) const;
    int getTroopIndex(int id) const;

    void action(QPoint move, QPoint attack, QString &log);
    bool isGameEnd() const;

    QSize getSize() const;
    QList<Troop> getTroops() const;
    QList<int> getActionQueue() const;

private:
    void regenerateActionQueue();
    void updateActionQueue();

    void checkForDeath();
    void loadFromFile(QString fileName);

    bool moveTroop(int id, QPoint destination, QString &log);

    QSize size;
    QList<Troop> troops;
    QList<int> actionQueue;
    int actionQueueLength;
};

#endif // FIELD_H
