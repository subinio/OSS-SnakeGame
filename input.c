#include "snake.h"

void input_handling(OUTPUT *p, SNK_CELL *s)
{
    HANDLE hin;
    INPUT_RECORD input_rec;
    DWORD events,cmodebackup,n_events;
    int direction = SNAKE_RIGHT;
    FOOD scores = {XMAX/2,YMAX/2,-1};
    hin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hin,&cmodebackup);
    display_snake(s,p,&scores);
    for(;;)
    {
        GetNumberOfConsoleInputEvents(hin,&n_events);
        if(n_events)
        {
            ReadConsoleInput(hin, &input_rec, 1, &events);
            switch(input_rec.EventType)
            {
                case KEY_EVENT:
                    switch(input_rec.Event.KeyEvent.wVirtualKeyCode)
                    {
                        case VK_ESCAPE:
                            SetConsoleMode(hin,cmodebackup);
                            exit(EXIT_SUCCESS);
                            break;

                        case VK_TAB:
                            puts("Tab, oh wow!");
                            break;

                        case VK_LEFT:
                            if(direction != SNAKE_RIGHT)
                                direction = SNAKE_LEFT;
                            break;

                        case VK_RIGHT:
                            if(direction != SNAKE_LEFT)
                                direction = SNAKE_RIGHT;
                            break;

                        case VK_UP:
                            if(direction != SNAKE_DOWN)
                                direction = SNAKE_UP;
                            break;

                        case VK_DOWN:
                            if(direction != SNAKE_UP)
                                direction = SNAKE_DOWN;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            FlushConsoleInputBuffer(hin);
        }
        snake_movement(s, direction);
        display_snake(s,p,&scores);
        if(snake_collision(s))
            return;
        Sleep(100);
    }
}
