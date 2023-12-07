// Advent of Code 2023
// Day 7: Camel Cards
// https://adventofcode.com/2023/day/7

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define DEBUG false 
using ll = long long;

map<char, int> CARDS = {
    {'T', 10},
    {'J', 11},
    {'Q', 12},
    {'K', 13},
    {'A', 14}
};

ll diff(string a) {
    ll res = 1;
    for (int i = 1; i < a.size(); ++i) {
        if (a[i] != a[i - 1]) {
            ++res;
        }
    }
    return res;
}

bool firstCard(string a, string b) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            int a_val = isdigit(a[i]) ? a[i] - '0' : CARDS[a[i]];
            int b_val = isdigit(b[i]) ? b[i] - '0' : CARDS[b[i]];
            return a_val < b_val;
        }
    }
    return false;
}

bool compare(pair<string, ll> a, pair<string, ll> b) {
    string aCp = a.first;
    string bCp = b.first;
    sort(aCp.begin(), aCp.end());
    sort(bCp.begin(), bCp.end());

    int aDiff = diff(aCp);
    int bDiff = diff(bCp);
    if (aDiff != bDiff) {
        return aDiff > bDiff;
    }
    if (aDiff == 1 || aDiff == 5 || aDiff == 4) {
        return firstCard(a.first, b.first);
    }
    if (aDiff == 2) {
        bool isFourA = aCp[2] == aCp[1] && aCp[2] == aCp[3];
        bool isFourB = bCp[2] == bCp[1] && bCp[2] == bCp[3];
        if ((isFourA && isFourB) || (!isFourA && !isFourB)) {
            return firstCard(a.first, b.first);
        }
        if (isFourA) {
            return false;
        }
        if (isFourB) {
            return true;
        }
    }
    if (aDiff == 3) {
        bool isThreeA = (aCp[0] == aCp[1] && aCp[1] == aCp[2]) || 
                        (aCp[1] == aCp[2] && aCp[2] == aCp[3]) ||
                        (aCp[2] == aCp[3] && aCp[3] == aCp[4]);
        bool isThreeB = (bCp[0] == bCp[1] && bCp[1] == bCp[2]) || 
                        (bCp[1] == bCp[2] && bCp[2] == bCp[3]) ||
                        (bCp[2] == bCp[3] && bCp[3] == bCp[4]);
        if ((isThreeA && isThreeB) || (!isThreeA && !isThreeB)) {
            return firstCard(a.first, b.first);
        }
        if (isThreeA) {
            return false;
        }
        if (isThreeB) {
            return true;
        }   

    }



    return a.second > b.second;
}

int main() {
    ifstream file(DEBUG? "example.txt" : "input.txt");;
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line, hand;
    ll bid, res = 0;
    vector<pair<string, ll>> rank;

    while (getline(file, line)) {
        istringstream iss(line);
        iss >> hand >> bid;
        rank.push_back(make_pair(hand, bid));
    }

    sort(rank.begin(), rank.end(), compare);
    for (int i = 0; i < rank.size(); ++i) {
        res += rank[i].second * (i + 1);
    }

    cout << res << endl;

    return 0;
}