// Advent of Code 2023
// Day 5: If You Give A Seed A Fertilizer
// https://adventofcode.com/2023/day/5

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;

struct MappingData {
    ll destStart;
    ll srcStart;
    ll length;
};

vector<MappingData> parseMapping(const vector<string>& lines) {
    vector<MappingData> mapping;
    ll destStart, srcStart, length;

    for (ll i = 1; i < lines.size(); ++i) {
        istringstream lineStream(lines[i]);
        lineStream >> destStart >> srcStart >> length;
        mapping.push_back(MappingData{ destStart, srcStart, length });
    }
    return mapping;
}

ll get_location(ll seed, const vector<vector<MappingData>>& mappings) {
    cout << "Seed: " << seed << endl;
    for (const auto& mapping : mappings) {
        for (const auto& data : mapping) {
            if (seed >= data.srcStart && seed < data.srcStart + data.length) {
                seed = seed + data.destStart - data.srcStart;
                // cout << "diff = " << data.destStart - data.srcStart << endl;
                // cout << "destStart: " << data.destStart << ", srcStart: " << data.srcStart << ", length: " << data.length << endl;
                // cout << seed << endl;
                break;
            }
        }
    }
    return seed;
}

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line, text;
    getline(file, line);
    istringstream lineStream(line);
    vector<ll> seeds;
    ll seed, range;

    lineStream >> text;
    while (lineStream >> seed) {
        seeds.push_back(seed);
    }

    vector<vector<MappingData>> mappings;
    vector<string> lines;
    while (getline(file, line)) {
        if (line.empty()) {
            mappings.push_back(parseMapping(lines));
            lines.clear();
        } else {
            lines.push_back(line);
        }
    }
    if (!lines.empty()) {
        mappings.push_back(parseMapping(lines));
    }

    ll minLocation = LONG_MAX;
    for (const auto& seed : seeds) {
        cout<<seed<<endl;
        minLocation = min(minLocation, get_location(seed, mappings));
    }

    cout << "Minimum location: " << minLocation << endl;

    return 0;
}