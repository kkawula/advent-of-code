// Advent of Code 2023
// Day 11: Cosmic Expansion
// https://adventofcode.com/2023/day/11

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

bool containGalaxyRow(string s) {
    return s.find('#') != string::npos;
}

bool containGalaxyCol(vector<string> universe, int col) {
    bool contain = false;
    for (int i = 0; i < universe.size(); i++) {
        if (universe[i][col] == '#') {
            contain = true;
            break;
        }
    }
    return contain;
}

vector<pair<ll, ll>> expand(vector<pair<ll, ll>> galaxies, vector<ll> rowsToExpand, vector<ll> colsToExpand, int rep) {
    vector<pair<ll, ll>> newGalaxies = galaxies;
    for (int row : rowsToExpand) {
        for (int i = 0; i < galaxies.size(); i++) {
            if (galaxies[i].first > row) {
                newGalaxies[i].first += rep;
            }
        }
    }

    for (int col : colsToExpand) {
        for (int i = 0; i < galaxies.size(); i++) {
            if (galaxies[i].second > col) {
                newGalaxies[i].second += rep;
            }
        }
    }
    return newGalaxies;
}

ll calculateDistance(vector<pair<ll, ll>> galaxies) {
    ll res = 0;
    for (int i = 0; i < galaxies.size(); i++) {
        // cout << "(" << galaxies[i].first << ", " << galaxies[i].second << ")" << endl;
    }
    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i; j < galaxies.size(); j++) {
            // cout << "(" << galaxies[i].first << ", " << galaxies[i].second << ") (" << galaxies[j].first << ", " << galaxies[j].second <<")"<< endl;
            // cout<< abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second)<<endl;;
            res += abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second);
        }
    }
    return res;
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
    vector <string> universe; 
    
    while (getline(file, line)) {
        universe.push_back(line);
    }

    vector<pair<ll, ll>> galaxies; 

    for (int i = 0; i < universe.size(); i++) {
        for (int j = 0; j < universe[0].size(); j++) {
            if (universe[i][j] == '#') {
                galaxies.push_back(make_pair(i, j));
            }
        }
    }

    vector<ll> rowsToExpand, colsToExpand;
    for (int i = 0; i < universe.size(); i++) {
        if (!containGalaxyRow(universe[i])) {
            rowsToExpand.push_back(i);
        }
        if (!containGalaxyCol(universe, i)) {
            colsToExpand.push_back(i);
        }
    }
    vector<pair<ll, ll>> galaxies1 = expand(galaxies, rowsToExpand, colsToExpand, 1);
    vector<pair<ll, ll>> galaxies2 = expand(galaxies, rowsToExpand, colsToExpand, 999999);

    res = calculateDistance(galaxies1);
    res2 = calculateDistance(galaxies2);
    cout << res << endl;
    cout << res2 << endl;
    return 0;
}