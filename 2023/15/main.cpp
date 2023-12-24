// Advent of Code 2023
// Day 15: Lens Library
// https://adventofcode.com/2023/day/15

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <unordered_map>

using namespace std;

#define DEBUG false
using ll = long long;

ll getHash(string s) {
    ll res = 0;
    for (int i = 0; i < s.size(); i++) {
        res += static_cast<ll>(s[i]);
        res *= 17;
        res %= 256;
    }
    return res;
}

void hashmap(vector<vector<string>>& boxes, unordered_map<string, int>& lens, string s) {
    if (s.find("-") != string::npos) {
        string label = s.substr(0, s.find("-"));
        int index = getHash(label);
        if (find(boxes[index].begin(), boxes[index].end(), label) != boxes[index].end()) {
            boxes[index].erase(find(boxes[index].begin(), boxes[index].end(), label));
        }
        
    }
    else {
        istringstream iss(s);
        string label, focal;
        getline(iss, label, '=');
        getline(iss, focal);
        int index = getHash(label);
        if (find(boxes[index].begin(), boxes[index].end(), label) == boxes[index].end()) {
            boxes[index].push_back(label);
            lens[label] = stoi(focal);
        }
        else {
            lens[label] = stoi(focal);
        }
    }
}

int main() {
    ifstream file(DEBUG? "example.txt" : "input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    ll res = 0;
    ll res2 = 0;

    vector<vector<string>> boxes(256, vector<string>());
    unordered_map<string, int> lens;
    
    while (getline(file, line, ',')) {
        res += getHash(line); // part 1 
        hashmap(boxes, lens, line); // part 2
    }

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < boxes[i].size(); j++) {
            res2 += (i + 1) * (j + 1) * lens[boxes[i][j]];
        }
    }

    cout << res << endl;
    cout << res2 << endl;
    return 0;
}