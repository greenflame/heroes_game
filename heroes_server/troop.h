#ifndef TROOP_H
#define TROOP_H

#include <QString>
#include <QPoint>
#include <QTime>

#include "unit.h"

enum AttackVerdict {

};

class AttackResult {
public:
    AttackVerdict verdict;
    int damage;
    int died;
};

class Field;

class Troop
{
public:
    Troop(QString owner, QPoint position, Unit unit, int count);

    QString toString() const;

    void attack(Troop &aim, QString &log);

    int getId() const;
    QString getOwner() const;
    QPoint getPosition() const;
    Unit getUnit() const;
    int getCount() const;
    int getHealth() const;

    friend class Field;

private:
    static float randomFloat();
    static int nextId();

    int id;
    QString owner;

    QPoint position;
    Unit unit;
    int count;
    int health;
};

#endif // TROOP_H
