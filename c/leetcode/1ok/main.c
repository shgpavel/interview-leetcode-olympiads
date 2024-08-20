int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int* returned = malloc(8);
    *returnSize = 2;

    for (int i = 0; i < numsSize - 1; ++i) {
        for (int j = i + 1; j < numsSize; ++j) {
            if (nums[i] + nums[j] == target) {
                returned[0] = i;
                returned[1] = j;
            }
        }
    }

    return returned;
}
