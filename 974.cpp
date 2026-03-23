// ну храни как в 560 но остатки от деления а не чиселки
// сделай префиксные, потом сделай аналогично 1.cpp, храни не индекс а колво

#include<vector>
#include<unordered_map>
#include<stdio.h>

class Solution {
public:
    int subarraysDivByK(std::vector<int>& nums, int k) {
        int ans=0;
        std::unordered_map<int, int> pf;
        pf[0]=1;

        int currSum, prevSum=0;
        int lengthOfNums = nums.size();
        for (int i=0; i<lengthOfNums; i++) {
            int curr = nums[i];
            currSum = ((prevSum+curr)%k + k)%k; 

            int target = currSum;
            int howMany = pf[target];
            ans+=howMany;

            pf[currSum] += 1;
            printf("idx: %d, self: %d ",i,curr);
            printf("cs: %d, target: %d, howMany: %d ",currSum,target,howMany);
            printf("ans: %d\n",ans);
            
            prevSum = currSum;
        }
        // это обычные префиксные, но т.к. полный аррэй валидный вариант, то нужен 0 в начале
        
        
        return ans;
    }
};


int main() {
    Solution s;
    std::vector<int> n1 {4,5,0,-2,-3,1};
    std::vector<int> n2 {5};

    int t1=5, t2=9;

    int a1 = s.subarraysDivByK(n1, t1);
    printf("%d\n", a1);
    int a2 = s.subarraysDivByK(n2, t2);
    printf("%d\n", a2);
}
