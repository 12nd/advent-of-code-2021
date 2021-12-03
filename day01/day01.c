#include <stdio.h>

int main(void) {
  int cur;
  int prev = -1;
  int tot = 0;
  while (scanf("%d", &cur) == 1) {
    if (prev != -1) {
      if (cur > prev)
        tot++;
    }
    prev = cur;
  }
  printf("%d\n", tot);
}
