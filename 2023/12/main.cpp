// Advent of Code 2023
// Day 12: Hot Springs
// https://adventofcode.com/2023/day/12

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

struct Spring {
    string record;
    vector<int> nums;
};

int validate(string record, vector<int> nums) {
    vector <int> newNums;
    char lastC = record[0];
    int currLen = 0;
    for (char c : record) {
        if (c == '#'){
            currLen++;
        } else {
            if (currLen > 0) {
                newNums.push_back(currLen);
                currLen = 0;
            } 
        }
    }
    if (currLen > 0) {
        newNums.push_back(currLen);
    }   

    if (newNums.size() != nums.size()) return false;
    for (int i = 0; i < nums.size(); i++){
        if (nums[i] != newNums[i]) return false;
    }
    return true;
}

int bruteForce(string record, vector<int> nums, int idx) {
    int res = 0;
    if (idx == record.size()) {
        if (validate(record, nums)) return 1;
        return 0;
    }
    bool checked = false;
    for (int i = idx; i < record.size(); i++) {
        if (record[i] == '?') {
            record[i] = '#';
            res += bruteForce(record, nums, i+1);
            record[i] = '.';
            res += bruteForce(record, nums, i+1);
            checked = true;
            break;
        }
        if (i == record.size() - 1 && !checked) {
            res += bruteForce(record, nums, i+1);
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

    string s;

    vector<Spring> springs;
    
    while (getline(file, line)) {
        istringstream iss(line);
        iss >> s;

        Spring spring;
        spring.record = s;

        while (getline(iss, s, ',')) {
            spring.nums.push_back(stoi(s));
        }
        springs.push_back(spring);
        res += bruteForce(spring.record, spring.nums, 0);
    }


    cout << res << endl;
    cout << res2 << endl;
    return 0;
}