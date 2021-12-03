#include <stdio.h>

int main(void) {
  int window[3];
  int indx = 0;
  int cur;
  int tot = 0;

  for (int i=0; i<3; ++i) {
    scanf("%d", &cur);
    window[i] = cur;
  }

  while (scanf("%d", &cur) == 1) {
    if (cur - window[indx] > 0)
      ++tot;
    window[indx] = cur;
    if (++indx == 3)
      indx = 0;
  }
  printf("%d\n", tot);

  return 0;
}
