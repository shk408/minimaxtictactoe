#include <limits.h>
#include <stdio.h>

void printboard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
}

int movesleft(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') return 1;
        }
    }
    return 0;
}

int evaluate(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == 'X') return 10;
            else if (board[i][0] == 'O') return -10;
        }
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == 'X') return 10;
            else if (board[0][i] == 'O') return -10;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 'X') return 10;
        else if (board[0][0] == 'O') return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 'X') return 10;
        else if (board[0][2] == 'O') return -10;
    }

    return 0;
}

int minimax(char board[3][3], int depth, int makemove) {
    int score=evaluate(board);

    if(score==10) return score-depth;
    if(score==-10) return score+depth;

    if(makemove) {
        int best=INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = 'X';
                    best=(best>minimax(board, depth+1, 0)?best:minimax(board, depth+1, 0));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
    else {
        int best=INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = 'O';
                    int move=minimax(board, depth+1, 1);
                    best=(move<best)?move:best;
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

void bestmove(char board[3][3], int *row, int *col) {
    int bestvalue=INT_MIN;
    *row=*col=-1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = 'X';
                int move=minimax(board, 0, 0);
                board[i][j] = '_';

                if(move>bestvalue) {
                    bestvalue=move;
                    *row=i;
                    *col=j;
                }
            }
        }
    }
}

int main() {
    char board[3][3] = {
        {'_', '_', '_'},
        {'_', '_', '_'},
        {'_', '_', '_'}
    };

    int playerturn;
    printf("do you want to move first? 1 for yes, 0 for no");
    scanf("%d",&playerturn);

    while(movesleft(board)) {
        printboard(board);

        if(evaluate(board)==10) {
            printf("Computer wins\n");
            break;
        }
        if(evaluate(board)==-10) {
            printf("player wins\n");
            break;
        }

        int row, col;
        if(playerturn==1) {
            printf("enter move");
            scanf("%d %d",&row,&col);

            if(board[row][col]=='_') {
                board[row][col]='O';
                playerturn=0;
            }
            else {
                printf("invalid move\n");
            }
        } else {
            bestmove(board,&row,&col);
            board[row][col]='X';
            playerturn=1;
        }
    }

    printboard(board);
    if(evaluate(board)==0) {
        printf("it's a draw");
    }
    return 0;
}