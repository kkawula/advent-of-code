// Advent of Code 2023
// Day 10: Pipe Maze
// https://adventofcode.com/2023/day/10

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

pair<ll, ll> findS(vector <string> maze) {
    for (ll i = 0; i < maze.size(); i++) {
        for (ll j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'S') {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

vector<pair<ll, ll>> neighbors(vector<string> maze, ll i, ll j) {
    switch (maze[i][j]) {
        case '|':
            return {{i - 1, j}, {i + 1, j}};
        case '-':
            return {{i, j - 1}, {i, j + 1}};
        case 'L':
            return {{i - 1, j}, {i, j + 1}};
        case 'J':
            return {{i - 1, j}, {i, j- 1}};
        case '7':
            return {{i + 1, j}, {i, j - 1}};
        case 'F':
            return {{i + 1, j}, {i, j + 1}};
        default:
            cout << "ERROR" << endl;
            return {};
        }
}

char inferS (vector<string> maze, ll i, ll j) {
    bool isUp = false;
    bool isDown = false;
    bool isLeft = false;
    bool isRight = false;

    if (i - 1 >= 0 && (maze[i - 1][j] == '|' || maze[i - 1][j] == 'F' || maze[i - 1][j] == '7')) {
        isUp = true;
    }
    if (i + 1 < maze.size() && (maze[i + 1][j] == '|' || maze[i + 1][j] == 'L' || maze[i + 1][j] == 'J')) {
        isDown = true;
    }
    if (j - 1 >= 0 && (maze[i][j - 1] == '-' || maze[i][j - 1] == 'L' || maze[i][j - 1] == 'F')) {
        isLeft = true;
    }
    if (j + 1 < maze[0].size() && (maze[i][j + 1] == '-' || maze[i][j + 1] == 'J' || maze[i][j + 1] == '7')) {
        isRight = true;
    }
    if (isUp && isDown){ return '|'; }
    if (isLeft && isRight) { return '-';}
    if (isUp && isRight) { return 'L'; }
    if (isUp && isLeft) { return 'J'; }
    if (isDown && isRight) { return 'F'; }
    if (isDown && isLeft) { return '7'; }
    throw invalid_argument("start position cannot be a pipe");
}

ll solve(vector <string>& maze, vector<vector<ll>>& d) {
    ll res = 0;
    queue<pair<ll, ll>> q;

    pair<ll, ll> pos = findS(maze);
    d[pos.first][pos.second] = 0;

    maze[pos.first][pos.second] = inferS(maze, pos.first, pos.second);
    q.push(pos);

    while(!q.empty()) {
        pair<ll, ll> cur = q.front();
        q.pop();
        res = max(res, d[cur.first][cur.second]);
        for (auto& p: neighbors(maze, cur.first, cur.second)) {

            if (p.first >= 0 && p.first < maze.size() && p.second >= 0 && p.second < maze[0].size() && d[p.first][p.second] > d[cur.first][cur.second] + 1) {
                d[p.first][p.second] = d[cur.first][cur.second] + 1;
                q.push(p);
            }
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
    vector <string> maze; 
    
    while (getline(file, line)) {
        maze.push_back(line);
    }
        
    vector<vector<ll>> d(maze.size(), vector<ll>(maze[0].size(), 1e10));
    
    res = solve(maze, d);
    
    cout << res << endl;
    return 0;
}