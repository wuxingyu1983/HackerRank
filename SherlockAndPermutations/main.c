#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct nm {
  unsigned int n;
  unsigned int m;
};

int main() {

  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int t;
  int i,j;
  struct nm *nms;

  scanf("%d", &t);

  nms = malloc(t * sizeof(struct nm));

  for (i = 0; i< t; i++) {
    unsigned int n, m;
    scanf("%u %u", &n, &m);
    struct nm *curr = &(nms[i]);
    curr->n = n;
    curr->m = m;
  }

  unsigned int n, m;
  int *div_up;
  int *div_down;
  unsigned int div;
  for (i = 0; i < t; i++) {
    struct nm *curr = &(nms[i]);
    n = curr->n;
    m = curr->m;

    if (m > m - 1) {
      m = m - 1;
    }

    div_up = malloc(m * sizeof(unsigned int));
    div_down = malloc(m * sizeof(unsigned int));

    for (j = 0; j < m; j++) {
      div_down[j] = j + 1;
      div_up[j] = curr->n + curr->m - 1 + j - m + 1;
    }

    int index = 0;
    for (index = 0; index < m;) {
      if (1 == div_down[index]) {
        index ++;
      }
      else {
        for (div = 2; ;) {
          if (0 == div_down[index] % div) {
            for (j = 0; j < m; j ++) {
              if (0 == div_up[j] % div) {
                div_up[j] = div_up[j] / div;
                break;
              }
            }
            div_down[index] = div_down[index] / div;
            if (1 == div_down[index]) {
              break;
            }
          }
          else {
            div ++;
          }
        }
      }
    }

    long long res = 1;
    for (j = 0; j < m; j ++) {
      res = res * div_up[j] % 1000000007;
    }
    printf("%u\n", res);

    free(div_up);
    free(div_down);
  }

  free(nms);

  return 0;
}
