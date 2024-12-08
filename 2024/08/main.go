// Advent of Code 2024
// Day 8: Resonant Collinearity
// https://adventofcode.com/2024/day/8

package main

import (
	"bufio"
	"fmt"
	"os"
)

type Point struct {
	x, y int
}

func (p Point) Sub(p2 Point) Point {
	return Point{p.x - p2.x, p.y - p2.y}
}

func (p Point) Add(p2 Point) Point {
	return Point{p.x + p2.x, p.y + p2.y}
}

type Antenna struct {
	point Point
	freq  byte
}

func main() {
	var antennasMap []string

	frequencyMap := make(map[byte][]Antenna)
	antiNodes1 := make(map[Point]struct{})
	antiNodesLine := make(map[Point]struct{})

	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan() {
		line := scanner.Text()
		antennasMap = append(antennasMap, line)
	}

	height := len(antennasMap)
	width := len(antennasMap[0])

	for y, row := range antennasMap {
		for x, cell := range row {
			if cell != '.' {
				antenna := Antenna{Point{x, y}, byte(cell)}
				frequencyMap[antenna.freq] = append(frequencyMap[antenna.freq], antenna)
			}
		}
	}

	for _, antennas := range frequencyMap {
		for i := 0; i < len(antennas); i++ {
			for j := i + 1; j < len(antennas); j++ {
				antenna1 := antennas[i]
				antenna2 := antennas[j]
				vec := antenna2.point.Sub(antenna1.point)

				antiNode1 := antenna2.point.Add(vec)
				antiNode2 := antenna1.point.Sub(vec)

				if antiNode1.x >= 0 && antiNode1.x < width && antiNode1.y >= 0 && antiNode1.y < height {
					antiNodes1[antiNode1] = struct{}{}
					antiNodesLine[antiNode1] = struct{}{}
				}

				if antiNode2.x >= 0 && antiNode2.x < width && antiNode2.y >= 0 && antiNode2.y < height {
					antiNodes1[antiNode2] = struct{}{}
					antiNodesLine[antiNode2] = struct{}{}
				}

				current := antiNode1
				for current.x >= 0 && current.x < width && current.y >= 0 && current.y < height {
					antiNodesLine[current] = struct{}{}
					current = current.Add(vec)
				}

				current = antiNode2
				for current.x >= 0 && current.x < width && current.y >= 0 && current.y < height {
					antiNodesLine[current] = struct{}{}
					current = current.Sub(vec)
				}

				antiNodesLine[antenna1.point] = struct{}{}
				antiNodesLine[antenna2.point] = struct{}{}
			}
		}

	}

	fmt.Println(len(antiNodes1), len(antiNodesLine))
}
