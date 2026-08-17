#include <string>
#include <vector>

class Solution {
public:
	std::string longestPalindrome(std::string s) {
		int n = s.size();
		int nMod = n*2+3;

		std::string sMod;
		sMod.push_back('!');
		sMod.push_back('$');
		for (int i=2; i<nMod-1; i++) {
			if (i%2==1) sMod.push_back(s[i/2-1]);
			else sMod.push_back('$');
		}
		sMod.push_back('^');

		std::vector<int> paliRadius(nMod, 0);
		int center=0;
		int rightEdge=0;
		int mRad=0;
		int mRadIdx=0;

		for (int i=0; i<nMod; i++) {
			int mirror = center-(i-center);

			// Inside bigger pali
			if (i<rightEdge) {

				// Fully inside
				if (paliRadius[mirror] + i < rightEdge) {
					paliRadius[i] = paliRadius[mirror];
					continue;

				// Not fully => at least radius up to the border
				} else paliRadius[i] = rightEdge-i;
			}
			
			// Expanding paliRadius[i]
			while (i - (paliRadius[i]+1) >= 0 &&
					i + (paliRadius[i]+1) <nMod &&
					sMod[i+1+paliRadius[i]] == sMod[i-1-paliRadius[i]]) {

				paliRadius[i]++;
			}

			// Past bounds of rightEdge
			if (i+paliRadius[i] > rightEdge) {
				center=i;
				rightEdge = i+paliRadius[i];
			}

			// Update maxRadius
			if (paliRadius[i] > mRad) {
				mRad=paliRadius[i];
				mRadIdx=i;
			}
		}
		
		int normalStartIdx = (mRadIdx-mRad)/2;
		return s.substr(normalStartIdx, mRad);
    }
};
