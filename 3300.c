int getDigSum(int num) {
    int ans = 0;
    do {
        ans+=num%10;
        num/=10;
    } while (num>0);
    return ans;
}

int minElement(int* nums, int numsSize) {
    int s;
    int min = 10000;
    for (int i=0; i<numsSize; i++) {
        s = getDigSum(nums[i]);
        min = (min>=s) ? s : min;
    }
    return min;
}
