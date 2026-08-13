#include <stdio.h>

int trap(int* height, int heightSize) {
    int lebeg=0;
	int riman=0;
	int upperLimitForLebeg=0;
	int c;

	for (int i=0; i<heightSize; i++) {
		c=height[i];
		riman+=c;
		if (upperLimitForLebeg<c) upperLimitForLebeg=c;
	}
    printf("riman:%d\n", riman);
	
	int h=1;
	int l=0;
	int r=heightSize-1;
	int ll=height[l];
	int rr=height[r];

	while (l<=r && h<=upperLimitForLebeg) {
		printf("l: %d, r: %d, ll: %d, rr:%d\n", l, r, ll, rr);
		if (ll>=h && rr>=h) {
			h++;
			lebeg += (1+r-l);
			printf("level %d lebeg: %d\n", h-1, 1+r-l);
		} else { 
			if (ll<h) ll=height[++l];
			else if (rr<h) rr=height[--r];
		}
	}
	return lebeg-riman;
}
