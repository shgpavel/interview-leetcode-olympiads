package main

import (
	"bufio"
	"fmt"
	"os"
)

func checkStr(s string) string {
	binStk := 0
	for _, ltr := range s {
		switch ltr {
		case 'R':
			binStk += 1
		case 'M':
			if binStk > 0 {
				binStk -= 1
			} else {
				return "No"
			}
		}
	}
	return "Yes"
}

func main() {
	var in *bufio.Reader
	var out *bufio.Writer

	in = bufio.NewReader(os.Stdin)
	out = bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var inS string
	fmt.Fscan(in, &inS)
	fmt.Fprint(out, checkStr(inS)+"\n")
}
