#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

void proc(unsigned char l[100][100][3], int start, int end, int c1, int c2, int n, int m) {
  if (0 == n % 2 && 0 == m % 2) {
    l[start][end][c1] = 2;
    l[start][end][c2] = 2;
  }
  else {
    if (1 == n % 2) {
      if (0 == m % 2) {
        l[start][end][c1] = 1;
      }
      else {
        l[start][end][3 - c1 - c2] = 1;
      }
    }
    if (1 == m % 2) {
      if (0 == n % 2) {
        l[start][end][c2] = 1;
      }
      else {
        l[start][end][3 - c1 - c2] = 1;
      }
    }
  }
}

/* Head ends here */
int stringReduction(char a[]) {
  unsigned int len = strlen(a);
  unsigned char l[100][100][3];
  // init
  for (int i = 0; i < len; i ++) {
    if ('a' == a[i]) {
      l[i][i][0] = 1;
      l[i][i][1] = 0;
      l[i][i][2] = 0;
    }
    else if ('b' == a[i]) {
      l[i][i][0] = 0;
      l[i][i][1] = 1;
      l[i][i][2] = 0;
    }
    else {
      l[i][i][0] = 0;
      l[i][i][1] = 0;
      l[i][i][2] = 1;
    }
  }

  for (int step = 1; step < len; step ++) {
    for (int i = 0; i < len - step; i ++) {
      l[i][i + step][0] = 0;
      l[i][i + step][1] = 0;
      l[i][i + step][2] = 0;
      for (int j = i; j < i + step; j ++) {
          if (l[i][j][0]) {
            if (l[j + 1][i + step][0]) {
              if (0 == l[i][i + step][0] || l[i][i + step][0] > (l[i][j][0] + l[j + 1][i + step][0])) {
                l[i][i + step][0] = l[i][j][0] + l[j + 1][i + step][0];
              }
            }
            if (l[j + 1][i + step][1]) {
              proc(l, i, i + step, 0, 1, l[i][j][0], l[j + 1][i + step][1]);
            }
            if (l[j + 1][i + step][2]) {
              proc(l, i, i + step, 0, 2, l[i][j][0], l[j + 1][i + step][2]);
            }
          }
          if (l[i][j][1]) {
            if (l[j + 1][i + step][1]) {
              if (0 == l[i][i + step][1] || l[i][i + step][1] > (l[i][j][1] + l[j + 1][i + step][1])) {
                l[i][i + step][1] = l[i][j][1] + l[j + 1][i + step][1];
              }
            }
            if (l[j + 1][i + step][0]) {
              proc(l, i, i + step, 1, 0, l[i][j][1], l[j + 1][i + step][0]);
            }
            if (l[j + 1][i + step][2]) {
              proc(l, i, i + step, 1, 2, l[i][j][1], l[j + 1][i + step][2]);
            }
          }
          if (l[i][j][2]) {
            if (l[j + 1][i + step][2]) {
              if (0 == l[i][i + step][2] || l[i][i + step][2] > (l[i][j][2] + l[j + 1][i + step][2])) {
                l[i][i + step][2] = l[i][j][2] + l[j + 1][i + step][2];
              }
            }
            if (l[j + 1][i + step][1]) {
              proc(l, i, i + step, 2, 1, l[i][j][2], l[j + 1][i + step][1]);
            }
            if (l[j + 1][i + step][0]) {
              proc(l, i, i + step, 2, 0, l[i][j][2], l[j + 1][i + step][0]);
            }
          }
      }
    }
  }

  int ret;

  ret = l[0][len - 1][0];
  if (0 == ret || (l[0][len - 1][1] && l[0][len - 1][1] < ret)) {
    ret = l[0][len - 1][1];
  }
  if (0 == ret || (l[0][len - 1][2] && l[0][len - 1][2] < ret)) {
    ret = l[0][len - 1][2];
  }

  return ret;
}

int main() {
  int res, t, i;
  scanf("%d",&t);
  int r[100];
  char a[100001];
  for (i=0;i<t;i++) {
    memset(a, 0, 100001);
    scanf("%s",a);
    res=stringReduction(a);
    r[i] = res;
  }
  for (i=0;i<t;i++) {
    printf("%d\n", r[i]);
  }

  return 0;
}
