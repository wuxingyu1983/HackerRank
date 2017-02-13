#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct nm {
  int n;
  int m;
};

int f(int n, int m) {
  if (0 == n || 0 == m) {
    return 1;
  }
  else {
    return (f(n - 1, m) + f(n, m - 1)) % 1000000007;
  }
}

int main() {

  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int t;
  int i;
  struct nm *nms;

  scanf("%d", &t);

  nms = malloc(t * sizeof(struct nm));

  for (i = 0; i< t; i++) {
    /* code */
    int n, m;
    scanf("%d %d", &n, &m);
    struct nm *curr = &(nms[i]);
    curr->n = n;
    curr->m = m;
  }

  for (i = 0; i < t; i++) {
    /* code */
    struct nm *curr = &(nms[i]);
    printf("%d\n", f(curr->n, curr->m - 1));
  }

  free(nms);

  return 0;
}
