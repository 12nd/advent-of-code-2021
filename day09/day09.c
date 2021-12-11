#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* global variables */
char area[102][500];
int low_points_r[10000];
int low_points_c[10000];
int n_lp = 0;

int compare (const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

/* int line_risk(char *line) */
int line_risk(int eval_idx)
{
    int risk = 0;
    for(int i=0; *(area[eval_idx + 1] + i) != '\0'; ++i) {
        int prev = *(area[eval_idx - 1] + i);
        int eval = *(area[eval_idx] + i);
        int next = *(area[eval_idx + 1] + i);
        int left = '9';
        int right = '9';
        if (i > 0)
            left = *(area[eval_idx] + i - 1);
        if (*(area[eval_idx + 1] + i + 1) != '\0')
            right = *(area[eval_idx] + i + 1);

        if (eval < prev && eval < next && eval && eval < left && eval < right) {
            risk += 1 + eval - '0';
            low_points_r[n_lp] = eval_idx;
            low_points_c[n_lp] = i;
            ++n_lp;
        }
    }
    return risk;
}

/* recursively find basin size using dfs */
bool seen[200][200] = {false};
int basin_size(int r, int c)
{
    int eval = *(area[r] + c);
    if (seen[r][c])
        return 0;
    seen[r][c] = true;

    if (eval  == '9' || c < 0 || eval ==  '\0' || eval == '\n')
        return 0;

    int out = 1;
    int dir[8] = {-1, 0, 1, 0, 0, 1, 0, -1};
        for (int i=0; i < 8; i+=2) {
            out += basin_size(r + dir[i], c + dir[i+1]);
        }
    return out;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");
    char line[500];
    /* initialise */
    /* first line stored is all 9 */
    strcpy(area[0],"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
    fgets(area[1], 300, inp_file);
    int n_lines = 1;
    int risk = 0;

    /* start on second line, evaluate risk for previous line */
    while (fgets(line, 300, inp_file) != NULL) {
        line[strcspn(line, "\n")] = 0;

        strcpy(area[++n_lines], line);

        risk += line_risk(n_lines - 1);
    }
    fclose(inp_file);
    /* last line */
    strcpy(area[++n_lines],"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
    risk += line_risk(n_lines - 1);

    /* part 2 */
    int out[10000] = {0};
    for (int i=0; i<n_lp; ++i) {
        out[i] = basin_size(low_points_r[i], low_points_c[i]);
    }

    printf("%d\n", risk);

    qsort(out, (unsigned long)n_lp, sizeof(int), compare);
    printf("%d\n", out[n_lp-1] * out[n_lp-2] * out[n_lp-3]);
}
