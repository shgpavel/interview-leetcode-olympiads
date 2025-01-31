#include <stdio.h>
#include <stddef.h>

int calcArea(int *left, int *right) {
	int min = (*left < *right) ? *left : *right;
	ptrdiff_t lower = right - left;
	return min * (int)lower;
}

int maxArea(int *height, int heightSize) {
	int *left = height,
		 *right = height + heightSize - 1;
	int area = calcArea(left, right);
	
	while (left < right) {
		area = calcArea(left, right);
		if ((*left < *(left + 1))
		&& area <= calcArea(left + 1, right)) {
			++left;
		}
		else if ((*right < *(right - 1))
					&& area <= calcArea(left, right - 1)) {
			--right;
		} else {
			break;
		}
	}

	return area;
}
