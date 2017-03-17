#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

unsigned long long min;
unsigned long long w;

void proc(int * x, unsigned long long * s, unsigned long long sum, int start, int n, int k, int last_s) {
  if (0 < k && k <= (n - start) && start < n) {
    proc(x, s, sum, start + 1, n, k, last_s);

    sum -= (x[start] - x[last_s]) * (w - s[start - 1]);
    if (1 == k) {
      if (sum < min) {
        min = sum;
      }
    }
    else {
      proc(x, s, sum, start + 1, n, k - 1, start);
    }
  }
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

    proc(x, s, min, 1, n, k - 1, 0);

    free(x);
    free(s);

    printf("%llu\n", min);

    return 0;
}
