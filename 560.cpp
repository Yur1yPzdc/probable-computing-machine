// сделай префиксные, потом сделай аналогично 1.cpp, храни не индекс а колво

#include<vector>
#include<unordered_map>
#include<stdio.h>

class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k) {
        int ans=0;
        std::unordered_map<int, int> pf;
        pf[0]=1;

        int currSum, prevSum=0;
        int lengthOfNums = nums.size();
        for (int i=0; i<lengthOfNums; i++) {
            int curr = nums[i];
            currSum = prevSum + curr; 

            int howMany = pf[-k+currSum];
            ans+=howMany;
            //printf("idx: %d, ans: %d\n",i, ans);

            pf[currSum] += 1;
            //printf("cs: %d, target: %d, howMany: %d\n",currSum,k-currSum,howMany);
            
            prevSum += curr;
        }
        // это обычные префиксные, но т.к. полный аррэй валидный вариант, то нужен 0 в начале
        
        
        return ans;
    }
};


int main() {
    Solution s;
    std::vector<int> n1 {1,1,1};
    std::vector<int> n2 {3,2,1};

    int t1=2, t2=3;

    int a1 = s.subarraySum(n1, t1);
    printf("%d\n", a1);
    int a2 = s.subarraySum(n2, t2);
    printf("%d\n", a2);
}
