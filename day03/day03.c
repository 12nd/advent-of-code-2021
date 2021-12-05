#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int binToDec(char *binStr)
{
    char *ptr;
    return strtol(binStr, &ptr, 2);
}

int invertBits(int dec)
{
    /* number of bits */
    int x = log2(dec) + 1;
    for (int i=0; i<x; ++i)
        dec = (dec^(1 << i));
    return dec;
}

int main(void)
{
    FILE *inFile;
    int nBits[12] = {0};
    char gamma[15] = "";
    char line[15];
    int nLines = 0;

    inFile = fopen("input.txt", "r");

    while (fgets(line, 15, inFile) != NULL) {
        for (int i=0; i < 12; ++i)
            nBits[i] += line[i]-'0';
        ++nLines;
    }

    for (int i=0; i < 12; ++i) {
        if (nBits[i] > (nLines >> 1))
            strcat(gamma, "1");
        else if (nBits[i] < (nLines >> 1))
            strcat(gamma, "0");
        else {
            printf("Even number\n");
            exit(1);
        }
    }

    printf("%d\n", binToDec(gamma) * invertBits(binToDec(gamma)));
}
