#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int pop(struct STACK *stack)
{
    return stack->items[stack->top--];
}



char find_corrupt(char *line)
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
            return bracket;
        }
    }
    free(stack);
    return 0;
}

int get_score(char bracket)
{
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

    int score = 0;

    while (fgets(line, BUFFER_CAP, inp_file) != NULL) {
        line[strcspn(line, "\n")] = 0;

        score += get_score(find_corrupt(line));
    }

    fclose(inp_file);

    printf("%d", score);
}
