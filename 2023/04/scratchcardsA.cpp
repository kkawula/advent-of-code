// Advent of Code 2023
// Day 4: Scratchcards
// https://adventofcode.com/2023/day/4

#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>

using namespace std;

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    string line,bar;
    int res = 0;

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

        int card_score = matches > 0 ? (1 << (matches - 1)) : 0;
        res += card_score;
    }

    cout << "res: " << res << endl;

    return 0;
}