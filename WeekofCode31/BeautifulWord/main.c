#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    char* w = (char *)malloc(101 * sizeof(char));
    memset(w, 0, 101);
    scanf("%s",w);
    // Print 'Yes' if the word is beautiful or 'No' if it is not.

    char vowels[6] = {'a', 'e', 'i', 'o', 'u', 'y'};

    int len = strlen(w);

    int i;
    char pre = 0;
    int flag = 0;       // 1 = vowel
    for (i = 0; i < len; i ++) {
        char cur = w[i];
        if (pre && pre == cur) {
            break;
        }

        int j;
        for (j = 0; j < 6; j ++) {
            if (vowels[j] == cur) {
                break;
            }
        }

        if (6 == j) {
            flag = 0;
        }
        else {
            if (1 == flag) {
                break;
            }
            flag = 1;
        }

        pre = cur;
    }

    if (len == i) {
        printf("Yes\n");
    }
    else {
        printf("No\n");
    }

    free(w);

    return 0;
}
