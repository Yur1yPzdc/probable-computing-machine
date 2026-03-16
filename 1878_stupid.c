#include <stdlib.h>

int getSumOfNeighborsAtDist(int* gds, int* pds, int self, int w, int h, int r) { // counts down twice, forgets top
    int ans=0;
    int top=self-(r*w);
    int left=self-(r);
    int bot=self+(r*w);
    int right=self+(r);

    ans+=gds[bot]+gds[right]-gds[top]-gds[left];
    ans+=pds[bot]+pds[left]-pds[top]-pds[right];

    return ans;
}

int* getBiggestThree(int** items, int h, int* ww, int* sizeOfReturn) {
    int w=ww[0];
    int biggestFirst=-1e5, biggestSecond=-1e5, biggestThird=-1e5;
    int* gds = (int*)malloc(w*h*sizeof(int));
    if (gds==NULL) {
        return NULL;
    }
    int* pds = (int*)malloc(w*h*sizeof(int));
    if (pds==NULL) {
        free(gds);
        return NULL;
    }
    
    for (int dc=0; dc<(w+h-1); dc++) {
        int rg,cg;
        if (dc<w) {
            rg=0;
            cg=dc;
        } else {
            rg=(dc-w)+1;
            cg=0;
        }
        int sg=0,sp=0;
        while (rg<h && cg<w) {
            sg+=items[rg][cg];
            sp+=items[rg][w-cg-1];
            gds[rg*w+cg]=sg;
            pds[rg*w+w-cg-1]=sp;
            rg++; cg++;
        }
    }
    printf("Grid:\n");
    for (int i=0; i<w*h; i++) {
        if (i%w == 0) printf("\n");
        printf("%d ", items[i/w][i%w]);
    }
    
    for (int i=0; i<w*h; i++) {
        int x=i%w, y=i/w;
        int val = items[y][x];
        int maxForThisOne=val;

        int idxX=i%w, idxY=i/w;
        int distHor = ((w-idxX-1)>idxX) ? idxX : (w-idxX-1);
        int distVer = ((h-idxY-1)>idxY) ? idxY : (h-idxY-1);
        int maxR = (distVer>distHor) ? distHor : distVer;

        for (int j=1; j<=maxR; j++) {
            int plusTopMinusBot = items[y-j][x]-items[y+j][x];
            int sumAtREqualsJ = getSumOfNeighborsAtDist(gds, pds, i, w, h, j)+plusTopMinusBot; // read gSONAD comment
            maxForThisOne = (maxForThisOne<sumAtREqualsJ) ? sumAtREqualsJ : maxForThisOne;
        }

        if (biggestFirst==maxForThisOne || biggestSecond==maxForThisOne || biggestThird==maxForThisOne) {
        } else if (maxForThisOne>biggestFirst) {
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

    free(gds);
    free(pds);

    int ansQ[3]={biggestFirst,biggestSecond,biggestThird};
    int isChanged=0, al=0;
    for (int i=0; i<3; i++) {
        if (ansQ[i]!=(-1e5)) {
            isChanged+=(1<<i);
            al++;
        }
    }
    int qq=0;
    int* answer=(int*)malloc(al*sizeof(int));
    for (int i=0; i<3; i++) {
        int t=(isChanged>>i)%2;
        if (t) {
            answer[qq]=ansQ[i];
            qq++;
        }
    }
    *sizeOfReturn = al;
    return answer;
}

int main() {
    int w=3,h=1;
    int hh[1] = 3;
    int* itemsRows=NULL;

    itemsRows = (int*)malloc(h*sizeof(int)); 
    if (itemsRows==NULL) return -1;
    for (int i=0; i<h; i++) {
        itemsRows[i] = (int)malloc(w*sizeof(int));
        for (int j=0; j<w; j++) itemsRows[i][j]=7;
    }

    int* ans = getBiggestThree(itemsRows,w,hh,ans);
    if (ans==NULL) return -1;

    free(itemsRows);

    return 0;
}

