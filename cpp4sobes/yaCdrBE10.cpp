#include <algorithm>
#include <iostream>
#include <vector>

#define int long long

signed main() {
	int n;
	std::cin >> n;

	std::vector<int> vals(n+1);
	for (int i=0; i<n; i++) {
		std::cin >> vals[i];
	}
	vals[n]=0;

	int mArea=0;
	std::vector<int> s;
	for (int i=0; i<=n; i++) {
		while (!s.empty() && vals[i]<vals[s.back()]) {
			int p = s.back();
			s.pop_back();

			int h = vals[p];

			int left = (!s.empty()) ? s.back() : -1;

			int w = i-left-1;
			mArea = std::max(mArea, w*h);
		}
		s.push_back(i);
	}

	std::cout << mArea << '\n';

	return 0;

}
