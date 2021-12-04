#include <stdio.h>

int main() {
    FILE *input;
    int posX = 0;
    int posY = 0;
    char line[10];
    int dist;

    input = fopen("input.txt", "r");

    while (fgets(line, 10, input) != NULL) {
        if (line[0] == 'f') {
            sscanf(line+8, "%d", &dist);
            posX += dist;
        }
        else if (line[0] == 'd') {
            sscanf(line+5, "%d", &dist);
            posY += dist;
        }
        else if (line[0] == 'u') {
            sscanf(line+3, "%d", &dist);
            posY -= dist;
        }
    }
    fclose(input);

    printf("%d\n", posX);
    printf("%d\n", posY);
    printf("%d\n", posX * posY);

    return 0;
}
