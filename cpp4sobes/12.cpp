#include <string>
#include <vector>

class Solution {
public:
	std::string intToRoman(int num) {
		std::vector<std::string> s(4);
		int n;
		int iter=0;
		char q[] = {'I','V','X','L','C','D','M'};
		while (num) {
			n = num%10;
			num/=10;

c:
			if (n==0) {
			} else if (n<4) {
				for (int j=0; j<n; j++) s[iter].push_back(q[2*iter]);
			} else if (n==4) {
				s[iter].push_back(q[2*iter]);
				s[iter].push_back(q[1+2*iter]);
			} else if (n==9) {
				s[iter].push_back(q[2*iter]);
				s[iter].push_back(q[2+2*iter]);
			} else {
				s[iter].push_back(q[1+2*iter]);
				n-=5;
				goto c;
			}
			iter++;
		}

		std::string ans;
		for (int i=s.size()-1; i>=0; i--) {
			for (auto x : s[i]) ans.push_back(x);
		}
		return ans;
    }
};
