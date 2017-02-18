#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main() {
  unsigned int t;
  unsigned long long days[100];

  scanf("%d", &t);

  for (unsigned int i = 0; i < t; i++) {
    unsigned long long day;
    scanf("%llu", &day);
    days[i] = day;
  }

  for (unsigned int i = 0; i < t; i ++) {
    unsigned long long middle = sqrtl(days[i]);
    printf("the middle is %llu\n", middle);
    if (1 == middle) {
      printf("odd\n");
    }
    else {
      if ( 0 == middle % 2) {
        if (days[i] == middle * middle) {
          if (0 == days[i] % 2) {
            printf("even\n");
          }
          else {
            printf("odd\n");
          }
        }
        else {
          if (0 == days[i] % 2) {
            printf("odd\n");
          }
          else {
            printf("even\n");
          }
        }
      }
      else {
        if (0 == days[i] % 2) {
          printf("even\n");
        }
        else {
          printf("odd\n");
        }
      }
    }
  }

  return 0;
}
