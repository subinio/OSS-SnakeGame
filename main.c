#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

/* Keyboard Input */
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13
#define ESC 27

/* Size of GameBoard */
#define BOARD_WIDTH 45
#define BOARD_HEIGHT 23

/* Game Border */
#define TOP_BORDER 5
#define BOTTOM_BORDER 27
#define LEFT_BORDER 5
#define RIGHT_BORDER 49

typedef struct Snake {
	COORD pos;
	int dir;
	struct Snake * pre;
	struct Snake * next;
}Snake;

typedef struct Food {
	COORD pos;
}Food;

Snake * Head;
Snake * Tail;

Food food;

/* Functions Declaration */
static int wait;
static int lives;
static int score;
static int speed;


static char MAP[23][45] =
{
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
};

void InitInfo(void);
void InitSnake(void);
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
void RelocateFood(void);
void RelocateSnake(void);

int main(void)
{
	system("title Snake Game(KSNB)");
	system("mode con cols=112 lines=33");
	
	RemoveCursor();

	srand((unsigned int)time(0)); 

	InitInfo();
	InitSnake();

	DrawTitle();
	DrawMap();
	
	RelocateFood();

	while (lives) 
	{
		Display();
		CheckSnakeDie(MoveSnake());
		GetInput();
		EatFood();
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

void InitInfo(void)
{
	wait = 150;
	lives = 100;
	score = 0;
	speed = 1;
}

void InitSnake(void)
{
	Head = (Snake *)malloc(sizeof(Snake));
	Head->pre = NULL;
	Head->next = NULL;

	Head->pos.X = (rand() % (BOARD_WIDTH - 2)) + LEFT_BORDER + 1;
	Head->pos.Y = (rand() % (BOARD_HEIGHT - 2)) + TOP_BORDER + 1;
	Head->dir = DOWN;

	Tail = Head;
}

void DrawSnake(void)
{
	Snake * temp = Head;

	while (temp != NULL)
	{
		SetCurrentCursorPos(temp->pos.X, temp->pos.Y);
		printf("¿");

		temp = temp->next;
	}
}

void DelSnake(void)
{
	Snake * temp = Head;

	while (temp != NULL)
	{
		SetCurrentCursorPos(temp->pos.X, temp->pos.Y);
		printf("  ");

		temp = temp->next;
	}
}

void DrawFood(void)
{
	SetCurrentCursorPos(food.pos.X, food.pos.Y);
	printf("¿");
}

void DrawMap(void)
{
	int i, j = 0;

	SetCurrentCursorPos(0, 5);
	
	for (i = 0; i < BOARD_HEIGHT; i++) 
	{
		printf("          ");
		for (j = 0; j < BOARD_WIDTH; j++) 
		{
			if (MAP[i][j] == 1)
				printf("¿");
		
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

bool IsCollisionTopBorder(void) 
{
	return (Head->pos.Y <= TOP_BORDER);
}

bool IsCollisionBottomBorder(void) 
{
	return (Head->pos.Y >= BOTTOM_BORDER);
}

bool IsCollisionLeftBorder(void) 
{
	return (Head->pos.X <= LEFT_BORDER);
}

bool IsCollisionRightBorder(void) 
{
	return (Head->pos.X >= RIGHT_BORDER);
}

int MoveSnake(void)
{
	Snake * temp = Tail;
	while (temp != Head) {
		temp->pos.X = temp->pre->pos.X;
		temp->pos.Y = temp->pre->pos.Y;
		temp->dir = temp->pre->dir;
		
		temp = temp->pre;
	}
	switch (Head->dir)
	{
	case UP:
		Head->pos.Y--;
		if (IsCollisionTopBorder()) 
		{
			return 0;
		}
		else 
		{
			return 1;
		}
		break;
	
	case DOWN:
		Head->pos.Y++;
		if (IsCollisionBottomBorder()) 
		{
			return 0;
		}
		else 
		{
			return 1;
		}
		break;
	
	case LEFT:
		Head->pos.X--;
		if (IsCollisionLeftBorder()) 
		{
			return 0;
		}
		else 
		{
			return 1;
		}
		break;
	
	case RIGHT:
		Head->pos.X++;
		if (IsCollisionRightBorder()) 
		{
			return 0;
		}
		else 
		{
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
		Head->dir = _getch();
		MoveSnake(Head->dir);
	}
}

void RelocateFood(void) 
{
	food.pos.X = (rand() % (BOARD_WIDTH - 2)) + LEFT_BORDER + 1;
	food.pos.Y = (rand() % (BOARD_HEIGHT - 2)) + TOP_BORDER + 1;

	DrawFood();
}

void RelocateSnake(void) 
{
	Head->pos.X = (rand() % (BOARD_WIDTH - 2)) + LEFT_BORDER + 1;
	Head->pos.Y = (rand() % (BOARD_HEIGHT - 2)) + TOP_BORDER + 1;
}

void AddTail(void) 
{

	Snake * new = (Snake *)malloc(sizeof(Snake));
	
	if (Tail == NULL) {
		
		new->dir = Head->dir;
		new->pos.X = Head->pos.X;
		new->pos.Y = Head->pos.Y + 1;
		new->pre = Head;
		Tail->next = NULL;
		Head->next = Tail;
		Tail = new;
		return;
	}

	switch (Tail->dir)
	{
	case UP:
		new->pos.X = Tail->pos.X;
		new->pos.Y = Tail->pos.Y - 1;
		new->dir = Tail->dir;
		break;

	case DOWN:
		new->pos.X = Tail->pos.X;
		new->pos.Y = Tail->pos.Y + 1;
		new->dir = Tail->dir;
		break;

	case LEFT:
		new->pos.X = Tail->pos.X + 1;
		new->pos.Y = Tail->pos.Y;
		new->dir = Tail->dir;
		break;

	case RIGHT:
		new->pos.X = Tail->pos.X - 1;
		new->pos.Y = Tail->pos.Y;
		new->dir = Tail->dir;
		break;

	default:
		break;
	}
	
	Tail->next = new;
	new->pre = Tail;
	new->next = NULL;
	Tail = new;
}

void EatFood(void)
{
	if (Head->pos.Y == food.pos.Y && Head->pos.X == food.pos.X)
	{
		score++;

		AddTail();
		RelocateFood();

		if (score == 5)
		{
			wait = 100;
			speed++;
		}
		else if (score == 7)
		{
			wait = 80;
			speed++;
		}
		else if (score == 9)
		{
			wait = 50;
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
