#include <stdio.h>

int main(void) {
  int window[3];
  int indx = 0;
  int cur;
  int tot1 = 0;
  int tot2 = 0;

  for (int i=0; i<3; ++i) {
    scanf("%d", &cur);
    window[i] = cur;
    if (i > 0) {
      if (cur > window[i-1])
        ++tot1;
    }
  }

  while (scanf("%d", &cur) == 1) {
    if (cur > window[(indx+2)%3])
      ++tot1;
    if (cur - window[indx] > 0)
      ++tot2;
    window[indx] = cur;
    if (++indx == 3)
      indx = 0;
  }
  printf("%d\n", tot1);
  printf("%d\n", tot2);

  return 0;
}
