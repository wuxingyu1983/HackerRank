#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct xy {
  unsigned int x;
  unsigned int y;
};

int main() {

  /* Enter your code here. Read input from STDIN. Print output to STDOUT */

  unsigned int n;
  unsigned int *a;
  int i = 0;

  scanf("%d", &n);
  a = malloc(n * sizeof(unsigned int));

  for (i = 0; i < n; i++) {
    /* code */
    unsigned int tmp;
    scanf("%d", &tmp);
    a[i] = tmp;
  }

  unsigned int q;
  scanf("%d", &q);

  struct xy *xys = malloc(q * sizeof(struct xy));

  for (i = 0; i < q; i++) {
    unsigned int x, y;
    scanf("%u %u", &x, &y);
    struct xy *curr = &(xys[i]);
    curr->x = x;
    curr->y = y;
  }

  for (i = 0; i < q; i ++) {
    struct xy *curr = &(xys[i]);
    if (curr->x > curr->y) {
      printf("Odd\n");
    }
    else {
      if (0 == (a[curr->x - 1] % 2)) {
        if (0 == a[curr->x] && curr->x < curr->y) {
          printf("Odd\n");
        }
        else {
          printf("Even\n");
        }
      }
      else {
        printf("Odd\n");
      }
    }
  }

  free(xys);
  free(a);

  return 0;
}
