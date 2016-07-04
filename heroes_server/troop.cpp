#include "troop.h"


Troop::Troop(QString owner, QPoint position, Unit unit, int count) {
    this->id = nextId();

    this->owner = owner;
    this->position = position;
    this->unit = unit;
    this->count = count;

    this->health = count * unit.health;
}

QString Troop::toString() const {
    QString result("[id: %1, owner: %2, position: (%3, %4), unit: %5, count: %6, health: %7]");
    result = result.arg(id).arg(owner).arg(position.x()).arg(position.y());
    result = result.arg(unit.name).arg(count).arg(health);
    return result;
}

void Troop::attack(Troop &aim) {
    float baseDamage = unit.damage_from + randomFloat() * (unit.damage_to - unit.damage_from);

    float attackDefenseModifier = 1;
    if (unit.attack > aim.unit.defence) {
        attackDefenseModifier = 1 + (unit.attack - aim.unit.defence) * 0.05;
    } else {
        attackDefenseModifier = 1 / (1 + (aim.unit.defence - unit.attack) * 0.05);
    }

    int totalDamage = qRound(baseDamage * count * attackDefenseModifier);
    totalDamage = qMax(1, totalDamage);
    totalDamage = qMin(32000, totalDamage);

    aim.health = qMax(0, aim.health - totalDamage);
    aim.count = (aim.health + aim.unit.health - 1) / aim.unit.health;
}

float Troop::randomFloat() {
    qsrand(QTime::currentTime().msec());
    return (float)(qrand() % 1000) / 1000.0;
}

int Troop::nextId()
{
    static int nextId = 0;
    return nextId++;
}

int Troop::getHealth() const
{
    return health;
}

int Troop::getCount() const
{
    return count;
}

Unit Troop::getUnit() const
{
    return unit;
}

QPoint Troop::getPosition() const
{
    return position;
}

QString Troop::getOwner() const
{
    return owner;
}

int Troop::getId() const
{
    return id;
}
