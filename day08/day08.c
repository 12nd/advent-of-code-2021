#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");
    char line[5000];
    int count = 0;

    while(fgets(line, 4500, inp_file) != NULL) {
        line[strcspn(line, "\n")] = 0;
        char *t = strtok(line, " |");
        for (int i=0; i<14; ++i) {
            /* probs need other input in part 2 */
            if (i > 9) {
                switch(strlen(t))
                    case 2 : case 4 : case 3 : case 7 : {++count;}
            }
            t = strtok(NULL, " |");
        }
    }
    printf("%d\n", count);
}
