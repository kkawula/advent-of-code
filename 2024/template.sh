DAY="${1:-}"
if [ -z "$DAY" ]; then
    echo "Usage: $0 <day>"
    exit 1
fi

DAY_PAD=$(printf "%02d" "$DAY")
DAY_NO_PAD=$(echo "$DAY" | sed 's/^0*//')


mkdir -p "$DAY_PAD"
touch "$DAY_PAD/main.go"
touch "$DAY_PAD/input.txt"
touch "$DAY_PAD/example.txt"


function template() {
    cat <<EOF
// Advent of Code 2024
// Day ${DAY_NO_PAD}: 
// https://adventofcode.com/2024/day/${DAY_NO_PAD}

package main

import (
	"bufio"
	"os"
)

func main() {
	scanner := bufio.NewScanner(os.Stdin)

	for scanner.Scan() {
		line := scanner.Text()
		println(line)
	}

}
EOF
}

template > "$DAY_PAD/main.go"

SESSION_COOKIE="${AOC_SESSION_COOKIE:-}"
if [ -z "$SESSION_COOKIE" ]; then
    echo "AOC_SESSION_COOKIE in not set"
    exit 1
fi

curl --cookie "session=${SESSION_COOKIE}" https://adventofcode.com/2024/day/${DAY_NO_PAD}/input -o "$DAY_PAD/input.txt"
