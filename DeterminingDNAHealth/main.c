#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int n;
    scanf("%d",&n);
    char* *genes = malloc(sizeof(char*) * n);
    for(int genes_i = 0; genes_i < n; genes_i++){
        genes[genes_i] = (char *)malloc(10240 * sizeof(char));
        scanf("%s",genes[genes_i]);
    }
    int *health = malloc(sizeof(int) * n);
    for(int health_i = 0; health_i < n; health_i++){
        scanf("%d",&health[health_i]);
    }
    int s;
    scanf("%d",&s);
    for(int a0 = 0; a0 < s; a0++){
        int first;
        int last;
        char* d = (char *)malloc(512000 * sizeof(char));
        scanf("%d %d %s",&first,&last,d);
        // your code goes here
    }
    return 0;
}
