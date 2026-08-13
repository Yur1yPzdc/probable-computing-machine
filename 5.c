#include <stdlib.h>
#include <string.h>
char* longestPalindrome(char* s) {
	// use Manacher's
    
	int n = strlen(s);
	int tLen = 2*n+4;
	
	char* transformedS = malloc(sizeof(char) * tLen);
	transformedS[0] = '^';
	transformedS[1] = '#';
    for (int i = 0; i < n; i++) {
        transformedS[2 * i + 2] = s[i];
        transformedS[2 * i + 3] = '#';
    }
    transformedS[2 * n + 2] = '$';
    transformedS[2 * n + 3] = '\0';

	int* P = calloc(tLen, sizeof(int)); // array of radiuses, all 0 for now
	int c=0, r=0; 
	// c = rightmost found pali center. always <= i
	// r = c's right boundary
	for (int i=1; i<tLen-1; i++) { // treat i as new palindrome center
		int mirror = 2*c-i; // mirror index of i relative to c (in transformedS)

		if (i<r) { // inside of known pali
			P[i] = (r-i < P[mirror]) ? (r-i) : P[mirror]; 
			// (radius at i) is at least (radius at mirror)
		} else P[i]=0; // 

		while (transformedS[i+P[i]+1] == transformedS[i-P[i]-1]) P[i]++; // if char same as mirror char, grow pali radius

		if (i+P[i] > r) {
			c=i; // new center
			r=i+P[i]; // right bound
		}
	}

	int maxLen=0, center=0;
	for (int i=1; i<tLen-1; i++) {
		if (P[i] > maxLen) {
			maxLen = P[i];
			center = i;
		}
	}

	int startOrig = (center - maxLen - 1)/2;
	int endOrig = startOrig + maxLen - 1;
	char* res = malloc(sizeof(char) * (maxLen+1));
	for (int i=0; i<maxLen; i++) res[i] = s[startOrig+i];
	res[maxLen] = '\0';

	free(transformedS); free(P);

	return res;
}
