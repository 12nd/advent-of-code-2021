#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_CAP 1000

typedef struct Pair {
    int num;
    int level;
} PAIR;

PAIR homework[BUFFER_CAP][BUFFER_CAP] = {0};
int line_len[BUFFER_CAP] = {0};
int n_lines = 0;
PAIR buffer[BUFFER_CAP] = {0};
int buffer_len = 0;

void explode(int n)
{
    if (n == 0)
        buffer[n+2].num += buffer[n+1].num;
    else if (n >= buffer_len - 2)
        buffer[n-1].num += buffer[n].num;
    else {
        buffer[n-1].num += buffer[n].num;
        buffer[n+2].num += buffer[n+1].num;
    }
    buffer[n].num = 0;
    --buffer[n].level;
    if (n+1 < --buffer_len)
        memmove(buffer+n+1, buffer+n+2, sizeof(PAIR) * (unsigned long)(buffer_len - n - 1));
}

void split_num(int n)
{
    memmove(buffer+n+2, buffer+n+1, sizeof(PAIR) * (unsigned long)(buffer_len++ - n - 1));
    int prev = buffer[n].num;
    buffer[n].num = prev >> 1;
    ++buffer[n].level;
    buffer[n+1].num = (prev+1) >> 1;
    buffer[n+1].level = buffer[n].level;
}

void reduce_num(void)
{
    for (;;) {
        int cont = 0;
        for (int i=0; i<buffer_len; ++i) {
            if (buffer[i].level >= 4) {
                explode(i);
                i = -1;
            }
        }
        for (int i=0; i<buffer_len; ++i) {
            if (buffer[i].num >= 10) {
                split_num(i);
                cont = 1;
                break;
            }
        }
        if (!cont)
            break;
    }
}

void addition(int l)
{
    memcpy(buffer+buffer_len, homework[l], sizeof(PAIR) * (unsigned long)line_len[l]);
    buffer_len += line_len[l];
    for (int i=0; i<buffer_len; ++i) {
        ++buffer[i].level;
    }
    reduce_num();
}

int magnitude(void)
{
    for (int i=0; i<buffer_len-1; ++i) {
        if (buffer[i].level == buffer[i+1].level) {
            buffer[i].num = buffer[i].num * 3 + 2 * buffer[i+1].num;
            --buffer[i].level;
            if (i+1 < --buffer_len)
                memmove(buffer+i+1, buffer+i+2, sizeof(PAIR) * (unsigned long)(buffer_len - i - 1));
            i = -1;
        }
    }
    return buffer[0].num;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    int c = 0;
    int l = -1;
    /* read input */
    while (c != EOF)
    {
        c = fgetc(fp);
        if (c == ',')
            continue;
        else if (c == '[')
            ++l;
        else if (c == ']')
            --l;
        else if (c == '\n') {
            ++n_lines;
        } else {
            homework[n_lines][line_len[n_lines]].num = c - '0';
            homework[n_lines][line_len[n_lines]++].level = l;
        }
    }
    fclose(fp);

    /* part 1 */
    memcpy(buffer, homework[0], sizeof(PAIR) * (unsigned long)line_len[0]);
    buffer_len = line_len[0];
    for (int line=1; line<n_lines; ++line) {
        addition(line);
    }
    printf("%d\n", magnitude());

    /* part 2 */
    int max_mag = 0;
    for (int i=0; i<n_lines; ++i) {
        for (int j=0; j<n_lines; ++j) {
            if (i == j)
                continue;
            memcpy(buffer, homework[i], sizeof(PAIR) * (unsigned long)line_len[i]);
            buffer_len = line_len[i];
            addition(j);
            int mag = magnitude();
            if (mag > max_mag)
                max_mag = mag;
        }
    }
    printf("%d\n", max_mag);
}
