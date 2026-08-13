#include <iostream>
#include <vector>
#include <string>

signed main() {
	int h, w;
	std::cin >> h;
	std::cin >> w;

	std::vector<char> grid;
	grid.resize(h*w);

	std::vector<int> length(w, 0);

	for (int row=0; row<h; row++) {
		std::string s;
		std::cin >> s;

		if ((int)s.size() == w) {
			for (int col=0; col<w; col++) {
				char c = s[col];
				grid[col + row*w] = c;

				if (c=='0') length[col]++;
			}
		} else {
			grid [row*w] = s[0];
			if (s[0] == '0') length[0]++;

			for (int col=1; col<w; col++) {
				std::cin >> s;
				char c = s[0];
				grid[row*w + col] = c;

				if (c=='0') length[col]++;
			}
		}
	}

	std::vector<int> start(w+1, 0);
	for (int c=0; c<w; c++) {
		start[c+1] = start[c] + length[c];
	}

	int tot = start[w];
	std::vector<int> pos(tot, 0);
	std::vector<int> ptr(w, 0);

	for (int c=0; c<w; c++) {
		ptr[c] = start[c];
	}

	for (int r=h-1; r>=0; r--) {
		int y=h-1-r;
		for (int c=0; c<w; c++) {
			if (grid[r*w + c] == '0') {
				int idx=ptr[c];
				pos[idx] = y;
				ptr[c] = idx+1;
			}
		}
	}

	std::vector<int> sand = length;
	std::vector<int> done(w,0);

	auto height = [&] (int c) {
		if (sand[c] == 0) {
			return 0;
		}
		if (done[c]) {
			return sand[c];
		}
		int idx = start[c] + sand[c]-1;
		return pos[idx]+1;
	};

	for (int i=0; i<w; i++) {
		done[i] = 1;
		int curr = sand[i];

		if (i<w-1) {
			int r=i+1;
			while (1) {
				int hr = height(r);
				if (hr <= curr+1) break;
				
				sand[r]--;
				curr++;
			}
		}
		
		if (i>=1) {
			int l=i-1;
			int hl = sand[l];
			
			if (hl-1 > curr) {
				int t = (hl-curr)/2;
				sand[l] -= t;
				curr+=t;
			}
		}

		sand[i] = curr;
	}

	for (int r=0; r<h; r++) {
		int y = h-1-r;
		for (int c=0; c<w; c++) {
			char q = '-';
			if (sand[c] > y) q='0';
			if (c!=0) std::cout << ' ';
			std::cout << q;
		}
		std::cout << '\n';
	}

	return 0;
}
