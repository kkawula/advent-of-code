// Advent of Code 2023
// Day 3: Gear Ratios
// https://adventofcode.com/2023/day/3

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int find_end(const string& s, int i) {
    while (i < s.size() && isdigit(s[i])) {
        ++i;
    }
    return i;
}

bool is_symbol(const string& s, int i) {
    return s[i] != '.' && !isdigit(s[i]);
}

int count_parts(const string& prev, const string& act, const string& next) {
    int res = 0;
    for (int i = 0; i < act.size(); ++i) {
        if (isdigit(act[i])) {
            int end = find_end(act, i);
            for (int j = max(0, i - 1); j < min((int)act.size(), end + 1); ++j) {
                if (is_symbol(prev, j) || is_symbol(act, j) || is_symbol(next, j)) {
                    res += stoi(act.substr(i, end - i));
                    break;
                }
            }
            i = end - 1;
        }
    }
    return res;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string prev, act, next;
    getline(file, act);

    prev = string(act.size(), '.');
    int res = 0;

    while (getline(file, next)) {
        res += count_parts(prev, act, next);
        prev = move(act);
        act = move(next);
    }
    res += count_parts(prev, act, string(act.size(), '.'));

    cout << res << endl;

    return 0;
}