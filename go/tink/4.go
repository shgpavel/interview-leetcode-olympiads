package main

import (
	"fmt"
)

func getReshetoErat(n int) []int {
	primes := make([]bool, n+1)
	for i := 2; i <= n; i++ {
		primes[i] = true
	}

	for p := 2; p*p <= n; p++ {
		if primes[p] {
			for i := p * p; i <= n; i += p {
				primes[i] = false
			}
		}
	}

	var resResheto []int
	for p := 2; p <= n; p++ {
		if primes[p] {
			resResheto = append(resResheto, p)
		}
	}
	return resResheto
}

func findDivisors(n int) []int {
	var divisors []int
	for i := 1; i*i <= n; i++ {
		if n%i == 0 {
			divisors = append(divisors, i)
			if i != n/i {
				divisors = append(divisors, n/i)
			}
		}
	}
	return divisors
}

func main() {
	var left, right, ctr int
	fmt.Scan(&left, &right)

	primes := getReshetoErat(right)
	primes = append(primes, 1)

outer:
	for iter := left; iter <= right; iter++ {
		for _, pr := range primes {
			if iter == pr {
				continue outer
			}
		}

		l := len(findDivisors(iter))
		//fmt.Printf("%d %d\n", iter, l)
		for _, pr := range primes {
			if l == pr {
				ctr++
				break
			}
		}
	}
	fmt.Println(ctr)
}
