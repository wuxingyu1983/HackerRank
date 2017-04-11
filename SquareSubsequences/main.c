#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int t;
    scanf("%d", &t);

    int *output = malloc(sizeof(int) * t);
    char s[201];
    for (int i = 0; i < t; i ++) {
        memset(s, 0, sizeof(s));
        scanf("%s", s);

        int len = strlen(s);

        
    }

    for (int i = 0; i < t; i ++) {
        printf("%d\n", output[i]);
    }

    free(output);

    return 0;
}
