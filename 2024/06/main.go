// Advent of Code 2024
// Day 6: Guard Gallivant
// https://adventofcode.com/2024/day/6

package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"slices"
)

type Direction int

const (
	North Direction = iota
	East
	South
	West
)

type Point struct {
	x, y int
}

func main() {
	var labMap []string

	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan() {
		line := scanner.Text()
		labMap = append(labMap, line)
	}

	sol1, err := run1(slices.Clone(labMap))
	if err != nil {
		fmt.Println(err)
		return
	}

	sol2, err := run2(slices.Clone(labMap))
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Println(sol1, sol2)
}

func run1(labMap []string) (int, error) {

	x, y, err := findGuardPosition(labMap)
	if err != nil {
		return -1, err
	}

	direction, err := getDirection(x, y, labMap)
	if err != nil {
		return -1, err
	}
	setVisited(x, y, labMap)

	for {
		x_next, y_next, err := getNextPosition(x, y, direction)
		if err != nil {
			return -1, err
		}
		if x_next < 0 || x_next >= len(labMap[0]) || y_next < 0 || y_next >= len(labMap) {
			break
		}
		if labMap[y_next][x_next] == '#' {
			direction = (direction + 1) % 4
		} else {
			x = x_next
			y = y_next
			setVisited(x, y, labMap)
		}
	}
	return countVisited(labMap), nil
}

func run2(labMap []string) (int, error) {
	freePoints := getFreePoints(labMap)
	maximumMoves := len(freePoints)

	counter := 0

	initX, initY, err := findGuardPosition(labMap)
	if err != nil {
		return -1, err
	}

	initDirection, err := getDirection(initX, initY, labMap)
	if err != nil {
		return -1, err
	}

	for _, point := range freePoints {
		labMapCopy := slices.Clone(labMap)

		labMapCopy[point.y] = labMapCopy[point.y][:point.x] + "#" + labMapCopy[point.y][point.x+1:]

		isLooped := true

		x, y := initX, initY
		direction := initDirection

		for i := 0; i < maximumMoves; i++ {

			x_next, y_next, err := getNextPosition(x, y, direction)
			if err != nil {
				return -1, err
			}
			if x_next < 0 || x_next >= len(labMapCopy[0]) || y_next < 0 || y_next >= len(labMapCopy) {
				isLooped = false
				break
			}
			if labMapCopy[y_next][x_next] == '#' {
				direction = (direction + 1) % 4
			} else {
				x = x_next
				y = y_next
			}
		}

		if isLooped {
			counter++
		}
	}

	return counter, nil

}

func getFreePoints(labMap []string) []Point {
	var freePoints []Point
	for y, row := range labMap {
		for x, cell := range row {
			if cell == '.' {
				freePoints = append(freePoints, Point{x, y})
			}
		}
	}
	return freePoints
}

func findGuardPosition(labMap []string) (int, int, error) {
	for y, row := range labMap {
		for x, cell := range row {
			if cell == '^' || cell == 'v' || cell == '>' || cell == '<' {
				return x, y, nil
			}
		}
	}
	return -1, -1, errors.New("Guard not found")
}

func getDirection(x, y int, labMap []string) (Direction, error) {
	switch labMap[y][x] {
	case '^':
		return North, nil
	case 'v':
		return South, nil
	case '>':
		return East, nil
	case '<':
		return West, nil
	default:
		return -1, errors.New("Invalid guard direction")
	}
}

func getNextPosition(x, y int, direction Direction) (int, int, error) {
	switch direction {
	case North:
		return x, y - 1, nil
	case South:
		return x, y + 1, nil
	case East:
		return x + 1, y, nil
	case West:
		return x - 1, y, nil
	default:
		return -1, -1, errors.New("Invalid direction")
	}
}

func setVisited(x, y int, labMap []string) {
	labMap[y] = labMap[y][:x] + "X" + labMap[y][x+1:]
}

func countVisited(labMap []string) int {
	count := 0
	for _, row := range labMap {
		for _, cell := range row {
			if cell == 'X' {
				count++
			}
		}
	}
	return count
}
