#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

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
    curr->n = n - 1;
    curr->m = m - 1;
  }

  unsigned int n, m;
  unsigned int div_up[1000001];
  unsigned int div_down[1000001];
  for (i = 0; i < t; i++) {
    struct nm *curr = &(nms[i]);
    n = curr->n;
    m = curr->m;

    if (m > n) {
      m = n;
    }

    for (j = 0; j < m; j++) {
      div_down[j] = j + 1;
      div_up[j] = curr->n + curr->m + j - m + 1;
    }

    unsigned int prime;
    for (prime = 2; prime <= m; prime ++) {
      if (1 == div_down[prime - 1]) {
        // not prime
      }
      else {
        // prime
        clock_t start;
        start = clock();
        printf("the prime :%d start at %fs\n", prime, (double)start / CLOCKS_PER_SEC);
        for (j = prime - 1; j < m;) {
          if (0 == div_down[j] % prime) {
            div_down[j] = div_down[j] / prime;

            int k;
            for (k = 0; k < m; k++) {
              if (0 == div_up[k] % prime) {
                div_up[k] = div_up[k] / prime;
                break;
              }
            }
          }
          else {
            j = j + prime;
          }
        }
      }
    }

    long long res = 1;
    for (j = 0; j < m; j ++) {
      if (1 != div_up[j]) {
        res = res * div_up[j] % 1000000007;
      }
    }

    printf("%u\n", res);
  }

  free(nms);

  return 0;
}
