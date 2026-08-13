#include <stdlib.h>
//#include <stdio.h>

int maxArea(int* height, int heightSize) {
	int mi, v;
	int vol=0;
    int a1=0;
    int a2=heightSize-1;
	int h1 = height[0];
	int h2 = height[a2];

	for (int i=0; i<heightSize-1; i++) {
        mi = (h1>h2) ? h2 : h1;	
		v = mi*abs(a1-a2);
        vol = (v>vol) ? v : vol;	
		//printf("a1: %d, a2: %d, minH: %d, volume: %d\n", a1, a2, mi, v);

		if (h1<h2) {
			h1 = height[++a1];
		} else {
			h2 = height[--a2];
		}
	}
	return vol;
}
