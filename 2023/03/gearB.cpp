// Advent of Code 2023
// Day 3: Gear Ratios
// https://adventofcode.com/2023/day/3

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

struct Item {
    int counter = 0;
    int value = 0;
};

map<int, Item> gear_map;

int find_end(const string& s, int i) {
    while (i < s.size() && isdigit(s[i])) {
        ++i;
    }
    return i;
}

bool is_symbol(const string& s, int i) {
    return s[i] != '.' && !isdigit(s[i]);
}

void update_item(int key, int part_value) {
    Item& item = gear_map[key];
    item.counter++;
    item.value = (item.value == 0) ? part_value : item.value * part_value;
}

int count_parts(const string& prev, const string& act, const string& next, int row) {
    int res = 0;
    for (int i = 0; i < act.size(); ++i) {
        if (isdigit(act[i])) {
            int end = find_end(act, i);
            int part_value = stoi(act.substr(i, end - i));
            for (int j = max(0, i - 1); j < min((int)act.size(), end + 1); ++j) {
                if (is_symbol(prev, j) || is_symbol(act, j) || is_symbol(next, j)) {
                    if (prev[j] == '*') update_item((row - 1)*act.size() + j, part_value);
                    if (act[j] == '*') update_item(row*act.size() + j, part_value);
                    if (next[j] == '*') update_item((row + 1)*act.size() + j, part_value);
                }
            }
            i = end;
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

    int row = 0;
    prev = string(act.size(), '.');

    int res = 0;
    while (getline(file, next)) {
        res += count_parts(prev, act, next, row++);
        swap(prev, act);
        swap(act, next);
    }
    res += count_parts(prev, act, string(act.size(), '.'), row);

    for(const auto& pair : gear_map) {
        if (pair.second.counter == 2) {
            res += pair.second.value;
        }
    }
    cout << res << "\n";

    return 0;
}