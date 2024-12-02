// Advent of Code 2024
// Day 2: Red-Nosed Reports
// https://adventofcode.com/2024/day/2

package main

import (
	"bufio"
	"math"
	"os"
	"slices"
	"strconv"
	"strings"
)

func main() {
	var counter1, counter2 int

	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan() {
		line := scanner.Text()
		strNums := strings.Fields(line)
		var nums []int

		for _, strNum := range strNums {

			num, _ := strconv.Atoi(strNum)
			nums = append(nums, num)
		}

		if isValid(nums) {
			counter1++
			counter2++
		} else if isValidRemoveOne(nums) {
			counter2++
		}

	}

	println(counter1, counter2)

}

func isValid(nums []int) bool {
	if len(nums) < 2 {
		return true
	}

	sign := nums[1] > nums[0]

	for i := 1; i < len(nums); i++ {
		if (nums[i] > nums[i-1]) != sign {
			return false
		}

		diff := int(math.Abs(float64(nums[i] - nums[i-1])))

		if diff < 1 || diff > 3 {
			return false
		}
	}

	return true
}

func isValidRemoveOne(nums []int) bool {
	for i := 0; i < len(nums); i++ {
		currnet := slices.Clone(nums)
		currnet = append(currnet[:i], currnet[i+1:]...)
		if isValid(currnet) {
			return true
		}
	}
	return false
}
