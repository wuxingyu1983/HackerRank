#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
  int N, K;
  scanf("%d", &N);
  scanf("%d", &K);
  int arr[N];

  unsigned long long * s;
  unsigned long long * f;

  s = malloc(sizeof(unsigned long long) * N);
  memset(s, 0, sizeof(unsigned long long) * N);
  f = malloc(sizeof(unsigned long long) * N);
  memset(f, 0, sizeof(unsigned long long) * N);

  for(int i = 0; i < N; i++) {
    int tmp;
    scanf("%d",&tmp);

    // 降序排列
    unsigned int j;
    for (j = 0; j < i; j ++) {
      if (arr[j] < tmp) {
        for (unsigned int k = i; k > j; k --) {
          arr[k] = arr[k - 1];
        }
        break;
      }
    }
    arr[j] = tmp;
  }

  unsigned long long unfair = 0;
  for (unsigned int i = 0; i < K; i ++) {
    for (unsigned int j = 0; j < N - i; j ++) {
      if (0 == i) {
        f[j] = 0;
        s[j] = 0;
      }
      else {
        f[j] = f[j] + s[j] + i * (arr[j + i - 1] - arr[j + i]);
        s[j] = s[j] + i * (arr[j + i - 1] - arr[j + i]);

        if (K - 1 == i) {
          if (0 == j) {
            unfair = f[j];
          }
          else {
            if (unfair > f[j]) {
              unfair = f[j];
            }
          }
        }
      }
    }
  }

  printf("%llu\n", unfair);

  free(s);
  free(f);

  return 0;
}
