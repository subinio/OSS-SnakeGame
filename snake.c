#include "snake.h"

void add_tail(SNK_CELL *s)
{
    while(s->next)
        s = s->next;
    s->next = (SNK_CELL *)calloc(1,sizeof(SNK_CELL));
    s->next->x = s->x;
    s->next->y = s->y;
    s->next->prev = s;
}

SNK_CELL *init_snake()
{
    SNK_CELL *s = (SNK_CELL *)calloc(5,sizeof(SNK_CELL));
    s->next = s+1;
    s->x = XMAX/2;
    s->y = YMAX/2;
    s[1].next = s+2;
    s[1].prev = s;
    s[1].x = s->x-1;
    s[1].y = s->y;
    s[2].next = s+3;
    s[2].prev = s+1;
    s[2].x = s->x-2;
    s[2].y = s->y;
    s[3].next = s+4;
    s[3].prev = s+2;
    s[3].x = s->x-3;
    s[3].y = s->y;
    s[4].prev = s+3;
    s[4].x = s->x-4;
    s[4].y = s->y;
    return s;
}

void snake_movement(SNK_CELL *s, int direction)
{
    while(s->next)
        s = s->next;

    do{
        s->x = s->prev->x;
        s->y = s->prev->y;
        s = s->prev;
    }while(s->prev);

    switch(direction)
    {
        case SNAKE_RIGHT:
            s->x = (s->x + 1) % (XMAX-1);
            if(!(s->x))
                ++(s->x);
            break;
        case SNAKE_LEFT:
            if(!(--(s->x)))
                s->x = XMAX-2;
            break;
        case SNAKE_DOWN:
            s->y = (s->y + 1) % (YMAX-1);
            if(!(s->y))
                ++(s->y);
            break;
        case SNAKE_UP:
            if(!(--(s->y)))
                s->y = YMAX-2;
            break;
        default:
            break;
    }
}

int snake_collision(SNK_CELL *s)
{
    int tmpx = s->x;
    int tmpy = s->y;
    s = s->next;
    while(s)
    {
        if(tmpx == s->x && tmpy == s->y)
            return 1;
        s = s->next;
    }
    return 0;
}
