#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define BUFFER_CAP 1000

typedef struct Node {
    int r;
    int c;
    int risk;
} NODE;

int cave[BUFFER_CAP][BUFFER_CAP] = {0};
int dist[BUFFER_CAP][BUFFER_CAP] = {0};
int n_columns = 0;
int n_rows = 0;
int heap_len = 0;


int min_child(NODE **heap, int v)
{
    int left = 2*v+1;
    int right = 2*v+2;
    if (right == heap_len)
        return left;
    if (heap[left]->risk < heap[right]->risk)
        return left;
    return right;
}

void swap(NODE *a, NODE *b)
{
    NODE tmp = *a;
    *a = *b;
    *b = tmp;
}

void heap_insert(NODE **heap, int r, int c, int risk)
{
    int i = heap_len;
    heap[heap_len] = malloc(sizeof(NODE));
    heap[heap_len]->r = r;
    heap[heap_len]->c = c;
    heap[heap_len++]->risk = risk;
    int parent = (i-1) >> 1;
    while (i > 0 && heap[parent]->risk > heap[i]->risk) {
        swap(heap[parent], heap[i]);
        i = parent;
        parent = (parent-1) >> 1;
    }
}

NODE *pop_min(NODE **heap)
{
    swap(heap[0], heap[--heap_len]);
    int i = 0;
    NODE *min_risk = (heap)[heap_len];
    while (i < heap_len >> 1 && heap[i]->risk > heap[min_child(heap, i)]->risk) {
        int mc = min_child(heap, i);
        swap(heap[i], heap[mc]);
        i = mc;
    }
    return min_risk;
}

int in_heap(NODE **heap, int r, int c)
{
    for (int i=0; i<heap_len; ++i) {
        if (heap[i]->r == r && heap[i]->c == c)
            return 1;
    }
    return 0;
}

void dijkstras(NODE **heap)
{
    int dir[8] = {-1, 0, 1, 0, 0, 1, 0, -1};
    while (heap_len > 0) {
        NODE *mv = pop_min(heap);
        int r = mv->r;
        int c = mv->c;
        int risk = mv->risk;
        free(mv);
        for (int i=0; i<8; i+=2) {
            int rr = r + dir[i];
            int cc = c + dir[i+1];
            if (rr < 0 || rr >= n_rows*5 || cc < 0 || cc >= n_columns*5)
                continue;
            int alt = risk + cave[rr][cc];
            if (alt < dist[rr][cc]) {
                dist[rr][cc] = alt;
                if (!in_heap(heap, rr, cc)) {
                    heap_insert(heap, rr, cc, alt);
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    FILE *inp_file = fopen(argv[1], "r");
    char line[BUFFER_CAP];

    for (int r=0; fgets(line, BUFFER_CAP, inp_file) != NULL; ++r) {
        line[strcspn(line, "\n")] = 0;
        n_columns = (int)strlen(line);
        for (int c=0; c < n_columns; ++c) {
            cave[r][c] = line[c] - '0';
            dist[r][c] = INT_MAX;
        }
        ++n_rows;
    }
    fclose(inp_file);
    dist[0][0] = 0;
    /* part 2 */
    for (int r=0; r<n_rows; ++r) {
        for (int c=0; c<n_columns; ++c) {
            int orig_val = cave[r][c];
            for (int dr=0; dr<5; ++dr) {
                for (int dc=0; dc<5; ++dc) {
                    if (dr == 0 && dc == 0)
                        continue;
                    int rr = (dr * n_rows) + r;
                    int cc = (dc * n_columns) + c;
                    int new_val = orig_val + dr + dc;
                    if (new_val > 9)
                        new_val = (new_val % 10) + 1;
                    cave[rr][cc] = new_val;
                    dist[rr][cc] = INT_MAX;
                }
            }
        }
    }

    /* static NODE *prioq; */
    NODE *prioq;
    heap_insert(&prioq, 0, 0, 0);
    dijkstras(&prioq);

    printf("%d\n", dist[n_rows-1][n_columns-1]);
    printf("%d\n", dist[n_rows*5-1][n_columns*5-1]);
    return 0;
}
