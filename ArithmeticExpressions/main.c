#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
  int n;
  scanf("%d", &n);

  unsigned char * ops = malloc(n);  // '+' - 1, '-' - 2, '*' - 3
  memset(ops, 3, n);

  int * nums = malloc(n * sizeof(unsigned int));
  for (int i = 0; i < n; i ++) {
    scanf("%d", &nums[i]);
  }

  unsigned char t[1000][101][2];

  int i;
  for (i = 0; i < n; i ++) {
    if (0 == i) {
      t[i][nums[i]][0] = 1;
      t[i][nums[i]][1] = 1;
    }
    else {
      int j;
      for (j = 1; j < 101; j ++) {
        if (t[i - 1][j][0]) {
          int tmp = (j + nums[i]) % 101;
          t[i][tmp][0] = j;
          t[i][tmp][1] = 1;
          if (0 == tmp) {
            break;
          }

          tmp = (101 + j - nums[i]) % 101;
          t[i][tmp][0] = j;
          t[i][tmp][1] = 2;
          if (0 == tmp) {
            break;
          }

          tmp = (j * nums[i]) % 101;
          t[i][tmp][0] = j;
          t[i][tmp][1] = 3;
          if (0 == tmp) {
            break;
          }
        }
      }

      if (j < 101) {
        break;
      }
    }
  }

  int p = 0;
  for (int j = i; j > 0; j --) {
    ops[j] = t[j][p][1];
    p = t[j][p][0];
  }

  for (int i = 0; i < n - 1; i ++) {
    printf("%d", nums[i]);
    switch (ops[i + 1]) {
      case 1:
      printf("+");
      break;
      case 2:
      printf("-");
      break;
      default:
      printf("*");
      break;
    }
  }
  printf("%d\n", nums[n - 1]);

  free(nums);
  free(ops);

  return 0;
}
