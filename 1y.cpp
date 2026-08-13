#include <iostream>
#include <vector>

int main() {
    int n, tmp;
	std::cin >> n;

    std::vector<int> trapsPos(n);
    std::vector<int> trapsLen(n);
    std::vector<int> trapsOch(n);
	for (int i=0; i<n; i++) {
		std::cin >> trapsPos[i];
	}

	for (int i=0; i<n; i++) {
		std::cin >> tmp;
		if (tmp==3) tmp=4;

		trapsLen[i] = tmp;
		if (tmp == 4 || tmp == 2) tmp++;
		trapsOch[i] = tmp;
	}

	for (int i=1; i<n; i++) { // validity check
		int lastEnd = trapsPos[i-1] + trapsLen[i-1];
		if (lastEnd >= trapsPos[i]) {
			std::cout << 0 << '\n';
			return 0;
		}
	}

	int m;
	std::cin >> m;

    std::vector<int> jPos(m);
    std::vector<int> jLen(m);
	for (int i=0; i<m; i++) {
		std::cin >> jPos[i];
	}
	for (int i=0; i<m; i++) {
		std::cin >> jLen[i];
	}

	for (int i=1; i<m; i++) {
		if (jPos[i] < jPos[i-1]+jLen[i-1]) {
			std::cout << 0 << '\n';
			return 0;
		}
	}

	int score = 0;
	int j=0;
	int ok;
	
	for (int i=0; i<n; i++) {
		while (j<m && jPos[j]+jLen[j] <= trapsPos[i]) j++;

		ok=0;

		if (j < m) {
			if (jPos[j] <= trapsPos[i] &&
					jPos[j]+jLen[j] >= trapsPos[i] + trapsLen[i]) {
				ok=1;
			}
		}

		if (ok==1) {
			score += trapsOch[i];
		} else {
			score--;
		}
	}

	if (score<0) score=0;

	std::cout << score << '\n';
	return 0;
}
