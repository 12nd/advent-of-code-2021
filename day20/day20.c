#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


bool iea[512] = {0};

bool image[500][500] = {0};
int rt = 200;
int ct = 200;
int rlen = 0;
int clen = 0;
bool img_cpy[500][500] = {0};

int bin_to_dec(char *bin)
{
    char *tmp = {0};
    return (int)strtol(bin, &tmp, 2);
}

bool enhance_pix(int r, int c)
{
    char pixels[10] = {0};
    for (int i=-1; i<2; ++i) {
        for (int j=-1; j<2; ++j) {
            if (image[r+i][c+j] == 1)
                strcat(pixels, "1");
            else
                strcat(pixels, "0");
        }
    }
    return iea[bin_to_dec(pixels)];
}

int enhance(bool on)
{
    memcpy(img_cpy, image, 500 * 500 * sizeof(bool));
    for (int rr=rt-1; rr < rt + rlen+1; ++rr) {
        for (int cc=ct-1; cc <= ct + clen+1; ++cc)
            img_cpy[rr][cc] = enhance_pix(rr, cc);
    }
    if (on)
        memset(image, 1, 500*500*sizeof(bool));
    else
        memset(image, 0, 500*500*sizeof(bool));
    --rt;
    --ct;
    rlen+=2;
    clen+=2;
    int count = 0;
    for (int i=rt; i<rt+rlen; ++i) {
        for (int j=ct; j<ct+clen; ++j) {
            image[i][j] = img_cpy[i][j];
            count += image[i][j];
        }
    }
    return count;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    char line[600];

    fgets(line, sizeof(line), fp);
    for (int i=0; i<512; ++i) {
        if (line[i] == '#')
            iea[i] = 1;
    }
    fseek(fp, 1, SEEK_CUR);
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = 0;
        for (int i=0; i<(int)strlen(line); ++i) {
            if (line[i] == '#')
                image[rt + rlen][ct + i] = 1;
        }
        if ((int)strlen(line) > clen)
            clen = (int)strlen(line);
        ++rlen;
    }
    fclose(fp);

    int count = 0;
    for (int i=0; i<50; ++i) {
        count = enhance(iea[0] && !(i%2));
        if (i == 1)
            printf("%d\n", count);
    }
    printf("%d\n", count);

    return 0;
}
