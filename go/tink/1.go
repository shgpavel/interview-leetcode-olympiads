package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString('\n')

	slices := strings.Split(input, ",")

	for i, str := range slices {
		var left, right int
		if !strings.Contains(str, "-") {
			fmt.Sscanf(str, "%d", &left)
			if i == len(slices)-1 {
				fmt.Printf("%d ", left)
			} else {
				fmt.Printf("%d", left)
			}
			continue
		}
		fmt.Sscanf(str, "%d-%d", &left, &right)
		for left <= right {
			if i == len(slices)-1 &&
				left == right {
				fmt.Printf("%d", left)
				left++
			}
			fmt.Printf("%d ", left)
			left++
		}
	}
	fmt.Printf("\n")
}
