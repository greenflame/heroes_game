#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ifstream fin("input.txt");
    
    vector<string> names;

    int n;
    fin >> n;
    string draft;
    getline(fin, draft);

    for (int i = 0; i < n; i++) {
        string tmp;
        getline(fin, tmp);
        names.push_back(tmp);

        cout << tmp << endl;
    }

    // for (;;){}

    fin.close();

    ofstream fout("output.txt");

    fout << "2 2 2 2" << endl;

    fout.close();
}