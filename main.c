#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

/* boolean type */
#define false 0
#define true 1
#define bool int

/* Keyboard Input*/
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13
#define ESC 27

/* Size of GameBoard*/
#define BOARD_WIDTH 20
#define BOARD_HEIGHT 8

/*Game Border*/
#define TOP_BORDER 0
#define BOTTOM_BORDER 9
#define LEFT_BORDER 1
#define RIGHT_BORDER 20

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

void Init(void);
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

	Init();

	InitMap();
	while (snake.lives) {
		Display();
		Die(MoveSnake());
		GetInput();
		EatFood();
		system("cls");
	}
	return 0;
}



void Init(void)
{
	snake.wait = 500;
	snake.direction = DOWN;
	snake.lives = 3;
	score = 0;
	speed = 1;
}

void InitMap(void)
{
	snake.pos.X = (rand() % BOARD_WIDTH) + 1;
	snake.pos.Y = (rand() % BOARD_HEIGHT) + 1;

	food.pos.X = (rand() % BOARD_WIDTH) + 1;
	food.pos.Y = (rand() % BOARD_HEIGHT) + 1;

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
	char TITLE[3][25] =
	{ "___________ __________",
		"|    A SNAKE GAME    |",
		"|********************|",
	};

	int i = 0;
	for (i = 0; i < 3; i++)
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

bool IsCollisionTopBorder(void) {
	return (snake.pos.Y <= TOP_BORDER + 1);
}

bool IsCollisionBottomBorder(void) {
	return (snake.pos.Y >= BOTTOM_BORDER + 1);
}

bool IsCollisionLeftBorder(void) {
	return (snake.pos.X <= LEFT_BORDER);
}

bool IsCollisionRightBorder(void) {
	return (snake.pos.X >= RIGHT_BORDER);
}

int MoveSnake(void)
{
	switch (snake.direction)
	{
	case UP:
		if (IsCollisionTopBorder())
			return 0;
		else {
			snake.pos.Y--;
			return 1;
		}
		break;
	case DOWN:
		if (IsCollisionBottomBorder())
			return 0;
		else {
			snake.pos.Y++;
			return 1;
		}
		break;
	case LEFT:
		if (IsCollisionLeftBorder())
			return 0;
		else {
			snake.pos.X--;
			return 1;
		}
		break;
	case RIGHT:
		if (IsCollisionRightBorder())
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

		food.pos.X = (rand() % BOARD_WIDTH) + 1;
		food.pos.Y = (rand() % BOARD_HEIGHT) + 1;

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

		snake.pos.X = (rand() % BOARD_WIDTH) + 1;
		snake.pos.Y = (rand() % BOARD_HEIGHT) + 1;
	}
}
