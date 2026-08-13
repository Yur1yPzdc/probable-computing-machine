#include <deque>
#include <vector>
// #include <stdio.h>

class Solution {
public:
	std::vector<int> remainingMethods(int n, int k, std::vector<std::vector<int>>& invocations) {

		std::vector<std::vector<int>> out(n), in(n);
        for (const auto& e : invocations) {
            out[e[0]].push_back(e[1]);
            in[e[1]].push_back(e[0]);
        }

		int anyOutsideInvokes = 0;
		std::vector<int> sus(n, 0); // first none are visited

		std::deque<int> q = {k}; // whose invocs to see (only fresh)
		sus[k] = 1;
		while (!q.empty()) {
			int i = q.front(); // clone first one
			q.pop_front(); // delete from queue
			if (sus[i] != 2) sus[i]=1; // if being processed => bugged
			 // printf("Visiting %d\n", i);

			for (auto v : out[i]) {
				if (sus[v] == 0) {
					sus[v] = 1;
					q.push_back(v);
				}
			}
		}

		for (auto e : invocations) {
			int invoker = e[0];
			int invoked = e[1];
			if (sus[invoker] == 0 && sus[invoked] ==1) {
				anyOutsideInvokes = 1;
				break;
			}
		}

		std::vector<int> a;
		if (!anyOutsideInvokes) {
			// printf("No outside invokers. Removing group, returning ok\n");
			for (int i=0; i<n; i++) if (sus[i] == 0) a.push_back(i);
		} else {
			// printf("Outside invokers exist. Removing none\n");
			for (int i=0; i<n; i++) a.push_back(i);
		}

		return a;
    }
};
