#ifndef UNIT_H
#define UNIT_H

#include <QString>
#include <QMap>

enum Movement {
    FLYING,
    WALKING
};

enum Attack {
    MELEE,
    DISTANT
};

class Unit
{
public:
    Unit();

    bool operator ==(const Unit &other) const;

    static QMap<QString, Unit> all();

    QString name;
    QString picture;
    QString faction;

    int level;
    char upgrade;

    int attack;
    int defence;

    int damage_from;
    int damage_to;
    Attack attack_type;

    int health;

    int speed;
    Movement movement_type;
    int size;

    int cost;
};

#endif // UNIT_H
