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

vector<pair<ll, ll>> calculateRanges(vector<pair<ll, ll>> seedRanges, const vector<vector<MappingData>>& mappings) {
    vector<pair<ll, ll>> newRanges;

    for (const auto& map : mappings) {
        newRanges.clear();

        while (!seedRanges.empty()) {
            auto currRange = seedRanges.back();
            seedRanges.pop_back();
            bool isMapped = false;

            for (const auto& data : map) {
                ll newRangeStart = max(currRange.first, data.srcStart);
                ll newRangeEnd = min(currRange.second, data.srcStart + data.length);

                if (newRangeStart < newRangeEnd) {
                    newRanges.push_back(make_pair(newRangeStart + data.destStart - data.srcStart, newRangeEnd + data.destStart - data.srcStart));
                    isMapped = true;

                    if (newRangeStart > currRange.first) {
                        seedRanges.push_back(make_pair(currRange.first, newRangeStart));
                    }
                    if (newRangeEnd < currRange.second) {
                        seedRanges.push_back(make_pair(newRangeEnd, currRange.second));
                    }
                    break;
                }
            }
            if (!isMapped) {
                newRanges.push_back(currRange);
            }
        }
        seedRanges = newRanges;
    }
    return seedRanges;
}

int main() {
    ifstream file("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line, text;
    getline(file, line);
    istringstream lineStream(line);
    vector<pair<ll, ll>> seedRanges;
    ll seed, range;

    lineStream >> text;
    while (lineStream >> seed >> range) {
        seedRanges.push_back(make_pair(seed, seed + range));
    }

    vector<vector<MappingData>> mappings;
    vector<string> lines;
    while (getline(inputFile, line)) {
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
    vector<pair<ll, ll>> ranges = calculateRanges(seedRanges, mappings);
    for (const auto& range : ranges) {
        minLocation = min(minLocation, range.first);
    }
    cout << minLocation << endl;

    return 0;
}