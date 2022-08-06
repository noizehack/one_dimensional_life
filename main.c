#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

struct Rule {
    int i;
    int b[8];
};

//prototypess
struct Rule fillRule(struct Rule rule);
int *make_random_board(int *board, int size);
int *make_one_dot_board(int *board, int size);
int *update_board(int *board, int *new_board, int size, struct Rule rule);
void print_board(int *board, int size, char on_c, char off_c);
void print_help(void);

//control c handler
bool running = true;
void sighandler(int sigint) {
    running = false;
}

int main(int argc, char *argv[]) {
    //control c quit handler
    signal(SIGINT, sighandler);

    // command line argument inputs
    if (argc > 8 || (argc > 1 && (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))) {
        print_help();
        return 1;
    } else {
        //rule
        struct Rule rule;
        rule.i = 30;
        if (argc > 1) {
            int x = atoi(argv[1]);
            rule.i = (x >= 0 && x <= 255) ? x : 30;
        }
        //start condition
        bool START_RND = false;
        if (argc > 2) {
            int x = atoi(argv[2]);
            START_RND = (x == 1) ? true : false;
        }
        //board size
        int BOARD_SIZE = 80;
        if (argc > 3) {
            int x = atoi(argv[3]);
            BOARD_SIZE = (x > 0) ? x : 80;
        }
        //frame time
        int FRAME_TIME = 100000;
        if (argc > 4) {
            int x = atoi(argv[4]);
            FRAME_TIME = (x > 0) ? x : 100000;
        }
        //generations
        int GENERATIONS = 1000;
        if (argc > 5) {
            int x = atoi(argv[5]);
            GENERATIONS = (x > 0) ? x : 1000;
        }
        //on char
        char ON_CHAR = '#';
        if (argc > 6) {
            ON_CHAR = argv[6][0];
        }
        //off char
        char OFF_CHAR = ' ';
        if (argc > 7) {
            OFF_CHAR = argv[7][0];
        }

        //setup
        //allocate board arrays
        int *board = (int *)malloc(sizeof(int) * BOARD_SIZE);
        int *temp_board = (int *)malloc(sizeof(int) * BOARD_SIZE);
        
        //random setup
        time_t t;
        srand((unsigned) time(&t));
        
        //fill out rule array
        rule = fillRule(rule);
        
        //make first board
        if (START_RND) {
            board = make_random_board(board, BOARD_SIZE);
        } else {
            board = make_one_dot_board(board, BOARD_SIZE);
        }
        
        //main loop
        int i = 0;
        while(running && i < GENERATIONS) {
            print_board(board, BOARD_SIZE, ON_CHAR, OFF_CHAR);
            board = update_board(board, temp_board, BOARD_SIZE, rule);
            usleep(FRAME_TIME);
            i++;
        }
        //free memmory and exit
        free(board);
        free(temp_board);
        return 0;
    }
}

//functions
struct Rule fillRule(struct Rule rule) {
    int x = rule.i;
    
    for (int i = 0; i < 8; i++) {
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

int *make_one_dot_board(int *board, int size) {
    int middle = (int) (size / 2);

    for (int i = 0; i < size; i++) {
        board[i] = (i != middle) ? 0 : 1;
    }
    return board;
}

int *update_board(int *board, int *new_board, int size, struct Rule rule) {
    int cur[3];
    int bin;
    for (int i = 0; i < size; i++) {
        // left of current pos
        cur[0] = ((i - 1) < 0) ? board[size - 1] : board[i - 1];
        // current pos
        cur[1] = board[i];
        // right of current pos
        cur[2] = ((i + 1) >= size) ? board[0] : board[i + 1];

        bin = cur[2] + (cur[1] * 2) + (cur[0] * 4);

        new_board[i] = rule.b[bin];
    }
    for (int i = 0; i < size; i++) {
        board[i] = new_board[i];
    }
    return board;
}
// has print side effects
void print_board(int *board, int size, char on_c, char off_c) {
    for (int i = 0; i < size; i++) {
        char c = (board[i] == 1) ? on_c : off_c;
        printf("%c", c);
    }
    printf("\n");
}
// has print side effects
void print_help(void) {
    printf("USAGE: ./oneDlife [RULE] [START_CONDITION] [BOARD_SIZE] [FRAME_TIME] [GENERATIONS] [ON_CHAR] [OFF_CHAR]\n\n");
    printf("PARAMETER(DEFAULT): EXPLANATION\n");
    printf("RULE(30): 0-255\n");
    printf("START_CONDITION(0): 0 = one dot in center, 1 = random board\n");
    printf("BOARD_SIZE(80): character width of the board\n");
    printf("FRAME_TIME(100000): uSecond delay between frames\n");
    printf("GENERATIONS(1000): number of generations to print\n");
    printf("ON_CHAR('#'): ASCII character that is printed to represent a 1\n");
    printf("OFF_CHAR(' '): ASCII character that is printed to represent a 0\n");
    printf("\nEXAMPLE USAGE\n");
    printf("./oneDlife 30 1 160 10000 10000 @ .\n");
}
