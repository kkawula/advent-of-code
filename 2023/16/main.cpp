// Advent of Code 2023
// Day 16: The Floor Will Be Lava
// https://adventofcode.com/2023/day/16

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
#include <set>

using namespace std;

#define DEBUG false
using ll = long long;

ll solve(vector<string> map, int r, int c, int dr, int dc) {
    ll res = 0;
    int n = map.size();
    int m = map[0].size();
    queue<tuple<int, int, int, int>> q;
    set<tuple<int, int, int, int>> seen;

    q.push({r, c, dr, dc});
    
    while (!q.empty()) {
        tie(r, c, dr, dc) = q.front();
        q.pop();

        if (seen.find({r, c, dr, dc}) != seen.end()) {
            continue;
        }
        
        if (r < 0 || r >= n || c < 0 || c >= m) {
            continue;
        }
        seen.insert({r, c, dr, dc});
        if (map[r][c] == '.' || (map[r][c] == '-' && dr == 0) || (map[r][c] == '|' && dc == 0)) {
            q.push({r + dr, c + dc, dr, dc});
        }
        else if (map[r][c] == '|') {
            q.push({r + 1, c, 1, 0});
            q.push({r - 1, c, -1, 0});
        }
        else if (map[r][c] == '-') {
            q.push({r, c + 1, 0, 1});
            q.push({r, c - 1, 0, -1});
        }
        else if (map[r][c] == '/') { 
            q.push({r - dc, c - dr, -1 * dc, -1 * dr});
        }
        else if (map[r][c] == '\\') {
            q.push({r + dc, c + dr, dc, dr});
        }

    }
    set<pair<int, int>> unique; 
    for (auto t : seen) {
        unique.insert({get<0>(t), get<1>(t)});
    }
    res = unique.size();

    return res;
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
    vector<string> map;

    while (getline(file, line)) {
        map.push_back(line);
    }
    res = solve(map, 0, 0, 0, 1);

    int n = map.size();
    int m = map[0].size();
    for (int i = 0; i < n; i++) {
        res2 = max(res2, solve(map, i, 0, 0, 1));
        res2 = max(res2, solve(map, i, m - 1, 0, -1));
    }

    for (int j = 0; j < m; j++) {
        res2 = max(res2, solve(map, 0, j, 1, 0));
        res2 = max(res2, solve(map, n - 1, j, -1, 0));
    }


    cout << res << endl;
    cout << res2 << endl;
    return 0;
}