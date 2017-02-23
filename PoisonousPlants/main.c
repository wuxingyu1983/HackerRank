#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int pos = -1;

struct plant {
  unsigned int p;       //pesticide
  unsigned int day;
};

struct plant * top(struct plant * * stk) {
  struct plant * ret = NULL;

  if (0 <= pos) {
    ret = stk[pos];
  }

  return ret;
}

void push(struct plant * * stk, struct plant * node) {
  stk[++ pos] = node;
}

struct plant * pop(struct plant * * stk) {
  struct plant * ret = NULL;

  if (0 <= pos) {
    ret = stk[pos];
    stk[pos --] = NULL;
  }

  return ret;
}

int main() {
  unsigned int n;

  scanf("%u", &n);

  struct plant * * plants;
  plants = malloc((n + 1) * sizeof(struct plant *));  // 最后加一个 0 的 plant 作为最后计算的触发条件
  memset(plants, 0, (n + 1) * sizeof(struct plant *));

  unsigned long long max = 0;

  for (unsigned int i = 0; i <= n; i++) {
    struct plant * now = malloc(sizeof(struct plant));

    if (i < n) {
      unsigned int p;
      scanf("%u", &p);

      now->p = p;
      now->day = 0;
    }
    else {
      now->p = 0;
      now->day = 0;
    }
    struct plant * left = top(plants);

    if (NULL == left || left->p < now->p) {
      push(plants, now);
    }
    else {
      struct plant * lleft;

      unsigned int tmp = 0;

      while (1) {
        left = pop(plants);
        lleft = top(plants);

        if (NULL == lleft || lleft->p >= left->p || (0 < tmp && left->day > tmp)) {
          push(plants, left);

          now->day = tmp;
          if (max < tmp) {
            max = tmp;
          }

          push(plants, now);
          break;
        }
        else {
          if (tmp < left->day + 1) {
            tmp = left->day + 1;
          }

          free(left);
        }
      }
    }
  }

  printf("%llu\n", max);

  free(plants);

  return 0;
}
