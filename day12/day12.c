#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct
{
    char name[10];
    char neighbours[100][10];
    int n_neighbours;
} CAVE;

CAVE caves[100] = {0};
int n_caves = 0;

int find_cave(char *name)
{
    for (int i=0; i<n_caves; ++i) {
        if (!strcmp(caves[i].name, name))
            return i;
    }
    return -1;
}

void insert_neighbour(char *a, char *b)
{
    int n = find_cave(a);
    if (n == -1) {
        strcpy(caves[n_caves].name, a);
        strcpy(caves[n_caves].neighbours[caves[n_caves].n_neighbours++], b);
        ++n_caves;
    } else
        strcpy(caves[n].neighbours[caves[n].n_neighbours++], b);
}

int count_paths(char *cur, bool *seen, bool twice)
{
    if (!strcmp(cur, "end"))
        return 1;

    int n = find_cave(cur);
    /* going back to small cave or start */
    if (seen[n] && islower(*cur) > 0) {
        if (!strcmp(cur, "start"))
            return 0;
        /* if cannot visit current cave twice */
        if (!twice)
            return 0;
        else twice = 0;
    }

    int seen_tmp = seen[n];
    seen[n] = 1;

    int out = 0;
    CAVE cur_cave = caves[n];
    for (int i=0; i<cur_cave.n_neighbours; ++i) {
        out += count_paths(cur_cave.neighbours[i], seen, twice);
    }
    seen[n] = seen_tmp;
    return out;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");

    char left[10], right[10];
    while (fscanf(inp_file, "%[^-]-%s\n", left, right) != EOF) {
        insert_neighbour(left, right);
        insert_neighbour(right, left);
    }
    fclose(inp_file);

    bool *seen = calloc((unsigned long)n_caves, sizeof(bool));
    printf("%d\n", count_paths("start", seen, false));
    printf("%d\n", count_paths("start", seen, true));
    free(seen);

    return 0;
}
