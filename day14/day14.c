#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_CAP 1000

int64_t pairs[26][26] = {0};
int rules[26][26] = {0};
int64_t ele_count[26] = {0};

int compare (const void *a, const void *b)
{
    const int64_t ai = *(const int64_t*)a;
    const int64_t bi = *(const int64_t*)b;
    if (ai < bi)
        return -1;
    else if (ai > bi)
        return 1;
    else
        return 0;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("Usage: %s <input file> <steps>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");

    char polymer[BUFFER_CAP] = {0};
    fgets(polymer, BUFFER_CAP, inp_file);
    /* initial polymer */
    ++ele_count[polymer[0] - 'A'];
    for (int i=0; i < (int)strlen(polymer) - 2; ++i)
    {
        int left = polymer[i] - 'A';
        int right = polymer[i+1] - 'A';
        ++pairs[left][right];
        ++ele_count[right];
    }

    memset(rules, -1, sizeof(int) * 26 * 26);
    fseek(inp_file, (int)ftell(inp_file) + 1, SEEK_SET);
    char a, b, c;
    while (fscanf(inp_file, "%c%c -> %c\n", &a, &b, &c) != EOF)
        rules[a - 'A'][b - 'A'] = c - 'A';
    fclose(inp_file);

    int64_t pairs_copy[26][26] = {0};
    for (int _=0; _<atoi(argv[2]); ++_) {
        memcpy(pairs_copy, pairs, sizeof(int64_t) * 26 * 26);
        for (int l=0; l<26; ++l) {
            for (int r=0; r<26; ++r) {
                if (pairs_copy[l][r] > 0 && rules[l][r] != -1) {
                    int middle = rules[l][r];
                    ele_count[middle] += pairs_copy[l][r];
                    pairs[l][middle] += pairs_copy[l][r];
                    pairs[middle][r] += pairs_copy[l][r];
                    pairs[l][r] -= pairs_copy[l][r];
                }
            }
        }
    }

    qsort(ele_count, 26, sizeof(int64_t), compare);
    for (int i=0; i<26; ++i) {
        if (ele_count[i] > 0) {
            printf("%ld\n", ele_count[25] - ele_count[i]);
            break;
        }
    }
    return 0;
}
