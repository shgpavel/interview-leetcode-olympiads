package main

import (
	"fmt"
)

func passMask(window string, rChars string) bool {
	charMap := make(map[rune]int)
	for _, ch := range rChars {
		charMap[ch]++
	}

	for _, ch := range window {
		if charMap[ch] > 0 {
			charMap[ch]--
		}
	}

	for _, count := range charMap {
		if count > 0 {
			return false
		}
	}
	return true
}

func findPassword(mainStr string, rChars string, maxLen int) string {
	n := len(mainStr)
	bestSubstr := ""
	bestIndex := -1

	for left, right := 0, 0; right < n; right++ {
		window := mainStr[left : right+1]

		if len(window) > maxLen {
			left++
			window = mainStr[left : right+1]
		}

		if len(window) <= maxLen && passMask(window, rChars) {
			if (left > bestIndex) || (left == bestIndex && len(window) > len(bestSubstr)) {
				bestSubstr = window
				bestIndex = left
			}
		}
	}

	if bestSubstr == "" {
		return "-1"
	}
	return bestSubstr
}

func main() {
	var chars, mask string
	var winLen int
	fmt.Scan(&chars, &mask, &winLen)
	fmt.Println(findPassword(chars, mask, winLen))
}
