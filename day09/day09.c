#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* global variables */
char eval_line[500];
char prev_line[500];

int line_risk(char *line)
{
    int risk = 0;
    for(int i=0; *(line + i) != '\0'; ++i) {
        int prev = *(prev_line + i);
        int eval = *(eval_line + i);
        int next = *(line + i);
        int left = '9';
        int right = '9';
        if (i > 0)
            left = *(eval_line + i - 1);
        if (*(line + i + 1) != '\0')
            right = *(eval_line + i + 1);

        if (eval < prev && eval < next && eval && eval < left && eval < right) {
            risk += 1 + eval - '0';
        }
    }
    return risk;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");
    char line[500];
    /* initialise */
    fgets(eval_line, 300, inp_file);
    strcpy(prev_line,"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
    int risk = 0;

    /* start on second line line, evaluate risk for previous line*/
    while(fgets(line, 300, inp_file) != NULL) {
        line[strcspn(line, "\n")] = 0;

        risk += line_risk(line);

        strcpy(prev_line, eval_line);
        strcpy(eval_line, line);
    }
    /* last line */
    risk += line_risk("9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");

    printf("%d\n", risk);
}
