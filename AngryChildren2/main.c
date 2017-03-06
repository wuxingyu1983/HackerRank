#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
  int N, K;
  scanf("%d", &N);
  scanf("%d", &K);
  int arr[N];

  int * * s;
  int * * f;

  s = malloc(sizeof(int *) * N);
  f = malloc(sizeof(int *) * N);

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

    s[i] = malloc(sizeof(int) * N);
    memset(s[i], 0, sizeof(int) * N);

    f[i] = malloc(sizeof(int) * N);
    memset(f[i], 0, sizeof(int) * N);
  }
/*
  for(int i = 0; i < N; i++) {
    printf("%d ", arr[i]);
  }
*/
  unsigned long long unfair = 0;
  for (unsigned int i = 0; i < K; i ++) {
    for (unsigned int j = 0; j < N - i; j ++) {
      if (0 == i) {
        f[j][j] = 0;
        s[j][j] = 0;
      }
      else {
        f[j][j + i] = f[j][j + i - 1] + s[j][j + i - 1] + i * (arr[j + i - 1] - arr[j + i]);
        s[j][j + i] = s[j][j + i - 1] + i * (arr[j + i - 1] - arr[j + i]);

        if (K - 1 == i) {
          if (0 == j) {
            unfair = f[j][j + i];
          }
          else {
            if (unfair > f[j][j + i]) {
              unfair = f[j][j + i];
            }
          }
        }
      }
    }
  }

  printf("%llu\n", unfair);

  for(int i = 0; i < N; i++) {
    free(s[i]);
    free(f[i]);
  }
  free(s);
  free(f);

  return 0;
}
