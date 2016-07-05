#include "troop.h"


Troop::Troop(QString owner, QPoint position, Unit unit, int count)
{
    this->owner = owner;
    this->position = position;
    this->unit = unit;
    this->count = count;

    this->health = count * unit.health;
}

bool Troop::operator ==(const Troop &other) const
{
    return owner == other.owner &&
            position == other.position &&
            unit == other.unit &&
            count == other.count &&
            health == other.health;
}

QString Troop::toString() const
{
    return QString("Owner: %2, position: (%3, %4), unit: %5, count: %6, health: %7.")
            .arg(owner)
            .arg(position.x())
            .arg(position.y())
            .arg(unit.name)
            .arg(count)
            .arg(health);
}

void Troop::attack(Troop &aim, QString &log)
{
    if ((position - aim.position).manhattanLength() > 1)
    {
        log.append(QString("%1 attack error (%2, %3). Unit is unreachable.\n")
                   .arg(unit.name)
                   .arg(aim.position.x())
                   .arg(aim.position.y()));

        return;
    }

    if (aim.owner == owner)
    {
        log.append(QString("%1 attack error (%2, %3). Unit is friend.\n")
                   .arg(unit.name)
                   .arg(aim.position.x())
                   .arg(aim.position.y()));

        return;
    }

    float baseDamage = unit.damage_from + randomFloat() * (unit.damage_to - unit.damage_from);

    float attackDefenseModifier = 1;
    if (unit.attack > aim.unit.defence)
    {
        attackDefenseModifier = 1 + (unit.attack - aim.unit.defence) * 0.05;
    } else
    {
        attackDefenseModifier = 1 / (1 + (aim.unit.defence - unit.attack) * 0.05);
    }

    int totalDamage = qRound(baseDamage * count * attackDefenseModifier);
    totalDamage = qMax(1, totalDamage);
    totalDamage = qMin(32000, totalDamage);

    int prevHealth = aim.health;
    int prevCount = aim.count;

    aim.health = qMax(0, aim.health - totalDamage);
    aim.count = (aim.health + aim.unit.health - 1) / aim.unit.health;

    log.append(QString("%1 attacks %2, damage: %3, died: %4.\n")
               .arg(unit.name)
               .arg(aim.unit.name)
               .arg(prevHealth - aim.health)
               .arg(prevCount - aim.count));
}

float Troop::randomFloat()
{
    qsrand(QTime::currentTime().msec());
    return (float)(qrand() % 1000) / 1000.0;
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
