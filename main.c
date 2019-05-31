/**
* Snake Game
* =========================================================================================================================
* This is Derivative from..
* Author : Abduvokhid Abdukhakimov
* Source : https://github.com/abdulwahid2802/SnakeGame
* License : MIT license
* Copyright (c) 2018 , All Rights Reserved.
* =========================================================================================================================
* Derivative Developer : kimkyeongnam(https://github.com/kimkyeongnam), subinio(https://github.com/subinio)
* 
* =========================================================================================================================
* File : main.c
* Purpose : Reduce errors, write high-readability code, and activate Snake Games with enhancements
* How To Play : After running, you can move Snake only direction key(→,←,↑,↓)
* Limitations : None
* Error Handling : None(complete)
*
**/

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
#define DIR_KEY 224

/* GameMenu Options */
#define GAMESTART 20
#define EXIT 22

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

Snake * Head;   //이중연결리스트에서 뱀의 머리를 가르키는 포인터 (언제나 Head->pre는 NULL)
Snake * Tail;   //이중연결리스트에서 뱀의 맨 마지막 꼬리를 가르키는 포인터 (언제나 Tail->next는 NULL)

Food food;

/* Global variables */
static int wait;        // 뱀의 속력을 나타내지만 실제로는 뱀이 다음동작을 하기 전 기다리는 시간 (wait의 값이 감소할 수록 속력이 빨라짐)
static int lives;       // 뱀의 목숨 수
static int score;       // 화면에 출력되는 점수(먹이를 먹을때마다 +1씩 증가)
static int speed;       // 화면에 출력되는 속도 (1, 2, 3 ... 으로 표현)

/* Functions Declaration */
void SetCurrentCursorPos(int x, int y);
void RemoveCursor(void);
void InitInfo(void);
void InitSnake(void);
void DrawSnake(void);
void DelSnake(void);
int MoveSnake(void);
void ChkSnakeDie(int moving);
void DrawFood(void);
void GetInput(void);
void ControlSpeed(void);
void EatFood(void);
void Display(void);
void DrawTitle(void);
void DrawScore(void);
void DrawSpeed(void);
void DrawLives(void);
void DrawMap(void);
void RelocateFood(void);
void RelocateSnake(void);
bool IsCollisionTopBorder(void);
bool IsCollisionBottomBorder(void);
bool IsCollisionLeftBorder(void);
bool IsCollisionRightBorder(void);
bool IsCollisionBody(void);
void AddTail(void);
void DelAllTail(void);
bool IsOppositeDir(int dirToMove);
bool IsSameDir(int dirToMove);
void FreeAllMemories(void);
bool IsAlive(void);
void GameStart(void);
void SelectMenu(void);
void ShowIntro(void);
int Choice(void);

int main(void)
{
	system("title Snake Game(KSNB)");        //cmd 창 제목
	system("mode con cols=112 lines=33");    //cmd 창 크기 고정

	RemoveCursor();

	srand((unsigned int)time(0));
	
	SelectMenu();    // 인트로 화면

	return 0;
}

void ShowIntro(void) 
{
	/* 인트로 화면 출력 */
	SetCurrentCursorPos(25, 5);
	printf("SnakeGame");
	SetCurrentCursorPos(25, 20);
	printf("GameStart");
	SetCurrentCursorPos(25, 22);
	printf("Exit");
}

void SelectMenu(void) 
{
	/*사용자의 선택(Choice 함수)에 따라 게임을 시작하거나 종료*/

	if (Choice() == GAMESTART)
	{
		GameStart();
	}
	else{
		SetCurrentCursorPos(25, 5);
		printf("게임을 종료했습니다.\n");
		getchar();
		exit(0);
	}
}

void GameStart(void) 
{
	/* SelectMenu함수에서 GameStart를 선택했을 경우 시작.
	   즉, 플레이 변수초기화 및 게임의 지속적 진행 등 게임의 전체를 다룸 */
	
	InitInfo();
	InitSnake();

	DrawTitle();
	DrawMap();

	RelocateFood();   //음식의 위치 랜덤으로 생성(초기화)

	while (IsAlive())
	{
		Display();                  //Map, Snake, Score, lives, Speed 등을 화면에 나타내줌.
		ChkSnakeDie(MoveSnake());   //뱀의 움직임에 따라 뱀이 죽었는지를 확인.
		GetInput();                 //사용자 입력
		EatFood();                  // 뱀이 먹이를 먹었는지 확인
	}

	FreeAllMemories();              // 게임이 끝난 후 사용한 메모리 해제(이중연결리스트 동적할당)
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
	wait = 130;
	lives = 10;
	score = 0;
	speed = 1;
}

