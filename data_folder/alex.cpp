#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <cstdio>

using namespace std;

class Troop {
public:
    Troop() {}
    Troop(int x, int y, string type, int count, int health) {
        this->x = x;
        this->y = y;
        this->type = type;
        this->count = count;
        this->health = health;
    }

    int x;
    int y;
    string type;
    int count;
    int health;
};

int manhettanLength(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int manhettanLength(Troop t1, Troop t2) {
    return manhettanLength(t1.x, t1.y, t2.x, t2.y);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    // Read troops
    vector<Troop> troops;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        Troop troop;
        cin >> troop.x >> troop.y >> troop.type >> troop.count >> troop.health;
        troops.push_back(troop);
    }

    // Read my troops
    vector<int> myTroops;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        myTroops.push_back(x);
    }

    // read enemy troops
    vector<int> enemyTroops;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        enemyTroops.push_back(x);
    }

    // Read acton queue
    vector<int> actionQueue;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        actionQueue.push_back(x);
    }

    // Find my name and current troop
    Troop curTroop = troops[actionQueue[0]];

    // Find ain
    Troop aim;
    aim.x = -1000;
    aim.y = -1000;
    for (int i = 0; i < enemyTroops.size(); i++) {
        Troop curAim = troops[enemyTroops[i]];
        if (manhettanLength(curTroop, curAim) < manhettanLength(curTroop, aim)) {
            aim = curAim;
        }
    }

    cout << aim.x << " " << aim.y << " " << aim.x << " " << aim.y << endl;
}