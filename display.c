#include "snake.h"

OUTPUT *init_display()
{
    int i;
    OUTPUT *p = (OUTPUT *)calloc(1,sizeof(OUTPUT));
    p->hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    p->cbs.X = XMAX;
    p->cbs.Y = YMAX;
    p->cwa.Right = XMAX-1;
    p->cwa.Bottom = YMAX-1;
    for(i = 0; i < YMAX*XMAX;++i)
        p->buffer[i].Char.AsciiChar = '#';
    return p;
}

void fill_corners(OUTPUT *p)
{
    int i;
    for(i=0;i<XMAX;++i)
    {
        p->buffer[i].Attributes = 3|8;
        p->buffer[XMAX*YMAX-1-i].Attributes = 3|8;
        p->buffer[i].Char.AsciiChar = 'X';
        p->buffer[XMAX*YMAX-1-i].Char.AsciiChar = 'X';
    }
    for(i=XMAX;i<XMAX*(YMAX-1);i+=XMAX)
    {
        p->buffer[i].Attributes = 3|8;
        p->buffer[i+XMAX-1].Attributes = 3|8;
        p->buffer[i].Char.AsciiChar = 'X';
        p->buffer[i+XMAX-1].Char.AsciiChar = 'X';
    }
}

static void display_scores(OUTPUT *p, FOOD *score)
{
    const COORD c0 = {XMAX+2,4};
    SetConsoleCursorPosition(p->hstdout,c0);
    printf("Score: %3d",++(score->score));
    do{
        score->x = rand() % (XMAX-1);
        score->y = rand() % (YMAX-1);
    }while(p->buffer[score->x+score->y*XMAX].Attributes);
}

void display_snake(SNK_CELL *s, OUTPUT *p, FOOD *score)
{
    SNK_CELL *s1 = s;
    p->buffer[score->x + score->y*XMAX].Attributes = 4|8;
    while(s)
    {
        p->buffer[s->x + s->y*XMAX].Attributes = 2|8;
        s = s->next;
    }
    if(s1->x == score->x && s1->y == score->y)
    {
        display_scores(p,score);
        add_tail(s1);
    }
    WriteConsoleOutputA(p->hstdout,p->buffer,p->cbs,p->c0,&(p->cwa));
    while(s1)
    {
        p->buffer[s1->x + s1->y*XMAX].Attributes = 0;
        s1 = s1->next;
    }
    p->buffer[score->x + score->y*XMAX].Attributes = 0;
}
