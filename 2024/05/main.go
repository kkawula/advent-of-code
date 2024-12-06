// Advent of Code 2024
// Day 5: Print Queue
// https://adventofcode.com/2024/day/5

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Rule struct {
	Left  int
	Right int
}

func main() {
	var sum1 int

	scanner := bufio.NewScanner(os.Stdin)

	var rules []Rule

	for scanner.Scan() {
		line := scanner.Text()

		if line == "" {
			break
		}

		parts := strings.Split(line, "|")
		num1, err1 := strconv.Atoi(parts[0])
		num2, err2 := strconv.Atoi(parts[1])

		if err1 != nil || err2 != nil {
			fmt.Fprintln(os.Stderr, "Invalid input")
			continue
		}

		rules = append(rules, Rule{num1, num2})
	}

	for scanner.Scan() {
		line := scanner.Text()

		parts := strings.Split(line, ",")

		var pages []int

		for _, part := range parts {
			num, err := strconv.Atoi(part)

			if err != nil {
				fmt.Fprintln(os.Stderr, "Invalid input")
				continue
			}

			pages = append(pages, num)
		}

		middleIndex := len(pages) / 2

		if checkRules(rules, pages) {
			sum1 += pages[middleIndex]
		}
	}

	fmt.Println(sum1)

}

func checkRules(rules []Rule, pages []int) bool {
	for i := 0; i < len(pages); i++ {
		for j := 0; j < len(rules); j++ {
			if rules[j].Left == pages[i] {
				if isBefore(rules[j].Right, pages[i], pages) {
					return false
				}
			} else if rules[j].Right == pages[i] {
				if isAfter(rules[j].Left, pages[i], pages) {
					return false
				}
			}
		}
	}

	return true
}

func isBefore(page, checkedPage int, pages []int) bool {
	for i := 0; i < len(pages); i++ {
		if pages[i] == page {
			return true
		} else if pages[i] == checkedPage {
			return false
		}
	}
	return true
}

func isAfter(page, checkedPage int, pages []int) bool {
	for i := len(pages) - 1; i >= 0; i-- {
		if pages[i] == page {
			return true
		} else if pages[i] == checkedPage {
			return false
		}
	}
	return true
}
