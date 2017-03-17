#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
  int n;
  int q;
  scanf("%d %d",&n,&q);
  int *a = malloc(sizeof(int) * n);
  for(int a_i = 0; a_i < n; a_i++){
    scanf("%d",&a[a_i]);
  }

  int * c = malloc(sizeof(int) * n);

  for(int a0 = 0; a0 < q; a0++){
    int left;
    int right;
    int x;
    int y;
    scanf("%d %d %d %d",&left,&right,&x,&y);

    unsigned int cnt = 0;
    for (int i = left; i <=right; i ++) {
      if (a[i] % x == y) {
        cnt ++;
      }
    }
    c[a0] = cnt;
  }

  for(int a0 = 0; a0 < q; a0++){
    printf("%d\n", c[a0]);
  }

  return 0;
}
