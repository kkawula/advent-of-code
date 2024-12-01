// Advent of Code 2024
// Day 1: Historian Hysteria
// https://adventofcode.com/2024/day/1

package main

import (
	"fmt"
	"math"
	"sort"
)

func main() {
	var left, right []int

	for {
		var l, r int
		n, _ := fmt.Scan(&l, &r)
		if n < 2 {
			break
		}

		left = append(left, l)
		right = append(right, r)
	}

	sort.Ints(left)
	sort.Ints(right)

	var total, similarity int

	for i := 0; i < len(left); i++ {
		total += int(math.Abs(float64(left[i] - right[i])))

		var count int

		for _, num := range right {
			if left[i] == num {
				count++
			}
		}

		similarity += count * left[i]
		count = 0

	}

	fmt.Println(total, similarity)

}
