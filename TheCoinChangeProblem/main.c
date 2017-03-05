#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

unsigned int m, n;
unsigned int * c;
int * * p;

unsigned long long getLen(int sum, unsigned int max) {
  unsigned long long ret = 0;

  if (0 > sum) {
    return 0;
  }

  if (0 <= p[max - 1][sum - 1]) {
    ret = p[max - 1][sum - 1];
  }
  else {
    for (unsigned int i = 0; i < max; i ++) {
      if (sum < c[i]) {
        break;
      }
      else if (sum == c[i]) {
        ret += 1;
        break;
      }
      else {
        ret += getLen(sum - c[i], i + 1);
      }
    }
    p[max - 1][sum - 1] = ret;
  }

  return ret;
}

int main() {
  scanf("%u %u", &n, &m);

  c = malloc(sizeof(unsigned int) * m);
  for (unsigned int i = 0; i < m; i ++) {
    unsigned int tmp;
    scanf("%u", &tmp);

    // 插入排序
    unsigned int j;
    for (j = 0; j < i; j ++) {
      if (c[j] > tmp) {
        for (unsigned int k = i; k > j; k --) {
          c[k] = c[k - 1];
        }
        break;
      }
    }
    c[j] = tmp;
  }

  p = malloc(sizeof(int *) * m);
  for (unsigned int i = 0; i < m; i ++) {
    p[i] = malloc(sizeof(int) * n);
    memset(p[i], -1, sizeof(int) * n);
  }

//  p[0][c[0] - 1] = 1;

  unsigned long long l = getLen(n, m);

  printf("%llu\n", l);

  return 0;
}
