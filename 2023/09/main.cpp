// Advent of Code 2023
// Day 9: Mirage Maintenance
// https://adventofcode.com/2023/day/9

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

ll next_number(vector<ll>& nums) {
    vector<ll> diffs;

    if (nums.size() == 1) {
        nums.push_back(nums.back());
        return nums.back();
    }
    
    for (int i = 1; i < nums.size(); ++i) {
        diffs.push_back(nums[i] - nums[i - 1]);
    }

    if( any_of(diffs.begin(), diffs.end(), [](int i){return i != 0;}) ) {
        nums.push_back(nums.back() + next_number(diffs));
    }
    else {
        nums.push_back(nums.back());
    }

    return nums.back();
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
    vector <vector<ll>> values; 
    
    while (getline(file, line)) {
        vector<ll> row;
        stringstream ss(line);
        ll val;
        while (ss >> val) {
            row.push_back(val);
        }
        values.push_back(row);
    }

    for (int i = 0; i < values.size(); ++i) {
        res += next_number(values[i]);
        reverse(values[i].begin(), values[i].end());
        res2 += next_number(values[i]);
    }
    
    cout << res << endl;
    cout << res2 << endl;

    return 0;
}