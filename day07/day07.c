#include <stdio.h>
#include <stdlib.h>

int compare (const void *a, const void *b)
{
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>", argv[0]);
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

    qsort(crabs, n_crabs, sizeof(int), compare);

    int med = crabs[n_crabs >> 1];
    int tot_fuel = 0;
    for (unsigned long i=0; i<n_crabs; ++i) {
        tot_fuel += abs(crabs[i] - med);
    }

    printf("%d", tot_fuel);

    return 0;
}
