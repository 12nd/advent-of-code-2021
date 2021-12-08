#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 3) {
        printf("Too few arguments\n");
        printf("Usage: %s <input file> <no. days>", argv[0]);
        exit(1);
    }

    int days = atoi(argv[2]);
    unsigned long long fish[9] = {0};
     /* read input */
    FILE *inp_file = fopen(argv[1], "r");
    int age;
    while (fscanf(inp_file, "%d", &age) == 1) {
        ++fish[age];
        fgetc(inp_file);
    }
    fclose(inp_file);

    for (int day=0; day<days; ++day) {
        /* number of 0 internal timer */
        unsigned long long new = fish[0];
        for (int i=1; i<9; ++i) {
            fish[i-1] = fish[i];
        }
        /* parents */
        fish[6] += new;
        /* new spawns (should be no existing fish of this age)*/
        fish[8] = new;
    }

    unsigned long long n_fish = 0;
    for (int i=0; i<9; ++i) {
        n_fish += fish[i];
    }
    printf("%llu\n", n_fish);

    return 0;
}
