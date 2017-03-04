#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  //  FILE* fstream = fopen("input.txt", "r");
  char input[100001];

  scanf("%s", input);
  //  fscanf(fstream, "%u", &n);

  unsigned int len = strlen(input);
  unsigned int cnt[26];
  memset(cnt, 0, 26 * sizeof(unsigned int));

  for (unsigned int i = 0; i < len; i ++) {
    cnt[input[i] - 'a'] ++;
  }

  unsigned int cnt1 = 0, cnt2 = 0;
  unsigned int alp1 = 0, alp2 = 0;

  for (unsigned int i = 0; i < 26; i ++) {
    if (cnt[i]) {
      if (0 == cnt1 || cnt[i] == cnt1) {
        cnt1 = cnt[i];
        alp1 ++;
      }
      else if (0 == cnt2 || cnt[i] == cnt2) {
        cnt2 = cnt[i];
        alp2 ++;
      }
      else {
        // 第3种出现数量
        printf("NO\n");
        return 0;
      }
    }
  }

  if (cnt2) {
    if (cnt1 > cnt2) {
      if (cnt1 == cnt2 + 1 && alp1 == 1) {
        printf("YES\n");
      }
      else if (1 == cnt2 && alp2 == 1) {
        printf("YES\n");
      }
      else {
        printf("NO\n");
      }
    }
    else {
      // cnt2 > cnt1
      if (cnt2 == cnt1 + 1 && alp2 == 1) {
        printf("YES\n");
      }
      else if (1 == cnt1 && alp1 == 1) {
        printf("YES\n");
      }
      else {
        printf("NO\n");
      }
    }
  }
  else {
    printf("YES\n");
  }

  return 0;
}
