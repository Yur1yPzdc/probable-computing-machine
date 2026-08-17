#include <algorithm>
#include <vector>

class Solution {
public:
    int stoneGameV(std::vector<int>& stoneValue) {
        if (stoneValue.size()==1) return 0;

		int n=stoneValue.size();
		std::vector<int> prefix(n+1, 0);
		for (int i=0; i<n; i++) 
			prefix[i+1] = stoneValue[i] + prefix[i];

		std::vector<std::vector<int>> subPts(n, std::vector<int>(n,0));

		int r, s, lS;
		for (int delta=2; delta<=n; delta++) {
			for (int l=0; l+delta-1<n; l++) {
				r = l+delta-1;
				
				s = prefix[r+1] - prefix[l];
				
				for (int k=l; k<r; k++) { // where to split
					lS = prefix[k+1] - prefix[l];

					if (lS<s-lS) subPts[l][r] = std::max(subPts[l][r], subPts[l][k]+lS);
					else if (lS>s-lS) subPts[l][r] = std::max(subPts[l][r], subPts[k+1][r]+s-lS);
					else subPts[l][r] = std::max(subPts[l][r], lS+std::max(subPts[l][k], subPts[k+1][r]));
				}
			}
		}

		return subPts[0][n-1];
    }
};
