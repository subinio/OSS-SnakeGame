#include "snake.h"

int main(void)
{
    OUTPUT *p = init_display();
    SNK_CELL *s = init_snake();
    srand((unsigned int)time(NULL));
    fill_corners(p);
    input_handling(p,s);
    return 0;
}
