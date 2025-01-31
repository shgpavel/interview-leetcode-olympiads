package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var in *bufio.Reader
	var out *bufio.Writer

	in = bufio.NewReader(os.Stdin)
	out = bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n int
	var x, y, z int64
	fmt.Fscan(in, &n, &x, &y, &z)

	a := make([]int64, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(in, &a[i])
	}

	targets := make([]int64, 0, 3)
	if x != 1 {
		targets = append(targets, x)
	}
	if y != 1 {
		targets = append(targets, y)
	}
	if z != 1 {
		targets = append(targets, z)
	}

	if len(targets) == 0 {
		fmt.Println(0)
		return
	}

	switch len(targets) {
	case 1:
		t := targets[0]
		minCost := int64(1e18)
		for _, num := range a {
			remainder := num % t
			cost := (t - remainder) % t
			if cost < minCost {
				minCost = cost
			}
		}
		fmt.Println(minCost)
	case 2:
		aTarget, bTarget := targets[0], targets[1]
		lcmAB := lcm(aTarget, bTarget)

		minA, minB, minAB := int64(1e18), int64(1e18),
			int64(1e18)
		for _, num := range a {
			costA := (aTarget - (num % aTarget)) % aTarget
			costB := (bTarget - (num % bTarget)) % bTarget
			costAB := (lcmAB - (num % lcmAB)) % lcmAB

			if costA < minA {
				minA = costA
			}
			if costB < minB {
				minB = costB
			}
			if costAB < minAB {
				minAB = costAB
			}
		}
		fmt.Println(min(minA+minB, minAB))
	case 3:
		aTarget, bTarget, cTarget := targets[0], targets[1], targets[2]
		lcmAB := lcm(aTarget, bTarget)
		lcmAC := lcm(aTarget, cTarget)
		lcmBC := lcm(bTarget, cTarget)
		lcmABC := lcm(lcmAB, cTarget)

		minA, minB, minC := int64(1e18), int64(1e18), int64(1e18)
		minAB, minAC, minBC, minABC := int64(1e18), int64(1e18), int64(1e18), int64(1e18)

		for _, num := range a {
			costA := (aTarget - (num % aTarget)) % aTarget
			costB := (bTarget - (num % bTarget)) % bTarget
			costC := (cTarget - (num % cTarget)) % cTarget
			costAB := (lcmAB - (num % lcmAB)) % lcmAB
			costAC := (lcmAC - (num % lcmAC)) % lcmAC
			costBC := (lcmBC - (num % lcmBC)) % lcmBC
			costABC := (lcmABC - (num % lcmABC)) % lcmABC

			if costA < minA {
				minA = costA
			}
			if costB < minB {
				minB = costB
			}
			if costC < minC {
				minC = costC
			}
			if costAB < minAB {
				minAB = costAB
			}
			if costAC < minAC {
				minAC = costAC
			}
			if costBC < minBC {
				minBC = costBC
			}
			if costABC < minABC {
				minABC = costABC
			}
		}

		options := []int64{
			minA + minB + minC,
			minAB + minC,
			minAC + minB,
			minBC + minA,
			minA + minBC,
			minB + minAC,
			minC + minAB,
			minABC,
		}

		minimal := options[0]
		for _, opt := range options {
			if opt < minimal {
				minimal = opt
			}
		}
		fmt.Println(minimal)
	}
}

func lcm(a, b int64) int64 {
	return a / gcd(a, b) * b
}

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func min(a, b int64) int64 {
	if a < b {
		return a
	}
	return b
}