void InitSnake(void)
{
	Head = (Snake *)malloc(sizeof(Snake));     //이중연결리스트로 초기화이므로 Head포인터에 바로 생성 가능
	Head->pre = NULL;
	Head->next = NULL;

	Head->pos.X = (rand() % (BOARD_WIDTH - 2)) + LEFT_BORDER + 1;   // -2를 한 이유 : 양쪽의 border두개를 빼주어야 함, +1을 한 이유 역시 border에 걸리면 안되기 때문
	Head->pos.Y = (rand() % (BOARD_HEIGHT - 2)) + TOP_BORDER + 1;
	Head->dir = DOWN;                                      //뱀의 방향은 기본값이 DOWN이므로 게임 시작과 동시에 아래방향으로 이동함.

	Tail = Head;          //아직 Tail이 없기 때문에 Tail 포인터 역시 Head 포인터와 같은 노드를 가르킴
}

void DrawSnake(void)
{
	Snake * temp = Head;       // Head 부터 Tail(NULL)까지 이중연결리스트를 돌아야 하므로 temp라는 이동포인터 생성

	while (temp != NULL)
	{
		SetCurrentCursorPos(temp->pos.X, temp->pos.Y);
		printf("Oo");

		temp = temp->next;
	}

	free(temp);  //temp 포인터 사용 후 메모리 해제
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

	free(temp);
}

void DrawFood(void)
{
	SetCurrentCursorPos(food.pos.X, food.pos.Y);
	printf("FF");
}

