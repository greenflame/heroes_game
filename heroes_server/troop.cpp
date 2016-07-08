#include "troop.h"


Troop::Troop(Player owner, QPoint position, Unit unit, int count)
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

QString Troop::toStringFull() const
{
    return QString("%1 (%2, %3) [%4] {%5/%6}")
            .arg(unit.name)
            .arg(position.x())
            .arg(position.y())
            .arg(owner)
            .arg(count)
            .arg(health);
}

QString Troop::toStringShort() const
{
    return QString("%1 (%2, %3)")
            .arg(unit.name)
            .arg(position.x())
            .arg(position.y());
}

void Troop::attack(Troop &aim, QString &log, bool &attackSuccess, int &damage, int &died)
{
    log.append(QString("%1 attacks %2. ")
               .arg(toStringShort())
               .arg(aim.toStringShort()));

    attackSuccess = false;
    damage = 0;
    died = 0;

    // Error handling
    if (distance(position, aim.position) > 1.5 && unit.attack_type == MELEE)
    {
        log.append(QString("Error: unreachable unit.\n"));
        return;
    }

    if (aim.owner == owner)
    {
        log.append(QString("Error: friend unit.\n"));
        return;
    }

    // Game mechanics
    float baseDamage = unit.damage_from + randomFloat() * (unit.damage_to - unit.damage_from);

    float attackDefenseModifier = 1;
    if (unit.attack > aim.unit.defence)
    {
        attackDefenseModifier = 1 + (unit.attack - aim.unit.defence) * 0.05;
    } else
    {
        attackDefenseModifier = 1 / (1 + (aim.unit.defence - unit.attack) * 0.05);
    }

    float rangedModifier = 1;
    if (unit.attack_type == DISTANT)
    {
        if (distance(position, aim.position) < 1.5 || distance(position, aim.position) > 6)
        {
            rangedModifier = 0.5;
        }
    }

    int totalDamage = qRound(baseDamage * count * attackDefenseModifier * rangedModifier);
    totalDamage = qMax(1, totalDamage);
    totalDamage = qMin(32000, totalDamage);

    int prevHealth = aim.health;
    int prevCount = aim.count;

    aim.health = qMax(0, aim.health - totalDamage);
    aim.count = (aim.health + aim.unit.health - 1) / aim.unit.health;

    attackSuccess = true;
    damage = prevHealth - aim.health;
    died = prevCount - aim.count;
    log.append(QString("Damage: %3, died: %4.\n")
               .arg(damage)
               .arg(died));
}

float Troop::randomFloat()
{
    qsrand(QTime::currentTime().msec());
    return (float)(qrand() % 1000) / 1000.0;
}

float Troop::distance(const QPoint &p1, const QPoint &p2)
{
    return qSqrt((p2.x() - p1.x()) * (p2.x() - p1.x()) +
                 (p2.y() - p1.y()) * (p2.y() - p1.y()));
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

Player Troop::getOwner() const
{
    return owner;
}
