// Advent of Code 2024
// Day 3: Mull It Over
// https://adventofcode.com/2024/day/3

package main

import (
	"bufio"
	"fmt"
	"os"
	"regexp"
	"strconv"
)

func main() {
	var sum1, sum2 int

	re1 := regexp.MustCompile(`mul\((\d+),\s*(\d+)\)`)
	re2 := regexp.MustCompile(`(?:mul\((\d+),\s*(\d+)\)|do\(\)|don't\(\))`)
	scanner := bufio.NewScanner(os.Stdin)
	do := true

	for scanner.Scan() {
		line := scanner.Text()

		matches1 := re1.FindAllStringSubmatch(line, -1)
		matches2 := re2.FindAllStringSubmatch(line, -1)

		for _, match := range matches1 {
			num1, err1 := strconv.Atoi(match[1])
			num2, err2 := strconv.Atoi(match[2])

			if err1 == nil && err2 == nil {
				sum1 += num1 * num2
			}
		}

		for _, match := range matches2 {
			if match[0] == "do()" {
				do = true
			} else if match[0] == "don't()" {
				do = false
			} else if do {
				num1, err1 := strconv.Atoi(match[1])
				num2, err2 := strconv.Atoi(match[2])

				if err1 == nil && err2 == nil {
					sum2 += num1 * num2
				}
			}
		}
	}

	fmt.Println(sum1, sum2)

}
