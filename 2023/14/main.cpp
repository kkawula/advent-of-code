// Advent of Code 2023
// Day 14: Parabolic Reflector Dish
// https://adventofcode.com/2023/day/14

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

int fall(vector<string> rocks) {
    int len = rocks.size();
    int res = 0;
    for (int i = 0; i < rocks.size(); i++) {
        for(int j = 0; j < rocks[i].length(); j++) {
            int k = i - 1;
            int falls = 0;
            if (rocks[i][j] == 'O') {
                while (k >= 0) {
                    if (rocks[k][j] == '#') {
                        break;
                    }
                    else if (rocks[k][j] == '.') {
                        falls++;
                    }
                    k--;
                }
                res += len - i + falls;
            }
            
        }
    }
    
    return res;
}

void fall2(vector<string>& rocks) {
    int len = rocks.size();
    int res = 0;

    for (int i = 0; i < rocks.size(); i++) {
        for(int j = 0; j < rocks[i].length(); j++) {
            int k = i - 1;
            int falls = 0;
            if (rocks[i][j] == 'O') {
                while (k >= 0) {
                    if (rocks[k][j] == '#') {
                        break;
                    }
                    else if (rocks[k][j] == '.') {
                        falls++;
                    }
                    k--;
                }
                if (falls > 0) {
                    rocks[i][j] = '.';
                    rocks[i - falls][j] = 'O';
                }
            }
            
        }
    }

    for (int i = 0; i < rocks.size(); i++) {
        for(int j = 0; j < rocks[i].length(); j++) {
            int k = j - 1;
            int falls = 0;
            if (rocks[i][j] == 'O') {
                while (k >= 0) {
                    if (rocks[i][k] == '#') {
                        break;
                    }
                    else if (rocks[i][k] == '.') {
                        falls++;
                    }
                    k--;
                }
                if (falls > 0) {
                    rocks[i][j] = '.';
                    rocks[i][j - falls] = 'O';
                }
            }
            
        }
    }

    // south
    for (int i = 0; i < rocks.size(); i++) {
        for(int j = 0; j < rocks[i].length(); j++) {
            int k = i + 1;
            int falls = 0;
            int lastFree = -1;
            if (rocks[i][j] == 'O') {
                while (k < rocks.size()) {
                    if (rocks[k][j] == '#') {
                        break;
                    }
                    else if (rocks[k][j] == '.') {
                        falls++;
                        lastFree = k;
                    }
                    k++;
                }
                if (falls > 0) {
                    rocks[i][j] = '.';
                    rocks[lastFree][j] = 'O';
                }

            }
            
        }
    }

    for (int i = 0; i < rocks.size(); i++) {
        for(int j = 0; j < rocks[i].length(); j++) {
            int k = j + 1;
            int falls = 0;
            int lastFree = -1;
            if (rocks[i][j] == 'O') {
                while (k < rocks[i].length()) {
                    if (rocks[i][k] == '#') {
                        break;
                    }
                    else if (rocks[i][k] == '.') {
                        falls++;
                        lastFree = k;
                    }
                    k++;
                }
                if (falls > 0) {
                    rocks[i][j] = '.';
                    rocks[i][lastFree] = 'O';
                }
            }
            
        }
    }
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

    vector<string> rocks;
    
    while (getline(file, line)) {
        rocks.push_back(line);
    }   
    int i = 0; 
    while (i <= 1000000000) { // never ends :(
        res += fall(rocks);
        i++;
        if (i % 10000 == 0) {
            cout << i << endl;
        }

    }
    fall2(rocks);
    for (int i = 0; i < rocks.size(); i++) {
        for(int j = 0; j < rocks[i].length(); j++) {
            if (rocks[i][j] == 'O') {
                res2 += rocks.size() - i;
            }
        }
    }    

    cout << res << endl;
    cout << res2 << endl;
    return 0;
}