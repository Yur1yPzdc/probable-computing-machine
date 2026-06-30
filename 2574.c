/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

//#include <stdio.h>
#include <stdlib.h>

int* leftRightDifference(int* nums, int numsSize, int* returnSize) {
	*returnSize = numsSize;
    int sum=0;
    int sumR=0;
    for (int i=0; i<numsSize; i++) sum+=nums[i];
    int* ans = malloc(numsSize * sizeof(int));
    ans[0] = sum-nums[0];
    //printf("%d ", ans[0]);
    for (int i=1; i<numsSize; i++) {
        sumR+=nums[i-1];
        ans[i] = abs(sum-nums[i]-sumR*2);
        //printf("%d ", ans[i]);
    }
    //for (int i=0; i<numsSize; i++) printf("%d ", ans[i]);
    return ans;
}

int main() {
	int nums1[4] = {10,4,8,3};
	int nums2[1] = {1};
    return 0;
}
