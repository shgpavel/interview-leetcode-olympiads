package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func worker(a []int, m int) int {
	a1 := a[0]
	a2 := a[1]
	days := a[2:]

	sort.Ints(days)

	minCostChange := 1 << 60
	windowSize := m
	totalDays := len(days)

	if totalDays >= windowSize {
		for i := 0; i <= totalDays-windowSize; i++ {
			L := days[i]
			R := days[i+windowSize-1]
			cost := max(0, L-a1) + max(0, R-a2)
			if cost < minCostChange {
				minCostChange = cost
			}
		}
	}

	costNoChange := 1 << 60
	if a1 <= a2 {
		costs := make([]int, totalDays)
		for i, num := range days {
			if num < a1 {
				costs[i] = a1 - num
			} else if num > a2 {
				costs[i] = num - a2
			} else {
				costs[i] = 0
			}
		}
		sort.Ints(costs)
		sum := 0
		for i := 0; i < m; i++ {
			sum += costs[i]
		}
		costNoChange = sum
	}

	minimalCost := minCostChange
	if a1 <= a2 && costNoChange < minimalCost {
		minimalCost = costNoChange
	}

	return minimalCost
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func main() {
	var in *bufio.Reader
	var out *bufio.Writer

	in = bufio.NewReader(os.Stdin)
	out = bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n, m int
	fmt.Fscan(in, &n, &m)

	a := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(in, &a[i])
	}
	fmt.Println(worker(a, m))
}
