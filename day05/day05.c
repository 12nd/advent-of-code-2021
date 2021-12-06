#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE *inpFile = fopen("input.txt", "r");
    int area[1000][1000] = {0};
    int dCount = 0;

    /* read input  */
    int a,b,c,d;
    while (fscanf(inpFile,"%d,%d -> %d,%d", &a, &b, &c, &d) != EOF) {
        if (a == c) {
            int x1 = b, x2 = d;
            if (b > d)
                x1 = d, x2 = b;
            for (int i=x1; i<=x2; ++i) {
                if (++area[i][a] == 2)
                    ++dCount;
            }
        } else if (b == d) {
            int y1 = a, y2 = c;
            if (a > c)
                y1 = c, y2 = a;
            for (int i=y1; i<=y2; ++i) {
                if (++area[b][i] == 2)
                    ++dCount;
            }
        } else {
            continue;
        }

    }
    printf("%d\n",dCount);

}
