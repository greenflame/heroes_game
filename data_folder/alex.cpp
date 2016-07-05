#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <cstdio>

using namespace std;

class Troop {
public:
    Troop() {}
    Troop(int id, string owner, int x, int y, string type, int count, int health) {
        this->id = id;
        this->owner = owner;
        this->x = x;
        this->y = y;
        this->type = type;
        this->count = count;
        this->health = health;
    }

    int id;
    string owner;
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
        cin >> troop.id >> troop.owner >> troop.x >> troop.y >> troop.type >> troop.count >> troop.health;
        troops.push_back(troop);
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
    string myName = "";
    Troop curTroop;

    for (int i = 0; i < troops.size(); i++) {
        if (troops[i].id == actionQueue[0]) {
            myName = troops[i].owner;
            curTroop = troops[i];
            break;
        }
    }

    // Find ain
    Troop aim;
    aim.x = -1000;
    aim.y = -1000;
    for (int i = 0; i < troops.size(); i++) {
        if (troops[i].owner != myName) {
            Troop curAim = troops[i];
            if (manhettanLength(curTroop, curAim) < manhettanLength(curTroop, aim)) {
                aim = curAim;
            }
        }
    }

    int dx = 0;
    int dy = 0;
    if (aim.x - curTroop.x != 0) {
        dx = (aim.x - curTroop.x) / abs(aim.x - curTroop.x);
    }
    if (aim.y - curTroop.y != 0) {
        dy = (aim.y - curTroop.y) / abs(aim.y - curTroop.y);
    }

    cout << curTroop.x + dx << " " << curTroop.y + dy << " " << aim.x << " " << aim.y << endl;
}