void DrawMap(void)
{
	char MAP[23][45] =
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

	int i, j = 0;

	SetCurrentCursorPos(0, 5);

	for (i = 0; i < BOARD_HEIGHT; i++)
	{
		SetCurrentCursorPos(LEFT_BORDER, TOP_BORDER + i);
		for (j = 0; j < BOARD_WIDTH; j++)
		{
			if (MAP[i][j] == 1)
				printf("XX");

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
	printf("                ");
	SetCurrentCursorPos(46, 1);
	printf("Score: %d", score);
}

void DrawLives(void) 
{
	SetCurrentCursorPos(46, 2);
	printf("                ");
	SetCurrentCursorPos(46, 2);
	printf("Lives: %d", lives);
}

void DrawSpeed(void) 
{
	SetCurrentCursorPos(46, 3);
	printf("                ");
	SetCurrentCursorPos(46, 3);
	printf("Speed: %d", speed);
}


void Display(void)
{
	/* 뱀, 먹이, 점수, 목숨, 속도 값을 화면에 출력하는 함수로, 
	   Sleep()이 존재하여 해당 Sleep으로 뱀의 속도를 조절함. */

	DrawScore();
	DrawLives();
	DrawSpeed();

	DrawFood();
	DrawSnake();

	Sleep(wait);

	DelSnake();
}

bool IsAlive(void) {      //뱀이 살아있는지 판별
	return (lives > 0);   //목숨이 남아있다면 true 반환
}

bool IsCollisionTopBorder(void)      //뱀의 머리(Head)가 위쪽 테두리에 충돌하였는지 판별
{
	return (Head->pos.Y <= TOP_BORDER);      //충돌하였다면 true 반환
}

bool IsCollisionBottomBorder(void)   //뱀의 머리(Head)가 아래쪽 테두리에 충돌하였는지 판별
{
	return (Head->pos.Y >= BOTTOM_BORDER);   //충돌하였다면 true 반환
}

bool IsCollisionLeftBorder(void)    //뱀의 머리(Head)가 왼쪽 테두리에 충돌하였는지 판별              
{
	return (Head->pos.X <= LEFT_BORDER);    //충돌하였다면 true 반환
}

bool IsCollisionRightBorder(void)   //뱀의 머리(Head)가 오른쪽 테두리에 충돌하였는지 판별
{
	return (Head->pos.X >= RIGHT_BORDER);  // 충돌하였다면 true 반환
}

bool IsCollisionBody(void)    //뱀의 머리(Head)가 자신의 몸과 충돌하였는지를 판별
{
	Snake * p = Head->next;

	while (p != NULL) {
		if (Head->pos.X == p->pos.X && Head->pos.Y == p->pos.Y) {
			return true;                                                   // 충돌하였다면 true 반환
		}
		else {
			p = p->next;
		}
	}

	free(p);

	return false;     //충돌하지 안았다면 false 반환
}

int MoveSnake(void)
{
	/* 사용자로부터 받은 Head->dir의 방향에 맞게 뱀을 움직임(이동)
	   뱀은 머리뿐만 아니라 몸통 전체가 움직여아 하기 때문에 Tail에서부터
	   각 노드들의 pre의 정보가 노드에 새롭게 저장되어야함 (이동하기 위해 앞 노드의 정보 필요) */

	Snake * temp = Tail;
	while (temp != Head) {                 //해당 반복문은 각 노드의 pre의 정보가 전달되는 것
		temp->pos.X = temp->pre->pos.X;
		temp->pos.Y = temp->pre->pos.Y;
		temp->dir = temp->pre->dir;

		temp = temp->pre;
	}

	switch (Head->dir)               //Head->dir 머리의 방향에 따라 뱀의 위치를 x나 y의 값을 조정하여 이동
	{
	case UP:
		Head->pos.Y--;
		if (IsCollisionTopBorder() || IsCollisionBody()){                    //위쪽방향이면 위쪽테두리 충돌검사와 몸충돌검사 실행 
			return 0;                                                        //충돌이 발생하면 0을 반환
		}
		else{
			return 1;                                                        //충돌이 발생하지 않으면 1반환
		}
		break;

	case DOWN:
		Head->pos.Y++;
		if (IsCollisionBottomBorder() || IsCollisionBody()){
			return 0;
		}
		else{
			return 1;
		}
		break;

	case LEFT:
		Head->pos.X--;
		if (IsCollisionLeftBorder() || IsCollisionBody()){
			return 0;
		}
		else{
			return 1;
		}
		break;

	case RIGHT:
		Head->pos.X++;
		if (IsCollisionRightBorder() || IsCollisionBody()){
			return 0;
		}
		else{
			return 1;
		}
		break;

	default:
		return 1;

	}

	free(temp);
}

bool IsOppositeDir(int dirToMove)                   //뱀이 현재움직이고 있는 방향과 정반대 방향인지를 판별
{
	if (Head->dir == UP && dirToMove == DOWN) {
		return true;                                 //정반대방향이면 true 반환
	}
	else if (Head->dir == DOWN && dirToMove == UP) {
		return true;
	}
	else if (Head->dir == LEFT && dirToMove == RIGHT) {
		return true;
	}
	else if (Head->dir == RIGHT && dirToMove == LEFT) {
		return true;
	}
	else {
		return false;                                //정반대방향이 아니라면 false반환
	}
}

bool IsSameDir(int dirToMove)     //뱀이 현재 움직이고 있는 방향과 같은 방향인지를 판별
{
	if (Head->dir == dirToMove) {
		return true;                    //같은 방향이면 true 반환
	}
	else {
		return false;
	}
}

void GetInput(void)            //사용자의 키보드 입력
{
	int getchar;

	if (_kbhit() != 0)
	{
		if (_getch() == DIR_KEY)            //오직 방향키만 받겠다는 의미 (DIR_KEY는 224인 값으로 방향키를 의미)
		{
			getchar = _getch();

			if (IsOppositeDir(getchar)) {    //현재 움직이는 방향과 정반대 방향이면 해당 키입력 먹지 않고 return;
				return;
			}
			else if (IsSameDir(getchar)) {   //현재 움직이는 방향과 정반대 방향이면 해당 키입력 먹지 않고 return;
				return; 
			}
			else {
				Head->dir = getchar; 
				MoveSnake();                 //위의 두 경우의 수가 아니라면 뱀을 움직임
			}
		}
	}
}

void RelocateFood(void)      //먹이가 먹혔을때 먹이를 랜덤위치에 재생성
{
	food.pos.X = (rand() % (BOARD_WIDTH - 2)) + LEFT_BORDER + 1;
	food.pos.Y = (rand() % (BOARD_HEIGHT - 2)) + TOP_BORDER + 1;

	DrawFood();
}

void RelocateSnake(void)    //뱀이 죽었을때 뱀을 랜덤위치에 재생성
{
	Head->pos.X = (rand() % (BOARD_WIDTH - 2)) + LEFT_BORDER + 1;
	Head->pos.Y = (rand() % (BOARD_HEIGHT - 2)) + TOP_BORDER + 1;
}

void AddTail(void)
{
	/* 뱀의 꼬리를 생성하는 함수로, 뱀의 꼬리는 무조건 Tail포인터의 next필드에 연결됨 */
	
	Snake * new = (Snake *)malloc(sizeof(Snake));

	switch (Tail->dir)          //마지막 꼬리의 위치에 따라 새로운 뱀의 꼬리가 생성되는 위치가 달라짐 (예. 아래방향으로 가고 있으면 꼬리는 y-1에 생성 되어야 함)
	{
	case UP:
		new->pos.X = Tail->pos.X;
		new->pos.Y = Tail->pos.Y + 1;
		new->dir = Tail->dir;
		break;

	case DOWN:
		new->pos.X = Tail->pos.X;
		new->pos.Y = Tail->pos.Y - 1;
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
	if (Head->pos.Y == food.pos.Y && Head->pos.X == food.pos.X)    //뱀이 먹이를 먹었는지 확인
	{
		score++;   //뱀이 먹이를 먹으면 +1점 오름

		AddTail();  // 뱀이 먹이를 먹으면 꼬리가 1칸 증가
		RelocateFood();  //먹이의 위치 재생성

		ControlSpeed();  //먹이를 먹음에 따라 속도 조절
	}
}

void ControlSpeed(void)  //wait의 숫자가 작을수록 뱀의 속도가 빠르다는 것을 의미함
{
	if (score == 5)
	{
		wait = 100;
		speed++;
		return;
	}
	else if (score == 7)
	{
		wait = 80;
		speed++;
		return;
	}
	else if (score == 9)
	{
		wait = 50;
		speed++;
		return;
	}
	else
	{
		return;
	}
}

void DelAllTail(void) 
{
	/*뱀이 죽었을 경우, 모든 꼬리들이 없어지기 때문에 각 꼬리노드들의 연결을 해제해 주고 
	  메모리를 위해 각 노드 역시 free시켜 준다. 단, Head는 남겨야 함 */

	Snake * temp = Tail;

	while (temp != Head) 
	{
		Tail = Tail->pre;
		free(temp);
		temp = Tail;
	}
	Head->next = NULL;
}

void ChkSnakeDie(int moving)  //뱀이 죽었는지를 판별
{
	if (!moving)
	{
		lives--;
		
		DelAllTail();

		DrawMap();

		RelocateSnake();
	}
}

void FreeAllMemories(void)   //게임이 종료되고 더이상 사용하지 않는 메모리(이중연결리스트 노드들) 해제
{
	Snake * temp = Head;

	while (temp != NULL)
	{
		Head = Head->next;
		free(temp);
		temp = Head;
	}

	free(temp);
	free(Head);
}

int Choice(void)     //사용자의 인트로 메뉴 선택
{
	ShowIntro();

	int y = GAMESTART;
	SetCurrentCursorPos(24, GAMESTART);
	printf(">");

	while (1)
	{
		int key;
		if (_kbhit() != 0)
		{
			key = _getch();

			SetCurrentCursorPos(24, y);
			printf(" ");

			switch (key)
			{
			case UP:
				y = (y - 2 < GAMESTART) ? EXIT : y - 2;
				if (y == GAMESTART) {
					SetCurrentCursorPos(24, GAMESTART);
					printf(">");
				}
				else {
					SetCurrentCursorPos(24, EXIT);
					printf(">");
				}
				break;

			case DOWN:
				y = (y + 2 > EXIT) ? GAMESTART : y + 2;
				if (y == GAMESTART) {
					SetCurrentCursorPos(24, GAMESTART);
					printf(">");
				}
				else {
					SetCurrentCursorPos(24, EXIT);
					printf(">");
				}
				break;

			case ENTER:
				system("cls");
				return y;
				break;
			}
		}
	}
}
