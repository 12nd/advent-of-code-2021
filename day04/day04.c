#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BOARD
{
    int board[5][5];
    int mark[5][5];
};

struct BOARD playBingo(struct BOARD board, int move)
{
    for (int i=0; i<5; ++i) {
        for (int j=0; j<5; ++j) {
            if (move == board.board[i][j])
                board.mark[i][j] = 1;
            else if (board.mark[i][j] != 1)
                board.mark[i][j] = 0;
        }
    }
    return board;
}

int checkWin(struct BOARD board)
{
    int vCnt[5] = {0};
    int dCnt[2] = {0};
    for (int i=0; i<5; ++i) {
        for (int j=0; j<5; ++j) {
            if (board.mark[i][j] == 0)
                break;
            else if (j == 4)
                /* horizontal win */
                return 1;
            else if (i == j)
                ++dCnt[0];
            else if (i + j == 4)
                ++dCnt[1];
            else
                ++vCnt[j];
        }
    }
    /* vertical win */
    for (int i=0; i<5; ++i) {
        if (vCnt[i] == 5)
            return 1;
    }
    /* diagonal win */
    for (int i=0; i<2; ++i) {
        if (dCnt[i] == 5)
            return 1;
    }
    return 0;
}

int calcScore(struct BOARD board, int move)
{
    int score = 0;
    for (int i=0; i<5; ++i) {
        for (int j=0; j<5; ++j) {
            if (board.mark[i][j] == 0)
                score += board.board[i][j];
        }
    }
    return score * move;
}

int main(void)
{
    FILE *inFile = fopen("input.txt", "r");
    char line[1000];
    int moves[1000] = {0};
    int nMoves = 0;
    struct BOARD boards[1000];
    int nBoards = 1;

    fgets(line, 900, inFile);
    char *t = strtok(line, ",");
    while (t != NULL) {
        moves[nMoves++] = atoi(t);
        t = strtok(NULL, ",");
    }

    /* reading board */
    int i = 0;
    while (fgets(line, 500, inFile) != NULL) {
        if (*line == '\n')
            continue;
        if (i == 5) {
            nBoards++;
            i = 0;
        }
        t = strtok(line, " ");
        for (int j=0; j<5; ++j) {
            boards[nBoards-1].board[i][j] = atoi(t);
            t = strtok(NULL, " ");
        }
        ++i;
    }

    /* play bingo */
    for (int m=0; m<nMoves; ++m) {
        for (int b=0; b<nBoards; ++b){
            boards[b] = playBingo(boards[b], moves[m]);
            if (checkWin(boards[b])) {
                printf("%d\n", calcScore(boards[b], moves[m]));
                return 0;
            }
        }
    }
    printf("No winner");
    return 0;
}
