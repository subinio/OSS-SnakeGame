#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

/* Keyboard Input*/
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13
#define ESC 27

/* Size of GameBoard*/
#define BOARD_WIDTH 45
#define BOARD_HEIGHT 23

/*Game Border*/
#define TOP_BORDER 5
#define BOTTOM_BORDER 27
#define LEFT_BORDER 5
#define RIGHT_BORDER 49

typedef struct Snake {
	COORD pos;
}Snake;

typedef struct Food {
	COORD pos;
}Food;

Snake snake;
Food food;

/*Functions Declaration*/
static int wait;
static int lives;
static int direction;
static int score;
static int speed;


static char MAP[23][45] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},

{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 ,0,0,0,0,0, 0,0,0,0,0, 0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},

{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},

{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},

{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

void Init(void);
void InitMap(void);
void DrawSnake(void);
void DelSnake(void);
void Display(void);
int MoveSnake(void);
void GetInput(void);
void EatFood(void);
void CheckSnakeDie(int moving);
void DrawTitle(void);
void DrawScore(void);
void DrawMap(void);
void DrawFood(void);
void SetCurrentCursorPos(int x, int y);
void RemoveCursor(void);

int main(void)
{
	system("title Snake Game(KSNB)");
	system("mode con cols=112 lines=33");
	RemoveCursor();

	srand(time(0));

	Init();

	DrawTitle();
	DrawMap();
	InitMap();
	DrawFood();
	while (lives) {
		Display();
		CheckSnakeDie(MoveSnake());
		GetInput();
		EatFood();
		SetCurrentCursorPos(6 * 2, 28);
	}
	return 0;
}

void SetCurrentCursorPos(int x, int y)
{
	COORD position = { 2 * x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void Init(void)
{
	wait = 100;
	direction = DOWN;
	lives = 100;
	score = 0;
	speed = 1;
}

void InitMap(void)
{
	snake.pos.X = (rand() % (BOARD_WIDTH - 2)) + LEFT_BORDER + 1;
	snake.pos.Y = (rand() % (BOARD_HEIGHT - 2)) + TOP_BORDER + 1;

	food.pos.X = (rand() % (BOARD_WIDTH - 2)) + LEFT_BORDER + 1;
	food.pos.Y = (rand() % (BOARD_HEIGHT - 2)) + TOP_BORDER + 1;
}

void DrawSnake(void)
{
	SetCurrentCursorPos(snake.pos.X,snake.pos.Y);
	printf("%d",snake.pos.X);
}

void DelSnake(void)
{
	SetCurrentCursorPos(snake.pos.X, snake.pos.Y);
	printf("  ");
}

void DrawFood(void)
{
	SetCurrentCursorPos(food.pos.X, food.pos.Y);
	printf("б┌");
}

void DrawMap(void)
{
	int i = 0, j = 0;
	
	SetCurrentCursorPos(0, 5);
	for (i = 0; i < BOARD_HEIGHT; i++) {
		printf("          ");
		for (j = 0; j < BOARD_WIDTH; j++) {
			if (MAP[i][j] == 1)
				printf("бс");
			else
				printf("  ");
		}
		printf("\n");
	}
}

void DrawTitle(void)
{
	SetCurrentCursorPos(26, 2);
	printf("Snake Game");
}

void DrawScore(void)
{
	SetCurrentCursorPos(46, 1);
	printf("Score: %d", score);
	SetCurrentCursorPos(46, 2);
	printf("Lives: %d", lives);
	SetCurrentCursorPos(46, 3);
	printf("Speed: %d", speed);
}

void Display(void)
{
	DrawScore();

	DrawSnake();

	Sleep(wait);

	DelSnake();
}

bool IsCollisionTopBorder(void) {
	return (snake.pos.Y <= TOP_BORDER);
}

bool IsCollisionBottomBorder(void) {
	return (snake.pos.Y >= BOTTOM_BORDER);
}

bool IsCollisionLeftBorder(void) {
	return (snake.pos.X <= LEFT_BORDER);
}

bool IsCollisionRightBorder(void) {
	return (snake.pos.X >= RIGHT_BORDER);
}

int MoveSnake(void)
{
	switch (direction)
	{
	case UP:
		snake.pos.Y--;
		if (IsCollisionTopBorder()) {
			return 0;
		}
		else {
			return 1;
		}
		break;
	case DOWN:
		snake.pos.Y++;
		if (IsCollisionBottomBorder()) {
			return 0;
		}
		else {
			return 1;
		}
		break;
	case LEFT:
		snake.pos.X--;
		if (IsCollisionLeftBorder()) {

			return 0;
		}
		else {
			return 1;
		}
		break;
	case RIGHT:
		snake.pos.X++;
		if (IsCollisionRightBorder()) {
			return 0;
		}
		else {
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
		direction = _getch();
		MoveSnake(direction);
	}
}
void RelocateFood(void) {
	food.pos.X = (rand() % (BOARD_WIDTH - 2)) + LEFT_BORDER + 1;
	food.pos.Y = (rand() % (BOARD_HEIGHT - 2)) + TOP_BORDER + 1;

	DrawFood();
}

void RelocateSnake(void) {
	snake.pos.X = (rand() % (BOARD_WIDTH - 2)) + LEFT_BORDER + 1;
	snake.pos.Y = (rand() % (BOARD_HEIGHT - 2)) + TOP_BORDER + 1;
}
void EatFood(void)
{
	if (snake.pos.Y == food.pos.Y && snake.pos.X == food.pos.X)
	{
		score++;

		RelocateFood();

		if (score == 5)
		{
			wait = 200;
			speed++;
		}
		else if (score == 7)
		{
			wait = 100;
			speed++;
		}
		else if (score == 9)
		{
			wait = 0;
			speed++;
		}

	}

}


void CheckSnakeDie(int moving)
{
	if (!moving)
	{
		lives--;

		RelocateSnake();
	}
}