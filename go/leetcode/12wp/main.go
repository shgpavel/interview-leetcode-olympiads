package main

import (
	"fmt"
)

func intToRoman(num int) string {
	ret := ""
	intr := map[int]string{
		1:    "I",
		5:    "V",
		10:   "X",
		50:   "L",
		100:  "C",
		500:  "D",
		1000: "M",
	}

	for num > 0 {

	}

	/*
		for ctr := 0; num > 0; num /= 10; ctr++ {
			ld := num % 10
			switch ctr {
			case 0:
				switch ld {
				case < 5:
					for i := 0; i < ld; i++ {
						ret += intr[1]
					}
				case >= 5:
					ret += intr[5]
					for i := 5; i < ld; i++ {
						ret += intr[1]
					}


				}
			}
		}
	*/
	return ret
}

func main() {
	fmt.Println(intToRoman(10))
}
