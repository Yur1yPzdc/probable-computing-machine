#include <math.h>

long long sumAndMultiply(int n) {
	long long ans=0;
	int s=0;
	int curr;
	int iter=0;
	while (n>0) {
		curr = n%10;
		if ( curr ) {
			s+=curr;
			ans += (long long) pow(10, iter) * curr;
			iter++;
		}

		n/=10;
	}
	
    return ans*s;
}
