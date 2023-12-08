// Advent of Code 2023
// Day 8: Haunted Wasteland
// https://adventofcode.com/2023/day/8

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

struct Node {
    string left;
    string right;
};

ll move(map<string, Node>& graph, string moves) {
    ll res = 0;
    string current = "AAA";
    while (true){
        for (int i = 0; i < moves.size(); ++i) {
            if (moves[i] == 'L') {
                current = graph[current].left;
            } else {
                current = graph[current].right;
            }
            ++res;
            if (current == "ZZZ") {
                return res;
            }
        }
    }
}

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

ll lcmArray(const std::vector<ll>& arr) {
    ll result = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        result = lcm(result, arr[i]);
    }
    return result;
}

ll moveSimultaneously(map<string, Node>& graph, vector<string> nodesA, string moves) {
    ll res = 1;
    ll currOnZ = 0;
    vector<ll> timesOnZ(nodesA.size(), 0);

    while (true){
        for (int i = 0; i < moves.size(); ++i) {
            if (moves[i] == 'L') {
                for (int j = 0; j < nodesA.size(); ++j) {
                    string nextNode = graph[nodesA[j]].left;
                    if (nextNode[2] == 'Z' && timesOnZ[j] == 0) {
                        timesOnZ[j] = res;
                        currOnZ += 1;
                    }
                    nodesA[j] = nextNode;
                }
            } else {
                for (int j = 0; j < nodesA.size(); ++j) {
                    string nextNode = graph[nodesA[j]].right;
                    if (nextNode[2] == 'Z' && timesOnZ[j] == 0) {
                        timesOnZ[j] = res;
                        currOnZ += 1;
                    }
                    nodesA[j] = nextNode;
                }
            }            
            ++res;
            if (currOnZ == nodesA.size()) {
                return lcmArray(timesOnZ);
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

    string line, moves;
    ll res = 0, res2 = 0;
    
    getline(file, moves);
    map<string, Node> graph;
    vector<string> nodesA;
    while (getline(file, line)) {
        stringstream ss(line);
        string key, value;
        getline(ss, key, '=');
        getline(ss, value);
        key.erase(remove(key.begin(), key.end(), ' '), key.end());

        value.erase(remove(value.begin(), value.end(), '('), value.end());
        value.erase(remove(value.begin(), value.end(), ')'), value.end());
        
        stringstream ssValue(value);
        string firstValue, secondValue;
        getline(ssValue, firstValue, ',');
        getline(ssValue, secondValue);
        firstValue.erase(remove(firstValue.begin(), firstValue.end(), ' '), firstValue.end());
        secondValue.erase(remove(secondValue.begin(), secondValue.end(), ' '), secondValue.end());

        graph[key] = Node{firstValue, secondValue};  
        if (key[2] == 'A') {
            nodesA.push_back(key);
        }
    }

    res = move(graph, moves);
    res2 = moveSimultaneously(graph, nodesA, moves);

    cout << res << endl;
    cout << res2 << endl;
    return 0;
}