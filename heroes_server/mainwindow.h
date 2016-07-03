#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QString>
#include <QDebug>


enum Movement {
    FLYING,
    WALKING
};

enum Attack {
    MELEE,
    DISTANT
};

class Unit {
public:
    Unit() {}

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

class Troop {
public:
    Troop(QString owner, QPoint position, Unit unit, int count) {
        static int nextId = 0;

        this->id = nextId++;
        this->owner = owner;
        this->position = position;
        this->unit = unit;
        this->count = count;
        this->health = count * unit.health;
    }

    QString toString() {
        return QString("[id: %1, owner: %2, position: (%3, %4), "
                       "unit: %5, count: %6, health: %7]")
                .arg(id).arg(owner).arg(position.x()).arg(position.y())
                .arg(unit.name).arg(count).arg(health);
    }

    int id;
    QString owner;

    QPoint position;
    Unit unit;
    int count;
    int health;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    // View
    void on_actionTest_triggered();
    void renderField(QSize cellSize);
    void printGameState();

    // Units
    void generateUnits();

    // Battlefield
    void generateActionQueue();
    bool troopExists(QPoint position);
    Troop getTroop(QPoint position);
    Troop getTrop(int id);

private:
    // View
    Ui::MainWindow *ui;

    // Units
    QMap<QString, Unit> units;

    // Battlefield
    QSize fieldSize;
    QList<Troop> troops;
    QList<int> actionQueue;
};

#endif // MAINWINDOW_H
