#ifndef TROOP_H
#define TROOP_H

#include <QString>
#include <QPoint>
#include <QTime>
#include <QtMath>
#include <QDebug>

#include "unit.h"

enum Player {
    FIRST_PALYER,
    SECOND_PLAYER
};

class Field;

class Troop
{
public:
    Troop(Player owner, QPoint position, Unit unit, int count);

    bool operator ==(const Troop &other) const;

    QString toStringFull() const;
    QString toStringShort() const;

    void attack(Troop &aim, QString &log, bool &attackSuccess, int &damage, int &died);

    Player getOwner() const;
    QPoint getPosition() const;
    Unit getUnit() const;
    int getCount() const;
    int getHealth() const;

    friend class Field;

private:
    static float randomFloat();
    static float distance(const QPoint &p1, const QPoint &p2);

    Player owner;
    QPoint position;
    Unit unit;
    int count;
    int health;
};

#endif // TROOP_H
