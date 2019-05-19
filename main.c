#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>


// GLOBAL CONSTANTS
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13
#define ESC 27

typedef struct Snake {
	COORD pos;
	int wait;
	int lives;
	int direction;
}Snake;

typedef struct Food {
	COORD pos;
}Food;

Snake snake;
Food food;

static int score;
static int speed;

static char TITLE[3][25] =
{ "___________ __________",
"|    A SNAKE GAME    |",
"|********************|",
};

static char MAP[15][25] =
{	
	"___________ __________",
	"|                    |",
	"|                    |" ,
	"|                    |" ,
	"|                    |" ,
	"|                    |" ,
	"|                    |" ,
	"|                    |" ,
	"|                    |" ,
	"|                    |" ,
	"|                    |" ,
	"----------------------"
};
                 
void init(void);
void InitMap(void);
void DrawSnake(void);
void DelSnake(void);
void Display(void);
int MoveSnake(void);
void GetInput(void);
void EatFood(void);
void Die(int a);
void DrawTitle(void);
void DrawScore(void);
void DrawMap(void);


int main(void)
{
	srand(time(0));

	init();

	InitMap();
	while (snake.lives){
		Display();
		Die(MoveSnake());
		GetInput();
		EatFood();
		system("cls");
	}
	return 0;
}



void init(void) 
{
	snake.wait = 500;
	snake.direction = DOWN;
	snake.lives = 3;
	score = 0;
	speed = 1;
}

void InitMap(void)
{
	snake.pos.X = (rand() % 20) + 1;
	snake.pos.Y = (rand() % 8) + 1;

	food.pos.X = (rand() % 20) + 1;
	food.pos.Y = (rand() % 8) + 1;

	MAP[food.pos.Y][food.pos.X] = 'o';

}

void DrawSnake(void)
{
	MAP[snake.pos.Y][snake.pos.X] = '*';
}

void DelSnake(void)
{
	MAP[snake.pos.Y][snake.pos.X] = ' ';
}

void DrawMap(void)
{
	int i = 0;
	for (i = 0; i < 12; i++)
		puts(MAP[i]);
}

void DrawTitle(void)
{
	int i = 0;
	for (i = 0; i < 4; i++)
		puts(TITLE[i]);
}

void DrawScore(void)
{
	printf("\n\nScore: %d", score);
	printf("\nLives: %d", snake.lives);
	printf("\nSpeed: %d", speed);
}

void Display(void)
{
	DrawSnake();

	DrawTitle();

	DrawMap();
	
	DrawScore();

	Sleep(snake.wait);

	DelSnake();
}

int MoveSnake(void)
{
	switch (snake.direction)
	{
	case UP:
		if (snake.pos.Y < 2)
			return 0;
		else {
			snake.pos.Y--;
			return 1;
		}
		break;
	case DOWN:
		if (snake.pos.Y > 9)
			return 0;
		else {
			snake.pos.Y++;
			return 1;
		}
		break;
	case LEFT:
		if (snake.pos.X <= 1)
			return 0;
		else {
			snake.pos.X--;
			return 1;
		}
		break;
	case RIGHT:
		if (snake.pos.X >= 20)
			return 0;
		else {
			snake.pos.X++;
			return 1;
		}
		break;
	default:
		return 1;
	}
}

void GetInput(void)
{
	if (_kbhit()) {
		snake.direction = _getch();
		MoveSnake(snake.direction);
	}
}

void EatFood(void)
{
	if (snake.pos.Y == food.pos.Y && snake.pos.X == food.pos.X)
	{
		score++;

		food.pos.X = (rand() % 20) + 1;
		food.pos.Y = (rand() % 8) + 1;

		MAP[food.pos.Y][food.pos.X] = 'o';
		if (score == 5)
		{
			snake.wait = 200;
			speed++;
		}
		else if (score == 7)
		{
			snake.wait = 100;
			speed++;
		}
		else if (score == 9)
		{
			snake.wait = 0;
			speed++;
		}

	}

}


void Die(int a)
{
	if (!a)
	{
		snake.lives--;

		snake.pos.X = (rand() % 20) + 1;
		snake.pos.Y = (rand() % 8) + 1;
	}
}