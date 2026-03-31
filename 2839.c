#include<stdio.h>
#include<stdbool.h>

bool canBeEqual(char* s1, char* s2) {
    for (int i=0; i<4; i++) {
        if ((s1[i]!=s2[i])&&(s1[i])!=s2[(i+2)%4]) return false;
    }
    bool b1, b2;
    b1 = (s1[0] ^ s1[2])==(s2[0] ^ s2[2]);
    b2 = (s1[1] ^ s1[3])==(s2[1] ^ s2[3]);
    return (b1&&b2);
}


int main() {
    char* s1="abcd";
    char* s2="cdab";
    char* ss1="abcd";
    char* ss2="dacb";
    printf("1: %d\n2: %d\n", canBeEqual(s1, s2), canBeEqual(ss1, ss2));
    return 0;
}
