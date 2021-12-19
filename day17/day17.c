#include <stdio.h>
#include <stdlib.h>

int x1,x2,y1,y2;

/* px, py = probe position at each step */
/* vx, vy = velocity */
int launch(int px, int py, int vx, int vy)
{
    px += vx;
    py += vy;
    /* overshot */
    if (px > x2 || py < y1)
        return 0;
    /* hit */
    if (px >= x1 && py <= y2)
        return 1;
    /* have not overshot or hit */
    return launch(px, py, vx - (vx > 0), vy - 1);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");
    fscanf(inp_file, "target area: x=%d..%d, y=%d..%d\n", &x1, &x2, &y1, &y2);
    fclose(inp_file);

    /* part 1 */
    printf("%d\n", (y1*(y1+1))>>1);

    /* part 2 */
    int out = 0;
    for (int vx=1; vx <= x2; ++vx) {
        for (int vy=y1; vy < -y1; ++vy) {
            out += launch(0, 0, vx, vy);
        }
    }

    printf("%d\n", out);
}
