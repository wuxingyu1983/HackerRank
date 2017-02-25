#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int pos = -1;

struct plant {
  unsigned int p;       //pesticide
  unsigned int day;     // 第day天还没死
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
      // 如果当前plant比左边的农药多，先push到栈中，等待时机进行生死的判断
//      printf("push node, p is %u, day is %u\n", now->p, now->day);
      push(plants, now);
    }
    else {
      // now->p <= left->p
      struct plant * lleft;

      while (1) {
        left = pop(plants);
        lleft = top(plants);

        if (lleft && lleft->p < left->p/*&& (lleft->day >= left->day || left->p > now->p)*/) {
//          if (i == n || 0 == now->day || left->day < now->day || (left->day == now->day && left->p >= now->p)) {
          if (left->p == now->p || left->day < now->day || 0 == now->day || left->p > now->p ) {
            //          if (left->day <= now->day || 0 == now->day || i == n) {
            // 要 pop 的 left plant，存活的 day 应该小于等于当前的 day，避免pop掉将来的plant
            if (now->day < left->day + 1) {
              now->day = left->day + 1;
            }

            if (max < now->day) {
              max = now->day;
            }

//            printf("pop node, p is %u, day is %u\n", left->p, left->day);

            free(left);
          }
          else {
            push(plants, left);
            push(plants, now);

//            printf("push node, p is %u, day is %u\n", now->p, now->day);

            break;
          }
        }
        else {
          push(plants, left);
          push(plants, now);

//          printf("push node, p is %u, day is %u\n", now->p, now->day);

          break;
        }
      }
    }
  }
  /*
  struct plant * now;
  while(now = pop(plants)) {
  if (max < now->day) {
  max = now->day;
}
}
*/
printf("%llu\n", max);

free(plants);

return 0;
}
