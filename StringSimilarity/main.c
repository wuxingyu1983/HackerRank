#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define DEBUG   0

struct myTuple {
    int originalIndex;   // stores original index of suffix
    int firstHalf;       // store rank for first half of suffix
    int secondHalf;      // store rank for second half of suffix
    struct myTuple * next;
    struct myTuple * last;
};

int cmp(struct myTuple a, struct myTuple b) {
    if(a.firstHalf == b.firstHalf) {
        return a.secondHalf < b.secondHalf;
    }
    else {
        return a.firstHalf < b.firstHalf;
    }
}

void quick_sort(struct myTuple s[], int l, int r)
{
    if (l < r)
    {
        int i = l, j = r;
        struct myTuple x = s[l];
        while (i < j)
        {
            while(i < j && !cmp(s[j], x))
                j--;
            if(i < j)
                s[i++] = s[j];

            while(i < j && cmp(s[i], x))
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
                negative = malloc(sizeof(struct myTuple));
                negative->firstHalf = s[i].firstHalf;
                negative->secondHalf = s[i].secondHalf;
                negative->originalIndex = s[i].originalIndex;
                negative->next = NULL;
                negative->last = negative;
            }
            else {
                negative->last->next = malloc(sizeof(struct myTuple));
                negative->last->next->firstHalf = s[i].firstHalf;
                negative->last->next->secondHalf = s[i].secondHalf;
                negative->last->next->originalIndex = s[i].originalIndex;
                negative->last->next->next = NULL;
                negative->last = negative->last->next;
            }
        }
        else {
            if (NULL == buckets[s[i].secondHalf]) {
                buckets[s[i].secondHalf] = malloc(sizeof(struct myTuple));
                buckets[s[i].secondHalf]->firstHalf = s[i].firstHalf;
                buckets[s[i].secondHalf]->secondHalf = s[i].secondHalf;
                buckets[s[i].secondHalf]->originalIndex = s[i].originalIndex;
                buckets[s[i].secondHalf]->next = NULL;
                buckets[s[i].secondHalf]->last = buckets[s[i].secondHalf];
            }
            else {
                buckets[s[i].secondHalf]->last->next = malloc(sizeof(struct myTuple));
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
        free(p);
        p = next;
    }
    negative = NULL;

    for (size_t i = 0; i < buckket_size; i++) {
        if (buckets[i]) {
            p = buckets[i];

            while (p) {
                s[index ++] = *p;
                next = p->next;
                free(p);
                p = next;
            }

            buckets[i] = NULL;
        }
    }

    for (size_t i = 0; i < len; i++) {
        if (NULL == buckets[s[i].firstHalf]) {
            buckets[s[i].firstHalf] = malloc(sizeof(struct myTuple));
            buckets[s[i].firstHalf]->firstHalf = s[i].firstHalf;
            buckets[s[i].firstHalf]->secondHalf = s[i].secondHalf;
            buckets[s[i].firstHalf]->originalIndex = s[i].originalIndex;
            buckets[s[i].firstHalf]->next = NULL;
            buckets[s[i].firstHalf]->last = buckets[s[i].firstHalf];
        }
        else {
            buckets[s[i].firstHalf]->last->next = malloc(sizeof(struct myTuple));
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
                free(p);
                p = next;
            }

            buckets[i] = NULL;
        }
    }
}

struct myTuple LS[18][100000];
struct myTuple L[100000];

