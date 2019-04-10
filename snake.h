#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define XMAX 42
#define YMAX 24
#define SNAKE_RIGHT 0
#define SNAKE_LEFT 1
#define SNAKE_DOWN 2
#define SNAKE_UP 3

typedef struct OUT_BUF OUTPUT;
typedef struct SNAKE_ITSELF SNK_CELL;
typedef struct FOOD_ FOOD;

struct OUT_BUF{
    COORD c0;
    COORD cbs;
    SMALL_RECT cwa;
    HANDLE hstdout;
    CHAR_INFO buffer[YMAX*XMAX];
};

struct SNAKE_ITSELF{
    int x;
    int y;
    struct SNAKE_ITSELF *next;
    struct SNAKE_ITSELF *prev;
};

struct FOOD_{
    int x;
    int y;
    int score;
};

void input_handling(OUTPUT *, SNK_CELL *);
OUTPUT *init_display();
void fill_corners(OUTPUT *);
void display(OUTPUT *);
int snake_collision(SNK_CELL *);
void add_tail(SNK_CELL *);
SNK_CELL *init_snake();
void display_snake(SNK_CELL *, OUTPUT *, FOOD *);
void snake_movement(SNK_CELL *, int );

#endif // SNAKE_H_INCLUDED
