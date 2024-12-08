// Advent of Code 2024
// Day 7: Bridge Repair
// https://adventofcode.com/2024/day/7

package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

type Equasion struct {
	result  int
	numbers []int
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	var equasions []Equasion

	for scanner.Scan() {
		line := scanner.Text()
		split := strings.Split(line, ": ")

		result, err := strconv.Atoi(split[0])
		if err != nil {
			fmt.Println("Error converting string to int:", err)
			continue
		}

		numbers := strings.Split(split[1], " ")

		var numbersInt []int
		for _, n := range numbers {
			num, err := strconv.Atoi(n)
			if err != nil {
				fmt.Println("Error converting string to int:", err)
				continue
			}
			numbersInt = append(numbersInt, num)
		}

		equasion := Equasion{result: result, numbers: numbersInt}
		equasions = append(equasions, equasion)

	}

	sol1, err := run1(equasions)
	if err != nil {
		fmt.Println(err)
		return
	}

	sol2, err := run2(equasions)
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Println(sol1, sol2)

}

func run1(equasions []Equasion) (int, error) {

	var correctResults int

	for _, e := range equasions {
		operatorNumber := len(e.numbers) - 1

		numberOfMasks := 1 << uint(operatorNumber)
		for i := 0; i < numberOfMasks; i++ {
			currentResult := e.numbers[0]
			mask := strconv.FormatInt(int64(i), 2)

			if len(mask) < operatorNumber {
				mask = strings.Repeat("0", operatorNumber-len(mask)) + mask
			}

			for j, m := range mask {
				if m == '1' {
					currentResult += e.numbers[j+1]
				} else {
					currentResult *= e.numbers[j+1]
				}
			}

			if currentResult == e.result {
				correctResults += e.result
				break
			}

		}

	}

	return correctResults, nil
}

func run2(equasions []Equasion) (int, error) {

	var correctResults int

	for _, e := range equasions {
		operatorNumber := len(e.numbers) - 1

		numberOfMasks := int(math.Pow(3, float64(operatorNumber)))
		for i := 0; i < numberOfMasks; i++ {
			currentResult := e.numbers[0]
			mask := strconv.FormatInt(int64(i), 3)

			if len(mask) < operatorNumber {
				mask = strings.Repeat("0", operatorNumber-len(mask)) + mask
			}

			for j, m := range mask {
				if m == '1' {
					currentResult += e.numbers[j+1]
				} else if m == '2' {
					currentResult *= e.numbers[j+1]
				} else {
					str1 := strconv.Itoa(currentResult)
					str2 := strconv.Itoa(e.numbers[j+1])
					concatentedStr := str1 + str2
					num, err := strconv.Atoi(concatentedStr)
					if err != nil {
						return -1, err
					}
					currentResult = num
				}
			}

			if currentResult == e.result {
				correctResults += e.result
				break
			}

		}

	}

	return correctResults, nil
}
