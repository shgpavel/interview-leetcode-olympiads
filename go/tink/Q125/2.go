package main

import (
	"bufio"
	"fmt"
	"math/bits"
	"os"
)

func worker(a int64) int64 {
	if a < 7 {
		return -1
	}

	var maxSum int64
	pos := bits.Len64(uint64(a)) - 1
	for x := pos; x >= 0; x-- {
		xBit := int64(1 << x)
		if xBit > a {
			continue
		}
		remaining := a - xBit
		if remaining < 3 {
			continue
		}
		y, z := findYandZ(remaining, x)
		sumTwo := y + z
		if sumTwo == 0 {
			continue
		}
		if total := xBit + sumTwo; total > maxSum {
			maxSum = total
		}
	}
	if maxSum >= 7 {
		return maxSum
	}
	return -1
}

func findYandZ(R int64, x int) (int64, int64) {
	yBit := bits.Len64(uint64(R)) - 1
	for yBit >= x && yBit > 0 {
		yBit--
	}
	if yBit < 0 {
		return 0, 0
	}
	y := int64(1 << yBit)
	remaining := R - y
	if remaining < 1 {
		for yBit > 0 {
			yBit--
			if yBit >= x {
				continue
			}
			y = int64(1 << yBit)
			remaining = R - y
			if remaining >= 1 {
				break
			}
		}
		if remaining < 1 {
			return 0, 0
		}
	}
	zBit := bits.Len64(uint64(remaining)) - 1
	for zBit >= yBit && zBit > 0 {
		zBit--
	}
	if zBit < 0 {
		return 0, 0
	}
	z := int64(1 << zBit)
	if y+z > R {
		return 0, 0
	}
	return y, z
}

func main() {
	var in *bufio.Reader
	var out *bufio.Writer

	in = bufio.NewReader(os.Stdin)
	out = bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var days int
	fmt.Fscan(in, &days)

	for i := 0; i < days; i++ {
		var a int64
		fmt.Fscan(in, &a)
		fmt.Println(worker(a))
	}
}
