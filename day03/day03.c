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

int strComp(const void *a, const void *b)
{
    return strcmp(b, a);
}

/* part 2 */
int rating(char inp[2000][15], int nLines, int oxy)
{
    int ptr1 = 0;
    int ptr2 = nLines;
    int rLines = nLines;
    qsort(inp, nLines, sizeof(inp[0]), strComp);

    for (int i=0; i < 12; ++i) {
        if (ptr2 - ptr1 == 1)
            break;
        int rBits = 0;
        for (int x=ptr1; x<ptr2; ++x) {
            if (inp[x][i] == '0')
                break;
            ++rBits;
        }
        if (oxy) {
            if (rBits/(float)rLines >= 0.5) {
                ptr2 -= (ptr2-rBits-ptr1);
            } else {
                ptr1 += rBits;
            }
            rLines = ptr2-ptr1;
        } else {
            if (rBits/(float)rLines < 0.5) {
                ptr2 -= (ptr2-rBits-ptr1);
            } else {
                ptr1 += rBits;
            }
            rLines = ptr2-ptr1;
        }
    }
    return ptr1;
}

int main(void)
{
    FILE *inFile;
    int nBits[12] = {0};
    char gamma[15] = "";
    char line[15];
    char inp[2000][15];
    int nLines = 0;

    inFile = fopen("input.txt", "r");

    while (fgets(line, 15, inFile) != NULL) {
        for (int i=0; i < 12; ++i)
            nBits[i] += line[i]-'0';
        strcpy(inp[nLines], line);
        ++nLines;
    }

    /* part 1 */
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

    fclose(inFile);

    printf("%d\n", binToDec(gamma) * invertBits(binToDec(gamma)));
    printf("%d\n", binToDec(inp[rating(inp,nLines,1)])*binToDec(inp[rating(inp,nLines,0)]));
    return 0;
}
