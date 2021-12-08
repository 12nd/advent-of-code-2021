#include <stdio.h>
#include <stdlib.h>

int compare (const void *a, const void *b)
{
   return ( *(int*)a - *(int*)b );
}

int part1(int *crabs, unsigned long n_crabs)
{
    qsort(crabs, n_crabs, sizeof(int), compare);
    int med = crabs[n_crabs >> 1];
    int tot_fuel = 0;
    for (unsigned long i=0; i<n_crabs; ++i) {
        tot_fuel += abs(crabs[i] - med);
    }
    return tot_fuel;
}

int fuel_cost(int n)
{
    return (n * (n+1)) >> 1;
}

int part2(int *crabs, unsigned long n_crabs)
{
    int sum_dist = 0;
    for (unsigned long i=0; i<n_crabs; ++i) {
        sum_dist += crabs[i];
    }
    int avg_f = sum_dist / (int)n_crabs;
    int tot_fuel_f = 0;
    int tot_fuel_c = 0;
    for (unsigned long i=0; i<n_crabs; ++i) {
        tot_fuel_f += fuel_cost(abs(crabs[i] - avg_f));
        tot_fuel_c += fuel_cost(abs(crabs[i] - avg_f+1));
    }
    /* return min fuel cost */
    return tot_fuel_f < tot_fuel_c ? tot_fuel_f:tot_fuel_c;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");
    int crabs[5000] = {0};
    int c;
    unsigned long n_crabs = 0;
    while (fscanf(inp_file, "%d", &c) == 1) {
        crabs[n_crabs++] = c;
        fgetc(inp_file);
    }
    fclose(inp_file);

    printf("%d\n", part1(crabs, n_crabs));
    printf("%d\n", part2(crabs, n_crabs));

    return 0;
}
