#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");
    int x1,x2,y1,y2;
    fscanf(inp_file, "target area: x=%d..%d, y=%d..%d\n", &x1, &x2, &y1, &y2);
    fclose(inp_file);

    int max_y = 0;
    for (int i = 1;  i < abs(y1); ++i) {
        max_y += i;
    }
    printf("%d\n", max_y);
}
