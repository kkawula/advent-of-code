// Advent of Code 2023
// Day 2: Cube Conundrum
// https://adventofcode.com/2023/day/2

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

map<string, int> parseLine(const string& line) {
    stringstream ss(line);
    string id, color;
    int cnt;
    ss >> id >> id;
    map<string, int> dict;
    while (ss >> cnt >> color) {
        if (color.back() == ',' || color.back() == ';') color.pop_back();
        dict[color] = max(dict[color], cnt);
    }
    return dict;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    int res = 0, res2 = 0;

    while (getline(file, line)) {
        map<string, int> dict = parseLine(line);
        if (dict["red"] <= 12 && dict["green"] <= 13 && dict["blue"] <= 14) {
            res += stoi(line.substr(5, line.find(':') - 5));
        }
        res2 += dict["red"] * dict["green"] * dict["blue"];
    }
    cout << res << "\n";
    cout << res2 << "\n";
    file.close();
    return 0;
}