#include <fstream>
#include <string>
#include <iostream>

// Advent of Code 2023
// Day 1: Trebuchet?!
// https://adventofcode.com/2023/day/1

using namespace std;

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    const string digits[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};


    string line;
    int idx = 0;
    int lastNumIdx = -2, lastNum = 0;
    int firstNumIdx = 1e9, firstNum = 0;
    int res = 0, res2 = 0;
    for (int i = 0; i < 1000 && getline(file, line); i++) {
        lastNumIdx = -2;
        firstNumIdx = 1e9;
        for (char c = '1'; c <= '9'; c++) {
            idx = line.find(c);
            if (idx != string::npos){
                if (firstNumIdx > idx) {
                firstNumIdx = idx;
                firstNum = c - '0';
                }
            }
            idx = line.rfind(c);
            if (idx != string::npos){
                if (lastNumIdx < idx) {
                lastNumIdx = idx;
                lastNum = c - '0';
                }
            }
        }
        res += firstNum * 10 + lastNum;
        for (int i = 1; i <= 9; i++) {
            idx = line.find(digits[i]);
            if (idx != string::npos){
                if (firstNumIdx > idx) {
                firstNumIdx = idx;
                firstNum = i;
                }
            }

            idx = line.rfind(digits[i]);
            if (idx != string::npos){
                if (lastNumIdx < idx) {
                lastNumIdx = idx;
                lastNum = i;
                }
            }
        }
        res2 += firstNum * 10 + lastNum;
    }
    cout << res << endl;
    cout << res2 << endl;

    file.close();
    return 0;
}