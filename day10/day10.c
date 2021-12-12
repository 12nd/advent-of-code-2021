#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_CAP 1024

char b_open[10] = "([{<";
char b_c_pair[10] = ")(][}{><";


/* basic stack with no overflow protection or any extras */
struct STACK
{
    char items[BUFFER_CAP];
    int top;
};

void push(struct STACK *stack, char x)
{
    stack->items[++stack->top] = x;
}

char pop(struct STACK *stack)
{
    return stack->items[stack->top--];
}

int is_empty(struct STACK *stack)
{
    return stack->top == -1;
}

/* compare function without subtraction to work with unsigned long long */
int compare (const void *a, const void *b)
{
    const unsigned long ai = *( const unsigned long* )a;
    const unsigned long bi = *( const unsigned long* )b;
    if(ai < bi) {
        return -1;
    } else if(ai > bi) {
        return 1;
    } else {
        return 0;
    }
}

int get_score(char bracket, int part)
{
    if (part == 1) {
        switch(bracket) {
            case ')':
                return 3;
            case ']':
                return 57;
            case '}':
                return 1197;
            case '>':
                return 25137;
        }
    } else if (part == 2) {
        switch(bracket) {
            case '(':
                return 1;
            case '[':
                return 2;
            case '{':
                return 3;
            case '<':
                return 4;
        }
    }
    return 0;
}

unsigned long long pt2[BUFFER_CAP] = {0};
int pt2_len = 0;

/* finds corrupt lines (also fixes unfinished lines for part 2) */
int find_corrupt(char *line)
{
    /* initialise stack (probably should have a function to do this) */
    struct STACK *stack = (struct STACK*)malloc(sizeof(struct STACK));
    stack->top = -1;
    for (int i = 0; *(line + i) != '\0'; ++i) {
        char bracket = *(line + i);
        /* if open bracket */
        if (strchr(b_open, bracket) != NULL) {
            push(stack, bracket);
        }
        /* if close bracket is not equal to the corresponding close from stack */
        else if (pop(stack) != *(strchr(b_c_pair, bracket) + 1)) {
            free(stack);
            return get_score(bracket, 1);
        }
    }
    unsigned long long score = 0;
    while (!is_empty(stack)) {
        score = score * 5 + (unsigned long long)get_score(pop(stack), 2);
    }
    pt2[pt2_len++] = score;
    free(stack);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");
    char line[BUFFER_CAP] = {0};

    int pt1 = 0;

    while (fgets(line, BUFFER_CAP, inp_file) != NULL) {
        line[strcspn(line, "\n")] = 0;

        pt1 += find_corrupt(line);
    }

    qsort(pt2, (unsigned long)pt2_len, sizeof(unsigned long long), compare);

    fclose(inp_file);

    printf("%d\n", pt1);
    printf("%llu\n", pt2[pt2_len >> 1]);
}
