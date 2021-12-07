#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("Too few arguments\n");
        printf("Usage: %s <input file> <no. days>", argv[0]);
    }

    int days=atoi(argv[2]);
    int n_fish = 0;
    int fish_size = 500;
    int *fish = (int *)malloc(fish_size * sizeof(int));
    FILE *inp_file = fopen(argv[1], "r");
    char line[10000];
    fgets(line, 9000, inp_file);
    fclose(inp_file);

    /* read input */
    char *t = strtok(line, ",");
    for (int i=0; t != NULL; ++i) {
        fish[i] = atoi(t);
        ++n_fish;
        t = strtok(NULL, ",");
    }

    for (int day=0; day<days; ++day) {
        int fish_inc = 0;
        for (int f=0; f<n_fish; ++f) {
            if (--fish[f] == -1) {
                fish[f] = 6;
                fish[n_fish + fish_inc] = 8;
                ++fish_inc;
                if (n_fish + fish_inc >= fish_size >> 1) {
                    fish = realloc(fish, fish_size * 2 * sizeof(int));
                    fish_size *= 2;
                }
            }
        }
        n_fish += fish_inc;
    }

    free(fish);

    printf("%d\n", n_fish);

}