unsigned long long getSubSimilarity(int len, int stp, int left, int right) {
    //    printf("stp = %d, left = %d, right = %d\n", stp, left, right);
    unsigned long long ret = 0;

    if (0 == stp) {
        if (LS[stp][left].firstHalf == LS[stp][right].firstHalf) {
            ret ++;

            if (LS[stp][left].secondHalf == LS[stp][right].secondHalf) {
                ret ++;
            }
        }
    }
    else {
        if (LS[stp][left].firstHalf == LS[stp][right].firstHalf) {
            ret += pow(2, stp);

            if (LS[stp][left].secondHalf == LS[stp][right].secondHalf && -1 != LS[stp][right].secondHalf) {
                ret += pow(2, stp);
            }
            else {
                // LS[stp][left].secondHalf == LS[stp][right].secondHalf
                if (-1 != LS[stp][left].secondHalf && -1 != LS[stp][right].secondHalf) {
                    if (right + pow(2, stp) < len) {
                        ret += getSubSimilarity(len, stp - 1, left + pow(2, stp), right + pow(2, stp));
                    }
                }
            }
        }
        else {
            // LS[stp][left].firstHalf != LS[stp][right].firstHalf
            ret = getSubSimilarity(len, stp - 1, left, right);
        }
    }

    return ret;
}

unsigned long long stringSimilarity(char a[]) {
    int len = strlen(a);
    long long ret = len;

    int suffixRank[18][len];
    //    printf("ret is %llu\n", ret);

    // Initialize suffix ranking on the basis of only single character
    // for single character ranks will be 'a' = 0, 'b' = 1, 'c' = 2 ... 'z' = 25
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

    //    printf("00 ret is %llu\n", ret);

    for (int i = 1; i < len; i++) {
        if (LS[0][0].firstHalf == LS[0][i].firstHalf) {
            if (LS[0][0].secondHalf == LS[0][i].secondHalf) {
                ret ++;
            }
        }
    }
    //    printf("11 ret is %llu\n", ret);

    // Create a tuple array for each suffix

    for(int cnt = 1, stp = 1; cnt < len; cnt *= 2, ++stp) {
        // On the basis of tuples obtained sort the tuple array

        //        quick_sort(L, 0, len - 1);
        radix_sort(L, len);
        /*
         for (int i = 0; i < len; i++) {
         printf("L[%d] is [%d, %d], index is %d\n", i, L[i].firstHalf, L[i].secondHalf, L[i].originalIndex);
         }
         printf("\n");
         */
        // Initialize rank for rank 0 suffix after sorting to its original index
        // in suffixRank array

        suffixRank[stp][L[0].originalIndex] = 0;

        for(int i = 1, currRank = 0; i < len; ++i) {

            // compare ith ranked suffix ( after sorting ) to (i - 1)th ranked suffix
            // if they are equal till now assign same rank to ith as that of (i - 1)th
            // else rank for ith will be currRank ( i.e. rank of (i - 1)th ) plus 1, i.e ( currRank + 1 )

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

        //        printf("LS[%d][%d] is [%d, %d], index is %d\n", stp, 0, LS[stp][0].firstHalf, LS[stp][0].secondHalf, LS[stp][0].originalIndex);
        for (int i = 1; i < len; i++) {
            //            printf("LS[%d][%d] is [%d, %d], index is %d\n", stp, i, LS[stp][i].firstHalf, LS[stp][i].secondHalf, LS[stp][i].originalIndex);
            if (LS[stp][0].firstHalf == LS[stp][i].firstHalf) {
                if (LS[stp][0].secondHalf == LS[stp][i].secondHalf) {
                    ret += cnt * 2;
                }
                else {
                    if (-1 != LS[stp][i].secondHalf) {
                        if (i + cnt * 2 < len) {
                            ret += getSubSimilarity(len, stp - 1, cnt * 2, i + cnt * 2);
                        }
                    }
                }
            }
        }
        //        printf("22 : ret is %llu\n", ret);
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
    unsigned long long * res = malloc(sizeof(unsigned long long) * t);
    for (i=0;i<t;i++) {
        memset(a, 0, 100001);

#if DEBUG
        fscanf(fp,"%s",a);
#else
        scanf("%s",a);
#endif

        res[i] = stringSimilarity(a);
    }

    for (i=0;i<t;i++) {
        printf("%llu\n", res[i]);
    }
    free(res);

#if DEBUG
    fclose(fp);
#endif

    return 0;
}
