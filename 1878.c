#include <stdlib.h>
#include <stdio.h>

int getSumOfNeighborsAtDist(int* gds, int* pds, int self, int w, int h, int r) { // counts corners twice
    int top=self-(r*w);
    int left=self-(r);
    int bot=self+(r*w);
    int right=self+(r);
    int ans=0;

    ans+=gds[bot]+gds[right]-gds[top]-gds[left];
    ans+=pds[bot]+pds[left]-pds[top]-pds[right];

    printf("for idx %d sum at R=%d is %d\n", self, r, ans);
    return ans;
}

void getBiggestThree(int* items, int w, int h, int* whereToReturn) {
    int biggestFirst=-1, biggestSecond=-1, biggestThird=-1;
    int* gds = (int*)malloc(w*h*sizeof(int));
    if (gds==NULL) {
        whereToReturn=NULL;
        return;
    }
    int* pds = (int*)malloc(w*h*sizeof(int));
    if (pds==NULL) {
        whereToReturn=NULL;
        free(gds);
        return;
    }
    
    for (int dc=0; dc<(w+h-1); dc++) {
        int rg,cg;
        if (dc<w) {
            rg=0;
            cg=dc;
        } else {
            rg=dc-w+1;
            cg=0;
        }
        int sg=0,sp=0;
        while (rg<h && cg<w) {
            sg+=items[rg*w+cg];
            sp+=items[rg*w+w-cg-1];
            gds[rg*w+cg]=sg;
            pds[rg*w+w-cg-1]=sp;
            rg++; cg++;
        }
    }

    for (int i=0; i<w*h; i++) {
        int val = items[i];
        int maxForThisOne=val;

        int idxX=i%w, idxY=i/w;
        int distHor = ((w-idxX-1)>idxX) ? idxX : (w-idxX-1);
        int distVer = ((h-idxY-1)>idxY) ? idxY : (h-idxY-1);
        int maxR = (distVer>distHor) ? distHor : distVer;

        printf("for idx %d maxR=%d, current max=%d\n", i, maxR, val);

        for (int j=1; j<=maxR; j++) {
            int sumAtREqualsJ = getSumOfNeighborsAtDist(gds, pds, i, w, h, j)
                -items[i-j*w]-items[i-j]-items[i+j*w]-items[i+j]; // minus corners counted twice
            maxForThisOne = (maxForThisOne<sumAtREqualsJ) ? sumAtREqualsJ : maxForThisOne;
        }

        printf("for idx %d max after rhombus=%d\n", i, maxForThisOne);

        if (maxForThisOne>biggestFirst) {
            biggestThird=biggestSecond;
            biggestSecond=biggestFirst;
            biggestFirst=maxForThisOne;
        } else if (maxForThisOne>biggestSecond) {
            biggestThird=biggestSecond;
            biggestSecond=maxForThisOne;
        } else if (maxForThisOne>biggestThird) {
            biggestThird=maxForThisOne;
        }
    }
    whereToReturn[0] = biggestFirst;
    whereToReturn[1] = biggestSecond;
    whereToReturn[2] = biggestThird;
}

int main() {
    int w=4,h=3;
    int* items=NULL;

    items = (int*)malloc(w*h*sizeof(int)); // row1 - row2 - row3
    if (items==NULL) return -1;

    for (int i=0; i<w*h; i++) items[i]=1;
    items[1]=2;

    int ans[3];

    getBiggestThree(items,w,h,ans);
    if (ans==NULL) return -1;

    printf("%d %d %d\n", ans[0],ans[1],ans[2]);

    return 0;
}
