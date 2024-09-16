package main

import (
	"fmt"
)

func main() {
	var numArg int
	fmt.Scan(&numArg)

	var slice []int
	for i := 0; i < numArg; i++ {
		var scannerV int
		fmt.Scan(&scannerV)
		slice = append(slice, scannerV)
	}
	//fmt.Println(slice)

	var skpdCtr, prevPos, snow int
	var iSpot []int
	result := 1
	for i, data := range slice {
		if data == -1 && (prevPos != 0 || slice[prevPos] != -1) {
			skpdCtr++
			iSpot = append(iSpot, i)
			continue
		}

		avail := slice[i] - slice[prevPos]
		if avail < i-prevPos {
			result = 0
			break
		}

		if len(iSpot) > 0 {
			for j := 0; j < len(iSpot); j++ {
				slice[iSpot[j]] = slice[prevPos] + j + 1
			}
			iSpot = nil
		}

		snow += data
		prevPos = i
	}

	for i, data := range slice {
		if data == -1 && i != 0 {
			slice[i] = slice[i-1] + 1
		}
	}

	if result == 1 {
		fmt.Println("YES")
		fmt.Printf("%d", slice[0])
		for i := 1; i < numArg; i++ {
			fmt.Printf(" %d", slice[i]-slice[i-1])
		}
		fmt.Printf("\n")
	} else {
		fmt.Println("NO")
	}
}
