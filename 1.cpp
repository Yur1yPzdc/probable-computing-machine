#include<stdio.h>
#include<unordered_map>
#include<vector>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        int el, tgtIdx, zeroth;
        std::vector<int> ans;
        std::unordered_map<int, int> m;

        zeroth = nums[0];
        m[zeroth] = 1;

        int l = nums.size();
        for (int i=1; i<l; i++) {
            el = nums[i];
            tgtIdx = m[target-el];
            //printf("%d \n", tgtIdx);

            if (tgtIdx != 0) {
                ans.push_back(tgtIdx-1);
                ans.push_back(i);
                //printf("done\n\n");
                return ans;
            }
            m[el] = i+1;
        }
        //printf("done\n\n");
        return {-1, -1};
    }
};

int main() {
    Solution s;
    std::vector<int> n1 {2,7,11,15};
    std::vector<int> n2 {3,2,4};
    std::vector<int> n3 {3,3};

    int t1=9, t2=6, t3=6;

    std::vector<int> a1 = s.twoSum(n1, t1);
    printf("%d, %d\n", a1[0], a1[1]);
    std::vector<int> a2 = s.twoSum(n2, t2);
    printf("%d, %d\n", a2[0], a2[1]);
    std::vector<int> a3 = s.twoSum(n3, t3);
    printf("%d, %d\n", a3[0], a3[1]);
}
