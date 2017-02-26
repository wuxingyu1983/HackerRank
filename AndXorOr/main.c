#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct mystk {
  unsigned int *  ptr;
  int             pos;
};

unsigned int top(struct mystk * stk) {
  unsigned int ret = 0;

  if (0 <= stk->pos) {
    ret = stk->ptr[stk->pos];
  }

  return ret;
}

void push(struct mystk * stk, unsigned int elem) {
  int p = stk->pos;
  stk->ptr[++ p] = elem;
  stk->pos = p;
}

unsigned int pop(struct mystk * stk) {
  unsigned int ret = 0;
  int p = stk->pos;

  if (0 <= p) {
    ret = stk->ptr[p];
    stk->ptr[p--] = 0;
    stk->pos = p;
  }

  return ret;
}

int main() {
//  FILE* fstream = fopen("input.txt", "r");
  unsigned int n;

  scanf("%u", &n);
//  fscanf(fstream, "%u", &n);

  struct mystk * as = malloc(sizeof(struct mystk));     // array A
  as->ptr = malloc(n * sizeof(unsigned int));
  memset(as->ptr, 0, n * sizeof(unsigned int));
  as->pos = -1;

  unsigned int max = 0;

  for (unsigned int i = 0; i < n; i++) {
    unsigned int a;
    scanf("%u", &a);
//    fscanf(fstream, "%u", &a);

    unsigned int left = pop(as);
    unsigned int lleft = top(as);

    if (0 == left) {
      push(as, a);
    }
    else if (0 == lleft) {
      push(as, left);
      push(as, a);

      unsigned int tmp = left ^ a;
      if (max < tmp) {
        max = tmp;
      }
      //      printf("1: max is %u\n", max);
    }
    else {
      unsigned int tmp = left ^ a;
      if (max < tmp) {
        max = tmp;
      }
      if (a > left) {
        push(as, left);
        push(as, a);
      }
      else {
        // a <= left
        while(left = pop(as)) {
          tmp = left ^ a;
          if (max < tmp) {
            max = tmp;
          }
          if (left <= a) {
            push(as, left);
            break;
          }
        }

        push(as, a);
      }
    }
  }

  printf("%u\n", max);

  free(as->ptr);
  free(as);

  return 0;
}
