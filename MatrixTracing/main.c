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

    clock_t start;
    start = clock();
    printf("start at %fs\n", (double)start / CLOCKS_PER_SEC);

    unsigned int prime;
    for (prime = 2; prime <= m; prime ++) {
      if (1 == div_down[prime - 1]) {
        // not prime
      }
      else {
        // prime
        unsigned int max_exp = log10(m) / log10(prime);
        unsigned int exp;

        unsigned int tmp = pow(prime, max_exp);
        for (exp = max_exp; exp > 0; exp --, tmp = tmp / prime) {
          for (j = tmp - 1; j < m;) {
            int k;
            if (0 == (curr->n + curr->m - m + 1) % tmp) {
                k = 0;
            }
            else {
                k = ((curr->n + curr->m - m + 1) / tmp + 1) * tmp - (curr->n + curr->m - m + 1);
            }
            int step = 1;
            if (0 == div_down[j] % tmp) {
              for (; k < m; k = k + step) {
                if (0 == div_up[k] % tmp) {
                  div_up[k] = div_up[k] / tmp;
                  div_down[j] = div_down[j] / tmp;
                  step = tmp;
                  break;
                }
              }
            }
            else {
              j = j + tmp;
            }
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

  clock_t end;
  end = clock();
  printf("end at %fs\n", (double)end / CLOCKS_PER_SEC);

  return 0;
}
