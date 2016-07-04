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
    int ind = getTroopIndex(actionQueue.takeFirst());

    moveTroop(ind, move, log);
    if (troopExists(attack))
    {
        troops[ind].attack(troops[getTroopIndex(attack)]);
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

bool Field::moveTroop(int id, QPoint destination, QString &log)
{
    int ind = getTroopIndex(id);

    troops[ind].position = destination;
    log.append(QString("%1 moved to (%2, %3)\n")
               .arg(troops[ind].getUnit().name)
               .arg(destination.x())
               .arg(destination.y()));

    return true;
}
