#include<stdio.h>

#define OFFSET 48

int hhmmToMinutes(char* s);

int findMinDifference(char** timePoints, int timePointsSize) {
    int ans=2000;
    int idx, idxWasMet;

    char buf[270];
    for (int i=0; i<270; i++) buf[i]='\0';

    for (int i=0; i<timePointsSize; i++) {
        int timeStamp=hhmmToMinutes(timePoints[i]);
        idx=timeStamp/8;
        idxWasMet=(timeStamp%8);

        unsigned char status = ((buf[idx]>>idxWasMet)%2);
        printf("stamp: %s, status: %d\n", timePoints[i],status);

        if (status=='\0') buf[idx] = buf[idx] | ('\1'<<idxWasMet);
        else if (status!='\0') return 0;
        
        if (idx<90) {
            if (status=='\0') buf[idx+180] = buf[idx];
        }
    }

    for (int i=0; i<270; i++) if (buf[i]!='\0') printf("idx: %d, val: %d\n",i,(unsigned char)buf[i]);

    int delta;
    int prev=-1;
    for (int i=0; i<270; i++) {
        for (int j=0; j<8; j++) {
            int curr = (( (unsigned char)(buf[i]) )>>j)%2;
            if (prev==-1 && curr==1) {
                prev=i*8+j; 
                printf("stamp: %d, ",i*8+j);
                printf("prev set\n");
            } else if (curr==1) {
                delta = i*8+j-prev;
                printf("stamp: %d, ",i*8+j);
                printf("prev: %d, delta: %d\n",prev,delta);
                ans = (ans>delta) ? delta : ans;
                prev=i*8+j; 
            }
        }
    }
    return ans;
}

int hhmmToMinutes(char* s) {
    int hr = 10*((int)(s[0]-OFFSET)) + ((int)(s[1]-OFFSET));
    int mn = 10*((int)(s[3]-OFFSET)) + ((int)(s[4]-OFFSET));
    return hr*60+mn;
}

int main() {
    char *c[] = {"02:15", "21:10", "02:15"};
    int s = 3;
    findMinDifference(c, s);

    return 0;
}
