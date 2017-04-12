#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int g;
    int cnt;
    scanf("%d",&g);
    char * * output;
    output = malloc(sizeof(char *) * g);
    for(int a0 = 0; a0 < g; a0++){
        int n;
        scanf("%d",&n);
        int *sequence = malloc(sizeof(int) * n);
        for(int sequence_i = 0; sequence_i < n; sequence_i++){
            scanf("%d",&sequence[sequence_i]);
        }

        output[a0] = malloc(6);
        memset(output[a0], 0, 6);

        cnt = 0;

        if (n > 2) {
            for (int i = 1; i < n - 1; i ++) {
                if (1 == sequence[i]) {
                    if (0 == sequence[i - 1] && 0 == sequence[i + 1]) {
                        sequence[i] = 0;
                    }
                }
            }

            for (int i = 1; i < n - 1; i ++) {
                if (0 == sequence[i - 1] && 0 == sequence[i + 1]) {
                    cnt ++;
                }
            }
        }

//        printf("cnt is %d\n", cnt);
        if (0 == (cnt % 2)) {
            strcpy(output[a0], "Bob");
        }
        else {
            strcpy(output[a0], "Alice");
        }

        // If Alice wins, print 'Alice' on a new line; otherwise, print 'Bob'
    }

    for(int a0 = 0; a0 < g; a0++){
        printf("%s\n", output[a0]);
        free(output[a0]);
    }

    free(output);

    return 0;
}
