#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int pos = -1;

struct building {
  unsigned int height;
  unsigned int pos;
};

struct building * top(struct building * * stk) {
  struct building * ret = NULL;

  if (0 <= pos) {
    ret = stk[pos];
  }

  return ret;
}

void push(struct building * * stk, struct building * node) {
  stk[++ pos] = node;
}

struct building * pop(struct building * * stk) {
  struct building * ret = NULL;

  if (0 <= pos) {
    ret = stk[pos];
    stk[pos --] = NULL;
  }

  return ret;
}

int main() {
  unsigned int n;

  scanf("%u", &n);

  struct building * * hs;
  hs = malloc(n * sizeof(struct building *));
  memset(hs, 0, n * sizeof(struct building *));

  unsigned long long max = 0;

  for (unsigned int i = 1; i <= n; i++) {
    unsigned int h;
    scanf("%u", &h);

    struct building * now = malloc(sizeof(struct building));
    now->height = h;
    now->pos = i;

    struct building * pre = top(hs);
    struct building * ppre = NULL;
    if (NULL == pre || pre->height <= now->height) {
      push(hs, now);
    }
    else {
      // 开始计算
      while (pre && pre->height > now->height) {
        pre = pop(hs);
        ppre = top(hs);
        if (ppre) {
          if (max < (pre->height * (now->pos - ppre->pos - 1))) {
            max = pre->height * (now->pos - ppre->pos - 1);
          }
        }
        else {
          if (max < (pre->height * (now->pos - 1))) {
            max = pre->height * (now->pos - 1);
          }
        }

        free(pre);
        pre = NULL;

        pre = ppre;
      }

      push(hs, now);
    }
  }

  struct building * pre;
  struct building * ppre = NULL;
  while (pre = pop(hs)) {
    ppre = top(hs);
    if (ppre) {
      if (max < (pre->height * (n - ppre->pos))) {
        max = pre->height * (n - ppre->pos);
      }
    }
    else {
      if (max < (pre->height * n)) {
        max = pre->height * n;
      }
    }

    free(pre);
    pre = NULL;
  }

  printf("%llu\n", max);

  free(hs);

  return 0;
}
