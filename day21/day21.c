#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int deterministic(int p1, int p2)
{
    int pos[2] = {p1, p2};
    int score[2] = {0};
    int dice = 1;
    for (;;) {
        for (int p=0; p<2; ++p) {
            pos[p] = (pos[p] + (dice * 3 + 2))%10 + 1;
            dice += 3;
            score[p] += pos[p];
            if (score[p] >= 1000)
                return score[!p] * (dice-1);
        }
    }
}


typedef struct N_universe {
    bool exists;
    uint64_t nu1;
    uint64_t nu2;
} N_universe;

/* dynamic programming memoization */
N_universe memo[10][10][21][21] = {0};

N_universe dirac(int p1, int p2, int s1, int s2)
{
    N_universe out = {0};
    out.exists = 1;
    /* don't need to check if s1 >= 21 as it would had been s2 in previous iteration */
    if (s2 >= 21) {
        out.nu2 = 1;
        return out;
    } else if (memo[p1][p2][s1][s2].exists)
        return memo[p1][p2][s1][s2];
    for (int d1=1; d1<=3; ++d1) {
        for (int d2=1; d2<=3; ++d2) {
            for (int d3=1; d3<=3; ++d3) {
                int new_pos = (p1 + d1 + d2 + d3)%10;
                int new_score = s1 + new_pos + 1;
                /* switch players */
                N_universe tmp = dirac(p2, new_pos, s2, new_score);
                out.nu1 += tmp.nu2;
                out.nu2 += tmp.nu1;
            }
        }
    }
    memo[p1][p2][s1][s2] = out;
    return out;
}


int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    int p1,p2;

    fscanf(fp, "Player %*d starting position: %d\n", &p1);
    fscanf(fp, "Player %*d starting position: %d\n", &p2);
    fclose(fp);

    printf("%d\n", deterministic(p1,p2));
    /* positions now 0 indexed for memo*/
    printf("%ld\n", dirac(p1-1, p2-1, 0, 0).nu1);

    return 0;
}
