#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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
    int actived = 0;
    int **t;
    t = malloc(2 * sizeof(int *));
    t[0] = malloc(sizeof(int) * pow(2,len));
    t[1] = malloc(sizeof(int) * pow(2,len));
    int **p;
    p = malloc(2 * sizeof(int *));
    p[0] = malloc(sizeof(int) * pow(2,len));
    p[1] = malloc(sizeof(int) * pow(2,len));
    int result = 0;

    for (int i = 0; i < len; i ++) {
      if (0 == i) {
        t[actived][0] = n / a[i];
        p[actived][0] = 1 * pow(2, (len - i - 1));
//        printf("t[0] is %d\n", t[actived][0] );
//        printf("p[0] is %d\n", p[actived][0] );
        if (1 == n / a[i]) {
          result = p[actived][0];
          break;
        }
        t[actived][1] = n;
        p[actived][1] = 0;
//        printf("t[1] is %d\n", t[actived][1] );
//        printf("p[1] is %d\n", p[actived][1]);
      }
      else {
        int max = pow(2, i);
        int last = 1 - actived;
        for (int j = 0; j < max; j ++) {
          if (t[last][j] && 0 == t[last][j] % a[i]) {
            t[actived][2 * j] = t[last][j] / a[i];
            p[actived][2 * j] = p[last][j] + 1 * pow(2, len - i - 1);
//            printf("t[%d] is %d\n", 2 * j, t[actived][2 * j]);
 //           printf("p[%d] is %d\n", 2 * j, p[actived][2 * j]);

            if (1 == t[actived][2 * j]) {
              if (0 == result || result < p[actived][2 * j]) {
                result = p[actived][2 * j];
              }
            }
          }
          else {
            t[actived][2 * j] = 0;
            p[actived][2 * j] = 0;
          }

          t[actived][2 * j + 1] = t[last][j];
          p[actived][2 * j + 1] = p[last][j];
//          printf("t[%d] is %d\n", 2 * j + 1, t[actived][2 * j + 1]);
 //         printf("p[%d] is %d\n", 2 * j + 1, p[actived][2 * j + 1]);
        }
      }
      actived = 1 - actived;
    }

    if (result) {
      int tmp = 1;
      int index = 0;
      printf("%d", tmp);
      while (0 < result) {
        if (1 == result / ((int)pow(2, len - index - 1))) {
          tmp *= a[index];
          printf(" %d", tmp);
        }
        result %= ((int)pow(2, len - index - 1));
        index ++;
      }
      printf("\n");
    }
    else {
      printf("-1\n");
    }
  }

  return 0;
}
