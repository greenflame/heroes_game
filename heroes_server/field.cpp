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

    waveMax = 1000;
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

Troop *Field::getTroop(QPoint position)
{
    for (int i = 0; i < troops.length(); i++)
    {
        if (troops[i].getPosition() == position)
        {
            return &troops[i];
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
    actionMove(move, log, motionPath);
    actionAttack(attack, log, attackSuccess, damage, died);
}

void Field::actionMove(QPoint move, QString &log, QList<QPoint> &motionPath)
{
    move = validatePoint(move, size);
    Troop &troop = *actionQueue.first();

    moveTroop(troop, move, log, motionPath);
}

void Field::actionAttack(QPoint attack, QString &log, bool &attackSuccess, int &damage, int &died)
{
    attack = validatePoint(attack, size);
    Troop &troop = *actionQueue.takeFirst();

    if (troopExists(attack))
    {
        troop.attack(*getTroop(attack), log, attackSuccess, damage, died);
    }
    else
    {
        attackSuccess = false;
        damage = 0;
        died = 0;
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
        if (args_s.length() == 1)
        {
            continue;
        }

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

    QList<QPoint> path;
    switch (troop.unit.movement_type)
    {
    case WALKING:
        path = searchWalkingPath(troop.position, destination, troop.unit.speed);
        break;
    case FLYING:
        path = searchFlyingPath(troop.position, destination, troop.unit.speed);
        break;
    }

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

QPoint Field::validatePoint(QPoint p, QSize s)
{
    QPoint res = p;

    res.rx() = qMax(0, res.x());
    res.ry() = qMax(0, res.y());

    res.rx() = qMin(s.width() - 1, res.x());
    res.ry() = qMin(s.height() - 1, res.y());

    return res;
}

void Field::doWave(QPoint waveCenter)
{
    // Clear maps
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            wave[i][j] = waveMax;
            obstacles[i][j] = 0;
            visited[i][j] = 0;
        }
    }

    // Fill obstacles
    for (int i = 0; i < troops.count(); i++)
    {
        obstacles[troops.at(i).position.x()][troops.at(i).position.y()] = 1;
    }
    obstacles[waveCenter.x()][waveCenter.y()] = 0;  // Exclude wave center

    // Wave
    QQueue<QPoint> queue;
    queue.enqueue(waveCenter);
    wave[waveCenter.x()][waveCenter.y()] = 0;

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

QList<QPoint> Field::searchWalkingPath(QPoint start, QPoint destination, int maxLength)
{
    // Adjust destination
    doWave(start);
    QPoint adjustedDestination = start;

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            QPoint curPoint(i, j);

            if (wave[i][j] != waveMax)  // Reachable
            {
                int oldDist = (adjustedDestination - destination).manhattanLength();
                int newDist = (curPoint - destination).manhattanLength();

                if (newDist < oldDist)  // Closest to aim
                {
                    adjustedDestination = curPoint;
                }

                if (newDist == oldDist && wave[curPoint.x()][curPoint.y()] <
                        wave[adjustedDestination.x()][adjustedDestination.y()]) // Closest to start
                {
                    adjustedDestination = curPoint;
                }
            }
        }
    }

    // Restore path
    doWave(adjustedDestination);
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

QList<QPoint> Field::searchFlyingPath(QPoint start, QPoint destination, int maxLength)
{
    doWave(start);
    QPoint end = start;

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            QPoint curCell(i, j);

            if (!obstacles[i][j] &&     // Reachable(obstacles)
                    (start - curCell).manhattanLength() <= maxLength &&    // Reachable(length)
                    (destination - curCell).manhattanLength() <
                    (destination - end).manhattanLength())
            {
                end = curCell;
            }
        }
    }

    QList<QPoint> result;
    result << start << end;
    return result;
}
