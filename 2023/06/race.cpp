// Advent of Code 2023
// Day 6: Wait For It
// https://adventofcode.com/2023/day/6

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

using ll = long long;

ll posibilities(ll time, ll distance) {
    double t1, t2;
    double deltaSqrt = sqrt(time * time  - 4 * distance);
    t1 = floor((time - deltaSqrt) / 2);
    t2 = ceil((time + deltaSqrt) / 2);
    cout << t1 << " " << t2 << endl;
    return (ll) t2 - t1 - 1;
}


int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string times, distances, buff;
    getline(file, times);
    getline(file, distances);
    istringstream timeStream(times);
    istringstream distanceStream(distances);

    timeStream >> buff;
    distanceStream >> buff;

    int time, distance;
    int res = 1;
    long long  res2 = 0;

    string timeB = "", distanceB ="";

    while (timeStream >> time && distanceStream >> distance) {
        // res *= posibilities(time, distance);
        timeB += to_string(time);
        distanceB += to_string(distance);
    }
    cout << stoll(timeB) << " " << stoll(distanceB) << endl;
    res2 = posibilities(stoll(timeB), stoll(distanceB));

    cout << res << endl;
    cout << res2 << endl;

    return 0;
}