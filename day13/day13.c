#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_CAP 5000

bool paper[BUFFER_CAP][BUFFER_CAP] = {0};
int vis_x = 0;
int vis_y = 0;

int fold_x(int split)
{
    int count = 0;
    for (int x=1; x <= split; ++x) {
        for (int y=0; y < vis_y; ++y) {
            bool overlap = paper[split - x][y] | paper[split + x][y];
            paper[split - x][y] = paper[split - x][y] | paper[split + x][y];
            count += overlap;
        }
    }
    vis_x = split;
    return count;
}

int fold_y(int split)
{
    int count = 0;
    for (int x=0; x < vis_x; ++x) {
        for (int y=1; y <= split; ++y) {
            bool overlap = paper[x][split - y] | paper[x][split + y];
            paper[x][split - y] = overlap;
            count += overlap;
        }
    }
    vis_y = split;
    return count;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");
    int x, y;
    char line[100] = {0};
    while (fgets(line, 100, inp_file) != NULL) {
        if (*line == '\n')
            break;
        sscanf(line, "%d, %d\n", &x, &y);
        x+1 > vis_x ? vis_x = x+1 : 0;
        y+1 > vis_y ? vis_y = y+1 : 0;
        paper[x][y] = 1;
    }
    /* follow instructions */
    bool first = 1;
    while (fgets(line, 100, inp_file) != NULL) {
        int split = atoi(line+13);
        char axis = *(line + 11);
        int pt1 = 0;
        if (axis == 'x') {
            pt1 += fold_x(split);
        } else {
            pt1 += fold_y(split);
        }
        /* part 1 */
        if (first) {
            printf("%d\n", pt1);
            first = 0;
        }
    }
    /* part 2 */
    for (int c=0; c < vis_y; ++c) {
        for (int r=0; r < vis_x; ++r) {
            if (paper[r][c])
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }

    fclose(inp_file);
    return 0;
}
