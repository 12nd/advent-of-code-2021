#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("Too few arguments\n");
        printf("Usage: %s <input file> <part>\n", argv[0]);
        exit(1);
    }

    static int area[1000][1000] = {0};
    FILE *inpFile = fopen(argv[1], "r");
    int dCount = 0;

    /* read input  */
    int x1,y1,x2,y2;
    while (fscanf(inpFile,"%d,%d -> %d,%d", &x1, &y1, &x2, &y2) != EOF) {
        if (x1 == x2) {
            int xInc = y1 > y2 ? -1:1;
            for (int i=y1; i != y2+xInc; i+=xInc) {
                if (++area[x1][i] == 2)
                    ++dCount;
            }
        } else if (y1 == y2) {
            int yInc = x1 > x2 ? -1:1;
            for (int i=x1; i != x2+yInc; i+=yInc) {
                if (++area[i][y1] == 2)
                    ++dCount;
            }
        /* diagonals */
        } else if (atoi(argv[2]) == 2) {
            int xInc = x1 > x2 ? -1:1;
            int yInc = y1 > y2 ? -1:1;
            int y = y1;
            for (int i=x1; i != x2+xInc; i+=xInc) {
                if (++area[i][y] == 2) {
                    ++dCount;
                }
                y += yInc;
            }
        }
    }
    fclose(inpFile);

    printf("%d\n",dCount);
    return 0;
}
