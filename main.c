#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Rule {
    int i;
    int b[8];
};

//prototypess
struct Rule fillRule(struct Rule rule);
int *make_random_board(int *board, int size);
int *update_board(int *board, int *new_board, int size, struct Rule rule);
void print_board(int *board, int size);

int main() {
    int rule_key[8][3] = {{1,1,1},{1,1,0},{1,0,1},{1,0,0},{0,1,1},{0,1,0},{0,0,1},{0,0,0}};

    int BOARD_SIZE = 80;
    int *board = (int *)malloc(sizeof(int) * BOARD_SIZE);
    int *temp_board = (int *)malloc(sizeof(int) * BOARD_SIZE);
    
    //random setup
    time_t t;
    srand((unsigned) time(&t));

    //fillRule test
    struct Rule rule;
    rule.i = 102;

    rule = fillRule(rule);
    
    board = make_random_board(board, BOARD_SIZE);
    for (int i = 0; i < 10000; i++) {
        print_board(board, BOARD_SIZE);
        board = update_board(board, temp_board, BOARD_SIZE, rule);
    }
}

//functions
struct Rule fillRule(struct Rule rule) {
    int x = rule.i;
    
    for (int i = 7; i > -1; i--) {
        rule.b[i] = x % 2;
        x /= 2;
    }
    
    return rule;
}

int *make_random_board(int *board, int size) {
    for (int i = 0; i < size; i++) {
        board[i] = rand() % 2;
    }
    return board;
}

int *update_board(int *board, int *new_board, int size, struct Rule rule) {
    int cur[3];
    int bin;
    for (int i = 0; i < size; i++) {
        // left of current pos
        cur[0] = ((i - 1) < 0) ? 0 : board[i - 1];
        // current pos
        cur[1] = board[i];
        // right of current pos
        cur[2] = ((i + 1) >= size) ? 0 : board[i + 1];

        bin = cur[2] + (cur[1] * 2) + (cur[0] * 4);

        new_board[i] = rule.b[bin];
    }
    return new_board;
}

void print_board(int *board, int size) {
    for (int i = 0; i < size; i++) {
        char c = (board[i] == 1) ? '#' : ' ';
        printf("%c", c);
    }
    printf("\n");
}

