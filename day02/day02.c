#include <stdio.h>
#include <stdlib.h>

struct COMMAND {
    char dir;
    int dist;
};

struct COMMAND parseLine(char *line) {
    struct COMMAND out;
    out.dir = line[0];
    if (out.dir == 'f') {
        sscanf(line+8, "%d", &out.dist);
    } else if (out.dir == 'd') {
        sscanf(line+5, "%d", &out.dist);
    } else if (out.dir == 'u') {
        sscanf(line+3, "%d", &out.dist);
    } else {
        printf("unreachable\n");
        exit(1);
    }
    return out;
}

int main(void) {
    FILE *inFile;
    int posX = 0;
    int posY = 0;
    int aim = 0;
    int posH = 0;
    int posD = 0;
    char line[20];

    inFile = fopen("input.txt", "r");

    while (fgets(line, 20, inFile) != NULL) {
        struct COMMAND cmd = parseLine(line);
        if (cmd.dir == 'f') {
            posX += cmd.dist;
            posH += cmd.dist;
            posD += aim * cmd.dist;
        } else if (cmd.dir == 'd') {
            posY += cmd.dist;
            aim += cmd.dist;
        } else if (cmd.dir == 'u') {
            posY -= cmd.dist;
            aim -= cmd.dist;
        }
    }
    fclose(inFile);

    printf("%d\n", posX * posY);
    printf("%d\n", posH * posD);

    return 0;
}
