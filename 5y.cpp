#include <functional>
#include <iostream>
#include <vector>

#define int long long

signed main() {
	int n;
	std::cin >> n;

	std::vector<int> wei(n+1);
	for (int i=1; i<=n; i++) {
		std::cin >> wei[i];
	}

	std::vector<int> prefix(n+1, 0);
	for (int i=1; i<=n; i++) {
		prefix[i] = prefix[i-1] + wei[i];
	}

	auto sumWei = [&](int l, int r) {
		if (l>r) return 0LL;
		return prefix[r] - prefix[l-1];
	};

	int m=n+2;

	auto id = [&](int l, int r) {
		return l*m + r;
	};

	int maksimum = (long long) (4e18);

	std::vector<int> dp((size_t)(m*m), 0);
	std::vector<int> rootsBegin((size_t)(m*m), 0);
	std::vector<int> rootsLen((size_t)(m*m), 0);
	std::vector<int> roots;
	roots.reserve(1e6);

	for (int i=1; i <= n+1; i++) {
		dp[(size_t) id(i, i-1)] = 0;
	}

	for (int length=1; length<=n; length++) {
		for (int l=1; l+length <= n+1; l++) {
			int r = l+length-1;
			int add = sumWei(l, r);
			int best = maksimum;

			int begin = (int)roots.size();

			for (int k=l; k<=r; k++) {
				int value = dp[(size_t) id(l, k-1)] +
					dp[(size_t) id(k+1, r)] + add;
				if (value < best) {
					best = value;
					roots.resize((size_t) begin);
					roots.push_back(k);
				} else if (value == best) {
					roots.push_back(k);
				}
			}

			dp[(size_t) id(l,r)] = best;
			rootsBegin[(size_t) id(l,r)] = begin;
			rootsLen[(size_t) id(l,r)] = (int)roots.size() - begin;
		}
	}

	std::vector<int> cnt((size_t) m*m,0);
	for (int i=1; i<=n+1; i++) cnt[(size_t) id(i, i-1)] = 1;

	for (int length=1; length<=n; length++) {
		for (int l=1; l+length <= n+1; l++) {
			int r=l+length-1;
			int ways = 0;

			int start = rootsBegin[(size_t) id(l,r)];
			int c = rootsLen[(size_t) id(l,r)];

			for (int t=0; t<c; t++) {
				int k = roots[(size_t) (start+t)];
				ways += cnt[(size_t) id(l,k-1)] * 
					cnt[(size_t) id(k+1,r)];
			}
			cnt[(size_t) id(l,r)] = ways;
		}
	}

	int k = cnt[(size_t) id(1,n)];
	std::cout << k << '\n';

	std::vector<int> out(n);

	std::function<void(int, int, int, int)> createAns = [&] (int l, int r, int idx, int pos) {
		if (l>r) return;

		int start = rootsBegin[(size_t) id(l,r)];
		int c = rootsLen[(size_t) id(l,r)];

		for (int t=0; t<c; t++) {
			int root = roots[(size_t) (start+t)];
			int left = cnt[(size_t) id(l, root-1)];
			int right = cnt[(size_t) id(root+1, r)];

			int total = left*right;

			if (idx >= total) {
				idx -= total;
				continue;
			}
			out[(size_t) pos] = root;

			int idxL=0;
			int idxR=0;

			if (right!=0) {
				idxL = idx/right;
				idxR = idx%right;
			}

			createAns(l, root-1, idxL, pos+1);
			createAns(root+1, r, idxR, (pos+1)+(root-l));
			return;
		}
	};

	for (int i=0; i<k; i++) {
		createAns(1, n, i, 0);

		for (int j=0; j<n; j++) std::cout << out[(size_t) j] << ' ';
		std::cout << '\n';
	}

	return 0;
}
