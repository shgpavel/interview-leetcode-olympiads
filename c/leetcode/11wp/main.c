/*
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7].
In this case, the max area of water (blue section) the container can contain is 49.

Input: height = [1,1]
Output: 1

*/

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
	int area, max = calcArea(left, right);
	
	for (size_t i = 0; left < right && i < 2 * (size_t)heightSize; ++i) {
		//printf("%d %d   %d\n", *left, *right, max);

		for (int *j = left; j < right; ++j) {
			area = calcArea(j, right);
			max = max < area ? area : max;
		}
		for (int *j = right; j > left; --j) {
			area = calcArea(left, j);
			max = max < area ? area : max;
		}

		if (i < (size_t)heightSize) {
			++left;
		} else {
			--right;
		}
	}
	
	return max;
}

int main() {
	//int a[10] = {1, 1};
	//int a[10] = {2,3,4,5,18,17,6};
	int a[10] = {1,8,6,2,5,4,8,3,7};
	//printf("%d\n", maxArea(a, 2));
	//printf("%d\n", maxArea(a, 7));
	printf("%d\n", maxArea(a, 9));
	
	return 0;
}
