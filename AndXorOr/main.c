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
  unsigned int n;

  scanf("%u", &n);

  struct mystk * as = malloc(sizeof(struct mystk));     // array A
  as->ptr = malloc(n * sizeof(unsigned int));
  memset(as->ptr, 0, n * sizeof(unsigned int));
  as->pos = -1;

  struct mystk * tmps = malloc(sizeof(struct mystk));   // 计算过程中临时的 stack
  tmps->ptr = malloc(n * sizeof(unsigned int));
  memset(tmps->ptr, 0, n * sizeof(unsigned int));
  tmps->pos = -1;

  unsigned int max = 0;
  unsigned int min1 = 0, min2 = 0;

  for (unsigned int i = 0; i < n; i++) {
    unsigned int a;
    scanf("%u", &a);

    unsigned int left = pop(as);
    unsigned int lleft = top(as);

    if (0 == left) {
      push(as, a);
    }
    else if (0 == lleft) {
      push(as, left);
      push(as, a);
      max = left ^ a;
//      printf("1: max is %u\n", max);
      if (a < left) {
        min1 = a;
        min2 = left;
      }
      else {
        min1 = left;
        min2 = a;
      }
    }
    else {
      unsigned int min = left;
      unsigned int tmp = min ^ a;
      if (max < tmp) {
        max = tmp;
//        printf("2: max is %u, min is %u, a is %u\n", max, min, a);
      }
      if (a <= min1 || a <= min2) {
        while (left > a) {
          push(tmps, left);

          left = pop(as);
          if (0 == left) {
            break;
          }
          if (left < min) {
            min = left;
            tmp = min ^ a;
            if (max < tmp) {
              max = tmp;
//              printf("3: max is %u, min is %u, a is %u\n", max, min, a);
            }
          }
        }
        if (left) {
          push(as, left);
          if (min <= min1) {
            min2 = min1;
            min1 = min;
          }
          else {
            min2 = min;
          }
        }
      }
      else {
        unsigned int cnt = 0;

        if (left <= a) {
          cnt ++;
        }

        while (cnt < 2) {
          push(tmps, left);

          left = pop(as);
          if (0 == left) {
            break;
          }

          if (left <= a) {
            cnt ++;
            if (2 == cnt) {
              break;
            }
          }

          if (left < min) {
            min = left;
            tmp = min ^ a;
            if (max < tmp) {
              max = tmp;
//              printf("5: max is %u, min is %u, a is %u\n", max, min, a);
            }
          }
        }

        if (left) {
          push(as, left);
        }
      }

      while (tmp = pop(tmps)) {
        push(as, tmp);
      }
      push(as, a);
    }
  }

  printf("%u\n", max);

  free(tmps->ptr);
  free(tmps);
  free(as->ptr);
  free(as);

  return 0;
}
