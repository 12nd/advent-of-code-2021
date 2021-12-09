#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DIGIT
{
    int segments[7];
};

int is_in(struct DIGIT a, struct DIGIT b, int len)
{
    int in = 0;
    for (int i=0; i<7; ++i) {
        if (a.segments[i] == 1 && b.segments[i] == 1)
            ++in;
    }
    if (in == len)
        return 1;
    return 0;
}

struct DIGIT parse_digit(char *str, int len) {
    struct DIGIT digit = {0};
    for (int i=0; i<len; ++i) {
        digit.segments[(int)str[i] - (int)'a'] = 1;
    }
    return digit;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");
    char line[5000];
    int pt1 = 0;
    int pt2 = 0;

    while(fgets(line, 4500, inp_file) != NULL) {
        line[strcspn(line, "\n")] = 0;
        struct DIGIT one = {0};
        struct DIGIT four = {0};
        struct DIGIT four_L = {0};
        char *t = strtok(line, " |");
        char num[4];
        num[0] = '\0';

        for (int i=0; i<10; ++i) {
            switch(strlen(t)) {
                case 2:
                    one = parse_digit(t, (int)strlen(t));
                    break;
                case 4:
                    four = parse_digit(t, (int)strlen(t));
                    break;
            }
            t = strtok(NULL, " |");
        }

        for (int s=0; s<7; ++s) {
            if (four.segments[s] != one.segments[s])
                four_L.segments[s] = 1;
            }

        /* output */
        for (int i = 0; i<4; ++i) {
            struct DIGIT digit = parse_digit(t, (int)strlen(t));
            switch(strlen(t)) {
                case 2:
                    ++pt1;
                    strcat(num, "1");
                    break;
                case 4:
                    ++pt1;
                    strcat(num, "4");
                    break;
                case 3:
                    ++pt1;
                    strcat(num, "7");
                    break;
                case 7:
                    ++pt1;
                    strcat(num, "8");
                    break;
                case 5:
                    if (is_in(one, digit, 2))
                        strcat(num, "3");
                    else if (is_in(four_L, digit, 2))
                        strcat(num, "5");
                    else
                        strcat(num, "2");
                    break;
                case 6:
                    if (is_in(four, digit, 4))
                        strcat(num, "9");
                    else if (is_in(four_L, digit, 2))
                        strcat(num, "6");
                    else
                        strcat(num, "0");
                    break;
            }
            t = strtok(NULL, " |");
        }
        pt2 += atoi(num);
    }


    printf("%d\n", pt1);
    printf("%d\n", pt2);
}
