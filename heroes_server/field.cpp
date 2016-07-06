#include "field.h"

Field::Field()
{
    init();
}

Field::Field(QString fileName)
{
    init();
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

QList<Troop> Field::getActionQueue() const
{
    QList<Troop> result;

    if (actionQueue.length() < actionQueueLength)
    {
        return result;
    }

    for (int i = 0; i < actionQueueLength; i++)
    {
        result.append(*actionQueue[i]);
    }

    return result;
}

void Field::init()
{
    size = QSize(15, 10);
    actionQueueLength = 15;

    neibours << QPoint(1, 0);
    neibours << QPoint(0, 1);
    neibours << QPoint(-1, 0);
    neibours << QPoint(0, -1);
}

QList<Troop> Field::getTroops() const
{
    return troops;
}

void Field::updateActionQueue()
{
    // Fill to length
    while (actionQueue.length() < actionQueueLength)
    {
        QList<Troop*> pointers;

        for (int i = 0; i < troops.length(); i++)
        {
            pointers.push_back(&troops[i]);
        }

        for (int i = 0; i < troops.length(); i++)
        {
            actionQueue.push_back(pointers.takeAt(qrand() % pointers.length()));
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

Troop Field::getTroop(QPoint position) const
{
    for (int i = 0; i < troops.length(); i++)
    {
        if (troops[i].getPosition() == position)
        {
            return troops[i];
        }
    }

    throw "Position is empty";
}

bool Field::isGameEnd() const
{
    QSet<QString> players;

    for (int i = 0; i < troops.count(); i++) {
        players.insert(troops[i].getOwner());
    }

    return players.size() == 1;
}

void Field::action(QPoint move, QPoint attack, QString &log,
                   QList<QPoint> &motionPath, bool &attackSuccess, int &damage, int &died)
{
    Troop &troop = *actionQueue.takeFirst();

    moveTroop(troop, move, log, motionPath);

    if (troopExists(attack))
    {
        troop.attack(troops[troops.indexOf(getTroop(attack))], log, attackSuccess, damage, died);
    }
    else
    {
        log.append(QString("%1 attacks (%2, %3). Error: noody is here.\n")
                   .arg(troop.toStringShort())
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
            actionQueue.removeAll(&troops[i]);
            troops.removeAt(i);
            i--;
        }
    }
}

void Field::loadFromFile(QString fileName)
{
    QFile input(fileName);
    input.open(QIODevice::ReadOnly | QIODevice::Text);

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

void Field::moveTroop(Troop &troop, QPoint destination, QString &log, QList<QPoint> &motionPath)
{
    log.append(QString("%1 moves to (%2, %3). ")
               .arg(troop.toStringFull())
               .arg(destination.x())
               .arg(destination.y()));

    // Adjust to map size
    destination.rx() = qMax(0, destination.x());
    destination.ry() = qMax(0, destination.y());

    destination.rx() = qMin(size.width() - 1, destination.x());
    destination.ry() = qMin(size.height() - 1, destination.y());

    if (troop.position == destination)
    {
        log.append(" Already here.");
        motionPath = QList<QPoint>() << troop.position;
        return;
    }

    destination = findReachableDestination(destination);
    doWave(destination);
    QList<QPoint> path = restorePath(troop.position, troop.unit.speed);

    troop.position = path.last();

    motionPath = path;
    log.append(QString("Moved to (%1, %2).\n")
               .arg(troop.position.x())
               .arg(troop.position.y()));
}

bool Field::cellExists(QPoint cell)
{
    return QRect(QPoint(), size).contains(cell);
}

void Field::initWaveMaps()
{
    // Clear maps
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            wave[i][j] = 1000;
            obstacles[i][j] = 0;
            visited[i][j] = 0;
        }
    }

    // Fill obstacles
    for (int i = 0; i < troops.count(); i++)
    {
        obstacles[troops.at(i).position.x()][troops.at(i).position.y()] = 1;
    }
}

QPoint Field::findReachableDestination(QPoint destination)
{
    initWaveMaps();

    // Wave
    QQueue<QPoint> queue;
    queue.enqueue(destination);

    while (!queue.empty())
    {
        QPoint curCell = queue.dequeue();
        visited[curCell.x()][curCell.y()] = 1;

        if (!obstacles[curCell.x()][curCell.y()])
        {
            return curCell;
        }

        for (int i = 0; i < neibours.length(); i++)
        {
            QPoint curNeib = curCell + neibours.at(i);

            if (cellExists(curNeib) && !visited[curNeib.x()][curNeib.y()])  // Exists and not visited
            {
                queue.enqueue(curNeib); // Add to queue
            }
        }
    }

    return QPoint(0, 0);
}

void Field::doWave(QPoint destination)
{
    initWaveMaps();

    // Wave
    QQueue<QPoint> queue;
    queue.enqueue(destination);
    wave[destination.x()][destination.y()] = 0;

    while (!queue.empty())
    {
        QPoint curCell = queue.dequeue();
        visited[curCell.x()][curCell.y()] = 1;

        for (int i = 0; i < neibours.length(); i++)
        {
            QPoint curNeib = curCell + neibours.at(i);

            if (cellExists(curNeib) && !obstacles[curNeib.x()][curNeib.y()])   // Exists and not obstacle
            {
                // Solve cur cell
                int curVal = wave[curCell.x()][curCell.y()];
                int neibVal = wave[curNeib.x()][curNeib.y()];

                wave[curCell.x()][curCell.y()] = qMin(curVal, neibVal+ 1);

                // Add to queue
                if (!visited[curNeib.x()][curNeib.y()])
                {
                    queue.enqueue(curNeib);
                }
            }
        }
    }
}

QList<QPoint> Field::restorePath(QPoint start, int maxLength)
{
    QList<QPoint> path;
    path.append(start);
    int lengthLeft = maxLength;

    while (lengthLeft > 0)
    {
        lengthLeft--;

        QPoint curCell = path.last();
        QPoint minNeib = curCell;

        for (int i = 0; i < neibours.length(); i++)
        {
            QPoint curNeib = curCell + neibours.at(i);

            if (cellExists(curNeib) && wave[curNeib.x()][curNeib.y()] < wave[minNeib.x()][minNeib.y()]) // Exists and less then min
            {
                minNeib = curNeib;
            }
        }

        if (minNeib != curCell)
        {
            path.append(minNeib);
        }
    }

    return path;
}
