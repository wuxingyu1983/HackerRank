#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int min_l;
int min_r[32];

void proc(int remain, int a[], int len, int curr, int now, int r[]) {
  int max = 0;
  int v = a[curr];
  int tmp = remain;

  if (curr == len) {
    return;
  }

  while (0 == tmp % v) {
    tmp /= v;
    max ++;
  }

  if (max) {
    for (int i = max; i > 0; i --) {
      for (int j = now; j < now + i; j ++) {
        r[j] = v;
      }
      tmp = pow(v, i);
      if (1 == remain / tmp) {
        if (0 == min_l || min_l > (now + i)) {
          min_l = now + i;
          for (int j = 0; j < min_l; j ++) {
            min_r[j] = r[j];
          }
        }
      }
      proc(remain / tmp, a, len, curr + 1, now + i, r);
    }
  }

  proc(remain, a, len, curr + 1, now, r);
}

int main() {
  int n,k;
  scanf("%d %d", &n, &k);

  int len = 0;
  int a[20];
  for (int i = 0; i < k; i ++) {
    int t;
    scanf("%d", &t);
    if (0 == n % t) {
      // sort
      if (0 == len) {
        a[len] = t;
      }
      else {
        int j;
        for (j = 0; j < len; j ++) {
          if (a[j] > t) {
            for (int l = len; l > j; l --) {
              a[l] = a[l - 1];
            }
            break;
          }
        }
        a[j] = t;
      }
      len ++;
    }
  }

  if (0 == len) {
    printf("-1\n");
  }
  else {
    min_l = 0;
    int result[32];
    proc(n, a, len, 0, 0, result);
    if (min_l) {
      int tmp = 1;
      printf("%d", tmp);
      for (int i = 0; i < min_l; i ++) {
        tmp *= min_r[i];
        printf(" %d", tmp);
      }
      printf("\n");
    }
    else {
      printf("-1\n");
    }
  }

  return 0;
}
