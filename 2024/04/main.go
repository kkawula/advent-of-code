// Advent of Code 2024
// Day 4: Ceres Search
// https://adventofcode.com/2024/day/4

package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var shirt []string
	var valid_XMAS, valid_X_MAS int

	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan() {
		line := scanner.Text()
		shirt = append(shirt, line)
	}

	height := len(shirt)
	width := len(shirt[0])

	for i := 0; i < height; i++ {
		for j := 0; j < width; j++ {
			if j+3 < width {
				if isXMAS(shirt[i][j], shirt[i][j+1], shirt[i][j+2], shirt[i][j+3]) {
					valid_XMAS++
				}
			}
			if i+3 < height {
				if isXMAS(shirt[i][j], shirt[i+1][j], shirt[i+2][j], shirt[i+3][j]) {
					valid_XMAS++
				}
			}
			if i+3 < height && j+3 < width {
				if isXMAS(shirt[i][j], shirt[i+1][j+1], shirt[i+2][j+2], shirt[i+3][j+3]) {
					valid_XMAS++
				}
			}
			if i+3 < height && j-3 >= 0 {
				if isXMAS(shirt[i][j], shirt[i+1][j-1], shirt[i+2][j-2], shirt[i+3][j-3]) {
					valid_XMAS++
				}
			}
		}
	}

	for i := 1; i < height-1; i++ {
		for j := 1; j < width-1; j++ {
			if shirt[i][j] != 'A' {
				continue
			}
			if isValidCross(shirt[i-1][j+1], shirt[i+1][j-1]) && isValidCross(shirt[i+1][j+1], shirt[i-1][j-1]) {
				valid_X_MAS++
			}

		}
	}

	fmt.Println(valid_XMAS, valid_X_MAS)
}

func isXMAS(a byte, b byte, c byte, d byte) bool {
	if a == 'X' && b == 'M' && c == 'A' && d == 'S' {
		return true
	} else if a == 'S' && b == 'A' && c == 'M' && d == 'X' {
		return true
	}
	return false
}

func isValidCross(a byte, b byte) bool {
	if a == 'S' && b == 'M' {
		return true
	} else if a == 'M' && b == 'S' {
		return true
	}
	return false
}
