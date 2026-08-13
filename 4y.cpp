#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <cstdint>

#define int long long

static uint64_t rnd64() {
    uint64_t r=0;
    for (int i=0; i<5; i++) {
        r = (r<<15) ^ (uint64_t)rand();
    }
    return r;
}

signed main() {

    srand((unsigned)time(0));

	int n=40;
    std::vector<int> a(n);

	for (int i=0; i<40; i++) std::cin >> a[i];

    int lHalf = n/2;
    int rHalf = n-lHalf; // rHalf = 20 = lHalf

    int lSize = 1LL << lHalf;
    int rSize = 1LL << rHalf;

    std::vector<int> lSums(lSize, 0);
    std::vector<int> rSums(rSize, 0);

    for (int i=0; i<20; i++) {
        int predel = 1LL << i;
        for (int mask=0; mask<predel; mask++) {
            lSums[mask | (1LL << i)] = lSums[mask] + a[i];
            rSums[mask | (1LL << i)] = rSums[mask] + a[lHalf+i];
        }
    }

	std::unordered_map<int, int> seen;
    seen.reserve((size_t) 2e6);

    int allMask = 0;
    for (int i=0; i<n; i++) allMask |= (1LL << i);

    while (1) {
        int m1 = (int)(rnd64() % (uint64_t)lSize);
        int m2 = (int)(rnd64() % (uint64_t)rSize);

        int full = m1 | (m2 << lHalf);
        if (full == 0) continue;

        int sum = lSums[m1] + rSums[m2];

        auto it = seen.find(sum);
        if (it == seen.end()) {
            seen[sum] = full;
            continue;
        }

        int other = it->second;
        if (other == full) continue;

        int s1 = other & (allMask ^ full);
        int s2 = full & (allMask ^ other);

        if (s1 == 0 || s2 == 0) continue;

        std::vector<int> out1;
        std::vector<int> out2;

        for (int i=0; i<n; i++) {
            if (((s1 >> i) & 1LL) != 0) {
                out1.push_back(i + 1);
            }
            if (((s2 >> i) & 1LL) != 0) {
                out2.push_back(i + 1);
            }
        }

        std::cout << (int) out1.size() << '\n';
        for (int i=0; i<(int) out1.size(); i++) {
            if (i!=0) std::cout << ' ';
            std::cout << out1[i];
        }
        std::cout << '\n';

        std::cout << (int) out2.size() << '\n';
        for (int i=0; i<(int) out2.size(); i++) {
            if (i!=0) std::cout << ' ';
            std::cout << out2[i];
        }
        std::cout << '\n';

        return 0;
    }
}
