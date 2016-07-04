#include "field.h"

Field::Field()
{
    size = QSize(15, 10);
    actionQueueLength = 15;
}

Field::Field(QString fileName)
{
    size = QSize(15, 10);           // Copy!!!
    actionQueueLength = 15;

    loadFromFile(fileName);
}

void Field::addTroop(Troop troop)
{
    troops.append(troop);
    regenerateActionQueue();
}

void Field::regenerateActionQueue()
{
    actionQueue.clear();
    updateActionQueue();
}

QSize Field::getSize() const
{
    return size;
}

QList<int> Field::getActionQueue() const
{
    return actionQueue.mid(0, actionQueueLength);
}

QList<Troop> Field::getTroops() const
{
    return troops;
}

void Field::updateActionQueue()
{
    // Check for death
    for (int i = 0; i < actionQueue.length(); i++)
    {
        if (!troopExists(actionQueue[i]))
        {
            actionQueue.removeAt(i);
            i--;
        }
    }

    // Fill to length
    while (actionQueue.length() < actionQueueLength)
    {
        QList<int> ids;

        for (int i = 0; i < troops.length(); i++)
        {
            ids.push_back(troops[i].getId());
        }

        for (int i = 0; i < troops.length(); i++)
        {
            actionQueue.push_back(ids.takeAt(qrand() % ids.length()));
        }
    }
}

bool Field::troopExists(QPoint position) const
{
    for (int i = 0; i < troops.length(); i++)
    {
        if (troops[i].getPosition() == position)
        {
            return true;
        }
    }

    return false;
}

int Field::getTroopIndex(QPoint position) const
{
    for (int i = 0; i < troops.length(); i++)
    {
        if (troops[i].getPosition() == position)
        {
            return i;
        }
    }

    throw "Position is empty";
}

int Field::getTroopIndex(int id) const
{
    for (int i = 0; i < troops.length(); i++)
    {
        if (troops[i].getId() == id)
        {
            return i;
        }
    }

    throw "Invalid id";
}

bool Field::troopExists(int id) const
{
    for (int i = 0; i < troops.length(); i++)
    {
        if (troops[i].getId() == id)
        {
            return true;
        }
    }

    return false;
}

bool Field::isGameEnd() const
{
    QSet<QString> players;

    for (int i = 0; i < troops.count(); i++) {
        players.insert(troops[i].getOwner());
    }

    return players.size() == 1;
}

void Field::action(QPoint move, QPoint attack, QString &log)
{
    Troop &troop = troops[getTroopIndex(actionQueue.takeFirst())];

    moveTroop(troop, move, log);

    if (troopExists(attack))
    {
        troop.attack(troops[getTroopIndex(attack)], log);
    }
    else
    {
        log.append(QString("%1 attack error (%2, %3). Noody is here.\n")
                   .arg(troop.unit.name)
                   .arg(attack.x())
                   .arg(attack.y()));
    }

    checkForDeath();
    updateActionQueue();
}

void Field::checkForDeath()
{
    for (int i = 0; i < troops.length(); i++)
    {
        if (troops[i].getHealth() == 0)
        {
            troops.removeAt(i);
            i--;
        }
    }
}

void Field::loadFromFile(QString fileName)
{
    QFile input(fileName);
    input.open(QIODevice::ReadOnly | QIODevice::Text);

    QString sizeStr = input.readLine();
    size.setWidth(sizeStr.split(" ").at(0).toInt());
    size.setHeight(sizeStr.split(" ").at(1).toInt());

    while(!input.atEnd())
    {
        QString args_s = input.readLine();
        QStringList args = args_s.split(", ");

        QString owner = args[0];
        QPoint position(args[1].toInt(), args[2].toInt());
        Unit unit = Unit::all()[args[3]];
        int count = args[4].toInt();

        addTroop(Troop(owner, position, unit, count));
    }

    input.close();
}

bool Field::moveTroop(Troop &troop, QPoint destination, QString &log)
{
    if (troopExists(destination))
    {
        log.append(QString("Error moving %1 to (%2, %3). Position is already taken.\n")
                   .arg(troop.getUnit().name)
                   .arg(destination.x())
                   .arg(destination.y()));
        return false;
    }

    if (!QRect(QPoint(), size).contains(destination))
    {
        log.append(QString("Error moving %1 to (%2, %3). Position is out of map.\n")
                   .arg(troop.getUnit().name)
                   .arg(destination.x())
                   .arg(destination.y()));
        return false;
    }

    if ((troop.position - destination).manhattanLength() > troop.unit.speed)
    {
        log.append(QString("Error moving %1 to (%2, %3). Position is too far.\n")
                   .arg(troop.getUnit().name)
                   .arg(destination.x())
                   .arg(destination.y()));
        return false;
    }

    troop.position = destination;
    log.append(QString("%1 moved to (%2, %3)\n")
               .arg(troop.unit.name)
               .arg(destination.x())
               .arg(destination.y()));

    return true;
}
