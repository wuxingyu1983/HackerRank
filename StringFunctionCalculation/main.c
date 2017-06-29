#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG   0

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


struct myTuple {
    int originalIndex;   // stores original index of suffix
    int firstHalf;       // store rank for first half of suffix
    int secondHalf;      // store rank for second half of suffix
    struct myTuple * next;
    struct myTuple * last;
};

struct myTuple round1[100000];
struct myTuple round2[100000];

void quick_sort(int s[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r;
        int x = s[l];
        while (i < j)
        {
            while(i < j && s[j] <= x)
            j--;
            if(i < j)
            s[i++] = s[j];

            while(i < j && s[i] > x)
            i++;
            if(i < j)
            s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1);
        quick_sort(s, i + 1, r);
    }
}

void radix_sort(struct myTuple s[], int len) {
    struct myTuple * negative = NULL;
    int buckket_size = len < 26 ? 26 : len;
    struct myTuple * * buckets = malloc(sizeof(struct myTuple * ) * buckket_size);
    memset(buckets, 0, sizeof(struct myTuple * ) * buckket_size);

    for (size_t i = 0; i < len; i++) {
        if (-1 == s[i].secondHalf) {
            if (NULL == negative) {
                negative = &round1[i];
                negative->firstHalf = s[i].firstHalf;
                negative->secondHalf = s[i].secondHalf;
                negative->originalIndex = s[i].originalIndex;
                negative->next = NULL;
                negative->last = negative;
            }
            else {
                negative->last->next = &round1[i];
                negative->last->next->firstHalf = s[i].firstHalf;
                negative->last->next->secondHalf = s[i].secondHalf;
                negative->last->next->originalIndex = s[i].originalIndex;
                negative->last->next->next = NULL;
                negative->last = negative->last->next;
            }
        }
        else {
            if (NULL == buckets[s[i].secondHalf]) {
                buckets[s[i].secondHalf] = &round1[i];
                buckets[s[i].secondHalf]->firstHalf = s[i].firstHalf;
                buckets[s[i].secondHalf]->secondHalf = s[i].secondHalf;
                buckets[s[i].secondHalf]->originalIndex = s[i].originalIndex;
                buckets[s[i].secondHalf]->next = NULL;
                buckets[s[i].secondHalf]->last = buckets[s[i].secondHalf];
            }
            else {
                buckets[s[i].secondHalf]->last->next = &round1[i];
                buckets[s[i].secondHalf]->last->next->firstHalf = s[i].firstHalf;
                buckets[s[i].secondHalf]->last->next->secondHalf = s[i].secondHalf;
                buckets[s[i].secondHalf]->last->next->originalIndex = s[i].originalIndex;
                buckets[s[i].secondHalf]->last->next->next = NULL;
                buckets[s[i].secondHalf]->last = buckets[s[i].secondHalf]->last->next;
            }
        }
    }

    int index = 0;
    struct myTuple * p = negative;
    struct myTuple * next;
    while (p) {
        s[index ++] = *p;
        next = p->next;
        p = next;
    }
    negative = NULL;

    for (size_t i = 0; i < buckket_size; i++) {
        if (buckets[i]) {
            p = buckets[i];

            while (p) {
                s[index ++] = *p;
                next = p->next;
                p = next;
            }

            buckets[i] = NULL;
        }
    }

    for (size_t i = 0; i < len; i++) {
        if (NULL == buckets[s[i].firstHalf]) {
            buckets[s[i].firstHalf] = &round2[i];
            buckets[s[i].firstHalf]->firstHalf = s[i].firstHalf;
            buckets[s[i].firstHalf]->secondHalf = s[i].secondHalf;
            buckets[s[i].firstHalf]->originalIndex = s[i].originalIndex;
            buckets[s[i].firstHalf]->next = NULL;
            buckets[s[i].firstHalf]->last = buckets[s[i].firstHalf];
        }
        else {
            buckets[s[i].firstHalf]->last->next = &round2[i];
            buckets[s[i].firstHalf]->last->next->firstHalf = s[i].firstHalf;
            buckets[s[i].firstHalf]->last->next->secondHalf = s[i].secondHalf;
            buckets[s[i].firstHalf]->last->next->originalIndex = s[i].originalIndex;
            buckets[s[i].firstHalf]->last->next->next = NULL;
            buckets[s[i].firstHalf]->last = buckets[s[i].firstHalf]->last->next;
        }
    }

    index = 0;
    for (size_t i = 0; i < buckket_size; i++) {
        if (buckets[i]) {
            p = buckets[i];

            while (p) {
                s[index ++] = *p;
                next = p->next;
                p = next;
            }

            buckets[i] = NULL;
        }
    }
}

