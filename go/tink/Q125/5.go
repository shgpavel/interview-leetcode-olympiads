package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	var in *bufio.Reader
	var out *bufio.Writer

	in = bufio.NewReader(os.Stdin)
	out = bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n int
	var s int64
	fmt.Fscan(in, &n, &s)

	a := make([]int64, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(in, &a[i])
	}

	prefix := make([]int64, n+1)
	for i := 1; i <= n; i++ {
		prefix[i] = prefix[i-1] + a[i-1]
	}

	var cuts int64

	for k := 1; k <= n-1; k++ {
		x := prefix[k] - s
		y := prefix[k+1] - s

		var left int64
		if x < 0 {
			left = 0
		} else if x > int64(k-1) {
			left = int64(k - 1)
		} else {
			left = x
		}

		pos := sort.Search(n+1, func(p int) bool {
			return prefix[p] >= y
		})

		right := int64(pos - 1)
		if right > int64(k-1) {
			right = int64(k - 1)
		}

		if right < left {
			continue
		}

		count := right - left + 1
		cuts += count * int64(n-k)
	}

	total := int64(n*(n+1)/2) + cuts
	fmt.Println(total)
}
