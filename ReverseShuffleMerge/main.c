#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int cnt[26];
int pos[26][10000];

int main() {
    char str[10001];
    scanf("%s", str);

    int len = strlen(str);

    char * output = malloc(sizeof(char) * (len / 2 + 1));
    memset(output, 0, sizeof(char) * (len / 2 + 1));

    memset(cnt, 0, sizeof(int) * 26);

    free(output);

    return 0;
}
