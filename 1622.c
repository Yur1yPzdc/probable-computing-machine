#include <stdlib.h>
#include <stdio.h>

#define MOD (long long)(1e9+7)

long long modPow(long long base, long long exp) {
    long long res=1;
    base%=MOD;

    while (exp>0) {
        if (exp&1) res=res*base%MOD;
        base=base*base%MOD;
        exp>>=1;
    }
    return res;
}
long long modInv(long long x) {
    return modPow(x, MOD-2);  
}
// from neuro using little Fermat's theorem

typedef struct {
    size_t* data;
    size_t size;
    size_t cap;
} IntVec;

static void intVecInit(IntVec* iv) {
    iv->data = NULL;
    iv->size = 0;
    iv->cap = 0;
}

int pushToIntVec(IntVec* iv, size_t item) {
    if (iv->size >= iv->cap) {
        size_t newCap = (iv->cap == 0) ? 8 : iv->cap*2;

        size_t* temp = realloc(iv->data, newCap * sizeof(size_t)); 
        if (temp==NULL) return -1;

        iv->data = temp;
        iv->cap = newCap;
    }
    // realloc if cap reached stuff
    
    iv->data[iv->size++] = item;
    return 0;
}

typedef struct {
    size_t* add; // aNext = aPrev*m%MOD if mul aPrev+a%MOD
    size_t* mul; // mNext = mPrev*m%MOD if mul or mPrev if add 
    size_t size;
    size_t cap;
} OpVec;

static void opVecInit(OpVec* ov) {
    ov->add = NULL;
    ov->mul = NULL;
    ov->size = 0;
    ov->cap = 0;
}

int pushToOpVec(OpVec* ov, size_t item, int isAdd) {
    if (ov->size >= ov->cap) {
        size_t newCap = (ov->cap == 0) ? 8 : ov->cap*2;

        size_t* tempAdd = realloc(ov->add, newCap * sizeof(size_t)); 
        size_t* tempMul = realloc(ov->mul, newCap * sizeof(size_t)); 
        if (tempAdd==NULL || tempMul==NULL) return -1;

        ov->add = tempAdd;
        ov->mul = tempMul;
        ov->cap = newCap;
    }
    // realloc if cap reached stuff
    
    size_t prevAdd = (ov->size == 0) ? 0 : ov->add[ov->size-1];
    size_t prevMul = (ov->size == 0) ? 1 : ov->mul[ov->size-1];

    if (isAdd) { 
        ov->add[ov->size] = (size_t)(((long long)(prevAdd+item))%MOD);
        ov->mul[ov->size] = prevMul;
    } else {
        ov->mul[ov->size] = (size_t)(((long long)(prevMul*item))%MOD);
        ov->add[ov->size] = (size_t)(((long long)(prevAdd*item))%MOD);
    }
    ov->size++;
    return 0;
}
// single vector stuff

typedef struct {
    OpVec ov;
    IntVec items;           // just items
    IntVec sinceWhenExists; // follows items but lists ov.size-1 since when exists
} Fancy;

Fancy* fancyCreate() {
    Fancy* f = malloc(sizeof(Fancy));

    if (f==NULL) return NULL;

    opVecInit(&f->ov);
    intVecInit(&f->items);
    intVecInit(&f->sinceWhenExists);

    return f;
}

void fancyAppend(Fancy* f, size_t val) {
    pushToIntVec(&f->items, val);
    pushToIntVec(&f->sinceWhenExists, f->ov.size);
}

void fancyAddAll(Fancy* f, size_t inc) {
    pushToOpVec(&f->ov, inc, 1);
}

void fancyMultAll(Fancy* f, size_t m) {
    pushToOpVec(&f->ov, m, 0);
}

long long fancyGetIndex(Fancy* f, long long idx) {
    if (idx<0|| (size_t)idx >= f->items.size) return -1;

    long long val = f->items.data[(size_t)idx];
    if (f->ov.size==0) return (long long)(val)%MOD;
    size_t beg = f->sinceWhenExists.data[(size_t)idx];

    long long finalAdd = f->ov.add[f->ov.size - 1];
    long long finalMul = f->ov.mul[f->ov.size - 1];
    long long begAdd = (beg==0) ? 0 : f->ov.add[beg-1];
    long long begMul = (beg==0) ? 1 : f->ov.mul[beg-1];

    long long deltaMul = finalMul*modInv(begMul)%MOD;
    long long deltaAdd = (finalAdd - begAdd*deltaMul%MOD + MOD) % MOD;

    return ((val*deltaMul)+deltaAdd)%MOD;
}

void fancyFree(Fancy* f) {
    if (f==NULL) return;

    free(f->ov.add);
    free(f->ov.mul);
    free(f->items.data);
    free(f->sinceWhenExists.data);
    free(f);
}

int main() {

    Fancy* obj = fancyCreate();
    fancyAppend(obj, 1);
    fancyAppend(obj, 3);
    fancyMultAll(obj, 10);
    fancyAddAll(obj, 2);
    fancyAppend(obj, 5);
    fancyMultAll(obj, 2);
    fancyAppend(obj, 9);

    printf("%lld Values: ", obj->items.size);
    for (int i=0; i<(obj->items.size); i++) {
        printf("%lld ", fancyGetIndex(obj, i));
    }
    printf("\nSince when exists: ");
    for (int i=0; i<(obj->items.size); i++) {
        printf("%llu ", obj->sinceWhenExists.data[i]);
    }
    printf("\n");

    fancyFree(obj);

    return 0;
}
