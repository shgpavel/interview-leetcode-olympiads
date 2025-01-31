package main

import (
	"bufio"
	"fmt"
	"os"
)

type Point struct {
	x, y int64
}

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	if a < 0 {
		a = -a
	}
	return a
}

func main() {
	var in *bufio.Reader
	var out *bufio.Writer

	in = bufio.NewReader(os.Stdin)
	out = bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n int
	fmt.Fscan(in, &n)

	points := make([]Point, n)
	for i := 0; i < n; i++ {
		var x, y int64
		fmt.Fscan(in, &x, &y)
		points[i] = Point{x, y}
	}

	if n < 3 {
		fmt.Println(0)
		return
	}

	maxLine := 1

	for i := 0; i < n; i++ {
		slopeCount := make(map[string]int)
		sameX := 1

		for j := 0; j < n; j++ {
			if i == j {
				continue
			}
			dx := points[j].x - points[i].x
			dy := points[j].y - points[i].y

			if dx == 0 {
				sameX++
				continue
			}

			g := gcd(dx, dy)
			dx /= g
			dy /= g

			if dx < 0 {
				dx = -dx
				dy = -dy
			}

			key := fmt.Sprintf("%d,%d", dy, dx)
			slopeCount[key]++
		}

		currentMax := sameX
		for _, count := range slopeCount {
			if count+1 > currentMax {
				currentMax = count + 1
			}
		}

		if currentMax > maxLine {
			maxLine = currentMax
		}
	}

	if maxLine == n {
		fmt.Println(0)
		return
	}

	if maxLine < 3 {
		fmt.Println(n / 3)
		return
	}

	s := n - maxLine
	t := maxLine / 2
	if t > s {
		t = s
	}
	remainingLine := maxLine - 2*t
	remainingOther := s - t
	totalRemaining := remainingLine + remainingOther
	res := t + (totalRemaining / 3)
	if res > n/3 {
		res = n / 3
	}
	fmt.Println(res)
}