struct myTuple LS[18][100000];
struct myTuple L[100000];       // 用于过程中排序的

int getLcp(int prev, int curr, int stp, int len) {
    int ret = 0;
    int size = pow(2, stp);

    if (0 == stp) {
        if (LS[stp][prev].firstHalf == LS[stp][curr].firstHalf) {
            ret += size;
        }
    }
    else {
        if (LS[stp][prev].firstHalf == LS[stp][curr].firstHalf) {
            ret += size;
            if (-1 != LS[stp][prev].secondHalf && -1 != LS[stp][curr].secondHalf) {
                ret += getLcp(prev + size, curr + size, stp - 1, len);
            }
        }
        else {
            ret = getLcp(prev, curr, stp - 1, len);
        }
    }

    return ret;
}

unsigned long long stringFunctionCalculation(char a[]) {
    unsigned long long ret = 0;

    int len = strlen(a);
    int suffixRank[18][len];

    for(int i = 0; i < len; ++i) {
        suffixRank[0][i] = a[i] - 'a';
        if (0 < i && suffixRank[0][i] == suffixRank[0][0]) {
            ret ++;
        }
    }

    for(int i = 0; i < len; ++i) {
        LS[0][i].firstHalf = suffixRank[0][i];
        LS[0][i].secondHalf = i + 1 < len ? suffixRank[0][i + 1] : -1;
        LS[0][i].originalIndex = i;

        L[i].firstHalf = LS[0][i].firstHalf;
        L[i].secondHalf = LS[0][i].secondHalf;
        L[i].originalIndex = i;
    }

    int cnt, stp;
    for(cnt = 1, stp = 1; cnt < len; cnt *= 2, ++stp) {
        radix_sort(L, len);

        if (len <= cnt * 2) {
            break;
        }
        else {
            // len > cnt * 2
            suffixRank[stp][L[0].originalIndex] = 0;

            for(int i = 1, currRank = 0; i < len; ++i) {
                if(L[i - 1].firstHalf != L[i].firstHalf || L[i - 1].secondHalf != L[i].secondHalf)
                ++currRank;

                suffixRank[stp][L[i].originalIndex] = currRank;
            }

            for(int i = 0; i < len; ++i) {
                L[i].firstHalf = suffixRank[stp][i];
                L[i].secondHalf = i + (cnt * 2) < len ? suffixRank[stp][i + (cnt * 2)] : -1;
                L[i].originalIndex = i;

                LS[stp][i].firstHalf = L[i].firstHalf;
                LS[stp][i].secondHalf = L[i].secondHalf;
                LS[stp][i].originalIndex = i;
            }
        }
    }

    // L 数组就是排序后的
    stp --;
    int lcp[len];
    lcp[0] = 0;

    struct building * * hs;
    hs = malloc(len * sizeof(struct building *));
    memset(hs, 0, len * sizeof(struct building *));

    for (int i = 1; i < len; i++) {
        lcp[i] = getLcp(L[i - 1].originalIndex, L[i].originalIndex, stp, len);
//        printf("lcp[%d] = %d, prev = %d, curr = %d\n", i, lcp[i], L[i - 1].originalIndex, L[i].originalIndex);

        struct building * now = malloc(sizeof(struct building));
        now->height = lcp[i];
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
                    if (ret < (pre->height * (now->pos - ppre->pos))) {
                        ret = pre->height * (now->pos - ppre->pos);
                    }
                }
                else {
                    if (ret < (pre->height * now->pos)) {
                        ret = pre->height * now->pos;
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
        if (ret < (pre->height * (len - ppre->pos))) {
          ret = pre->height * (len - ppre->pos);
        }
      }
      else {
        if (ret < (pre->height * len)) {
          ret = pre->height * len;
        }
      }

      free(pre);
      pre = NULL;
    }

    return ret;
}

int main() {
    char a[100001];
    memset(a, 0, 100001);

#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    fscanf(fp,"%s", a);
#else
    scanf("%s", a);
#endif

    int len = strlen(a);
    unsigned long long ret = stringFunctionCalculation(a);
    if (len > ret) {
        ret = len;
    }

    printf("%llu\n", ret);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
