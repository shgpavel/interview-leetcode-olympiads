package main

import (
	"bufio"
	"fmt"
	"os"
)

const MOD int64 = 998244353

func main() {
	var in *bufio.Reader
	var out *bufio.Writer

	in = bufio.NewReader(os.Stdin)
	out = bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n, k int
	fmt.Fscan(in, &n, &k)

	a := make([]int64, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(in, &a[i])
	}
	s := make([]int64, k+1)
	s[0] = int64(n) % MOD
	for m := 1; m <= k; m++ {
		s[m] = 0
	}

	for _, ai := range a {
		powA := int64(1)
		current := ai % MOD
		for m := 1; m <= k; m++ {
			powA = powA * current % MOD
			s[m] = (s[m] + powA) % MOD
		}
	}

	maxP := k
	fact := make([]int64, maxP+1)
	fact[0] = 1
	for i := 1; i <= maxP; i++ {
		fact[i] = fact[i-1] * int64(i) % MOD
	}

	invFact := make([]int64, maxP+1)
	invFact[maxP] = powMod(fact[maxP], MOD-2)
	for i := maxP - 1; i >= 0; i-- {
		invFact[i] = invFact[i+1] * int64(i+1) % MOD
	}

	pow2 := make([]int64, k+1)
	pow2[0] = 1
	for p := 1; p <= k; p++ {
		pow2[p] = pow2[p-1] * 2 % MOD
	}

	inv2 := powMod(2, MOD-2)
	for p := 1; p <= k; p++ {
		var sTotal int64
		for m := 0; m <= p; m++ {
			if m > p || (p-m) > k {
				continue
			}
			c := fact[p] * invFact[m] % MOD
			c = c * invFact[p-m] % MOD
			sm := s[m]
			spm := s[p-m]
			term := c * sm % MOD
			term = term * spm % MOD
			sTotal = (sTotal + term) % MOD
		}
		sumDoubles := pow2[p] * s[p] % MOD
		temp := (sTotal - sumDoubles) % MOD
		if temp < 0 {
			temp += MOD
		}
		fp := temp * inv2 % MOD
		fmt.Println(fp)
	}
}

func powMod(a, exponent int64) int64 {
	res := int64(1)
	a = a % MOD
	for exponent > 0 {
		if exponent%2 == 1 {
			res = res * a % MOD
		}
		a = a * a % MOD
		exponent /= 2
	}
	return res
}
