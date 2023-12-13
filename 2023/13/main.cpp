// Advent of Code 2023
// Day 13: Point of Incidence
// https://adventofcode.com/2023/day/13

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;

#define DEBUG false 
using ll = long long;

bool check(vector<string> mirror, int i, int j) {
    while (i >= 0 && j < mirror.size()) {
        if (mirror[i] != mirror[j]) {
            return false;
        }
        i--;
        j++;
    }
    return true;
}


ll reflection(vector<string> mirror) {
    ll res = 0;

    for (int i = 0; i < mirror.size() - 1; i++) {
        if (mirror[i] == mirror[i + 1]) {
            if (check(mirror, i, i + 1)) {
                res += i + 1;
            }
        }
    }

    return res;
}

bool oneDiff(string s1, string s2) {
    int diff = 0;
    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] != s2[i]) {
            diff++;
        }
    }
    return diff == 1;
}

bool check2(vector<string> mirror, int i, int j, bool diffAllowed) {
    bool wasDiff = false;
    if (!diffAllowed) {
        wasDiff = true;
    }
    
    while (i >= 0 && j < mirror.size()) {
        if (mirror[i] != mirror[j]) {
            if (diffAllowed && oneDiff(mirror[i], mirror[j])) {
                diffAllowed = false;
                wasDiff = true;
            }
            else {
                return false;
            }
        }
        i--;
        j++;
    }
    return wasDiff;
}

ll reflection2(vector<string> mirror) {
    ll res = 0;

    for (int i = 0; i < mirror.size() - 1; i++) {
        if (mirror[i] == mirror[i + 1]) {
            if (check2(mirror, i, i + 1, true)) {
                res += i + 1;
            }
        }
        else if (oneDiff(mirror[i], mirror[i + 1])) {
            if (check2(mirror, i - 1, i + 2, false)) { // we skip first diff, because it breaks check func
                res += i + 1;
            }
        }
    }

    return res;
}

vector<string> parseToCols(vector<string> rows) {
    vector<string> cols(rows[0].length(), "");
    for (int i = 0; i < rows[0].length(); i++) {  
        for (int j = 0; j < rows.size(); j++) {
            cols[i] += rows[j][i];
        }
    }
    
    return cols;
}

int main() {
    ifstream file(DEBUG? "example.txt" : "input.txt");;
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    ll res = 0;
    ll res2 = 0;

    vector<string> mirror;
    
    while (getline(file, line)) {
        if (!line.empty()) { // input has to contain to empty lines at the end
            mirror.push_back(line);
        }
        else {
            res += 100 * reflection(mirror);
            res += reflection(parseToCols(mirror));

            res2 += 100 * reflection2(mirror);
            res2 += reflection2(parseToCols(mirror));
            
            mirror.clear();
        }
    }


    cout << res << endl;
    cout << res2 << endl;
    return 0;
}