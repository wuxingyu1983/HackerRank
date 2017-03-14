#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    unsigned int total = 0;
    int n;
    int t;
    scanf("%d %d",&n,&t);
    int nn;
    nn = n;
    int c;
    for(int c_i = 0; c_i < t; c_i++){
       scanf("%d",&c);

       // 先补充再取
       if (5 > n) {
         total += (nn - n);
         n = nn;
       }

       n -= c;
    }

    printf("%u\n", total);

    return 0;
}
