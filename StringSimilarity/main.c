#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

struct myTuple {
    int originalIndex;   // stores original index of suffix
    int firstHalf;       // store rank for first half of suffix
    int secondHalf;      // store rank for second half of suffix
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

unsigned long long stringSimilarity(char a[]) {
    int suffixRank[13][100000];
    int len = strlen(a);
    long long ret = len;

    printf("ret is %llu\n", ret);

    // Initialize suffix ranking on the basis of only single character
    // for single character ranks will be 'a' = 0, 'b' = 1, 'c' = 2 ... 'z' = 25
    for(int i = 0; i < len; ++i) {
        suffixRank[0][i] = a[i] - 'a';
        if (0 < i && suffixRank[0][i] == suffixRank[0][0]) {
            ret ++;
        }
    }

    printf("ret is %llu\n", ret);

    // Create a tuple array for each suffix
    struct myTuple L[len];

    for(int cnt = 1, stp = 1; cnt < len; cnt *= 2, ++stp) {
        for(int i = 0; i < len; ++i) {
            L[i].firstHalf = suffixRank[stp - 1][i];
            L[i].secondHalf = i + cnt < len ? suffixRank[stp - 1][i + cnt] : -1;
            L[i].originalIndex = i;
        }

        // On the basis of tuples obtained sort the tuple array

        quick_sort(L, 0, len - 1);

        for (int i = 0; i < len; i++) {
            printf("L[%d] is [%d, %d], index is %d\n", i, L[i].firstHalf, L[i].secondHalf, L[i].originalIndex);
        }
        printf("\n");

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

        for (int i = 1; i < len; i++) {
            if (suffixRank[stp][i] == suffixRank[stp][0]) {
                ret ++;
            }
        }
        printf("ret is %llu\n", ret);
    }

    return ret;
}

int main() {
    int t, i;
    scanf("%d",&t);
    char a[100001];
    unsigned long long * res = malloc(sizeof(unsigned long long) * t);
    for (i=0;i<t;i++) {
        memset(a, 0, 100001);
        scanf("%s",a);
        res[i] = stringSimilarity(a);
    }

    for (i=0;i<t;i++) {
        printf("%llu\n", res[i]);
    }
    free(res);

    return 0;
}
