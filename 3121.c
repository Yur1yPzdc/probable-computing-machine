#include <stdio.h>

int numberOfSpecialChars(char* word) {
	int buf[123]; // only lowercase & uppercase
	for (int i=0; i<123; i++) buf[i] = 999999;

	int cnt=0;
	int ans=0;
    char curr=word[cnt];
	while (curr != '\0') {
		printf("letter: %c\n", curr);
		if (curr>='a') {    // lowercase english letter
			printf("lower\n");
			if (buf[curr-32]!=999999 && (buf[curr]==999999 || buf[curr]<buf[curr-32])) { // first occurence after uppercase
				printf("met after upper: %c\n", curr);
				ans--;
				if (buf[curr]==999999) ans++;
			}
			buf[curr] = cnt; // update last found occasion lowercase
		} else { // uppercase english letter
			printf("upper\n");
			if (buf[curr]==999999 && buf[curr+32]!=999999) { // first occasion of uppercase
				printf("first upper: %c\n", curr);
				ans++;
			}
			if (buf[curr]==999999) buf[curr] = cnt; // dont update last found occasion lowercase
		}
		curr = word[cnt++];
	}
	return ans;
}


int main() {
	char* w1 = "abc";
	char* w2 = "dDDadDddCE";
	//printf("TESTING: %c, %c\n", 122-25, 122-25-32);
	//printf("%s: %d\n", w1, numberOfSpecialChars(w1));
	printf("%s: %d\n", w2, numberOfSpecialChars(w2));
	return 0;
}
