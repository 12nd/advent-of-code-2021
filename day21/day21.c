#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    int pos[2];
    int score[2];
    int dice = 1;

    fscanf(fp, "Player %*d starting position: %d\n", &pos[0]);
    fscanf(fp, "Player %*d starting position: %d\n", &pos[1]);
    fclose(fp);

    bool end = 0;
    while (!end) {
        for (int p=0; p<2; ++p) {
            pos[p] = (pos[p] + (dice * 3 + 2))%10 + 1;
            dice += 3;
            score[p] += pos[p];
            if (score[p] >= 1000) {
                printf("%d\n", score[!p] * (dice-1));
                end = 1;
                break;
            }
        }
    }

    return 0;
}
