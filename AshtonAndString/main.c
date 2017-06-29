#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG   0

struct myTuple {
    int originalIndex;   // stores original index of suffix
    int firstHalf;       // store rank for first half of suffix
    int secondHalf;      // store rank for second half of suffix
    struct myTuple * next;
    struct myTuple * last;
};

struct myTuple round1[100000];
struct myTuple round2[100000];

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
/*
    printf("stp = %d, prev = %d, curr = %d\n", stp, prev, curr);

    for (int i = 0; i < len; i++) {
        printf("LS[%d][%d] is firstHalf is %d, secondHalf is %d\n", stp, i, LS[stp][i].firstHalf, LS[stp][i].secondHalf);
    }
*/
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

char ashtonAndString(char a[], int k) {
    char ret = ' ';

    clock_t start,finish;
    double TheTimes;

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
        start = clock();
        radix_sort(L, len);
        finish = clock();
        TheTimes = (double)(finish-start)/CLOCKS_PER_SEC;
#if DEBUG
        printf("radix_sort consume : %fs\n", TheTimes);
#endif

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
    for (int i = 1; i < len; i++){
        lcp[i] = getLcp(L[i - 1].originalIndex, L[i].originalIndex, stp, len);
//        printf("lcp[%d] = %d\n", i, lcp[i]);
    }

    int sum = 0;
    int last_common = 0;
    for (int i = 0; i < len; i++) {
        last_common = lcp[i];
        int round_sum = (len - L[i].originalIndex + 1) * (len - L[i].originalIndex) / 2 - (last_common + 1) * last_common / 2;
//        printf("%d : round_sum is %d\n", i, round_sum);
        if (round_sum + sum >= k) {
            int x = k - sum;
            int l = 1;
            int r = len - L[i].originalIndex;
            int mid;
            while (l <= r) {
                mid = (l + r) / 2;
//                printf("l = %d, r = %d, mid = %d\n", l, r, mid);
                if ((mid + 1) * mid / 2 == x) {
                    break;
                }
                else if ((mid + 1) * mid / 2 > x) {
                    r = mid - 1;
                }
                else {
                    l = mid + 1;
                }
            }

            if ((mid + 1) * mid / 2 == x) {
                ret = a[L[i].originalIndex + mid - 1];
            }
            else {
                ret = a[L[i].originalIndex + (x - (mid - 1) * mid) - 1];
            }

            break;
        }
        sum += round_sum;
    }

    return ret;
}

int main() {
    int t, i;

#if DEBUG
    FILE * fp = fopen("input.txt", "r");
    fscanf(fp,"%d",&t);
#else
    scanf("%d",&t);
#endif

    char a[100001];
    char * res = malloc(sizeof(char) * t);
    for (i=0;i<t;i++) {
        memset(a, 0, 100001);
        int k;

#if DEBUG
        fscanf(fp,"%s",a);
        fscanf(fp,"%d",&k);
#else
        scanf("%s",a);
        scanf("%d",&k);
#endif

        res[i] = ashtonAndString(a, k);
    }

    for (i=0;i<t;i++) {
        printf("%c\n", res[i]);
    }

    free(res);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
