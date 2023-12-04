// Advent of Code 2023
// Day 4: Scratchcards
// https://adventofcode.com/2023/day/4

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    string line, bar;
    int res = 0, idx = 0;
    vector<int> copies(1, 1);

    while (getline(file, line)) {
        istringstream iss(line);
        set<int> winning_numbers, my_numbers;
        int num;
        
        iss >> bar >> bar;
        while (iss >> num) {
            winning_numbers.insert(num);
        }

        iss.clear();
        iss >> bar;
        while (iss >> num) {
            my_numbers.insert(num);
        }

        int matches = 0;
        for (const auto& num : my_numbers) {
            if (winning_numbers.count(num) > 0) {
                matches++;
            }
        }
        if (copies.size() < idx + matches + 1) {
            copies.resize(idx + matches + 1, 1);
        }
        for (int j = 0; j < copies[idx]; j++) {
            for (int i = idx + 1; i < idx + matches + 1; i++) {
                copies[i]++;
            }
        }
        
        res += copies[idx];
        idx++;
    }

    cout << "res: " << res << endl;

    return 0;
}