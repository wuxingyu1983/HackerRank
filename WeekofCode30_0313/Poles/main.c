#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

unsigned long long min;
unsigned long long w;

long long * * p;

long long proc(int * x, unsigned long long * s, int start, int n, int k, int last_s) {
  long long ret = 0;

  if (p[last_s][k]) {
    ret = p[last_s][k];
  }
  else {
    for (int i = start; i <= n - k; i ++) {
      long long tmp = (x[i] - x[last_s]) * (w - s[i - 1]);
      if (k > 1) {
        tmp += proc(x, s, i + 1, n, k - 1, i);
      }

      if (tmp > ret) {
        ret = tmp;
      }
    }

    p[last_s][k] = ret;
  }

  return ret;
}

int main(){
    int n;
    int k;
    scanf("%d %d",&n,&k);

    int * x = malloc(sizeof(int) * n);
    memset(x, 0, sizeof(int) * n);

    unsigned long long * s = malloc(sizeof(unsigned long long) * n);
    memset(s, 0, sizeof(unsigned long long) * n);

    min = 0;
    w = 0;
    unsigned long long tmp = 0;

    p = malloc(sizeof(long long *) * (n + 1));
    for (int i = 0; i < n + 1; i ++) {
      p[i] = malloc(sizeof(long long) * (k + 1));
      memset(p[i], 0, sizeof(long long) * (k + 1));
    }

    for(int a0 = 0; a0 < n; a0++){
        int x_i;
        int w_i;
        scanf("%d %d",&x_i,&w_i);

        x[a0] = x_i;
        min += (x[a0] - x[0]) * w_i;

        tmp += w_i;
        s[a0] = tmp;

        w += w_i;
    }

    if (0 < (k - 1)) {
      min -= proc(x, s, 1, n, k - 1, 0);
    }

    free(x);
    free(s);

    printf("%llu\n", min);

    return 0;
}
