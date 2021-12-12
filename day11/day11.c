#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int dumbo[10][10] = {0};
bool flashed[10][10] = {false};
int n_flash = 0;


/* recursive flash function */
void flash(int r, int c) {
    ++n_flash;
    flashed[r][c] = true;
    dumbo[r][c] = 0;

    for (int dr = r-1; dr <= r+1; ++dr) {
        for (int dc = c-1; dc <= c+1; ++dc) {
            if (0 <= dr && dr < 10 && 0 <= dc && dc < 10) {
                if (!flashed[dr][dc] && ++dumbo[dr][dc] > 9)
                    flash(dr, dc);
            }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");
    char line[20] = {0};

    /* input file */
    for (int i=0; i<10; ++i) {
        fgets(line, 15, inp_file);
        for (int j=0; j<10; ++j) {
            dumbo[i][j] = line[j] - '0';
        }
    }

    int step = 0;
    int pt1 = 0;
    while (1) {
        /* part 1 */
        if (step == 100)
            pt1 = n_flash;
        ++step;

        for (int r=0; r<10; ++r) {
            for (int c=0; c<10; ++c) {
                if (!flashed[r][c] && ++dumbo[r][c] > 9)
                    flash(r,c);
            }
        }
        /* part 2 */
        bool all_flash = 1;
        for (int r=0; r<10; ++r) {
            for (int c=0; c<10; ++c) {
                if (!flashed[r][c]) {
                    all_flash = 0;
                    break;
                }
            }
        }
        if (all_flash)
            break;
        memset(flashed, 0, sizeof(flashed[0][0]) * 10 * 10);
    }

    fclose(inp_file);

    printf("%d\n", pt1);
    printf("%d\n", step);
}
