#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int pos = -1;

unsigned int top(unsigned int * stk) {
  unsigned int ret = 0;

  if (0 <= pos) {
    ret = stk[pos];
  }

  return ret;
}

void push(unsigned int * stk, unsigned int elem) {
  stk[++ pos] = elem;
}

unsigned int pop(unsigned int * stk) {
  unsigned int ret = 0;

  if (0 <= pos) {
    ret = stk[pos];
    stk[pos --] = 0;
  }

  return ret;
}

int main() {
  unsigned int n;

  scanf("%u", &n);

  unsigned int * as;    // array A
  as = malloc(n * sizeof(unsigned int));
  memset(as, 0, n * sizeof(unsigned int));

  unsigned int * tmps;   // 计算过程中临时的 stack
  tmps = malloc(n * sizeof(unsigned int));
  memset(tmps, 0, n * sizeof(unsigned int));

  unsigned int max = 0;

  for (unsigned int i = 0; i < n; i++) {
    unsigned int a;
    scanf("%u", &a);

  }

  printf("%u\n", max);

  free(tmps);
  free(as);

  return 0;
}
