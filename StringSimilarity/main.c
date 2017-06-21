#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

unsigned long long stringSimilarity(char a[]) {
    long long ret = strlen(a);

    

    return ret;
}

int main() {
    int t, i;
    scanf("%d",&t);
    char a[100001];
    unsigned long long * res = malloc(sizeof(unsigned long long) * t);
    for (i=0;i<t;i++) {
        memset(a, 0, 100001);
        scanf("%s",a);
        res[i] = stringSimilarity(a);
    }

    for (i=0;i<t;i++) {
        printf("%llu\n", res[i]);
    }
    free(res);

    return 0;
}
