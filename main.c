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
}Snake;

typedef struct Food {
	COORD pos;
}Food;

Snake snake;
Food food;

static int score;
static int speed;
static int direction;

static char HEADER[4][25] =
{ "___________ __________",
"|    A SNAKE GAME    |",
"|********************|",
"___________ __________",
};
static char FOOTER[25] =
{
	"----------------------"
};
static char MAP[15][25] =
{
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
};


//함수 원형 선언
void Init();
void InitMap();
void DrawSnake();
void DelSnake();
int DrawMap();
void MoveSnake(int direction);
void GetInput();
void EatFood();
void Die(int a);

int main()
{
	srand(time(0));

	init();

	InitMap();
	direction = 80;
	while (snake.lives){
		Die(DrawMap());
		GetInput();
		EatFood();
		system("cls");
	}
	return 0;
}



void Init() {

	snake.wait = 500;
	snake.lives = 3;
	score = 0;
	speed = 1;
	direction = DOWN;

	return;
}

void InitMap()
{
	snake.pos.X = (rand() % 20) + 1;
	snake.pos.Y = (rand() % 8) + 1;

	food.pos.X = (rand() % 20) + 1;
	food.pos.Y = (rand() % 8) + 1;

	MAP[food.pos.Y][food.pos.X] = 'o';

}

void DrawSnake()
{
	MAP[snake.pos.Y][snake.pos.X] = '*';
}

void DelSnake()
{
	MAP[snake.pos.Y][snake.pos.X] = ' ';
}

int DrawMap()
{
	DrawSnake();
	for (int i = 0; i < 4; i++)
		puts(HEADER[i]);

	for (int i = 0; i < 10; i++)
		puts(MAP[i]);

	puts(FOOTER);

	printf("\n\nScore: %d", score);
	printf("\nLives: %d", snake.lives);
	printf("\nSpeed: %d", speed);

	Sleep(snake.wait);
	DelSnake();
}

void MoveSnake(int direction)
{
	switch (direction)
	{
	case UP:
		if (snake.pos.Y <= 0)
			return;
		else
			snake.pos.Y--;
		break;
	case DOWN:
		if (snake.pos.Y >= 9)
			return;
		else
			snake.pos.Y++;
		break;
	case LEFT:
		if (snake.pos.X <= 1)
			return;
		else
			snake.pos.X--;
		break;
	case RIGHT:
		if (snake.pos.X >= 20)
			return;
		else
			snake.pos.X++;
		break;
	default:
		return;
	}
}

void GetInput()
{
	int direction = 0;
	if (_kbhit()) {
		direction = _getch();
		MoveSnake(direction);
	}
	else
		return;
}

void EatFood()
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