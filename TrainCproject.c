#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "console.h"
#include <stdbool.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")
#define WIDTH_CONSOLE_WINDOW 1050
#define HEIGHT_CONSOLE_WINDOW 600
//build-wall//
#define CONSOLE_TOP 2
#define CONSOLE_LEFT 3
#define CONSOLE_RIGHT 90
#define CONSOLE_BOTTOM 33

#define MENU_TOP 12
#define MENU_LEFT 53
#define MENU_RIGHT 88
#define MENU_BOTTOM 30
#define GAMEOVER_TOP 10
#define GAMEOVER_LEFT 53
#define GAMEOVER_RIGHT 88
#define GAMEOVER_BOTTOM 28
//snake//
#define MAX_LENGTH ((CONSOLE_BOTTOM - CONSOLE_TOP - 1) * (CONSOLE_RIGHT - CONSOLE_LEFT - 1))
#define LEVEL_GAME_MAX 9
#define NUMBER_FOOD_EACH_LV 12 //1:1:1
#define COORD_SNAKE_START_X ((CONSOLE_LEFT + CONSOLE_RIGHT) / 2)
#define COORD_SNAKE_START_Y ((CONSOLE_TOP + CONSOLE_BOTTOM) / 2)
#define LEVEL_UP_1 0
#define LEVEL_UP_2 25
#define LEVEL_UP_3 50
#define LEVEL_UP_4 100
#define LEVEL_UP_5 175
#define LEVEL_UP_6 250
#define LEVEL_UP_7 350
#define LEVEL_UP_8 450
#define LEVEL_UP_9 750
#define EASY_SPEED 80
#define NORMAL_SPEED 65
#define HARD_SPEED 50
#define NIGHTMARE_SPEED 35
#define EASY_SPEED_SPECIAL 70
#define NORMAL_SPEED_SPECIAL 55
#define HARD_SPEED_SPECIAL 40
#define NIGHTMARE_SPEED_SPECIAL 20
#define LEVEL_UPDATE_MAP 4

int count = 0, times = 0, amount_abstacle = 0, restart, i, j, k, row, col_s, col_n, col_a, col_k, col_e;
bool temp = false, check = true;

enum DIRECTION
{
	UP,
	LEFT,
	RIGHT,
	DOWN
};
struct Coordinate
{
	int x, y;
};
struct Snake
{
	struct Coordinate bend[MAX_LENGTH];
	int length, color, score;
	double speed_hor, speed_ver;
	enum DIRECTION direc;
};
struct Food
{
	int shape;
	int color;
	int score;
};
struct Food_coord
{
	struct Coordinate coord;
	int score, level;
};
struct HighScore
{
	char name[18];
	int score;
};

struct HighScore highScore[60];

//===============================================FUNCTION LIST===================================================
//------------------------------------MENU----------------------------------
void logo();
void buildHorizontalWall(int, int, int);
void buildVerticalWall(int, int, int);
void buildMenuWall(int, int, int, int);
void buildFence(int, int, int);
void gameMenu();
void selectMenu(int *, bool *, int *);
void enterMenu(int, int);
void gif1(int *);
void gif2(int *);
void gif3(int *);
void gif4(int *);
void gif5(int *);
void type();
void selectType(int *, bool *, int *);
void enterType(int, int);
void typeSpecial();
void selectTypeSpecial(int *, bool *, int *);
void enterTypeSpecial(int, int);
void typeClassic();
void selectTypeClassic(int *, bool *, int *);
void enterTypeClassic(int, int);
void mod();
void selectMod(int *, bool *, int *);
void enterMod(int, int);
void cleanTable();
void aboutTable();
void helpClassicTable();
void helpSpecialTable();
void showHighScore(int);
void showHighScoreGameover(int);
void goodBye();
void pause();
void checkHighScore(int, int);
void gameover(int, int);
void congratulation(int);
bool isEmpty(int);
void getHighScore(int);
bool checkName(char *);
void initScore(int key);
void lag();
void showCursorType();
void finishGame();
void resizeConsole(int, int);
//-----------------------------------SPECIAL-----------------------------------
void declere_snake(struct Snake *, int);
void draw_snake(struct Snake);
void control_move_snake(struct Snake *);
void update_snake(struct Snake *, struct Food_coord *, int);
void declere_food(struct Food *);
void draw_main_food(struct Food *, struct Food_coord *, int, struct Snake *, struct Snake *);
void draw_toxic_food(struct Food *, struct Food_coord *, int, struct Snake *, struct Snake *);
void draw_any_food(struct Food *, struct Food_coord *, int, struct Snake *, struct Snake *);
void call_food(struct Food *, struct Food_coord *, int, struct Snake *, struct Snake *);
void display_score(int *, int *, int *, struct Food_coord *, struct Snake, struct Snake);
void logo_score(int, int);
void build_wall();
void draw_obstacle(struct Coordinate *, struct Snake *, int *);
void check_obstacle(struct Coordinate *, struct Snake *, int *);
void through_obstacle(struct Snake *, int);
void build_table_game();
void inGameSpecialInstruction();
void end_game(struct Snake, int *);
void declere_challenge(struct Snake *);
void challenge_1(struct Snake *);
void challenge_2(struct Snake *);
void delete_challenge(struct Snake *);

//-------------------------------------CLASSIC------------------------------------
void draw_snake_classic(struct Snake);
void updateFood(struct Snake, struct Food_coord *, struct Food_coord *);
void update_snake_classic(struct Snake *, struct Food_coord *, struct Food_coord *);
void declere_food_classic(struct Food_coord *, struct Snake);
void drawFood(struct Food_coord);
void drawBigFood(struct Food_coord);
void deleteBigFood(struct Food_coord *);
void snakeScore(struct Snake *, struct Food_coord, struct Food_coord);
void throughWall(struct Snake *);
void inGameClassicInstruction(int);

//=============================================MAIN=========================================================
int main()
{
	int countLine, color, pos = 44;
	bool exit;
	system("Title Game-Snake-Fcode");
	resizeConsole(WIDTH_CONSOLE_WINDOW, HEIGHT_CONSOLE_WINDOW);
	srand(time(NULL));
	//--------------------------reading file HighScore-----------------------
	initScore(0);
	lag();
	initScore(5);
	lag();
	initScore(10);
	lag();
	initScore(15);
	lag();
	initScore(20);
	lag();
	initScore(25);
	lag();
	initScore(30);
	lag();
	initScore(35);
	lag();
	initScore(40);
	lag();
	initScore(45);
	lag();
	initScore(50);
	lag();
	initScore(55);
	lag();
	PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
	//-----------------------------MENU----------------------------------
	//--------------START HIGHSCORE HELP ABOUT QUIT-----------------------
beginMenu:
	noCursorType();
	system("cls");
	color = ColorCode_Blue;
	countLine = 1;
	exit = false;
	gameMenu();
	buildFence(24, 54, 87);
	buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
	while (!exit)
	{
		i = rand() % 15 + 1;
		TextColor(i);
		logo();
		selectMenu(&countLine, &exit, &color);
		gif1(&pos);
		gif2(&pos);
		gif3(&pos);
		TextColor(i);
		gif4(&pos);
		gif5(&pos);
		pos++;
		if (pos >= 129)
			pos = 42;
		Sleep(70);
	}
	enterMenu(12 + countLine * 2, color);
	//-----------------------------------START----------------------------
	if (countLine == 1)
	{
		//---------------------------------START---------------------------
		//-----------------------------CLASSIC SPECIAL BACK-------------------------
	beginMenuStart:
		cleanTable();
		color = ColorCode_Grey;
		countLine = 1;
		exit = false;
		buildFence(24, 54, 87);
		buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
		type();
		while (!exit)
		{
			i = rand() % 15 + 1;
			TextColor(i);
			logo();
			selectType(&countLine, &exit, &color);
			gif1(&pos);
			gif2(&pos);
			gif3(&pos);
			TextColor(i);
			gif4(&pos);
			gif5(&pos);
			pos++;
			if (pos >= 129)
				pos = 42;
			Sleep(70);
		}
		enterType(14 + countLine * 2, color);

		if (countLine == 1)
		{
			//---------------------------CLASSIC------------------------------
			//-----------------------NORMAL MODERN BACK------------------------

		beginMenuStartClassic:
			cleanTable();
			color = ColorCode_Yellow;
			countLine = 1;
			exit = false;
			buildFence(24, 54, 87);
			buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
			TextColor(128);
			gotoXY(65, 13);
			printf("    CLASSIC   ");
			typeClassic();
			while (!exit)
			{
				i = rand() % 15 + 1;
				TextColor(i);
				logo();
				selectTypeClassic(&countLine, &exit, &color);
				gif1(&pos);
				gif2(&pos);
				gif3(&pos);
				TextColor(i);
				gif4(&pos);
				gif5(&pos);
				pos++;
				if (pos >= 129)
					pos = 42;
				Sleep(70);
			}
			enterTypeClassic(14 + countLine * 2, color);

			if (countLine == 1)
			{
				//------------------------CLASSIC NORMAL-------------------------
				//---------------------EASY NORMAL HARD BACK---------------------
				cleanTable();
				color = ColorCode_Cyan;
				countLine = 1;
				exit = false;
				buildFence(24, 54, 87);
				buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
				TextColor(224);
				gotoXY(60, 13);
				printf("   CLASSIC - NORMAL   ");
				mod();
				while (!exit)
				{
					i = rand() % 15 + 1;
					TextColor(i);
					logo();
					selectMod(&countLine, &exit, &color);
					gif1(&pos);
					gif2(&pos);
					gif3(&pos);
					TextColor(i);
					gif4(&pos);
					gif5(&pos);
					pos++;
					if (pos >= 129)
						pos = 42;
					Sleep(70);
				}
				enterMod(13 + countLine * 2, color);

				struct Snake snake;
				struct Food_coord bigFood;
				struct Food_coord food;
				int control, hp;

				//-----------------------CLASSIC NORMAL EASY game--------------------
				if (countLine == 1)
				{
				beginMenuStartClassicNormalEasy:
					PlaySound(NULL, NULL, SND_ASYNC);
					restart = 0;
					hp = 1;
					control = 1;
					count = 0;
					temp = false;

					noCursorType();
					system("cls");
					build_wall();
					build_table_game();
					inGameClassicInstruction(0);
					deleteBigFood(&bigFood);

					declere_snake(&snake, EASY_SPEED);
					declere_food_classic(&food, snake);

					while (control == 1)
					{
						//print
						drawFood(food);
						if (temp == true)
						{
							if (times == 0)
								PlaySound(TEXT("BigFoodAppear.wav"), NULL, SND_ASYNC);
							times++;
							gotoXY(90 - times, CONSOLE_BOTTOM);
							printf(" ");
							drawBigFood(bigFood);
							if (times == 90)
							{
								temp = false;
								deleteBigFood(&bigFood);
							}
						}
						draw_snake_classic(snake);
						//move
						control_move_snake(&snake);
						//score
						snakeScore(&snake, food, bigFood);
						//pause
						if (restart == 1)
						{
							TextColor(default_ColorCode);
							goto beginMenuStartClassicNormalEasy;
						}
						else if (restart == 2)
						{
							TextColor(default_ColorCode);
							PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
							goto beginMenu;
						}
						//snake become longer
						update_snake_classic(&snake, &food, &bigFood);
						//score
						snakeScore(&snake, food, bigFood);
						//speed
						if (snake.score >= 60)
						{
							snake.speed_hor = NIGHTMARE_SPEED;
							snake.speed_ver = NIGHTMARE_SPEED * 1.5;
						}
						else if (snake.score >= 30)
						{
							snake.speed_hor = HARD_SPEED;
							snake.speed_ver = HARD_SPEED * 1.5;
						}
						else if (snake.score >= 15)
						{
							snake.speed_hor = NORMAL_SPEED;
							snake.speed_ver = NORMAL_SPEED * 1.5;
						}
						//++++++++++++++END_GAME++++++++++++++++++//
						end_game(snake, &hp);
						if (hp == 0)
							control = 0;
					}
					//game over
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP - 2, MENU_BOTTOM - 2);
					gameover(snake.score, 0);
					//restart or go to Menu
					if (restart == 1)
					{
						TextColor(default_ColorCode);
						goto beginMenuStartClassicNormalEasy;
					}
					else if (restart == 2)
					{
						TextColor(default_ColorCode);
						PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
						goto beginMenu;
					}
				}
				//-----------------------CLASSIC NORMAL NORMAL game-------------------
				else if (countLine == 2)
				{
				beginMenuStartClassicNormalNormal:
					PlaySound(NULL, NULL, SND_ASYNC);
					restart = 0;
					hp = 1;
					control = 1;
					count = 0;
					temp = false;

					noCursorType();
					system("cls");
					build_wall();
					build_table_game();
					inGameClassicInstruction(5);
					deleteBigFood(&bigFood);

					declere_snake(&snake, NORMAL_SPEED);
					declere_food_classic(&food, snake);

					while (control == 1)
					{
						//print
						drawFood(food);
						if (temp == true)
						{
							if (times == 0)
								PlaySound(TEXT("BigFoodAppear.wav"), NULL, SND_ASYNC);
							times++;
							gotoXY(90 - times, CONSOLE_BOTTOM);
							printf(" ");
							drawBigFood(bigFood);
							if (times == 90)
							{
								temp = false;
								deleteBigFood(&bigFood);
							}
						}
						draw_snake_classic(snake);
						//move
						control_move_snake(&snake);
						//score
						snakeScore(&snake, food, bigFood);
						//pause
						if (restart == 1)
						{
							TextColor(default_ColorCode);
							goto beginMenuStartClassicNormalNormal;
						}
						else if (restart == 2)
						{
							TextColor(default_ColorCode);
							PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
							goto beginMenu;
						}
						//snake become longer
						update_snake_classic(&snake, &food, &bigFood);
						//score
						snakeScore(&snake, food, bigFood);
						//speed
						if (snake.score >= 50)
						{
							snake.speed_hor = NIGHTMARE_SPEED;
							snake.speed_ver = NIGHTMARE_SPEED * 1.5;
						}
						else if (snake.score >= 20)
						{
							snake.speed_hor = HARD_SPEED;
							snake.speed_ver = HARD_SPEED * 1.5;
						}
						//++++++++++++++END_GAME++++++++++++++++++//
						end_game(snake, &hp);
						if (hp == 0)
							control = 0;
					}
					//game over
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP - 2, MENU_BOTTOM - 2);
					gameover(snake.score, 5);
					//restart or go to Menu
					if (restart == 1)
					{
						TextColor(default_ColorCode);
						goto beginMenuStartClassicNormalNormal;
					}
					else if (restart == 2)
					{
						TextColor(default_ColorCode);
						PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
						goto beginMenu;
					}
				}
				//-----------------------CLASSIC NORMAL HARD game---------------------
				else if (countLine == 3)
				{
				beginMenuStartClassicNormalHard:
					PlaySound(NULL, NULL, SND_ASYNC);
					restart = 0;
					hp = 1;
					control = 1;
					count = 0;
					temp = false;

					noCursorType();
					system("cls");
					build_wall();
					build_table_game();
					inGameClassicInstruction(10);
					deleteBigFood(&bigFood);

					declere_snake(&snake, HARD_SPEED);
					declere_food_classic(&food, snake);

					while (control == 1)
					{
						//print
						drawFood(food);
						if (temp == true)
						{
							if (times == 0)
								PlaySound(TEXT("BigFoodAppear.wav"), NULL, SND_ASYNC);
							times++;
							gotoXY(90 - times, CONSOLE_BOTTOM);
							printf(" ");
							drawBigFood(bigFood);
							if (times == 90)
							{
								temp = false;
								deleteBigFood(&bigFood);
							}
						}
						draw_snake_classic(snake);
						//move
						control_move_snake(&snake);
						//score
						snakeScore(&snake, food, bigFood);
						//pause
						if (restart == 1)
						{
							TextColor(default_ColorCode);
							goto beginMenuStartClassicNormalHard;
						}
						else if (restart == 2)
						{
							TextColor(default_ColorCode);
							PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
							goto beginMenu;
						}
						//snake become longer
						update_snake_classic(&snake, &food, &bigFood);
						//score
						snakeScore(&snake, food, bigFood);
						//speed
						if (snake.score >= 30)
						{
							snake.speed_hor = NIGHTMARE_SPEED;
							snake.speed_ver = NIGHTMARE_SPEED * 1.5;
						}
						//++++++++++++++END_GAME++++++++++++++++++//
						end_game(snake, &hp);
						if (hp == 0)
							control = 0;
					}
					//game over
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP - 2, MENU_BOTTOM - 2);
					gameover(snake.score, 10);
					//restart or go to Menu
					if (restart == 1)
					{
						TextColor(default_ColorCode);
						goto beginMenuStartClassicNormalHard;
					}
					else if (restart == 2)
					{
						TextColor(default_ColorCode);
						PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
						goto beginMenu;
					}
				}
				//--------------------------GO BACK-----------------------
				else if (countLine == 4)
				{
					goto beginMenuStartClassic;
				}
			}
			else if (countLine == 2)
			{
				//------------------------CLASSIC MODERN-------------------------
				//---------------------EASY NORMAL HARD BACK---------------------
				cleanTable();
				color = ColorCode_Cyan;
				countLine = 1;
				exit = false;
				buildFence(24, 54, 87);
				buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
				TextColor(208);
				gotoXY(60, 13);
				printf("   CLASSIC - MODERN   ");
				mod();
				while (!exit)
				{
					i = rand() % 15 + 1;
					TextColor(i);
					logo();
					selectMod(&countLine, &exit, &color);
					gif1(&pos);
					gif2(&pos);
					gif3(&pos);
					TextColor(i);
					gif4(&pos);
					gif5(&pos);
					pos++;
					if (pos >= 129)
						pos = 42;
					Sleep(70);
				}
				enterMod(13 + countLine * 2, color);

				struct Snake snake;
				struct Food_coord bigFood;
				struct Food_coord food;
				int control, hp;

				//----------------------CLASSIC MODERN EASY game------------------
				if (countLine == 1)
				{
				beginMenuStartClassicModernEasy:
					PlaySound(NULL, NULL, SND_ASYNC);
					restart = 0;
					hp = 1;
					control = 1;
					count = 0;
					temp = false;

					noCursorType();
					system("cls");
					build_wall();
					build_table_game();
					inGameClassicInstruction(15);
					deleteBigFood(&bigFood);

					declere_snake(&snake, EASY_SPEED);
					declere_food_classic(&food, snake);

					while (control == 1)
					{
						//print
						drawFood(food);
						if (temp == true)
						{
							if (times == 0)
								PlaySound(TEXT("BigFoodAppear.wav"), NULL, SND_ASYNC);
							times++;
							gotoXY(90 - times, CONSOLE_BOTTOM);
							printf(" ");
							drawBigFood(bigFood);
							if (times == 90)
							{
								temp = false;
								deleteBigFood(&bigFood);
							}
						}
						//snake go through wall
						throughWall(&snake);
						draw_snake_classic(snake);
						//move
						control_move_snake(&snake);
						//score
						snakeScore(&snake, food, bigFood);
						//pause
						if (restart == 1)
						{
							TextColor(default_ColorCode);
							goto beginMenuStartClassicModernEasy;
						}
						else if (restart == 2)
						{
							TextColor(default_ColorCode);
							PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
							goto beginMenu;
						}
						//snake become longer
						update_snake_classic(&snake, &food, &bigFood);
						//score
						snakeScore(&snake, food, bigFood);
						//speed
						if (snake.score >= 60)
						{
							snake.speed_hor = NIGHTMARE_SPEED;
							snake.speed_ver = NIGHTMARE_SPEED * 1.5;
						}
						else if (snake.score >= 30)
						{
							snake.speed_hor = HARD_SPEED;
							snake.speed_ver = HARD_SPEED * 1.5;
						}
						else if (snake.score >= 15)
						{
							snake.speed_hor = NORMAL_SPEED;
							snake.speed_ver = NORMAL_SPEED * 1.5;
						}
						//++++++++++++++END_GAME++++++++++++++++++//
						end_game(snake, &hp);
						if (hp == 0)
							control = 0;
					}
					//game over
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP - 2, MENU_BOTTOM - 2);
					gameover(snake.score, 15);
					//restart or go to Menu
					if (restart == 1)
					{
						TextColor(default_ColorCode);
						goto beginMenuStartClassicModernEasy;
					}
					else if (restart == 2)
					{
						TextColor(default_ColorCode);
						PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
						goto beginMenu;
					}
				}
				//----------------------CLASSIC MODERN NORMAL game----------------
				else if (countLine == 2)
				{
				beginMenuStartClassicModernNormal:
					PlaySound(NULL, NULL, SND_ASYNC);
					restart = 0;
					hp = 1;
					control = 1;
					count = 0;
					temp = false;

					noCursorType();
					system("cls");
					build_wall();
					build_table_game();
					inGameClassicInstruction(20);
					deleteBigFood(&bigFood);

					declere_snake(&snake, NORMAL_SPEED);
					declere_food_classic(&food, snake);

					while (control == 1)
					{
						//print
						drawFood(food);
						if (temp == true)
						{
							if (times == 0)
								PlaySound(TEXT("BigFoodAppear.wav"), NULL, SND_ASYNC);
							times++;
							gotoXY(90 - times, CONSOLE_BOTTOM);
							printf(" ");
							drawBigFood(bigFood);
							if (times == 90)
							{
								temp = false;
								deleteBigFood(&bigFood);
							}
						}
						//snake go through wall
						throughWall(&snake);
						draw_snake_classic(snake);
						//move
						control_move_snake(&snake);
						//score
						snakeScore(&snake, food, bigFood);
						//pause
						if (restart == 1)
						{
							TextColor(default_ColorCode);
							goto beginMenuStartClassicModernNormal;
						}
						else if (restart == 2)
						{
							TextColor(default_ColorCode);
							PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
							goto beginMenu;
						}
						//snake become longer
						update_snake_classic(&snake, &food, &bigFood);
						//score
						snakeScore(&snake, food, bigFood);
						//speed
						if (snake.score >= 50)
						{
							snake.speed_hor = NIGHTMARE_SPEED;
							snake.speed_ver = NIGHTMARE_SPEED * 1.5;
						}
						else if (snake.score >= 20)
						{
							snake.speed_hor = HARD_SPEED;
							snake.speed_hor = HARD_SPEED * 1.5;
						}
						//++++++++++++++END_GAME++++++++++++++++++//
						end_game(snake, &hp);
						if (hp == 0)
							control = 0;
					}
					//game over
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP - 2, MENU_BOTTOM - 2);
					gameover(snake.score, 20);
					//restart or go to Menu
					if (restart == 1)
					{
						TextColor(default_ColorCode);
						goto beginMenuStartClassicModernNormal;
					}
					else if (restart == 2)
					{
						TextColor(default_ColorCode);
						PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
						goto beginMenu;
					}
				}
				//-----------------------CLASSIC MODERN HARD game---------------------
				else if (countLine == 3)
				{

				beginMenuStartClassicModernHard:
					PlaySound(NULL, NULL, SND_ASYNC);
					restart = 0;
					hp = 1;
					control = 1;
					count = 0;
					temp = false;

					noCursorType();
					system("cls");
					build_wall();
					build_table_game();
					inGameClassicInstruction(25);
					deleteBigFood(&bigFood);

					declere_snake(&snake, HARD_SPEED);
					declere_food_classic(&food, snake);

					while (control == 1)
					{
						//print
						drawFood(food);
						if (temp == true)
						{
							if (times == 0)
								PlaySound(TEXT("BigFoodAppear.wav"), NULL, SND_ASYNC);
							times++;
							gotoXY(90 - times, CONSOLE_BOTTOM);
							printf(" ");
							drawBigFood(bigFood);
							if (times == 90)
							{
								temp = false;
								deleteBigFood(&bigFood);
							}
						}
						//snake go through wall
						throughWall(&snake);
						draw_snake_classic(snake);
						//move
						control_move_snake(&snake);
						//score
						snakeScore(&snake, food, bigFood);
						//pause
						if (restart == 1)
						{
							TextColor(default_ColorCode);
							goto beginMenuStartClassicModernHard;
						}
						else if (restart == 2)
						{
							TextColor(default_ColorCode);
							PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
							goto beginMenu;
						}
						//snake become longer
						update_snake_classic(&snake, &food, &bigFood);
						//score
						snakeScore(&snake, food, bigFood);
						//speed
						if (snake.score >= 30)
						{
							snake.speed_hor = NIGHTMARE_SPEED;
							snake.speed_ver = NIGHTMARE_SPEED * 1.5;
						}
						//++++++++++++++END_GAME++++++++++++++++++//
						end_game(snake, &hp);
						if (hp == 0)
							control = 0;
					}
					//game over
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP - 2, MENU_BOTTOM - 2);
					gameover(snake.score, 25);
					//restart or go to Menu
					if (restart == 1)
					{
						TextColor(default_ColorCode);
						goto beginMenuStartClassicModernHard;
					}
					else if (restart == 2)
					{
						TextColor(default_ColorCode);
						PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
						goto beginMenu;
					}
				}
				//--------------------------GO BACK-----------------------
				else if (countLine == 4)
				{
					goto beginMenuStartClassic;
				}
			}
			else if (countLine == 3)
			{
				goto beginMenuStart;
			}
		}
		else if (countLine == 2)
		{
			//-----------------------------SPECIAL-----------------
			//------------------------SPECIAL 1 SPECIAL 2 BACK--------------
		beginMenuStartSpecial:
			cleanTable();
			color = ColorCode_Yellow;
			countLine = 1;
			exit = false;
			buildFence(24, 54, 87);
			buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
			TextColor(192);
			gotoXY(65, 13);
			printf("    SPECIAL    ");
			typeSpecial();
			while (!exit)
			{
				i = rand() % 15 + 1;
				TextColor(i);
				logo();
				selectTypeSpecial(&countLine, &exit, &color);
				gif1(&pos);
				gif2(&pos);
				gif3(&pos);
				TextColor(i);
				gif4(&pos);
				gif5(&pos);
				pos++;
				if (pos >= 129)
					pos = 42;
				Sleep(70);
			}
			enterTypeSpecial(14 + countLine * 2, color);

			if (countLine == 1)
			{
				//-------------------------------SPECIAL 1--------------------------
				//--------------------------EASY NORMAL HARD BACK-----------------------------
				cleanTable();
				color = ColorCode_Cyan;
				countLine = 1;
				exit = false;
				buildFence(24, 54, 87);
				buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
				TextColor(224);
				gotoXY(65, 13);
				printf("    SPECIAL 1   ");
				mod();
				while (!exit)
				{
					i = rand() % 15 + 1;
					TextColor(i);
					logo();
					selectMod(&countLine, &exit, &color);
					gif1(&pos);
					gif2(&pos);
					gif3(&pos);
					TextColor(i);
					gif4(&pos);
					gif5(&pos);
					pos++;
					if (pos >= 129)
						pos = 42;
					Sleep(70);
				}
				enterMod(13 + countLine * 2, color);

				int control;
				int level_game;
				int hp;
				int score;
				struct Food food[LEVEL_GAME_MAX + 1];
				struct Food_coord food_coord[LEVEL_GAME_MAX * NUMBER_FOOD_EACH_LV];
				struct Snake snake, challenge;
				struct Coordinate obstacle[200];

				//---------------------SPECIAL 1 EASY game------------------
				if (countLine == 1)
				{
				beginMenuStartSpecialSpecial1Easy:
					PlaySound(NULL, NULL, SND_ASYNC);
					restart = 0;
					level_game = 1;
					hp = 3;
					control = 1;
					score = 0;

					system("cls");
					//build play area
					build_wall();
					build_table_game();
					inGameSpecialInstruction(30);
					//snake and food at begin
					declere_food(food);
					declere_snake(&snake, EASY_SPEED_SPECIAL);
					delete_challenge(&challenge);
					call_food(food, food_coord, level_game, &snake, &challenge);

					//=====================================Main_game=====================================================//
					while (control == 1)
					{
						int level_difference = level_game;
						//print
						draw_snake(snake);
						//move
						control_move_snake(&snake);
						//snake hit obstacle and go through
						if (level_game >= LEVEL_UPDATE_MAP)
						{
							check_obstacle(obstacle, &snake, &hp);
							through_obstacle(&snake, level_game);
						}
						if (level_game == 2 || level_game >= 5)
						{
							challenge_1(&challenge);
						}
						if (level_game == 3)
						{
							challenge_2(&challenge);
						}
						//Pause
						if (restart == 1)
						{
							TextColor(default_ColorCode);
							goto beginMenuStartSpecialSpecial1Easy;
						}
						else if (restart == 2)
						{
							TextColor(default_ColorCode);
							PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
							goto beginMenu;
						}
						//score
						display_score(&score, &level_game, &hp, food_coord, snake, challenge);
						logo_score(score, level_game);
						//snake become longer
						update_snake(&snake, food_coord, level_game);
						//score
						display_score(&score, &level_game, &hp, food_coord, snake, challenge);
						logo_score(score, level_game);
						//food appear
						draw_toxic_food(food, food_coord, level_game, &snake, &challenge);
						draw_any_food(food, food_coord, level_game, &snake, &challenge);
						draw_main_food(food, food_coord, level_game, &snake, &challenge);
						//level up
						if (level_game == level_difference + 1)
						{
							//finish game
							if (level_game == 9)
							{
								finishGame();
								PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
								goto beginMenu;
							}
							clrscr();
							gotoXY(COORD_SNAKE_START_X, COORD_SNAKE_START_Y);
							//build play area
							build_wall();
							build_table_game();
							//build obstacle
							if (level_game >= LEVEL_UPDATE_MAP)
							{
								draw_obstacle(obstacle, &snake, &hp);
							}
							//snake and food at begin
							declere_food(food);
							//speed
							if (level_game >= 7)
								declere_snake(&snake, NIGHTMARE_SPEED_SPECIAL);
							else if (level_game >= 5)
								declere_snake(&snake, HARD_SPEED_SPECIAL);
							else if (level_game >= 3)
								declere_snake(&snake, NORMAL_SPEED_SPECIAL);
							else
								declere_snake(&snake, EASY_SPEED_SPECIAL);
							if (level_game != 4)
								declere_challenge(&challenge);
							call_food(food, food_coord, level_game, &snake, &challenge);
							congratulation(level_game);
							inGameSpecialInstruction(30);
							TextColor(level_game);

							//Plus HP
							if (level_game % 3 == 0)
								hp++;
						}

						//++++++++++++++END_GAME++++++++++++++++++//
						end_game(snake, &hp);
						if (hp == 0)
							control = 0;
					}
					//game over
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP - 2, MENU_BOTTOM - 2);
					gameover(score, 30);
					//restart or go to Menu
					if (restart == 1)
					{
						TextColor(default_ColorCode);
						goto beginMenuStartSpecialSpecial1Easy;
					}
					else if (restart == 2)
					{
						TextColor(default_ColorCode);
						PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
						goto beginMenu;
					}
				}
				//---------------------SPECIAL 1 NORMAL game------------------
				else if (countLine == 2)
				{
				beginMenuStartSpecialSpecial1Normal:
					PlaySound(NULL, NULL, SND_ASYNC);
					restart = 0;
					level_game = 1;
					hp = 3;
					control = 1;
					score = 0;

					system("cls");
					//build play area
					build_wall();
					build_table_game();
					inGameSpecialInstruction(35);
					//snake and food at begin
					declere_food(food);
					declere_snake(&snake, NORMAL_SPEED_SPECIAL);
					delete_challenge(&challenge);
					call_food(food, food_coord, level_game, &snake, &challenge);

					//=====================================Main_game=====================================================//
					while (control == 1)
					{
						int level_difference = level_game;
						//print
						draw_snake(snake);
						//move
						control_move_snake(&snake);
						//snake hit obstacle and go through
						if (level_game >= LEVEL_UPDATE_MAP)
						{
							check_obstacle(obstacle, &snake, &hp);
							through_obstacle(&snake, level_game);
						}
						if (level_game == 2 || level_game >= 5)
						{
							challenge_1(&challenge);
						}
						if (level_game == 3)
						{
							challenge_2(&challenge);
						}
						//pause
						if (restart == 1)
						{
							TextColor(default_ColorCode);
							goto beginMenuStartSpecialSpecial1Normal;
						}
						else if (restart == 2)
						{
							TextColor(default_ColorCode);
							PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
							goto beginMenu;
						}
						//score
						display_score(&score, &level_game, &hp, food_coord, snake, challenge);
						logo_score(score, level_game);
						//snake become longer
						update_snake(&snake, food_coord, level_game);
						//score
						display_score(&score, &level_game, &hp, food_coord, snake, challenge);
						logo_score(score, level_game);
						//food appear
						draw_toxic_food(food, food_coord, level_game, &snake, &challenge);
						draw_any_food(food, food_coord, level_game, &snake, &challenge);
						draw_main_food(food, food_coord, level_game, &snake, &challenge);
						//level up
						if (level_game == level_difference + 1)
						{
							//finish game
							if (level_game == 9)
							{
								finishGame();
								PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
								goto beginMenu;
							}

							clrscr();
							gotoXY(COORD_SNAKE_START_X, COORD_SNAKE_START_Y);
							//build play area
							build_wall();
							build_table_game();
							//build obstacle
							if (level_game >= LEVEL_UPDATE_MAP)
							{
								draw_obstacle(obstacle, &snake, &hp);
							}
							//snake and food at begin
							declere_food(food);
							//speed
							if (level_game >= 6)
								declere_snake(&snake, NIGHTMARE_SPEED_SPECIAL);
							else if (level_game >= 4)
								declere_snake(&snake, HARD_SPEED_SPECIAL);
							else
								declere_snake(&snake, NORMAL_SPEED_SPECIAL);
							if (level_game != 4)
								declere_challenge(&challenge);
							call_food(food, food_coord, level_game, &snake, &challenge);
							congratulation(level_game);
							inGameSpecialInstruction(35);
							TextColor(level_game);
							//---Plus HP----
							if (level_game % 3 == 0)
								hp++;
						}
						//++++++++++++++END_GAME++++++++++++++++++//
						end_game(snake, &hp);
						if (hp == 0)
							break;
					}
					//game over
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP - 2, MENU_BOTTOM - 2);
					gameover(score, 35);
					//restart or go to Menu
					if (restart == 1)
					{
						TextColor(default_ColorCode);
						goto beginMenuStartSpecialSpecial1Normal;
					}
					else if (restart == 2)
					{
						TextColor(default_ColorCode);
						PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
						goto beginMenu;
					}
				}
				//---------------------SPECIAL 1 HARD game-------------------
				else if (countLine == 3)
				{
				beginMenuStartSpecialSpecial1Hard:
					PlaySound(NULL, NULL, SND_ASYNC);
					restart = 0;
					level_game = 1;
					hp = 3;
					control = 1;
					score = 0;

					system("cls");
					//build play area
					build_wall();
					build_table_game();
					inGameSpecialInstruction(40);
					//snake and food at begin
					declere_food(food);
					declere_snake(&snake, HARD_SPEED_SPECIAL);
					delete_challenge(&challenge);
					call_food(food, food_coord, level_game, &snake, &challenge);

					//=====================================Main_game=====================================================//
					while (control == 1)
					{
						int level_difference = level_game;
						//print
						draw_snake(snake);
						//move
						control_move_snake(&snake);
						//snake hit obstacle and go through
						if (level_game >= LEVEL_UPDATE_MAP)
						{
							check_obstacle(obstacle, &snake, &hp);
							through_obstacle(&snake, level_game);
						}
						if (level_game == 2 || level_game >= 5)
						{
							challenge_1(&challenge);
						}
						if (level_game == 3)
						{
							challenge_2(&challenge);
						}
						//pause
						if (restart == 1)
						{
							TextColor(default_ColorCode);
							goto beginMenuStartSpecialSpecial1Hard;
						}
						else if (restart == 2)
						{
							TextColor(default_ColorCode);
							PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
							goto beginMenu;
						}
						//score
						display_score(&score, &level_game, &hp, food_coord, snake, challenge);
						logo_score(score, level_game);
						//snake become longer
						update_snake(&snake, food_coord, level_game);
						if (level_game >= LEVEL_UPDATE_MAP)
						{
							check_obstacle(obstacle, &snake, &hp);
							through_obstacle(&snake, level_game);
						}
						//score
						display_score(&score, &level_game, &hp, food_coord, snake, challenge);
						logo_score(score, level_game);
						//food appear
						draw_toxic_food(food, food_coord, level_game, &snake, &challenge);
						draw_any_food(food, food_coord, level_game, &snake, &challenge);
						draw_main_food(food, food_coord, level_game, &snake, &challenge);
						//level up
						if (level_game == level_difference + 1)
						{
							//finish game
							if (level_game == 9)
							{
								finishGame();
								PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
								goto beginMenu;
							}

							clrscr();
							gotoXY(COORD_SNAKE_START_X, COORD_SNAKE_START_Y);
							//build play area
							build_wall();
							build_table_game();
							//build obstacle
							if (level_game >= LEVEL_UPDATE_MAP)
							{
								draw_obstacle(obstacle, &snake, &hp);
							}

							//snake and food at begin
							declere_food(food);
							//speed
							if (level_game >= 4)
								declere_snake(&snake, NIGHTMARE_SPEED_SPECIAL);
							else
								declere_snake(&snake, HARD_SPEED_SPECIAL);
							if (level_game != 4)
								declere_challenge(&challenge);
							call_food(food, food_coord, level_game, &snake, &challenge);
							congratulation(level_game);
							inGameSpecialInstruction(40);
							TextColor(level_game);
							//---Plus HP----
							if (level_game % 3 == 0)
								hp++;
						}
						//++++++++++++++END_GAME++++++++++++++++++//
						end_game(snake, &hp);
						if (hp == 0)
							break;
					}
					//gameover
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP - 2, MENU_BOTTOM - 2);
					gameover(score, 40);
					//restart or go to Meny
					if (restart == 1)
					{
						TextColor(default_ColorCode);
						goto beginMenuStartSpecialSpecial1Hard;
					}
					else if (restart == 2)
					{
						TextColor(default_ColorCode);
						PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
						goto beginMenu;
					}
				}
				//--------------------------GO BACK---------------------------
				else if (countLine == 4)
				{
					goto beginMenuStartSpecial;
				}
			}
			else if (countLine == 2)
			{
				//--------------------------------SPECIAL 2---------------------------
				//----------------------------EASY NORMAL HARD BACK------------------------
				cleanTable();
				color = ColorCode_Cyan;
				countLine = 1;
				exit = false;
				buildFence(24, 54, 87);
				buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
				TextColor(208);
				gotoXY(65, 13);
				printf("    SPECIAL 2   ");
				mod();
				while (!exit)
				{
					i = rand() % 15 + 1;
					TextColor(i);
					logo();
					selectMod(&countLine, &exit, &color);
					gif1(&pos);
					gif2(&pos);
					gif3(&pos);
					TextColor(i);
					gif4(&pos);
					gif5(&pos);
					pos++;
					if (pos >= 129)
						pos = 42;
					Sleep(70);
				}
				enterMod(13 + countLine * 2, color);

				int control;
				int level_game = 1;
				int hp = 3;
				int score = 0;
				struct Food food[LEVEL_GAME_MAX + 1];
				struct Food_coord food_coord[LEVEL_GAME_MAX * NUMBER_FOOD_EACH_LV];
				struct Snake snake, challenge;
				struct Coordinate obstacle[200];

				//------------------SPECIAL 2 EASY game----------------------
				if (countLine == 1)
				{
				beginMenuStartSpecialSpecial2Easy:
					PlaySound(NULL, NULL, SND_ASYNC);
					restart = 0;
					level_game = 1;
					hp = 3;
					control = 1;
					score = 0;

					system("cls");
					//buil play area
					build_wall();
					build_table_game();
					inGameSpecialInstruction(45);
					//snake and food at
					declere_food(food);
					declere_snake(&snake, EASY_SPEED_SPECIAL);
					delete_challenge(&challenge);
					call_food(food, food_coord, level_game, &snake, &challenge);
					//=====================================Main_game=====================================================//
					while (control == 1)
					{
						int level_difference = level_game;
						//print
						draw_snake(snake);
						//move
						control_move_snake(&snake);
						//snake hit obstacle and go through
						if (level_game >= LEVEL_UPDATE_MAP)
						{
							check_obstacle(obstacle, &snake, &hp);
							through_obstacle(&snake, level_game);
						}
						if (level_game == 2 || level_game >= 5)
						{
							challenge_1(&challenge);
						}
						if (level_game == 3)
						{
							challenge_2(&challenge);
						}
						//pause
						if (restart == 1)
						{
							TextColor(default_ColorCode);
							goto beginMenuStartSpecialSpecial2Easy;
						}
						else if (restart == 2)
						{
							TextColor(default_ColorCode);
							PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
							goto beginMenu;
						}
						//score
						display_score(&score, &level_game, &hp, food_coord, snake, challenge);
						logo_score(score, level_game);
						//food appear
						draw_toxic_food(food, food_coord, level_game, &snake, &challenge);
						draw_any_food(food, food_coord, level_game, &snake, &challenge);
						draw_main_food(food, food_coord, level_game, &snake, &challenge);
						//level up
						if (level_game == level_difference + 1)
						{
							//finish game
							if (level_game == 9)
							{
								finishGame();
								PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
								goto beginMenu;
							}

							clrscr();
							//build play area
							build_wall();
							//build obstacle
							if (level_game >= LEVEL_UPDATE_MAP)
							{
								draw_obstacle(obstacle, &snake, &hp);
							}
							build_table_game();
							//snake and food at begin
							declere_food(food);
							//speed
							if (level_game >= 7)
								declere_snake(&snake, NIGHTMARE_SPEED_SPECIAL);
							else if (level_game >= 5)
								declere_snake(&snake, HARD_SPEED_SPECIAL);
							else if (level_game >= 3)
								declere_snake(&snake, NORMAL_SPEED_SPECIAL);
							else
								declere_snake(&snake, EASY_SPEED_SPECIAL);
							if (level_game != 4)
								declere_challenge(&challenge);
							call_food(food, food_coord, level_game, &snake, &challenge);
							congratulation(level_game);
							inGameSpecialInstruction(45);
							TextColor(level_game);
							//---Plus HP----
							if (level_game % 3 == 0)
								hp++;
						}
						//++++++++++++++END_GAME++++++++++++++++++//
						end_game(snake, &hp);
						if (hp == 0)
							break;
					}
					//game over
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP - 2, MENU_BOTTOM - 2);
					gameover(score, 45);
					//restart or go to Menu
					if (restart == 1)
					{
						TextColor(default_ColorCode);
						goto beginMenuStartSpecialSpecial2Easy;
					}
					else if (restart == 2)
					{
						TextColor(default_ColorCode);
						PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
						goto beginMenu;
					}
				}
				//------------------SPECIAL 2 NORMAL game-------------------
				else if (countLine == 2)
				{
				beginMenuStartSpecialSpecial2Normal:
					PlaySound(NULL, NULL, SND_ASYNC);
					restart = 0;
					level_game = 1;
					hp = 3;
					control = 1;
					score = 0;

					system("cls");
					//build play area
					build_wall();
					build_table_game();
					inGameSpecialInstruction(50);
					//snake and food at begin
					declere_food(food);
					declere_snake(&snake, NORMAL_SPEED_SPECIAL);
					delete_challenge(&challenge);
					call_food(food, food_coord, level_game, &snake, &challenge);
					//=====================================Main_game=====================================================//
					while (control == 1)
					{
						int level_difference = level_game;
						//print
						draw_snake(snake);
						//move
						control_move_snake(&snake);
						//snake hit obstacle and go through
						if (level_game >= LEVEL_UPDATE_MAP)
						{
							check_obstacle(obstacle, &snake, &hp);
							through_obstacle(&snake, level_game);
						}
						if (level_game == 2 || level_game >= 5)
						{
							challenge_1(&challenge);
						}
						if (level_game == 3)
						{
							challenge_2(&challenge);
						}
						//pause
						if (restart == 1)
						{
							TextColor(default_ColorCode);
							goto beginMenuStartSpecialSpecial2Normal;
						}
						else if (restart == 2)
						{
							TextColor(default_ColorCode);
							PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
							goto beginMenu;
						}
						//score
						display_score(&score, &level_game, &hp, food_coord, snake, challenge);
						logo_score(score, level_game);
						//food apear
						draw_toxic_food(food, food_coord, level_game, &snake, &challenge);
						draw_any_food(food, food_coord, level_game, &snake, &challenge);
						draw_main_food(food, food_coord, level_game, &snake, &challenge);
						//level up
						if (level_game == level_difference + 1)
						{
							//finish game
							if (level_game == 9)
							{
								finishGame();
								PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
								goto beginMenu;
							}

							clrscr();
							//build play area
							build_wall();
							//build obstacle
							if (level_game >= LEVEL_UPDATE_MAP)
							{
								draw_obstacle(obstacle, &snake, &hp);
							}
							build_table_game();
							//snake and food at begin
							declere_food(food);
							//speed
							if (level_game >= 6)
								declere_snake(&snake, NIGHTMARE_SPEED_SPECIAL);
							else if (level_game >= 4)
								declere_snake(&snake, HARD_SPEED_SPECIAL);
							else
								declere_snake(&snake, NORMAL_SPEED_SPECIAL);
							if (level_game != 4)
								declere_challenge(&challenge);
							call_food(food, food_coord, level_game, &snake, &challenge);
							congratulation(level_game);
							inGameSpecialInstruction(50);
							TextColor(level_game);
							//---Plus HP----
							if (level_game % 3 == 0)
								hp++;
						}
						//++++++++++++++END_GAME++++++++++++++++++//
						end_game(snake, &hp);
						if (hp == 0)
							break;
					}
					//game over
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP - 2, MENU_BOTTOM - 2);
					gameover(score, 50);
					//restart or go to Menu
					if (restart == 1)
					{
						TextColor(default_ColorCode);
						goto beginMenuStartSpecialSpecial2Normal;
					}
					else if (restart == 2)
					{
						TextColor(default_ColorCode);
						PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
						goto beginMenu;
					}
				}
				//------------------SPECIAL 2 HARD game-----------------------
				else if (countLine == 3)
				{
				beginMenuStartSpecialSpecial2Hard:
					PlaySound(NULL, NULL, SND_ASYNC);
					restart = 0;
					level_game = 1;
					hp = 3;
					control = 1;
					score = 0;

					system("cls");
					//build play area
					build_wall();
					build_table_game();
					inGameSpecialInstruction(55);
					//snake and food at begin
					declere_food(food);
					declere_snake(&snake, HARD_SPEED_SPECIAL);
					delete_challenge(&challenge);
					call_food(food, food_coord, level_game, &snake, &challenge);

					//=====================================Main_game=====================================================//
					while (control == 1)
					{
						int level_difference = level_game;
						//print
						draw_snake(snake);
						//move
						control_move_snake(&snake);
						//snake hit obstacle and go through
						if (level_game >= LEVEL_UPDATE_MAP)
						{
							check_obstacle(obstacle, &snake, &hp);
							through_obstacle(&snake, level_game);
						}
						if (level_game == 2 || level_game >= 5)
						{
							challenge_1(&challenge);
						}
						if (level_game == 3)
						{
							challenge_2(&challenge);
						}
						//pause
						if (restart == 1)
						{
							TextColor(default_ColorCode);
							goto beginMenuStartSpecialSpecial2Hard;
						}
						else if (restart == 2)
						{
							TextColor(default_ColorCode);
							PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
							goto beginMenu;
						}
						//score
						display_score(&score, &level_game, &hp, food_coord, snake, challenge);
						logo_score(score, level_game);
						//food appear
						draw_toxic_food(food, food_coord, level_game, &snake, &challenge);
						draw_any_food(food, food_coord, level_game, &snake, &challenge);
						draw_main_food(food, food_coord, level_game, &snake, &challenge);
						//level up
						if (level_game == level_difference + 1)
						{
							//finish game
							if (level_game == 9)
							{
								finishGame();
								PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
								goto beginMenu;
							}
							//build obstacle

							clrscr();

							gotoXY(COORD_SNAKE_START_X, COORD_SNAKE_START_Y);
							//build play area
							build_wall();
							//build obstacle
							if (level_game >= LEVEL_UPDATE_MAP)
							{
								draw_obstacle(obstacle, &snake, &hp);
							}
							build_table_game();
							//snake and food at begin
							declere_food(food);
							//speed
							if (level_game >= 4)
								declere_snake(&snake, NIGHTMARE_SPEED_SPECIAL);
							else
								declere_snake(&snake, HARD_SPEED_SPECIAL);
							if (level_game != 4)
								declere_challenge(&challenge);
							call_food(food, food_coord, level_game, &snake, &challenge);
							congratulation(level_game);
							inGameSpecialInstruction(55);
							TextColor(level_game);
							//---Plus HP----
							if (level_game % 3 == 0)
								hp++;
						}
						//++++++++++++++END_GAME++++++++++++++++++//
						end_game(snake, &hp);
						if (hp == 0)
							break;
					}
					//game over
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP - 2, MENU_BOTTOM - 2);
					gameover(score, 55);
					//restart or go to Menu
					if (restart == 1)
					{
						TextColor(default_ColorCode);
						goto beginMenuStartSpecialSpecial2Hard;
					}
					else if (restart == 2)
					{
						TextColor(default_ColorCode);
						PlaySound(TEXT("MenuTheme.wav"), NULL, SND_ASYNC || SND_LOOP);
						goto beginMenu;
					}
				}
				//--------------------GO BACK---------------------------
				else if (countLine == 4)
				{
					goto beginMenuStartSpecial;
				}
			}
			//------------------------GO BACK-------------------------
			else if (countLine == 3)
			{
				goto beginMenuStart;
			}
		}
		//---------------------------GO BACK------------------------
		else if (countLine == 3)
		{
			goto beginMenu;
		}
	}
	//----------------------------------HIGHSCORE--------------------------
	else if (countLine == 2)
	{
		//----------------------------CLASSIC SPECIAL BACK------------------
	beginMenuHighScore:
		cleanTable();
		color = ColorCode_Grey;
		countLine = 1;
		exit = false;
		buildFence(24, 54, 87);
		buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
		type();
		while (!exit)
		{
			i = rand() % 15 + 1;
			TextColor(i);
			logo();
			selectType(&countLine, &exit, &color);
			gif1(&pos);
			gif2(&pos);
			gif3(&pos);
			TextColor(i);
			gif4(&pos);
			gif5(&pos);
			pos++;
			if (pos >= 129)
				pos = 42;
			Sleep(70);
		}
		enterType(14 + countLine * 2, color);

		if (countLine == 1)
		{
			//---------------------------CLASSIC------------------------------
			//-----------------------NORMAL MODERN BACK------------------------
		beginMenuHighScoreClassic:
			cleanTable();
			color = ColorCode_Yellow;
			countLine = 1;
			exit = false;
			buildFence(24, 54, 87);
			buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
			TextColor(128);
			gotoXY(65, 13);
			printf("    CLASSIC   ");
			typeClassic();
			while (!exit)
			{
				i = rand() % 15 + 1;
				TextColor(i);
				logo();
				selectTypeClassic(&countLine, &exit, &color);
				gif1(&pos);
				gif2(&pos);
				gif3(&pos);
				TextColor(i);
				gif4(&pos);
				gif5(&pos);
				pos++;
				if (pos >= 129)
					pos = 42;
				Sleep(70);
			}
			enterTypeClassic(14 + countLine * 2, color);

			if (countLine == 1)
			{
				//------------------------CLASSIC NORMAL-------------------------
				//---------------------EASY NORMAL HARD BACK---------------------
			beginHighScoreClassicNormal:
				cleanTable();
				color = ColorCode_Cyan;
				countLine = 1;
				exit = false;
				buildFence(24, 54, 87);
				buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
				TextColor(224);
				gotoXY(60, 13);
				printf("   CLASSIC - NORMAL   ");
				mod();
				while (!exit)
				{
					i = rand() % 15 + 1;
					TextColor(i);
					logo();
					selectMod(&countLine, &exit, &color);
					gif1(&pos);
					gif2(&pos);
					gif3(&pos);
					TextColor(i);
					gif4(&pos);
					gif5(&pos);
					pos++;
					if (pos >= 129)
						pos = 42;
					Sleep(70);
				}
				enterMod(13 + countLine * 2, color);

				//-----------------------show CLASSIC NORMAL EASY score--------------------
				if (countLine == 1)
				{
					exit = false;
					cleanTable();
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
					showHighScore(0);
					while (!exit)
					{
						i = rand() % 15 + 1;
						TextColor(i);
						logo();
						Sleep(70);
						if (_kbhit())
						{
							char kitu = _getch();
							if (kitu == 8)
							{
								for (i = 0; i < 60; i++)
								{
									strcpy(highScore[i].name, "PLAYER");
									highScore[i].score = 0;
								}
								getHighScore(0);
								cleanTable();
								buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
								showHighScore(0);
							}
							else if (kitu == 13)
							{
								goto beginMenu;
							}
						}
					}
				}
				//-----------------------show CLASSIC NORMAL NORMAL score-------------------
				else if (countLine == 2)
				{
					exit = false;
					cleanTable();
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
					showHighScore(5);
					while (!exit)
					{
						i = rand() % 15 + 1;
						TextColor(i);
						logo();
						Sleep(70);
						if (_kbhit())
						{
							char kitu = _getch();
							if (kitu == 8)
							{
								for (i = 0; i < 60; i++)
								{
									strcpy(highScore[i].name, "PLAYER");
									highScore[i].score = 0;
								}
								getHighScore(5);
								cleanTable();
								buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
								showHighScore(5);
							}
							else if (kitu == 13)
							{
								goto beginMenu;
							}
						}
					}
				}
				//------------------------show CLASSIC NORMAL HARD game---------------------
				else if (countLine == 3)
				{
					exit = false;
					cleanTable();
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
					showHighScore(10);
					while (!exit)
					{
						i = rand() % 15 + 1;
						TextColor(i);
						logo();
						Sleep(70);
						if (_kbhit())
						{
							char kitu = _getch();
							if (kitu == 8)
							{
								for (i = 0; i < 60; i++)
								{
									strcpy(highScore[i].name, "PLAYER");
									highScore[i].score = 0;
								}
								getHighScore(10);
								cleanTable();
								buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
								showHighScore(10);
							}
							else if (kitu == 13)
							{
								goto beginMenu;
							}
						}
					}
				}
				//--------------------------GO BACK-----------------------
				else if (countLine == 4)
				{
					goto beginMenuHighScoreClassic;
				}
			}
			else if (countLine == 2)
			{
				//------------------------CLASSIC MODERN-------------------------
				//---------------------EASY NORMAL HARD BACK---------------------
			beginHighScoreClassicModern:
				cleanTable();
				color = ColorCode_Cyan;
				countLine = 1;
				exit = false;
				buildFence(24, 54, 87);
				buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
				TextColor(208);
				gotoXY(60, 13);
				printf("   CLASSIC - MODERN   ");
				mod();
				while (!exit)
				{
					i = rand() % 15 + 1;
					TextColor(i);
					logo();
					selectMod(&countLine, &exit, &color);
					gif1(&pos);
					gif2(&pos);
					gif3(&pos);
					TextColor(i);
					gif4(&pos);
					gif5(&pos);
					pos++;
					if (pos >= 129)
						pos = 42;
					Sleep(70);
				}
				enterMod(13 + countLine * 2, color);

				//-----------------------show CLASSIC MODERN EASY score--------------------
				if (countLine == 1)
				{
					exit = false;
					cleanTable();
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
					showHighScore(15);
					while (!exit)
					{
						i = rand() % 15 + 1;
						TextColor(i);
						logo();
						Sleep(70);
						if (_kbhit())
						{
							char kitu = _getch();
							if (kitu == 8)
							{
								for (i = 0; i < 60; i++)
								{
									strcpy(highScore[i].name, "PLAYER");
									highScore[i].score = 0;
								}
								getHighScore(15);
								cleanTable();
								buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
								showHighScore(15);
							}
							else if (kitu == 13)
							{
								goto beginMenu;
							}
						}
					}
				}
				//-----------------------show CLASSIC MODERN NORMAL score--------------------
				else if (countLine == 2)
				{
					exit = false;
					cleanTable();
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
					showHighScore(20);
					while (!exit)
					{
						i = rand() % 15 + 1;
						TextColor(i);
						logo();
						Sleep(70);
						if (_kbhit())
						{
							char kitu = _getch();
							if (kitu == 8)
							{
								for (i = 0; i < 60; i++)
								{
									strcpy(highScore[i].name, "PLAYER");
									highScore[i].score = 0;
								}
								getHighScore(20);
								cleanTable();
								buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
								showHighScore(20);
							}
							else if (kitu == 13)
							{
								goto beginMenu;
							}
						}
					}
				}
				//-----------------------show CLASSIC MODERN HARD score--------------------
				else if (countLine == 3)
				{
					exit = false;
					cleanTable();
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
					showHighScore(25);
					while (!exit)
					{
						i = rand() % 15 + 1;
						TextColor(i);
						logo();
						Sleep(70);
						if (_kbhit())
						{
							char kitu = _getch();
							if (kitu == 8)
							{
								for (i = 0; i < 60; i++)
								{
									strcpy(highScore[i].name, "PLAYER");
									highScore[i].score = 0;
								}
								getHighScore(25);
								cleanTable();
								buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
								showHighScore(25);
							}
							else if (kitu == 13)
							{
								goto beginMenu;
							}
						}
					}
				}
				//----------------------------------GO BACK-----------------------
				else if (countLine == 4)
				{
					goto beginMenuHighScoreClassic;
				}
			}
			//---------------------GO BACK-----------------------
			else if (countLine == 3)
			{
				goto beginMenuHighScore;
			}
		}
		else if (countLine == 2)
		{
			//-----------------------SPECIAL-----------------------
			//------------------SPECIAL 1 SPECIAL 2---------------
		beginMenuHighScoreSpecial:
			cleanTable();
			color = ColorCode_Yellow;
			countLine = 1;
			exit = false;
			buildFence(24, 54, 87);
			buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
			TextColor(192);
			gotoXY(65, 13);
			printf("    SPECIAL    ");
			typeSpecial();
			while (!exit)
			{
				i = rand() % 15 + 1;
				TextColor(i);
				logo();
				selectTypeSpecial(&countLine, &exit, &color);
				gif1(&pos);
				gif2(&pos);
				gif3(&pos);
				TextColor(i);
				gif4(&pos);
				gif5(&pos);
				pos++;
				if (pos >= 129)
					pos = 42;
				Sleep(70);
			}
			enterTypeSpecial(14 + countLine * 2, color);

			if (countLine == 1)
			{
				//-------------------------------SPECIAL 1--------------------------
				//--------------------------EASY NORMAL HARD BACK-----------------------------
			beginMenuHighScoreSpecialSpecial1:
				cleanTable();
				color = ColorCode_Cyan;
				countLine = 1;
				exit = false;
				buildFence(24, 54, 87);
				buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
				TextColor(224);
				gotoXY(65, 13);
				printf("    SPECIAL 1   ");
				mod();
				while (!exit)
				{
					i = rand() % 15 + 1;
					TextColor(i);
					logo();
					selectMod(&countLine, &exit, &color);
					gif1(&pos);
					gif2(&pos);
					gif3(&pos);
					TextColor(i);
					gif4(&pos);
					gif5(&pos);
					pos++;
					if (pos >= 129)
						pos = 42;
					Sleep(70);
				}
				enterMod(13 + countLine * 2, color);

				//---------------------show SPECIAL SPECIAL 1 EASY score-----------------
				if (countLine == 1)
				{
					exit = false;
					cleanTable();
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
					showHighScore(30);
					while (!exit)
					{
						i = rand() % 15 + 1;
						TextColor(i);
						logo();
						Sleep(70);
						if (_kbhit())
						{
							char kitu = _getch();
							if (kitu == 8)
							{
								for (i = 0; i < 60; i++)
								{
									strcpy(highScore[i].name, "PLAYER");
									highScore[i].score = 0;
								}
								getHighScore(30);
								cleanTable();
								buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
								showHighScore(30);
							}
							else if (kitu == 13)
							{
								goto beginMenu;
							}
						}
					}
				}
				//---------------------show SPECIAL SPECIAL 1 NORMAL score-----------------
				else if (countLine == 2)
				{
					exit = false;
					cleanTable();
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
					showHighScore(35);
					while (!exit)
					{
						i = rand() % 15 + 1;
						TextColor(i);
						logo();
						Sleep(70);
						if (_kbhit())
						{
							char kitu = _getch();
							if (kitu == 8)
							{
								for (i = 0; i < 60; i++)
								{
									strcpy(highScore[i].name, "PLAYER");
									highScore[i].score = 0;
								}
								getHighScore(35);
								cleanTable();
								buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
								showHighScore(35);
							}
							else if (kitu == 13)
							{
								goto beginMenu;
							}
						}
					}
				}
				//---------------------show SPECIAL SPECIAL 1 HARD score-----------------
				else if (countLine == 3)
				{
					exit = false;
					cleanTable();
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
					showHighScore(40);
					while (!exit)
					{
						i = rand() % 15 + 1;
						TextColor(i);
						logo();
						Sleep(70);
						if (_kbhit())
						{
							char kitu = _getch();
							if (kitu == 8)
							{
								for (i = 0; i < 60; i++)
								{
									strcpy(highScore[i].name, "PLAYER");
									highScore[i].score = 0;
								}
								getHighScore(40);
								cleanTable();
								buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
								showHighScore(40);
							}
							else if (kitu == 13)
							{
								goto beginMenu;
							}
						}
					}
				}
				//----------------------------GO BACK-----------------------------
				else if (countLine == 4)
				{
					goto beginMenuHighScoreSpecial;
				}
			}
			else if (countLine == 2)
			{
				//--------------------------------SPECIAL 2---------------------------
				//----------------------------EASY NORMAL HARD BACK------------------------
			beginMenuHighScoreSpecialSpecial2:
				cleanTable();
				color = ColorCode_Cyan;
				countLine = 1;
				exit = false;
				buildFence(24, 54, 87);
				buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
				TextColor(208);
				gotoXY(65, 13);
				printf("    SPECIAL 2   ");
				mod();
				while (!exit)
				{
					i = rand() % 15 + 1;
					TextColor(i);
					logo();
					selectMod(&countLine, &exit, &color);
					gif1(&pos);
					gif2(&pos);
					gif3(&pos);
					TextColor(i);
					gif4(&pos);
					gif5(&pos);
					pos++;
					if (pos >= 129)
						pos = 42;
					Sleep(70);
				}
				enterMod(13 + countLine * 2, color);

				//------------------show SPECIAL SPECIAL 2 EASY score----------------------
				if (countLine == 1)
				{
					exit = false;
					cleanTable();
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
					showHighScore(45);
					while (!exit)
					{
						i = rand() % 15 + 1;
						TextColor(i);
						logo();
						Sleep(70);
						if (_kbhit())
						{
							char kitu = _getch();
							if (kitu == 8)
							{
								for (i = 0; i < 60; i++)
								{
									strcpy(highScore[i].name, "PLAYER");
									highScore[i].score = 0;
								}
								getHighScore(45);
								cleanTable();
								buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
								showHighScore(45);
							}
							else if (kitu == 13)
							{
								goto beginMenu;
							}
						}
					}
				}
				//------------------show SPECIAL SPECIAL 2 NORMAL score----------------------
				else if (countLine == 2)
				{
					exit = false;
					cleanTable();
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
					showHighScore(50);
					while (!exit)
					{
						i = rand() % 15 + 1;
						TextColor(i);
						logo();
						Sleep(70);
						if (_kbhit())
						{
							char kitu = _getch();
							if (kitu == 8)
							{
								for (i = 0; i < 60; i++)
								{
									strcpy(highScore[i].name, "PLAYER");
									highScore[i].score = 0;
								}
								getHighScore(50);
								cleanTable();
								buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
								showHighScore(50);
							}
							else if (kitu == 13)
							{
								goto beginMenu;
							}
						}
					}
				}
				//------------------show SPECIAL SPECIAL 2 HARD score----------------------
				else if (countLine == 3)
				{
					exit = false;
					cleanTable();
					buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
					showHighScore(55);
					while (!exit)
					{
						i = rand() % 15 + 1;
						TextColor(i);
						logo();
						Sleep(70);
						if (_kbhit())
						{
							char kitu = _getch();
							if (kitu == 8)
							{
								for (i = 0; i < 60; i++)
								{
									strcpy(highScore[i].name, "PLAYER");
									highScore[i].score = 0;
								}
								getHighScore(55);
								cleanTable();
								buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
								showHighScore(55);
							}
							else if (kitu == 13)
							{
								goto beginMenu;
							}
						}
					}
				}
				//--------------------GO BACK---------------------------
				else if (countLine == 4)
				{
					goto beginMenuHighScoreSpecial;
				}
			}
			//--------------------GO BACK---------------------------
			else if (countLine == 3)
			{
				goto beginMenuHighScore;
			}
		}
		//--------------------GO BACK---------------------------
		else if (countLine == 3)
		{
			goto beginMenu;
		}
	}
	//-----------------------------------HELP-------------------------------
	else if (countLine == 3)
	{
		//---------------------------CLASSIC SPECIAL BACK-------------------
	beginMenuHelp:
		cleanTable();
		color = ColorCode_Grey;
		countLine = 1;
		exit = false;
		buildFence(24, 54, 87);
		buildMenuWall(MENU_LEFT, MENU_RIGHT, MENU_TOP, MENU_BOTTOM);
		type();
		while (!exit)
		{
			i = rand() % 15 + 1;
			TextColor(i);
			logo();
			selectType(&countLine, &exit, &color);
			gif1(&pos);
			gif2(&pos);
			gif3(&pos);
			TextColor(i);
			gif4(&pos);
			gif5(&pos);
			pos++;
			if (pos >= 129)
				pos = 42;
			Sleep(70);
		}
		enterType(14 + countLine * 2, color);

		//--------------------introduce CLASSIC--------------------
		if (countLine == 1)
		{
			cleanTable();
			buildMenuWall(20, 117, 12, 30);
			helpClassicTable();
			_getch();
			goto beginMenu;
		}
		//--------------------introduce SPECIAL--------------------
		else if (countLine == 2)
		{
			cleanTable();
			buildMenuWall(20, 117, 12, 30);
			helpSpecialTable();
			_getch();
			goto beginMenu;
		}
		//-----------------------GO BACK-------------------------
		else if (countLine == 3)
		{
			goto beginMenu;
		}
	}
	//-----------------------------------ABOUT------------------------------
	else if (countLine == 4)
	{
		cleanTable();
		buildMenuWall(40, 90, 12, 30);
		aboutTable();
		_getch();
		system("cls");
		goto beginMenu;
	}
	//-----------------------------------QUIT------------------------------
	else if (countLine == 5)
	{
		goodBye();
		gotoXY(0, 35);
		return 0;
	}
	return 0;
}

//===============================================FUNCTION DETAIL=========================================
//========================================MENU====================================================
//--------------------------------------logo--------------------------------------
void logo()
{
	gotoXY(20, 2);
	printf("%c%c%c%c%c%c%c%c    %c%c%c      %c%c%c          %c%c%c          %c%c%c     %c%c%c    %c0%c%c%c%c%c%c%c%c%c%c         %c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 149, 219, 162, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoXY(20, 3);
	printf("%c%c%c         %c%c%c%c%c    %c%c%c         %c%c%c%c%c         %c%c%c   %c%c%c      %c0%c                  %c%c%c      %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoXY(20, 4);
	printf(" %c%c%c        %c%c%c%c%c%c   %c%c%c        %c%c%c %c%c%c        %c%c%c %c%c%c        %c0%c                   %c     %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 222, 219, 219, 219);
	gotoXY(20, 5);
	printf("  %c%c%c       %c%c%c %c%c%c  %c%c%c       %c%c%c   %c%c%c       %c%c%c%c%c%c         %c0%c%c%c%c%c%c%c%c%c%c          %c    %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 220, 220, 220, 220, 220, 220, 220, 220, 220, 223, 219, 219, 219);
	gotoXY(20, 6);
	printf("   %c%c%c      %c%c%c  %c%c%c %c%c%c      %c%c%c     %c%c%c      %c%c%c%c%c%c         %c0%c%c%c%c%c%c%c%c%c%c              %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 223, 223, 223, 223, 223, 223, 223, 223, 223, 219, 219, 219);
	gotoXY(20, 7);
	printf("    %c%c%c     %c%c%c   %c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c%c%c%c%c     %c%c%c %c%c%c        %c0%c                      %c%c%c     %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoXY(20, 8);
	printf("     %c%c%c    %c%c%c    %c%c%c%c%c    %c%c%c         %c%c%c    %c%c%c   %c%c%c      %c0%c                    %c%c%c      %c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoXY(20, 9);
	printf("%c%c%c%c%c%c%c%c    %c%c%c      %c%c%c   %c%c%c           %c%c%c   %c%c%c     %c%c%c    %c0%c%c%c%c%c%c%c%c%c%c           %c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
}
//------------------------------------Game Menu------------------------------------
void gameMenu()
{
	TextColor(9);
	gotoXY(60, 14);
	printf("%c%c%c%c", 219, 219, 219, 153);
	TextColor(144);
	gotoXY(70, 14);
	printf("      START      ");
	TextColor(160);
	gotoXY(70, 16);
	printf("    HIGHSCORE    ");
	TextColor(176);
	gotoXY(70, 18);
	printf("      HELP       ");
	TextColor(224);
	gotoXY(70, 20);
	printf("      ABOUT      ");
	gotoXY(70, 22);
	TextColor(207);
	printf("      QUIT       ");
}
void buildHorizontalWall(int y, int a, int b)
{
	gotoXY(a, y);
	for (i = a; i <= b; i++)
	{
		printf("%c", 205);
	}
}
void buildVerticalWall(int x, int a, int b)
{
	for (i = a; i <= b; i++)
	{
		gotoXY(x, i);
		printf("%c", 186);
	}
}
void buildMenuWall(int x, int y, int a, int b)
{
	TextColor(ColorCode_DarkWhite);
	gotoXY(x, a);
	printf("%c", 201);
	gotoXY(y, a);
	printf("%c", 187);
	gotoXY(x, b);
	printf("%c", 200);
	gotoXY(y, b);
	printf("%c", 188);
	buildHorizontalWall(a, x + 1, y - 1);
	buildHorizontalWall(b, x + 1, y - 1);
	buildVerticalWall(x, a + 1, b - 1);
	buildVerticalWall(y, a + 1, b - 1);
}
void buildFence(int a, int x, int y)
{
	TextColor(ColorCode_Cyan);
	gotoXY(x, a);
	for (i = 0; i < y - x + 1; i++)
	{
		printf("%c", 247);
	}
}
void selectMenu(int *countLine, bool *exitMenu, int *color)
{
	int countLine1 = *countLine;
	if (_kbhit())
	{
		char kitu = _getch();
		if (kitu == 13)
			*exitMenu = true;
		else if (kitu == -32)
		{
			kitu = _getch();
			if (kitu == 80)
			{
				if (*countLine < 5)
				{
					(*countLine)++; //go down
				}
			}
			else if (kitu == 72)
				if (*countLine > 1)
					(*countLine)--; //go up
		}
		else if (kitu == 'w')
		{
			if (*countLine > 1)
				(*countLine)--;
		}
		else if (kitu == 's')
		{
			if (*countLine < 5)
			{
				(*countLine)++; //go down
			}
		}
	}
	if (*countLine != countLine1)
	{
		switch (*countLine)
		{
		case 1:
			*color = ColorCode_Blue;
			break;
		case 2:
			*color = ColorCode_Green;
			break;
		case 3:
			*color = ColorCode_Cyan;
			break;
		case 4:
			*color = ColorCode_Yellow;
			break;
		case 5:
			*color = ColorCode_Red;
			break;
		}
		TextColor(*color);
		int d = *countLine - countLine1;
		if (d < 0)
		{
			gotoXY(60, 12 + countLine1 * 2);
			printf("    ");
			gotoXY(60, 10 + countLine1 * 2);
			printf("%c%c%c%c", 219, 219, 219, 153);
		}
		else
		{
			gotoXY(60, 12 + countLine1 * 2);
			printf("    ");
			gotoXY(60, 14 + countLine1 * 2);
			printf("%c%c%c%c", 219, 219, 219, 153);
		}
	}
}
void enterMenu(int row, int color)
{
	int pos = 60;
	while (pos != 83)
	{
		TextColor(default_ColorCode);
		gotoXY(pos, row);
		printf(" ");
		TextColor(color);
		gotoXY(pos + 3, row);
		printf("%c", 219);
		gotoXY(pos + 4, row);
		printf("%c", 153);
		pos++;
		Sleep(20);
	}
	if (pos == 83)
	{
		gotoXY(pos, row);
		printf("    ");
	}
}
//--------------------------------------Animation-----------------------------------
void gif1(int *pos)
{
	if (*pos >= 45 && *pos <= 78)
	{
		gotoXY(*pos + 9, 26);
		printf(" ");
		gotoXY(*pos + 9, 27);
		printf(" ");
		gotoXY(*pos + 9, 28);
		printf(" ");
	}
	if (*pos >= 44 && *pos <= 77)
	{
		TextColor(ColorCode_DarkCyan);
		gotoXY(*pos + 10, 26);
		printf("3");
		TextColor(ColorCode_DarkYellow);
		gotoXY(*pos + 10, 27);
		printf("6");
		TextColor(ColorCode_Blue);
		gotoXY(*pos + 10, 28);
		printf("9");
	}
}
void gif2(int *pos)
{

	if (*pos >= 47 && *pos <= 80)
	{
		gotoXY(*pos + 7, 26);
		printf(" ");
		gotoXY(*pos + 7, 27);
		printf(" ");
		gotoXY(*pos + 7, 28);
		printf(" ");
	}
	if (*pos >= 46 && *pos <= 79)
	{
		TextColor(ColorCode_DarkGreen);
		gotoXY(*pos + 8, 26);
		printf("2");
		TextColor(ColorCode_DarkPink);
		gotoXY(*pos + 8, 27);
		printf("5");
		TextColor(ColorCode_Grey);
		gotoXY(*pos + 8, 28);
		printf("8");
	}
}
void gif3(int *pos)
{
	if (*pos >= 49 && *pos <= 82)
	{
		gotoXY(*pos + 5, 26);
		printf(" ");
		gotoXY(*pos + 5, 27);
		printf(" ");
		gotoXY(*pos + 5, 28);
		printf(" ");
	}
	if (*pos >= 48 && *pos <= 81)
	{
		TextColor(ColorCode_DarkBlue);
		gotoXY(*pos + 6, 26);
		printf("1");
		TextColor(ColorCode_DarkRed);
		gotoXY(*pos + 6, 27);
		printf("4");
		TextColor(ColorCode_DarkWhite);
		gotoXY(*pos + 6, 28);
		printf("7");
	}
}
void gif4(int *pos)
{
	if (*pos >= 52 && *pos <= 84)
	{
		gotoXY(*pos + 2, 27);
		printf(" ");
	}
	if (*pos >= 51 && *pos <= 83)
	{
		gotoXY(*pos + 3, 27);
		printf("%c", 153);
	}
	if (*pos >= 53 && *pos <= 85)
	{
		gotoXY(*pos + 1, 27);
		printf(" ");
	}
	if (*pos >= 52 && *pos <= 84)
	{
		gotoXY(*pos + 2, 27);
		printf("%c", 219);
	}
	if (*pos >= 54 && *pos <= 86)
	{
		gotoXY(*pos, 27);
		printf(" ");
	}
	if (*pos >= 53 && *pos <= 85)
	{
		gotoXY(*pos + 1, 27);
		printf("%c", 219);
	}
	if (*pos >= 55 && *pos <= 87)
	{
		gotoXY(*pos - 1, 27);
		printf(" ");
	}
	if (*pos >= 54 && *pos <= 86)
	{
		gotoXY(*pos, 27);
		printf("%c", 219);
	}
}
void gif5(int *pos)
{
	if (*pos >= 89 && *pos <= 122)
	{
		gotoXY(176 - *pos, 27);
		printf(" ");
	}
	if (*pos >= 88 && *pos <= 121)
	{
		gotoXY(175 - *pos, 27);
		printf("%c", 153);
	}
	if (*pos >= 90 && *pos <= 123)
	{
		gotoXY(177 - *pos, 27);
		printf(" ");
	}
	if (*pos >= 89 && *pos <= 122)
	{
		gotoXY(176 - *pos, 27);
		printf("%c", 219);
	}
	if (*pos >= 91 && *pos <= 124)
	{
		gotoXY(178 - *pos, 27);
		printf(" ");
	}
	if (*pos >= 90 && *pos <= 123)
	{
		gotoXY(177 - *pos, 27);
		printf("%c", 219);
	}
	if (*pos >= 92 && *pos <= 125)
	{
		gotoXY(179 - *pos, 27);
		printf(" ");
	}
	if (*pos >= 91 && *pos <= 124)
	{
		gotoXY(178 - *pos, 27);
		printf("%c", 219);
	}
	if (*pos >= 95 && *pos <= 128)
	{
		gotoXY(182 - *pos, 27);
		printf(" ");
	}
	TextColor(ColorCode_Red);
	if (*pos >= 94 && *pos <= 127)
	{
		gotoXY(181 - *pos, 27);
		printf("0");
	}
}
//-------------------------------------Select START----------------------------------
void mod()
{
	TextColor(ColorCode_Cyan);
	gotoXY(60, 15);
	printf("%c%c%c%c", 219, 219, 219, 153);
	TextColor(48);
	gotoXY(70, 15);
	printf("      EASY       ");
	TextColor(32);
	gotoXY(70, 17);
	printf("      NORMAL     ");
	TextColor(64);
	gotoXY(70, 19);
	printf("      HARD       ");
	TextColor(16);
	gotoXY(70, 21);
	printf("      BACK       ");
	TextColor(ColorCode_DarkWhite);
}
void selectMod(int *countLine, bool *exit, int *color)
{
	int countLine1 = *countLine;
	if (_kbhit())
	{
		char kitu = _getch();
		if (kitu == 13)
			*exit = true;
		else if (kitu == -32)
		{
			kitu = _getch();
			if (kitu == 80)
			{
				if (*countLine < 4)
				{
					(*countLine)++; //go down
				}
			}
			else if (kitu == 72)
				if (*countLine > 1)
					(*countLine)--; //go up
		}
		else if (kitu == 'w')
		{
			if (*countLine > 1)
				(*countLine)--;
		}
		else if (kitu == 's')
		{
			if (*countLine < 4)
			{
				(*countLine)++; //go down
			}
		}
	}
	if (*countLine != countLine1)
	{
		switch (*countLine)
		{
		case 1:
			*color = ColorCode_Cyan;
			break;
		case 2:
			*color = ColorCode_Green;
			break;
		case 3:
			*color = ColorCode_Red;
			break;
		case 4:
			*color = ColorCode_Blue;
			break;
		}
		TextColor(*color);
		int d = *countLine - countLine1;
		if (d < 0)
		{
			gotoXY(60, 13 + countLine1 * 2);
			printf("    ");
			gotoXY(60, 11 + countLine1 * 2);
			printf("%c%c%c%c", 219, 219, 219, 153);
		}
		else
		{
			gotoXY(60, 13 + countLine1 * 2);
			printf("    ");
			gotoXY(60, 15 + countLine1 * 2);
			printf("%c%c%c%c", 219, 219, 219, 153);
		}
	}
}
void enterMod(int row, int color)
{
	int pos = 60;
	while (pos != 83)
	{
		TextColor(default_ColorCode);
		gotoXY(pos, row);
		printf(" ");
		TextColor(color);
		gotoXY(pos + 3, row);
		printf("%c", 219);
		gotoXY(pos + 4, row);
		printf("%c", 153);
		pos++;
		Sleep(20);
	}
	if (pos == 83)
	{
		gotoXY(pos, row);
		printf("    ");
	}
}
//--------------------------------------CleanTable-----------------------------------
void cleanTable()
{
	TextColor(ColorCode_DarkWhite);
	for (i = 0; i < 20; i++)
	{
		gotoXY(53, 12 + i);
		printf("                                    ");
	}
}
//----------------------------------------About----------------------------------------
void aboutTable()
{
	TextColor(ColorCode_Yellow);
	gotoXY(58, 13);
	printf(" F-CODE Project");
	/*gotoXY(60, 15);
	TextColor(224);
	printf("  Hoang Hai   ");
	gotoXY(60, 17);
	TextColor(176);
	printf("  Melt Melt   ");
	gotoXY(60, 19);
	TextColor(207);
	printf("  Trung Kien  ");
	*/
	TextColor(ColorCode_White);
	gotoXY(43, 15);
	printf("Hello There!");
	gotoXY(43, 16);
	printf("We are college students of FPT University K15.");
	gotoXY(43, 17);
	printf("This is a game as our team project");
	gotoXY(43, 18);
	printf("for F-CODE Club in our school.");
	TextColor(ColorCode_White);
	gotoXY(43, 19);
	printf("We hope that you will enjoy this game.");
	gotoXY(43, 20);
	printf("We are not professional");
	gotoXY(43, 21);
	printf("so there can be some 'bugs' in the game.");
	gotoXY(43, 22);
	printf("If you found it please contact with our team");
	gotoXY(43, 23);
	printf("through Facebook:");
	gotoXY(43, 24);
	TextColor(224);
	printf("  Hoang Hai   www.facebook.com/HoangPhiHai1999");
	gotoXY(43, 25);
	TextColor(176);
	printf("  Melt Melt   www.facebook.com/melt.melt.900  ");
	gotoXY(43, 26);
	TextColor(207);
	printf("  Trung Kien  www.facebook.com/kien123456k    ");
	gotoXY(41, 28);
	TextColor(ColorCode_Red);
	printf(" Press any key on the keyboard to return to menu");
}
//-----------------------------------------Help-------------------------------------------
void helpClassicTable()
{
	//13
	TextColor(128);
	gotoXY(62, 13);
	printf("    CLASSIC    ");
	//15
	TextColor(default_ColorCode);
	gotoXY(30, 15);
	printf("There are 2 type of Classic: ");
	TextColor(224);
	printf("  NORMAL  ");
	TextColor(default_ColorCode);
	printf("  ");
	TextColor(208);
	printf("  MODERN  ");
	//16
	gotoXY(30, 16);
	TextColor(224);
	printf("  NORMAL  ");
	TextColor(default_ColorCode);
	printf("   snake will die if it hit the wall or hit its body");
	//17
	TextColor(208);
	gotoXY(30, 17);
	printf("  MODERN  ");
	TextColor(default_ColorCode);
	printf("   snake will go through wall if it hit the wall and die if it hit its body");
	//19
	TextColor(ColorCode_Cyan);
	gotoXY(30, 19);
	printf("Control: ");
	TextColor(default_ColorCode);
	gotoXY(43, 19);
	printf("UP: upward arrow / w");
	gotoXY(75, 19);
	printf("DOWN: downward arrow / s");
	//20
	gotoXY(43, 20);
	printf("LEFT: leftward arrow / a");
	gotoXY(75, 20);
	printf("RIGHT: rightward arrow / d");
	//22
	TextColor(ColorCode_Cyan);
	gotoXY(30, 22);
	printf("Bait:");
	TextColor(default_ColorCode);
	gotoXY(43, 22);
	printf("normal 0: 1 point");
	gotoXY(75, 22);
	printf("special %c: 5 points", 36);
	//23
	gotoXY(43, 23);
	printf("normal 0: appear when the previous normal bait is eaten");
	//24
	gotoXY(43, 24);
	printf("special %c: appear when 5 previous normal baits is eaten", 36);
	//25
	gotoXY(43, 25);
	printf("            disappear when time progress bar is empty");
	//26
	TextColor(ColorCode_Blue);
	gotoXY(45, 26);
	printf("You can press space to pause or continue the game");
	//28
	TextColor(ColorCode_Red);
	gotoXY(45, 28);
	printf(" Press any key on the keyboard to return to menu");
}
void helpSpecialTable()
{
	//13
	TextColor(192);
	gotoXY(62, 13);
	printf("    SPECIAL    ");
	//15
	TextColor(default_ColorCode);
	gotoXY(30, 15);
	printf("There are 2 type of Special: ");
	TextColor(224);
	printf(" SPECIAL 1 ");
	TextColor(default_ColorCode);
	printf(" ");
	TextColor(208);
	printf(" SPECIAL 2 ");
	//16
	gotoXY(30, 16);
	TextColor(224);
	printf(" SPECIAL 1 ");
	TextColor(default_ColorCode);
	printf("   snake will die if it hit the wall, hit its body or eat bait has value 0");
	//17
	TextColor(208);
	gotoXY(30, 17);
	printf(" SPECIAL 2 ");
	TextColor(default_ColorCode);
	printf("   Like SPECIAL 1 but will not become longer after eat bait");
	//19
	TextColor(ColorCode_Cyan);
	gotoXY(30, 19);
	printf("Control: ");
	TextColor(default_ColorCode);
	gotoXY(43, 19);
	printf("UP: upward arrow / w");
	gotoXY(75, 19);
	printf("DOWN: downward arrow / s");
	//20
	gotoXY(43, 20);
	printf("LEFT: leftward arrow / a");
	gotoXY(75, 20);
	printf("RIGHT: rightward arrow / d");
	//22
	TextColor(ColorCode_Cyan);
	gotoXY(30, 22);
	printf("Bait:");
	TextColor(default_ColorCode);
	gotoXY(43, 22);
	printf("has value x ( 0 < x <= current level ) : x point(s)");
	//23
	gotoXY(43, 23);
	printf("has value x (x > current level ) : - 1 Life");
	//24
	gotoXY(43, 24);
	printf("has value 0 : Life = 0");
	//25
	gotoXY(43, 25);
	printf("Your points will help you level up and gain Life in level 3, 6");
	//26
	TextColor(ColorCode_Blue);
	gotoXY(45, 26);
	printf("You can press space to pause or continue the game");
	//28
	gotoXY(45, 28);
	TextColor(ColorCode_Red);
	printf(" Press any key on the keyboard to return to menu");
}
//---------------------------------------HighScore-----------------------------------------
void showHighScore(int key)
{
	FILE *f = NULL;
	if (key == 0)
		f = fopen("hsCNE.txt", "r");
	else if (key == 5)
		f = fopen("hsCNN.txt", "r");
	else if (key == 10)
		f = fopen("hsCNH.txt", "r");
	else if (key == 15)
		f = fopen("hsCME.txt", "r");
	else if (key == 20)
		f = fopen("hsCMN.txt", "r");
	else if (key == 25)
		f = fopen("hsCMH.txt", "r");
	else if (key == 30)
		f = fopen("hsS1E.txt", "r");
	else if (key == 35)
		f = fopen("hsS1N.txt", "r");
	else if (key == 40)
		f = fopen("hsS1H.txt", "r");
	else if (key == 45)
		f = fopen("hsS2E.txt", "r");
	else if (key == 50)
		f = fopen("hsS2N.txt", "r");
	else if (key == 55)
		f = fopen("hsS2H.txt", "r");
	char *ch = (char *)malloc(30 * sizeof(char));

	int count = 0;
	gotoXY(65, 13);
	TextColor(176);
	printf("  HIGH  SCORE  ");
	gotoXY(56, 15);
	TextColor(ColorCode_White);
	printf("Player's Name");
	gotoXY(79, 15);
	printf("Score");
	while (!feof(f))
	{
		if (count == 10)
			break;
		count++;
		fscanf(f, "%s", ch);
		if (count % 2 == 1)
		{
			if (count == 1)
				TextColor(ColorCode_Red);
			else if (count == 3)
				TextColor(ColorCode_Yellow);
			else if (count == 5)
				TextColor(ColorCode_Green);
			else if (count == 7)
				TextColor(ColorCode_Blue);
			else if (count == 9)
				TextColor(ColorCode_Grey);
			gotoXY(60, 16 + count);
			printf("%s ", ch);
		}
		else
		{
			gotoXY(80, 15 + count);
			printf("%s", ch);
		}
	}
	gotoXY(56, 27);
	TextColor(ColorCode_Red);
	printf(" Press Enter to return to Menu ");
	gotoXY(55, 29);
	printf(" Press Backspace to reset record");
	fclose(f);
}
void showHighScoreGameover(int key)
{
	FILE *f = NULL;
	if (key == 0)
		f = fopen("hsCNE.txt", "r");
	else if (key == 5)
		f = fopen("hsCNN.txt", "r");
	else if (key == 10)
		f = fopen("hsCNH.txt", "r");
	else if (key == 15)
		f = fopen("hsCME.txt", "r");
	else if (key == 20)
		f = fopen("hsCMN.txt", "r");
	else if (key == 25)
		f = fopen("hsCMH.txt", "r");
	else if (key == 30)
		f = fopen("hsS1E.txt", "r");
	else if (key == 35)
		f = fopen("hsS1N.txt", "r");
	else if (key == 40)
		f = fopen("hsS1H.txt", "r");
	else if (key == 45)
		f = fopen("hsS2E.txt", "r");
	else if (key == 50)
		f = fopen("hsS2N.txt", "r");
	else if (key == 55)
		f = fopen("hsS2H.txt", "r");
	char *ch = (char *)malloc(30 * sizeof(char));

	int count = 0;
	gotoXY(64, 17);
	TextColor(176);
	printf("  HIGH  SCORE  ");
	gotoXY(56, 18);
	TextColor(ColorCode_White);
	printf("Player's Name");
	gotoXY(79, 18);
	printf("Score");
	while (!feof(f))
	{
		if (count == 10)
			break;
		count++;
		fscanf(f, "%s", ch);
		if (count % 2 == 1)
		{
			if (count == 1)
				TextColor(ColorCode_Red);
			else if (count == 3)
				TextColor(ColorCode_Yellow);
			else if (count == 5)
				TextColor(ColorCode_Green);
			else if (count == 7)
				TextColor(ColorCode_Blue);
			else if (count == 9)
				TextColor(ColorCode_Grey);
			gotoXY(60, 19 + (count - 1) / 2);
			printf("%s ", ch);
		}
		else
		{
			gotoXY(80, 19 + (count - 1) / 2);
			printf("%s", ch);
		}
	}
	fclose(f);
}
bool isEmpty(int key)
{
	FILE *f = NULL;
	long size = 0;
	if (key == 0)
		f = fopen("hsCNE.txt", "r");
	else if (key == 5)
		f = fopen("hsCNN.txt", "r");
	else if (key == 10)
		f = fopen("hsCNH.txt", "r");
	else if (key == 15)
		f = fopen("hsCME.txt", "r");
	else if (key == 25)
		f = fopen("hsCMH.txt", "r");
	else if (key == 20)
		f = fopen("hsCMN.txt", "r");
	else if (key == 30)
		f = fopen("hsS1E.txt", "r");
	else if (key == 35)
		f = fopen("hsS1N.txt", "r");
	else if (key == 40)
		f = fopen("hsS1H.txt", "r");
	else if (key == 45)
		f = fopen("hsS2E.txt", "r");
	else if (key == 50)
		f = fopen("hsS2N.txt", "r");
	else if (key == 55)
		f = fopen("hsS2H.txt", "r");
	if (f)
	{
		fseek(f, 0, SEEK_END);
		size = ftell(f);
		fclose(f);
	}
	return (size == 0);
}
void getHighScore(int key)
{
	FILE *f = NULL;
	if (key == 0)
		f = fopen("hsCNE.txt", "w");
	else if (key == 5)
		f = fopen("hsCNN.txt", "w");
	else if (key == 10)
		f = fopen("hsCNH.txt", "w");
	else if (key == 15)
		f = fopen("hsCME.txt", "w");
	else if (key == 20)
		f = fopen("hsCMN.txt", "w");
	else if (key == 25)
		f = fopen("hsCMH.txt", "w");
	else if (key == 30)
		f = fopen("hsS1E.txt", "w");
	else if (key == 35)
		f = fopen("hsS1N.txt", "w");
	else if (key == 40)
		f = fopen("hsS1H.txt", "w");
	else if (key == 45)
		f = fopen("hsS2E.txt", "w");
	else if (key == 50)
		f = fopen("hsS2N.txt", "w");
	else if (key == 55)
		f = fopen("hsS2H.txt", "w");
	for (i = key; i < key + 5; i++)
	{
		fprintf(f, "%s ", highScore[i].name);
		fprintf(f, "%d\n", highScore[i].score);
	}
	fclose(f);
}
bool checkName(char _name[18])
{
	if (strlen(_name) > 17 || strlen(_name) < 1)
		return false;
	for (i = 0; i < strlen(_name); i++)
	{
		if (_name[i] > 122)
			return false;
		if (_name[i] < 97 && _name[i] > 90)
			return false;
		if (_name[i] < 65 && _name[i] > 57)
			return false;
		if (_name[i] < 48)
			return false;
	}
	return true;
}
void initScore(int key)
{
	if (isEmpty(key))
	{
		for (i = key; i < key + 5; i++)
		{
			strcpy(highScore[i].name, "PLAYER");
			highScore[i].score = 0;
		}
		getHighScore(key);
	}
	else
	{
		char arr[30];
		int count = 0;
		FILE *f = NULL;
		if (key == 0)
			f = fopen("hsCNE.txt", "r");
		else if (key == 5)
			f = fopen("hsCNN.txt", "r");
		else if (key == 10)
			f = fopen("hsCNH.txt", "r");
		else if (key == 15)
			f = fopen("hsCME.txt", "r");
		else if (key == 20)
			f = fopen("hsCMN.txt", "r");
		else if (key == 25)
			f = fopen("hsCMH.txt", "r");
		else if (key == 30)
			f = fopen("hsS1E.txt", "r");
		else if (key == 35)
			f = fopen("hsS1N.txt", "r");
		else if (key == 40)
			f = fopen("hsS1H.txt", "r");
		else if (key == 45)
			f = fopen("hsS2E.txt", "r");
		else if (key == 50)
			f = fopen("hsS2N.txt", "r");
		else if (key == 55)
			f = fopen("hsS2H.txt", "r");
		char *ch = (char *)malloc(30 * sizeof(char));
		for (i = key; i < key + 5;)
		{
			while (!feof(f))
			{
				count++;
				fscanf(f, "%s", arr);
				if (count % 2 == 1)
					strcpy(highScore[i].name, arr);
				else
				{
					highScore[i].score = atoi(arr);
					i++;
				}
			}
		}
		fclose(f);
	}
}
void checkHighScore(int _score, int key)
{
	char _name[18];
	int temp = key + 5;
	for (i = key + 4; i > key - 1; i--)
		if (_score > highScore[i].score)
			temp = i;
	if (temp == key + 5)
	{
		TextColor(ColorCode_Cyan);
		gotoXY(GAMEOVER_LEFT + 15, GAMEOVER_TOP + 3);
		printf("Sorry!");
		gotoXY(GAMEOVER_LEFT + 6, GAMEOVER_TOP + 4);
		printf("You can't beat the record!");
		gotoXY(GAMEOVER_LEFT + 9, GAMEOVER_TOP + 5);
		printf("Good luck next time!");
		TextColor(ColorCode_White);
		gotoXY(GAMEOVER_LEFT + 8, GAMEOVER_TOP + 15);
		printf("Press Enter to restart");
		gotoXY(GAMEOVER_LEFT + 5, GAMEOVER_TOP + 17);
		printf("Press ESC to go back to menu");
		showHighScoreGameover(key);
		while (true)
		{
			if (_kbhit())
			{
				char kitu = _getch();
				if (kitu == 13)
				{
					restart = 1;
					break;
				}
				else if (kitu == 27)
				{
					restart = 2;
					break;
				}
			}
		}
	}
	else
	{
		gotoXY(GAMEOVER_LEFT + 12, GAMEOVER_TOP + 4);
		TextColor(ColorCode_Yellow);
		printf("CONGRATULATION!");
		gotoXY(GAMEOVER_LEFT + 11, GAMEOVER_TOP + 5);
		printf("You are in top 5!");
		gotoXY(GAMEOVER_LEFT + 5, GAMEOVER_TOP + 6);
		TextColor(ColorCode_Red);
		printf("Enter a name without spaces");
		gotoXY(GAMEOVER_LEFT + 2, GAMEOVER_TOP + 7);
		printf("Name length can't longer than 18");
		TextColor(ColorCode_White);
		gotoXY(GAMEOVER_LEFT + 3, GAMEOVER_TOP + 12);
		printf("Press Enter to enter your name");
		gotoXY(GAMEOVER_LEFT + 5, GAMEOVER_TOP + 14);
		printf("Press ESC to go back to menu");
		gotoXY(GAMEOVER_LEFT + 1, GAMEOVER_TOP + 9);
		TextColor(ColorCode_Cyan);
		printf("Player: ");
		while (true)
		{
			if (_kbhit())
			{
				char kitu = _getch();
				if (kitu == 13)
				{
					TextColor(default_ColorCode);
					gotoXY(GAMEOVER_LEFT + 3, GAMEOVER_TOP + 12);
					printf("Press Enter to save your record");
					gotoXY(GAMEOVER_LEFT + 9, GAMEOVER_TOP + 9);
					showCursorType();
					gets(_name);
					restart = 1;
					break;
				}
				else if (kitu == 27)
				{
					restart = 2;
					return;
				}
			}
		}
		while (!checkName(_name))
		{
			TextColor(default_ColorCode);
			gotoXY(GAMEOVER_LEFT + 9, GAMEOVER_TOP + 9);
			printf("                          ");
			putchar(186);
			putchar(186);
			printf("                                       %c", 186);
			gotoXY(GAMEOVER_LEFT + 3, GAMEOVER_TOP + 12);
			printf("Press Enter to save your record");
			gotoXY(GAMEOVER_LEFT + 8, GAMEOVER_TOP + 10);
			TextColor(ColorCode_Red);
			printf("Your name is invalid!");
			gotoXY(GAMEOVER_LEFT + 9, GAMEOVER_TOP + 9);
			gets(_name);
		}
		TextColor(ColorCode_White);
		gotoXY(GAMEOVER_LEFT + 3, GAMEOVER_TOP + 12);
		printf("    Press Enter to restart     ");
		gotoXY(GAMEOVER_LEFT + 5, GAMEOVER_TOP + 14);
		printf("Press ESC to go back to menu");
		noCursorType();
		while (true)
		{
			if (_kbhit())
			{
				char kitu = _getch();
				if (kitu == 13)
				{
					restart = 1;
					break;
				}
				else if (kitu == 27)
				{
					restart = 2;
					break;
				}
			}
		}
		for (j = key + 4; j > temp; j--)
		{
			strcpy(highScore[j].name, highScore[j - 1].name);
			highScore[j].score = highScore[j - 1].score;
		}
		strcpy(highScore[temp].name, _name);
		highScore[temp].score = _score;
		getHighScore(key);
	}
}
void lag()
{
	gotoXY(0, 0);
	printf("a");
	gotoXY(0, 0);
	printf("");
}
//---------------------------Select QUIT----------------------
void goodBye()
{
	gotoXY(60, 27);
	printf("((((((: GOOD BYE :))))))");
	gotoXY(54, 27);
	printf("      ");
	gotoXY(84, 27);
	printf("    ");
	gotoXY(54, 26);
	printf("                                  ");
	gotoXY(54, 28);
	printf("                                  ");
}
//----------------------------Select type-------------------------
void type()
{
	TextColor(ColorCode_Grey);
	gotoXY(60, 16);
	printf("%c%c%c%c", 219, 219, 219, 153);
	TextColor(128);
	gotoXY(70, 16);
	printf("     CLASSIC     ");
	TextColor(192);
	gotoXY(70, 18);
	printf("     SPECIAL     ");
	TextColor(16);
	gotoXY(70, 20);
	printf("      BACK       ");
}
void selectType(int *countLine, bool *exit, int *color)
{
	int countLine1 = *countLine;
	if (_kbhit())
	{
		char kitu = _getch();
		if (kitu == 13)
			*exit = true;
		else if (kitu == -32)
		{
			kitu = _getch();
			if (kitu == 80)
			{
				if (*countLine < 3)
				{
					(*countLine)++; //go down
				}
			}
			else if (kitu == 72)
				if (*countLine > 1)
					(*countLine)--; //go up
		}
		else if (kitu == 'w')
		{
			if (*countLine > 1)
				(*countLine)--;
		}
		else if (kitu == 's')
		{
			if (*countLine < 3)
			{
				(*countLine)++; //go down
			}
		}
	}
	if (*countLine != countLine1)
	{
		switch (*countLine)
		{
		case 1:
			*color = ColorCode_Grey;
			break;
		case 2:
			*color = ColorCode_Red;
			break;
		case 3:
			*color = ColorCode_Blue;
			break;
		}
		TextColor(*color);
		int d = *countLine - countLine1;
		if (d < 0)
		{
			gotoXY(60, 14 + countLine1 * 2);
			printf("    ");
			gotoXY(60, 12 + countLine1 * 2);
			printf("%c%c%c%c", 219, 219, 219, 153);
		}
		else
		{
			gotoXY(60, 14 + countLine1 * 2);
			printf("    ");
			gotoXY(60, 16 + countLine1 * 2);
			printf("%c%c%c%c", 219, 219, 219, 153);
		}
	}
}
void enterType(int row, int color)
{
	int pos = 60;
	while (pos != 83)
	{
		TextColor(default_ColorCode);
		gotoXY(pos, row);
		printf(" ");
		TextColor(color);
		gotoXY(pos + 3, row);
		printf("%c", 219);
		gotoXY(pos + 4, row);
		printf("%c", 153);
		pos++;
		Sleep(20);
	}
	if (pos == 83)
	{
		gotoXY(pos, row);
		printf("    ");
	}
}
//--------------------------------------Select type Special-----------------------------
void typeSpecial()
{
	TextColor(ColorCode_Yellow);
	gotoXY(60, 16);
	printf("%c%c%c%c", 219, 219, 219, 153);
	TextColor(224);
	gotoXY(70, 16);
	printf("    SPECIAL 1    ");
	TextColor(208);
	gotoXY(70, 18);
	printf("    SPECIAL 2    ");
	TextColor(16);
	gotoXY(70, 20);
	printf("      BACK       ");
}
void selectTypeSpecial(int *countLine, bool *exit, int *color)
{
	int countLine1 = *countLine;
	if (_kbhit())
	{
		char kitu = _getch();
		if (kitu == 13)
			*exit = true;
		else if (kitu == -32)
		{
			kitu = _getch();
			if (kitu == 80)
			{
				if (*countLine < 3)
				{
					(*countLine)++; //go down
				}
			}
			else if (kitu == 72)
				if (*countLine > 1)
					(*countLine)--; //go up
		}
		else if (kitu == 'w')
		{
			if (*countLine > 1)
				(*countLine)--;
		}
		else if (kitu == 's')
		{
			if (*countLine < 3)
			{
				(*countLine)++; //go down
			}
		}
	}
	if (*countLine != countLine1)
	{
		switch (*countLine)
		{
		case 1:
			*color = ColorCode_Yellow;
			break;
		case 2:
			*color = ColorCode_Pink;
			break;
		case 3:
			*color = ColorCode_Blue;
			break;
		}
		TextColor(*color);
		int d = *countLine - countLine1;
		if (d < 0)
		{
			gotoXY(60, 14 + countLine1 * 2);
			printf("    ");
			gotoXY(60, 12 + countLine1 * 2);
			printf("%c%c%c%c", 219, 219, 219, 153);
		}
		else
		{
			gotoXY(60, 14 + countLine1 * 2);
			printf("    ");
			gotoXY(60, 16 + countLine1 * 2);
			printf("%c%c%c%c", 219, 219, 219, 153);
		}
	}
}
void enterTypeSpecial(int row, int color)
{
	int pos = 60;
	while (pos != 83)
	{
		TextColor(default_ColorCode);
		gotoXY(pos, row);
		printf(" ");
		TextColor(color);
		gotoXY(pos + 3, row);
		printf("%c", 219);
		gotoXY(pos + 4, row);
		printf("%c", 153);
		pos++;
		Sleep(20);
	}
	if (pos == 83)
	{
		gotoXY(pos, row);
		printf("    ");
	}
}

//--------------------------------------Select type Classic--------------------------------
void typeClassic()
{
	TextColor(ColorCode_Yellow);
	gotoXY(60, 16);
	printf("%c%c%c%c", 219, 219, 219, 153);
	TextColor(224);
	gotoXY(70, 16);
	printf("     NORMAL      ");
	TextColor(208);
	gotoXY(70, 18);
	printf("     MODERN      ");
	TextColor(16);
	gotoXY(70, 20);
	printf("      BACK       ");
}

void selectTypeClassic(int *countLine, bool *exit, int *color)
{
	int countLine1 = *countLine;
	if (_kbhit())
	{
		char kitu = _getch();
		if (kitu == 13)
			*exit = true;
		else if (kitu == -32)
		{
			kitu = _getch();
			if (kitu == 80)
			{
				if (*countLine < 3)
				{
					(*countLine)++; //go down
				}
			}
			else if (kitu == 72)
				if (*countLine > 1)
					(*countLine)--; //go up
		}
		else if (kitu == 'w')
		{
			if (*countLine > 1)
				(*countLine)--;
		}
		else if (kitu == 's')
		{
			if (*countLine < 3)
			{
				(*countLine)++; //go down
			}
		}
	}
	if (*countLine != countLine1)
	{
		switch (*countLine)
		{
		case 1:
			*color = ColorCode_Yellow;
			break;
		case 2:
			*color = ColorCode_Pink;
			break;
		case 3:
			*color = ColorCode_Blue;
			break;
		}
		TextColor(*color);
		int d = *countLine - countLine1;
		if (d < 0)
		{
			gotoXY(60, 14 + countLine1 * 2);
			printf("    ");
			gotoXY(60, 12 + countLine1 * 2);
			printf("%c%c%c%c", 219, 219, 219, 153);
		}
		else
		{
			gotoXY(60, 14 + countLine1 * 2);
			printf("    ");
			gotoXY(60, 16 + countLine1 * 2);
			printf("%c%c%c%c", 219, 219, 219, 153);
		}
	}
}

void enterTypeClassic(int row, int color)
{
	int pos = 60;
	while (pos != 83)
	{
		TextColor(default_ColorCode);
		gotoXY(pos, row);
		printf(" ");
		TextColor(color);
		gotoXY(pos + 3, row);
		printf("%c", 219);
		gotoXY(pos + 4, row);
		printf("%c", 153);
		pos++;
		Sleep(20);
	}
	if (pos == 83)
	{
		gotoXY(pos, row);
		printf("    ");
	}
}
//-------------------------------------------Pause------------------------------------------------
void pause()
{
	restart = 1;
	bool Continue = false;
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 20);
	printf("(    Press Space to continue    )");
	TextColor(240);
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 22);
	printf("             RESTART              ");
	TextColor(default_ColorCode);
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 24);
	printf("          BACK TO MENU            ");
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 26);
	printf("(     Press Enter to select     )");
	while (Continue == false)
	{
		if (_kbhit())
		{
			char kitu = _getch();
			if (kitu == 32)
			{
				TextColor(ColorCode_White);
				gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 20);
				printf("(     Press Space to pause      )");
				gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 22);
				printf("                                  ");
				gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 24);
				printf("                                  ");
				gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 26);
				printf("                                 ");
				restart = 0;
				Continue = true;
			}
			else if (kitu == -32)
			{
				kitu = _getch();
				if (kitu == 80 && restart == 1)
				{
					//go down
					restart = 2;
					TextColor(default_ColorCode);
					gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 22);
					printf("             RESTART              ");
					TextColor(240);
					gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 24);
					printf("          BACK TO MENU            ");
				}
				else if (kitu == 72 && restart == 2)
				{
					//go up
					restart = 1;
					TextColor(240);
					gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 22);
					printf("             RESTART              ");
					TextColor(default_ColorCode);
					gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 24);
					printf("          BACK TO MENU            ");
				}
			}
			else if (kitu == 'w' && restart == 2)
			{
				//go up
				restart = 1;
				TextColor(240);
				gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 22);
				printf("             RESTART              ");
				TextColor(default_ColorCode);
				gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 24);
				printf("          BACK TO MENU            ");
			}
			else if (kitu == 's' && restart == 1)
			{
				//go down
				restart = 2;
				TextColor(default_ColorCode);
				gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 22);
				printf("             RESTART              ");
				TextColor(240);
				gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 24);
				printf("          BACK TO MENU            ");
			}
			else if (kitu == 13)
			{
				Continue = true;
			}
		}
	}
}
//----------------------------------------Game Over------------------------------------
void gameover(int _score, int key)
{
	for (i = GAMEOVER_TOP + 1; i <= GAMEOVER_BOTTOM - 1; i++)
	{
		gotoXY(GAMEOVER_LEFT + 1, i);
		for (j = GAMEOVER_LEFT + 1; j <= GAMEOVER_RIGHT - 1; j++)
		{
			printf(" ");
		}
	}
	gotoXY(GAMEOVER_LEFT + 8, GAMEOVER_TOP + 2);
	TextColor(192);
	printf("      GAME OVER      ");
	checkHighScore(_score, key);
}
//-------------------------------------Congratulation-----------------------------------
void congratulation(int level_game)
{
	TextColor(level_game);
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 20);
	printf("         CONGRATULATION          ");
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 22);
	if (level_game % 3 == 0)
	{
		printf(" YOU PASSED LEVEL %d / LIFE + 1  ", level_game - 1);
	}
	else
	{
		printf("       YOU PASSED LEVEL %d       ", level_game - 1);
	}
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 24);
	printf("    Press any key to continue    ");
	PlaySound(TEXT("LevelUp.wav"), NULL, SND_SYNC);
	_getch();
	TextColor(default_ColorCode);
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 20);
	printf("                                 ");
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 22);
	printf("                                 ");
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 24);
	printf("                                 ");
}
//--------------------------------------Finish game--------------------------------------
void finishGame()
{
	TextColor(241);
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 20);
	printf("         CONGRATULATION!!!       ");
	TextColor(ColorCode_Blue);
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 22);
	printf("      YOU FINISHED THE GAME!!!   ");
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 24);
	printf("    WE HOPE YOU ENJOY THE GAME   ");
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 26);
	printf("  Press any key to back to MENU  ");
	PlaySound(TEXT("FinishGame.wav"), NULL, SND_ASYNC);
	_getch();
	PlaySound(NULL, NULL, SND_ASYNC);
	TextColor(default_ColorCode);
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 20);
	printf("                                 ");
}
//--------------------------------------Resize console--------------------------------------
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
//=============================================GAME================================================
//======================================SPECIAL GAME=============================================
//=======================================SNAKE=================================================
void declere_snake(struct Snake *snake, int speed)
{
	snake->bend[0].x = COORD_SNAKE_START_X;
	snake->bend[0].y = COORD_SNAKE_START_Y;
	snake->bend[1].x = COORD_SNAKE_START_X - 1;
	snake->bend[1].y = COORD_SNAKE_START_Y;
	snake->bend[2].x = COORD_SNAKE_START_X - 2;
	snake->bend[2].y = COORD_SNAKE_START_Y;
	snake->length = 3;
	snake->direc = RIGHT;
	snake->score = 0;
	snake->color = default_ColorCode;
	snake->speed_hor = speed;
	snake->speed_ver = snake->speed_hor * 1.5;
}
void draw_snake(struct Snake snake)
{
	gotoXY(snake.bend[0].x, snake.bend[0].y);
	TextColor(snake.color);
	putchar(153);

	for (i = 1; i <= snake.length; i++)
	{
		if (i < snake.length)
		{
			gotoXY(snake.bend[i].x, snake.bend[i].y);
			TextColor(snake.color);
			putchar(219);
			TextColor(default_ColorCode);
		}
		else
		{
			gotoXY(snake.bend[i].x, snake.bend[i].y);
			puts(" ");
		}
	}
	if (snake.direc == UP || snake.direc == DOWN)
	{
		Sleep(snake.speed_ver);
	}
	else
	{
		Sleep(snake.speed_hor);
	}
}
void update_snake(struct Snake *snake, struct Food_coord *food_coord, int level_game)
{
	for (i = 0; i < level_game * NUMBER_FOOD_EACH_LV; i++)
	{
		if (snake->bend[0].x == food_coord[i].coord.x && snake->bend[0].y == food_coord[i].coord.y)
		{
			for (i = snake->length + 1; i > 0; i--)
			{
				snake->bend[i] = snake->bend[i - 1];
			}
			snake->length++;
			if (snake->direc == UP)
			{
				snake->bend[0].y--;
			}
			else if (snake->direc == DOWN)
			{
				snake->bend[0].y++;
			}
			else if (snake->direc == LEFT)
			{
				snake->bend[0].x--;
			}
			else if (snake->direc == RIGHT)
			{
				snake->bend[0].x++;
			}
			break;
		}
	}
}

//---------------------------------------show cursor-----------------------------
void showCursorType()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = TRUE;
	info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

//++++++++++++++++++++Control_And_Move_Snake++++++++++++++++++++++++++++++++//
void control_move_snake(struct Snake *snake)
{
	for (i = snake->length; i > 0; i--)
	{
		snake->bend[i] = snake->bend[i - 1];
	}
	int key = inputKey();
	if ((key == key_Up && snake->direc != DOWN) || (key == 'w' && snake->direc != DOWN))
	{
		snake->direc = UP;
	}
	else if ((key == key_Down && snake->direc != UP) || (key == 's' && snake->direc != UP))
	{
		snake->direc = DOWN;
	}
	else if ((key == key_Left && snake->direc != RIGHT) || (key == 'a' && snake->direc != RIGHT))
	{
		snake->direc = LEFT;
	}
	else if ((key == key_Right && snake->direc != LEFT) || (key == 'd' && snake->direc != LEFT))
	{
		snake->direc = RIGHT;
	}
	else if (key == 32)
	{
		pause();
	}

	if (snake->direc == UP)
	{
		snake->bend[0].y--;
	}
	else if (snake->direc == DOWN)
	{
		snake->bend[0].y++;
	}
	else if (snake->direc == LEFT)
	{
		snake->bend[0].x--;
	}
	else if (snake->direc == RIGHT)
	{
		snake->bend[0].x++;
	}
}

//=======================================FOOD=================================================
void declere_food(struct Food *food)
{
	for (i = 1; i <= LEVEL_GAME_MAX; i++)
	{
		food[i].color = i;
		food[i].shape = i;
		food[i].score = i;
	}
	// food_end_game
	food[0].color = 12;
	food[0].score = 0;
	food[0].shape = 0;
}
void draw_main_food(struct Food *food, struct Food_coord *food_coord, int level_game, struct Snake *snake, struct Snake *challenge)
{
	int width = (CONSOLE_RIGHT - CONSOLE_LEFT);
	int height = (CONSOLE_BOTTOM - CONSOLE_TOP);
	for (i = 0; i < level_game * NUMBER_FOOD_EACH_LV * 1 / 3; i++)
	{
		if ((snake->bend[1].x == food_coord[i].coord.x && snake->bend[1].y == food_coord[i].coord.y) || (challenge->bend[1].x == food_coord[i].coord.x && challenge->bend[1].y == food_coord[i].coord.y))
		{
			// print main food of level//
			if (snake->bend[1].x == food_coord[i].coord.x && snake->bend[1].y == food_coord[i].coord.y)
			{
				snake->color = food[food_coord[i].level].color;
			}
			int level_food = 1 + rand() % level_game;
			food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
			food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
			// check main food
		checkMainFood:
			check = true;
			for (j = 0; j < level_game * NUMBER_FOOD_EACH_LV; j++)
			{
				if (j != i)
				{
					while (food_coord[j].coord.x == food_coord[i].coord.x && food_coord[j].coord.y == food_coord[i].coord.y)
					{
						food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
						food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
						check = false;
					}
					if (check == false)
						goto checkMainFood;
				}
			}
			// check snake
			for (j = 0; j < snake->length; j++)
			{
				while (snake->bend[j].x == food_coord[i].coord.x && snake->bend[j].y == food_coord[i].coord.y)
				{
					food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
					food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
					check = false;
				}
				if (check == false)
					goto checkMainFood;
			}
			// check challenge
			for (j = 0; j < challenge->length; j++)
			{
				while (challenge->bend[j].x == food_coord[i].coord.x && challenge->bend[j].y == food_coord[i].coord.y)
				{
					food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
					food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
					check = false;
				}
				if (check == false)
					goto checkMainFood;
				// check obstacle
				if (level_game >= LEVEL_UPDATE_MAP)
				{
					// prevent food == obsacle top
					while ((food_coord[i].coord.x == width * 2 / 9 && food_coord[i].coord.y <= height * 2 / 5) || (food_coord[i].coord.x == width * 3 / 9 && food_coord[i].coord.y <= height * 2 / 5))
					{
						food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
						food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
						check = false;
					}
					if (check == false)
						goto checkMainFood;
					// prevent food == obsacle bottom
					while ((food_coord[i].coord.x == width * 7 / 9 && food_coord[i].coord.y >= height * 3 / 5) || (food_coord[i].coord.x == width * 8 / 9 && food_coord[i].coord.y >= height * 3 / 5))
					{
						food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
						food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
						check = false;
					}
					if (check == false)
						goto checkMainFood;
				}
			}
			food_coord[i].score = food[level_food].score;
			gotoXY(food_coord[i].coord.x, food_coord[i].coord.y);
			TextColor(food[level_food].color);
			printf("%d", food[level_food].shape);
			food_coord[i].level = level_food;
			TextColor(default_ColorCode);
		}
	}
}
void draw_toxic_food(struct Food *food, struct Food_coord *food_coord, int level_game, struct Snake *snake, struct Snake *challenge)
{
	int width = (CONSOLE_RIGHT - CONSOLE_LEFT);
	int height = (CONSOLE_BOTTOM - CONSOLE_TOP);
	for (i = level_game * NUMBER_FOOD_EACH_LV * 1 / 3; i < level_game * NUMBER_FOOD_EACH_LV * 2 / 3; i++)
	{
		if ((snake->bend[1].x == food_coord[i].coord.x && snake->bend[1].y == food_coord[i].coord.y) || (challenge->bend[1].x == food_coord[i].coord.x && challenge->bend[1].y == food_coord[i].coord.y))
		{
			if (snake->bend[1].x == food_coord[i].coord.x && snake->bend[1].y == food_coord[i].coord.y)
			{
				snake->color = default_ColorCode;
			}
			// print toxic food //
			int level_food = level_game + 1 + rand() % (LEVEL_GAME_MAX - level_game);
			food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
			food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
			// check toxic food
		checkToxicFood:
			check = true;
			for (j = 0; j < level_game * NUMBER_FOOD_EACH_LV; j++)
			{
				if (j != i)
				{
					while (food_coord[j].coord.x == food_coord[i].coord.x && food_coord[j].coord.y == food_coord[i].coord.y)
					{
						food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
						food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
						check = false;
					}
					if (check == false)
						goto checkToxicFood;
				}
			}
			// check snake
			for (j = 0; j < snake->length; j++)
			{
				while (snake->bend[j].x == food_coord[i].coord.x && snake->bend[j].y == food_coord[i].coord.y)
				{
					food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
					food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
					check = false;
				}
				if (check == false)
					goto checkToxicFood;
			}
			// check challenge
			for (j = 0; j < challenge->length; j++)
			{
				while (challenge->bend[j].x == food_coord[i].coord.x && challenge->bend[j].y == food_coord[i].coord.y)
				{
					food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
					food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
					check = false;
				}
				if (check == false)
					goto checkToxicFood;
			}
			// check obstacle
			if (level_game >= LEVEL_UPDATE_MAP)
			{
				// prevent food == obsacle top
				while ((food_coord[i].coord.x == width * 2 / 9 && food_coord[i].coord.y <= height * 2 / 5) || (food_coord[i].coord.x == width * 3 / 9 && food_coord[i].coord.y <= height * 2 / 5))
				{
					food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
					food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
					check = false;
				}
				if (check == false)
					goto checkToxicFood;
				// prevent food == obsacle bottom
				while ((food_coord[i].coord.x == width * 7 / 9 && food_coord[i].coord.y >= height * 3 / 5) || (food_coord[i].coord.x == width * 8 / 9 && food_coord[i].coord.y >= height * 3 / 5))
				{
					food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
					food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
					check = false;
				}
				if (check == false)
					goto checkToxicFood;
			}
			food_coord[i].level = level_food;
			food_coord[i].score = food[level_food].shape;
			gotoXY(food_coord[i].coord.x, food_coord[i].coord.y);
			TextColor(food[level_food].color);
			printf("%d", food[level_food].shape);
			TextColor(default_ColorCode);
		}
	}
}
void draw_any_food(struct Food *food, struct Food_coord *food_coord, int level_game, struct Snake *snake, struct Snake *challenge)
{
	int width = (CONSOLE_RIGHT - CONSOLE_LEFT);
	int height = (CONSOLE_BOTTOM - CONSOLE_TOP);
	for (i = level_game * NUMBER_FOOD_EACH_LV * 2 / 3; i < level_game * NUMBER_FOOD_EACH_LV; i++)
	{
		if ((snake->bend[1].x == food_coord[i].coord.x && snake->bend[1].y == food_coord[i].coord.y) || (challenge->bend[1].x == food_coord[i].coord.x && challenge->bend[1].y == food_coord[i].coord.y))
		{
			if (snake->bend[1].x == food_coord[i].coord.x && snake->bend[1].y == food_coord[i].coord.y)
			{
				if (food_coord[i].level > 0 && food_coord[i].level <= level_game)
				{
					snake->color = food[food_coord[i].level].color;
				}
				else
				{
					snake->color = default_ColorCode;
				}
			}
			int level_food = 1 + rand() % LEVEL_GAME_MAX;
			food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
			food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 4);
			// check food in range (0,9)
		checkAnyFood:
			check = true;
			for (j = 0; j < level_game * NUMBER_FOOD_EACH_LV; j++)
			{
				if (j != i)
				{
					while (food_coord[j].coord.x == food_coord[i].coord.x && food_coord[j].coord.y == food_coord[i].coord.y)
					{
						food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
						food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
						check = false;
					}
					if (check == false)
						goto checkAnyFood;
				}
			}
			// check snake
			for (j = 0; j < snake->length; j++)
			{
				while (snake->bend[j].x == food_coord[i].coord.x && snake->bend[j].y == food_coord[i].coord.y)
				{
					food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
					food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 4);
					check = false;
				}
				if (check == false)
					goto checkAnyFood;
			}
			// check challenge
			for (j = 0; j < challenge->length; j++)
			{
				while (challenge->bend[j].x == food_coord[i].coord.x && challenge->bend[j].y == food_coord[i].coord.y)
				{
					food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
					food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 4);
					check = false;
				}
				if (check == false)
					goto checkAnyFood;
			}

			// check obstacle
			if (level_game >= LEVEL_UPDATE_MAP)
			{
				// prevent food == obsacle top
				while ((food_coord[i].coord.x == width * 2 / 9 && food_coord[i].coord.y <= height * 2 / 5) || (food_coord[i].coord.x == width * 3 / 9 && food_coord[i].coord.y <= height * 2 / 5))
				{
					food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
					food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 4);
					check = false;
				}
				if (check == false)
					goto checkAnyFood;
				// prevent food == obsacle bottom
				while ((food_coord[i].coord.x == width * 7 / 9 && food_coord[i].coord.y >= height * 3 / 5) || (food_coord[i].coord.x == width * 8 / 9 && food_coord[i].coord.y >= height * 3 / 5))
				{
					food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
					food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 4);
					check = false;
				}
				if (check == false)
					goto checkAnyFood;
			}

			food_coord[i].score = food[level_food].shape;
			gotoXY(food_coord[i].coord.x, food_coord[i].coord.y);
			TextColor(food[level_food].color);
			printf("%d", food[level_food].shape);
			TextColor(default_ColorCode);
			food_coord[i].level = level_food;
		}
	}
}
void call_food(struct Food *food, struct Food_coord *food_coord, int level_game, struct Snake *snake, struct Snake *challenge)
{
	int width = (CONSOLE_RIGHT - CONSOLE_LEFT);
	int height = (CONSOLE_BOTTOM - CONSOLE_TOP);

	// print main food of level//
	for (i = 0; i < level_game * NUMBER_FOOD_EACH_LV * 1 / 3; i++)
	{
		int level_food = 1 + rand() % level_game;
		food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
		food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
		// check main food
	checkMainFood:
		check = true;
		for (j = 0; j < i; j++)
		{
			while (food_coord[j].coord.x == food_coord[i].coord.x && food_coord[j].coord.y == food_coord[i].coord.y)
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkMainFood;
		}
		// check snake
		for (j = 0; j < snake->length; j++)
		{
			while (snake->bend[j].x == food_coord[i].coord.x && snake->bend[j].y == food_coord[i].coord.y)
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkMainFood;
		}
		// check challenge
		for (j = 0; j < challenge->length; j++)
		{
			while (challenge->bend[j].x == food_coord[i].coord.x && challenge->bend[j].y == food_coord[i].coord.y)
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkMainFood;
		}
		// check obstacle
		if (level_game >= LEVEL_UPDATE_MAP)
		{
			// prevent food == obsacle top
			while ((food_coord[i].coord.x == width * 2 / 9 && food_coord[i].coord.y <= height * 2 / 5) || (food_coord[i].coord.x == width * 3 / 9 && food_coord[i].coord.y <= height * 2 / 5))
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkMainFood;
			// prevent food == obsacle bottom
			while ((food_coord[i].coord.x == width * 7 / 9 && food_coord[i].coord.y >= height * 3 / 5) || (food_coord[i].coord.x == width * 8 / 9 && food_coord[i].coord.y >= height * 3 / 5))
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkMainFood;
		}

		food_coord[i].score = food[level_food].score;
		food_coord[i].level = level_food;
		gotoXY(food_coord[i].coord.x, food_coord[i].coord.y);
		TextColor(food[level_food].color);
		printf("%d", food[level_food].shape);
		TextColor(default_ColorCode);
	}

	// print toxic food//
	for (i = level_game * NUMBER_FOOD_EACH_LV * 1 / 3; i < level_game * NUMBER_FOOD_EACH_LV * 2 / 3; i++)
	{
		int level_food = level_game + 1 + rand() % (LEVEL_GAME_MAX - level_game + 1);
		if (level_food == 10)
		{
			level_food = 0;
		}
		food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
		food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
		// check toxic food
	checkToxicFood:
		check = true;
		for (j = 0; j < i; j++)
		{
			while (food_coord[j].coord.x == food_coord[i].coord.x && food_coord[j].coord.y == food_coord[i].coord.y)
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkToxicFood;
		}
		// check snake
		for (j = 0; j < snake->length; j++)
		{
			while (snake->bend[j].x == food_coord[i].coord.x && snake->bend[j].y == food_coord[i].coord.y)
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkToxicFood;
		}
		// check challenge
		for (j = 0; j < challenge->length; j++)
		{
			while (challenge->bend[j].x == food_coord[i].coord.x && challenge->bend[j].y == food_coord[i].coord.y)
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkToxicFood;
		}
		// check obstacle
		if (level_game >= LEVEL_UPDATE_MAP)
		{
			// prevent food == obsacle top
			while ((food_coord[i].coord.x == width * 2 / 9 && food_coord[i].coord.y <= height * 2 / 5) || (food_coord[i].coord.x == width * 3 / 9 && food_coord[i].coord.y <= height * 2 / 5))
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkToxicFood;
			// prevent food == obsacle bottom
			while ((food_coord[i].coord.x == width * 7 / 9 && food_coord[i].coord.y >= height * 3 / 5) || (food_coord[i].coord.x == width * 8 / 9 && food_coord[i].coord.y >= height * 3 / 5))
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkToxicFood;
		}

		food_coord[i].score = food[level_food].score;
		food_coord[i].level = level_food;
		gotoXY(food_coord[i].coord.x, food_coord[i].coord.y);
		TextColor(food[level_food].color);
		printf("%d", food[level_food].shape);
		TextColor(default_ColorCode);
	}

	// print food in range (0 , 9)//
	for (i = level_game * NUMBER_FOOD_EACH_LV * 2 / 3; i < level_game * NUMBER_FOOD_EACH_LV; i++)
	{
		int level_food = 1 + rand() % (LEVEL_GAME_MAX + 1);
		if (level_food == 10)
		{
			level_food = 0;
		}
		food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
		food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
		// check food in range (0,9)
	checkAnyFood:
		check = true;
		for (j = 0; j < i; j++)
		{
			while (food_coord[j].coord.x == food_coord[i].coord.x && food_coord[j].coord.y == food_coord[i].coord.y)
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkAnyFood;
		}
		// check snake
		for (j = 0; j < snake->length; j++)
		{
			while (snake->bend[j].x == food_coord[i].coord.x && snake->bend[j].y == food_coord[i].coord.y)
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkAnyFood;
		}
		// check challenge
		for (j = 0; j < challenge->length; j++)
		{
			while (challenge->bend[j].x == food_coord[i].coord.x && challenge->bend[j].y == food_coord[i].coord.y)
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkAnyFood;
		}
		// check obstacle
		if (level_game >= LEVEL_UPDATE_MAP)
		{
			// prevent food == obsacle top
			while ((food_coord[i].coord.x == width * 2 / 9 && food_coord[i].coord.y <= height * 2 / 5) || (food_coord[i].coord.x == width * 3 / 9 && food_coord[i].coord.y <= height * 2 / 5))
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkAnyFood;
			// prevent food == obsacle bottom
			while ((food_coord[i].coord.x == width * 7 / 9 && food_coord[i].coord.y >= height * 3 / 5) || (food_coord[i].coord.x == width * 8 / 9 && food_coord[i].coord.y >= height * 3 / 5))
			{
				food_coord[i].coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
				food_coord[i].coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
				check = false;
			}
			if (check == false)
				goto checkAnyFood;
		}

		food_coord[i].score = food[level_food].score;
		food_coord[i].level = level_food;
		gotoXY(food_coord[i].coord.x, food_coord[i].coord.y);
		TextColor(food[level_food].color);
		printf("%d", food[level_food].shape);
		TextColor(default_ColorCode);
	}
}

//=======================================Score=================================================
void display_score(int *score, int *level_game, int *hp, struct Food_coord *food_coord, struct Snake snake, struct Snake challenge)
{
	if (*score == LEVEL_UP_2 && *score < LEVEL_UP_3)
	{
		*level_game = 2;
	}
	else if (*score >= LEVEL_UP_3 && *score < LEVEL_UP_4)
	{
		*level_game = 3;
	}
	else if (*score >= LEVEL_UP_4 && *score < LEVEL_UP_5)
	{
		*level_game = 4;
	}
	else if (*score >= LEVEL_UP_5 && *score < LEVEL_UP_6)
	{
		*level_game = 5;
	}
	else if (*score >= LEVEL_UP_6 && *score < LEVEL_UP_7)
	{
		*level_game = 6;
	}
	else if (*score >= LEVEL_UP_7 && *score < LEVEL_UP_8)
	{
		*level_game = 7;
	}
	else if (*score >= LEVEL_UP_8 && *score < LEVEL_UP_9)
	{
		*level_game = 8;
	}
	else if (*score >= LEVEL_UP_9)
	{
		*level_game = 9;
	}
	for (i = 0; i < *level_game * NUMBER_FOOD_EACH_LV; i++)
	{
		if (snake.bend[0].x == food_coord[i].coord.x && snake.bend[0].y == food_coord[i].coord.y)
		{
			if (food_coord[i].level == 0)
			{
				PlaySound(TEXT("EndGame.wav"), NULL, SND_ASYNC);
				*hp = 0;
			}
			else if (food_coord[i].level <= *level_game)
			{
				PlaySound(TEXT("ClassicFood_SpecialFood.wav"), NULL, SND_ASYNC);
				*score += food_coord[i].score;
			}
			else if (food_coord[i].level > *level_game)
			{
				PlaySound(TEXT("HigherLevelFood.wav"), NULL, SND_ASYNC);
				*hp -= 1;
			}
		}
	}
	for (int i = 0; i < challenge.length; i++)
	{
		for (int j = 0; j < snake.length; j++)
		{
			if (snake.bend[j].x == challenge.bend[i].x && snake.bend[j].y == challenge.bend[i].y)
			{
				PlaySound(TEXT("EndGame.wav"), NULL, SND_ASYNC);
				*hp = 0;
			}
		}
	}
	TextColor(*level_game);
	gotoXY(CONSOLE_RIGHT + 12, CONSOLE_TOP + 2);
	printf("LIFE:");
	for (i = 0; i < 7; i++)
	{
		if (i < *hp)
			printf(" %c", 153);
		else
			printf("  ");
	}
	gotoXY(CONSOLE_RIGHT + 5, CONSOLE_TOP + 4);
	printf("Score: %d", *score);
	gotoXY(CONSOLE_RIGHT + 25, CONSOLE_TOP + 4);
	printf("Level: %d", *level_game);
}
void logo_score(int score, int level_game)
{
	int x = CONSOLE_RIGHT + 5, y = CONSOLE_TOP + 6;

	gotoXY(x, y);
	char letter_S[5][5] = {{' ', 'F', 'F', 'F', 'F'},
												 {'F', ' ', ' ', ' ', ' '},
												 {' ', 'F', 'F', 'F', ' '},
												 {' ', ' ', ' ', ' ', 'F'},
												 {'F', 'F', 'F', 'F', ' '}};

	char letter_N[5][5] = {{'C', ' ', ' ', ' ', 'C'},
												 {'C', 'C', ' ', ' ', 'C'},
												 {'C', ' ', 'C', ' ', 'C'},
												 {'C', ' ', ' ', 'C', 'C'},
												 {'C', ' ', ' ', ' ', 'C'}};

	char letter_A[5][5] = {{' ', ' ', 'O', ' ', ' '},
												 {' ', 'O', ' ', 'O', ' '},
												 {'O', 'O', 'O', 'O', 'O'},
												 {'O', ' ', ' ', ' ', 'O'},
												 {'O', ' ', ' ', ' ', 'O'}};

	char letter_K[5][5] = {{'D', ' ', ' ', ' ', 'D'},
												 {'D', ' ', ' ', 'D', ' '},
												 {'D', ' ', 'D', ' ', ' '},
												 {'D', 'D', ' ', 'D', ' '},
												 {'D', ' ', ' ', ' ', 'D'}};

	char letter_E[5][5] = {{'E', 'E', 'E', 'E', 'E'},
												 {'E', ' ', ' ', ' ', ' '},
												 {'E', 'E', 'E', 'E', 'E'},
												 {'E', ' ', ' ', ' ', ' '},
												 {'E', 'E', 'E', 'E', 'E'}};

	int list_level_up[10] = {0, LEVEL_UP_1, LEVEL_UP_2, LEVEL_UP_3, LEVEL_UP_4, LEVEL_UP_5, LEVEL_UP_6, LEVEL_UP_7, LEVEL_UP_8, LEVEL_UP_9};
	int ratio;
	int pass_score = 0;
	for (i = 1; i < 10; i++)
	{
		if (score >= list_level_up[i] && score <= list_level_up[i + 1])
		{
			level_game = i;
			pass_score += list_level_up[i];
			ratio = (list_level_up[i + 1] - pass_score) / 25;
		}
	}
	for (row = 0; row < 5; row++)
	{
		//S = 0 - 5 cell//
		for (col_s = 0; col_s < 5; col_s++)
		{
			if ((score - pass_score) / ratio >= 0 + col_s + 1)
			{
				TextColor(level_game);
			}
			printf("%c", letter_S[row][col_s]);
			TextColor(default_ColorCode);
		}
		printf(" ");
		//N = 5 - 10 cell//
		for (col_n = 0; col_n < 5; col_n++)
		{
			if ((score - pass_score) / ratio >= 5 + col_n + 1)
			{
				TextColor(level_game);
			}
			printf("%c", letter_N[row][col_n]);
			TextColor(default_ColorCode);
		}
		printf(" ");
		//A = 10 - 15 cell//
		for (col_a = 0; col_a < 5; col_a++)
		{
			if ((score - pass_score) / ratio >= 10 + col_a + 1)
			{
				TextColor(level_game);
			}
			printf("%c", letter_A[row][col_a]);
			TextColor(default_ColorCode);
		}
		printf(" ");
		//k = 15 - 20//
		for (col_k = 0; col_k < 5; col_k++)
		{
			if ((score - pass_score) / ratio >= 15 + col_k + 1)
			{
				TextColor(level_game);
			}
			printf("%c", letter_K[row][col_k]);
			TextColor(default_ColorCode);
		}
		printf(" ");
		//e = 20 - 25//
		for (col_e = 0; col_e < 5; col_e++)
		{
			if ((score - pass_score) / ratio >= 20 + col_e + 1)
			{
				TextColor(level_game);
			}
			printf("%c", letter_E[row][col_e]);
			TextColor(default_ColorCode);
		}
		gotoXY(x, y += 1);
	}
}

//=========================================BUILD WALL=========================================
void build_wall()
{
	TextColor(default_ColorCode);
	gotoXY(CONSOLE_LEFT, CONSOLE_TOP);
	for (i = CONSOLE_TOP; i <= CONSOLE_BOTTOM; i++)
	{
		for (j = CONSOLE_LEFT; j < CONSOLE_RIGHT; j++)
		{
			if (i == CONSOLE_TOP || i == CONSOLE_BOTTOM)
			{
				if (j == CONSOLE_LEFT && i == CONSOLE_TOP)
				{
					printf("%c", 201);
				}
				else if (j == CONSOLE_LEFT && i == CONSOLE_BOTTOM)
				{
					printf("%c", 200);
				}
				else if (j == CONSOLE_RIGHT - 1 && i == CONSOLE_TOP)
				{
					printf("%c", 187);
				}
				else if (j == CONSOLE_RIGHT - 1 && i == CONSOLE_BOTTOM)
				{
					printf("%c", 188);
				}
				else
					printf("%c", 205);
			}
			else
				break;
		}
		if (i > CONSOLE_TOP && i < CONSOLE_BOTTOM)
		{
			gotoXY(CONSOLE_LEFT, i);
			printf("%c", 186);
			gotoXY(CONSOLE_RIGHT - 1, i);
			printf("%c", 186);
		}
		printf("\n");
		gotoXY(CONSOLE_LEFT, i);
	}
}
void build_table_game()
{
	for (i = CONSOLE_RIGHT - 1; i < CONSOLE_RIGHT + 40; i++)
	{
		if (i == CONSOLE_RIGHT - 1)
		{
			gotoXY(i, CONSOLE_TOP);
			putchar(203);
			gotoXY(i, CONSOLE_BOTTOM - 1);
			putchar(202);
		}
		else if (i == CONSOLE_RIGHT + 39)
		{
			gotoXY(i, CONSOLE_TOP);
			putchar(187);
			gotoXY(i, CONSOLE_BOTTOM - 1);
			putchar(188);
		}
		else
		{
			gotoXY(i, CONSOLE_TOP);
			putchar(205);
			gotoXY(i, CONSOLE_BOTTOM - 1);
			putchar(205);
		}
	}
	for (i = CONSOLE_TOP + 1; i < CONSOLE_BOTTOM - 1; i++)
	{
		gotoXY(CONSOLE_RIGHT + 39, i);
		putchar(186);
	}
}
void draw_obstacle(struct Coordinate *obstacle, struct Snake *snake, int *hp)
{
	amount_abstacle = 0;
	int width = (CONSOLE_RIGHT - CONSOLE_LEFT);
	int height = (CONSOLE_BOTTOM - CONSOLE_TOP);
	obstacle[0].x = 1;
	obstacle[0].y = 1;
	// divide width console game to 9 part; height to 5 part
	for (i = CONSOLE_TOP; i <= height * 2 / 5; i++)
	{
		gotoXY(width * 2 / 9, i);
		if (i == CONSOLE_TOP)
		{
			printf("%c", 203);
		}
		else
		{
			printf("%c", 186);
		}
		obstacle[amount_abstacle].x = width * 2 / 9;
		obstacle[amount_abstacle].y = i;
		amount_abstacle++;
		gotoXY(width * 3 / 9, i);
		if (i == CONSOLE_TOP)
		{
			printf("%c", 203);
		}
		else
		{
			printf("%c", 186);
			obstacle[amount_abstacle].x = width * 3 / 9;
			obstacle[amount_abstacle].y = i;
			amount_abstacle++;
		}
	}
	for (i = CONSOLE_BOTTOM; i >= height * 3 / 5; i--)
	{
		gotoXY(width * 7 / 9, i - 1);
		if (i == CONSOLE_BOTTOM)
		{
			printf("%c", 202);
		}
		else
		{
			printf("%c", 186);
			obstacle[amount_abstacle].x = width * 7 / 9;
			obstacle[amount_abstacle].y = i - 1;
			amount_abstacle++;
		}
		gotoXY(width * 8 / 9, i - 1);
		if (i == CONSOLE_BOTTOM)
		{
			printf("%c", 202);
		}
		else
		{
			printf("%c", 186);
			obstacle[amount_abstacle].x = width * 8 / 9;
			obstacle[amount_abstacle].y = i - 1;
			amount_abstacle++;
		}
	}
}
void check_obstacle(struct Coordinate *obstacle, struct Snake *snake, int *hp)
{
	for (i = 0; i < amount_abstacle; i++)
	{
		if (snake->bend[0].x == obstacle[i].x && snake->bend[0].y == obstacle[i].y)
		{
			PlaySound(TEXT("EndGame.wav"), NULL, SND_ASYNC);
			*hp = 0;
		}
	}
}
void through_obstacle(struct Snake *snake, int level_game)
{
	int width = (CONSOLE_RIGHT - CONSOLE_LEFT);
	int height = (CONSOLE_BOTTOM - CONSOLE_TOP);
	if (level_game >= LEVEL_UPDATE_MAP)
	{
		for (i = 1; i < width * 1 / 9; i++)
		{
			if (snake->bend[0].x == width * 2 / 9 + i && snake->bend[1].y == CONSOLE_TOP + 1 && snake->direc == UP)
			{
				snake->bend[0].x = width * 7 / 9 + i;
				snake->bend[0].y = CONSOLE_BOTTOM - 2;
				break;
			}
			else if (snake->bend[0].x == width * 7 / 9 + i && snake->bend[1].y == CONSOLE_BOTTOM - 2 && snake->direc == DOWN)
			{
				snake->bend[0].x = width * 2 / 9 + i;
				snake->bend[0].y = CONSOLE_TOP + 1;
				break;
			}
		}
	}
}
//========================================Build challenges===============================//
void declere_challenge(struct Snake *challenge)
{
	challenge->bend[0].x = (CONSOLE_RIGHT - CONSOLE_LEFT) / 2;
	challenge->bend[0].y = CONSOLE_TOP + 3;
	challenge->bend[1].x = (CONSOLE_RIGHT - CONSOLE_LEFT) / 2;
	challenge->bend[1].y = CONSOLE_TOP + 2;
	challenge->bend[2].x = (CONSOLE_RIGHT - CONSOLE_LEFT) / 2;
	challenge->bend[2].y = CONSOLE_TOP + 1;
	challenge->length = 3;
	challenge->direc = DOWN;
	challenge->color = ColorCode_Red;
	challenge->speed_hor = 0;
	challenge->speed_ver = 0;
}
void challenge_1(struct Snake *challenge)
{
	draw_snake(*challenge);
	for (int i = challenge->length; i > 0; i--)
	{
		challenge->bend[i] = challenge->bend[i - 1];
	}
	if (challenge->direc == RIGHT)
	{
		challenge->direc = UP;
	}
	else if (challenge->direc == LEFT)
	{
		challenge->direc = DOWN;
	}

	if (challenge->bend[0].y == CONSOLE_BOTTOM - 2 && challenge->direc == DOWN)
	{
		challenge->direc = RIGHT;
	}
	else if (challenge->bend[0].y == CONSOLE_TOP + 1 && challenge->direc == UP)
	{
		challenge->direc = LEFT;
	}

	if (challenge->direc == UP)
	{
		challenge->bend[0].y--;
	}
	else if (challenge->direc == DOWN)
	{
		challenge->bend[0].y++;
	}
	else if (challenge->direc == RIGHT)
	{
		challenge->bend[0].x++;
	}
	else if (challenge->direc == LEFT)
	{
		challenge->bend[0].x--;
	}
}
void challenge_2(struct Snake *challenge)
{
	draw_snake(*challenge);
	for (int i = challenge->length; i > 0; i--)
	{
		challenge->bend[i] = challenge->bend[i - 1];
	}
	// random direction
	int direc_of_challenge = 1 + rand() % 16;
	if (direc_of_challenge == 4 && challenge->direc != DOWN)
	{
		challenge->direc = UP;
	}
	else if (direc_of_challenge == 8 && challenge->direc != UP)
	{
		challenge->direc = DOWN;
	}
	else if (direc_of_challenge == 12 && challenge->direc != RIGHT)
	{
		challenge->direc = LEFT;
	}
	else if (direc_of_challenge == 16 && challenge->direc != LEFT)
	{
		challenge->direc = RIGHT;
	}
	// limit challenge
	// bot
	if (challenge->bend[1].y == CONSOLE_BOTTOM - 2 && challenge->direc == DOWN)
	{
		if (challenge->bend[0].x != CONSOLE_RIGHT - 2 || challenge->bend[0].x + 1 != CONSOLE_RIGHT - 2)
		{
			challenge->direc = RIGHT;
		}
		else
			challenge->direc = LEFT;
	}
	//right
	if (challenge->bend[1].x == CONSOLE_RIGHT - 2 && challenge->direc == RIGHT)
	{
		if (challenge->bend[0].y - 1 != CONSOLE_TOP + 1)
		{
			challenge->direc = UP;
		}
		else
			challenge->direc = DOWN;
	}
	//top
	if (challenge->bend[1].y == CONSOLE_TOP + 1 && challenge->direc == UP)
	{
		if (challenge->bend[0].x - 1 != CONSOLE_LEFT)
		{
			challenge->direc = LEFT;
		}
		else
			challenge->direc = RIGHT;
	}

	//left
	if (challenge->bend[1].x == CONSOLE_LEFT + 1 && challenge->direc == LEFT)
	{
		if (challenge->bend[0].y - 1 != CONSOLE_BOTTOM - 2)
		{
			challenge->direc = DOWN;
		}
		else
			challenge->direc = UP;
	}

	if (challenge->direc == UP)
	{
		challenge->bend[0].y--;
	}
	else if (challenge->direc == DOWN)
	{
		challenge->bend[0].y++;
	}
	else if (challenge->direc == LEFT)
	{
		challenge->bend[0].x--;
	}
	else if (challenge->direc == RIGHT)
	{
		challenge->bend[0].x++;
	}
}
void delete_challenge(struct Snake *challenge)
{
	challenge->bend[0].x = 0;
	challenge->bend[0].y = 0;
	challenge->bend[1].x = 0;
	challenge->bend[1].y = 0;
	challenge->bend[2].x = 0;
	challenge->bend[2].y = 0;
	challenge->length = 3;
	challenge->direc = DOWN;
	challenge->color = ColorCode_Red;
	challenge->speed_hor = 0;
	challenge->speed_ver = 0;
}
//=========================================END GAME=========================================
void end_game(struct Snake snake, int *hp)
{
	for (i = 3; i < snake.length; i++)
	{
		if (snake.bend[i].x == snake.bend[0].x && snake.bend[i].y == snake.bend[0].y)
		{
			PlaySound(TEXT("EndGame.wav"), NULL, SND_ASYNC);
			*hp = 0;
		}
	}
	if (snake.bend[1].x == CONSOLE_LEFT || snake.bend[1].x == CONSOLE_RIGHT - 1 || snake.bend[1].y == CONSOLE_TOP || snake.bend[1].y == CONSOLE_BOTTOM - 1)
	{
		PlaySound(TEXT("EndGame.wav"), NULL, SND_ASYNC);
		*hp = 0;
	}
}

//==========================================Classic game=====================================
void draw_snake_classic(struct Snake snake)
{
	TextColor(default_ColorCode);
	gotoXY(snake.bend[0].x, snake.bend[0].y);
	printf("%c", 153);
	for (i = 1; i <= snake.length; i++)
	{
		if (i < snake.length)
		{
			gotoXY(snake.bend[i].x, snake.bend[i].y);
			putchar(219);
		}
		else
		{
			gotoXY(snake.bend[i].x, snake.bend[i].y);
			puts(" ");
		}
	}
	if (snake.direc == UP || snake.direc == DOWN)
	{
		Sleep(snake.speed_ver);
	}
	else
	{
		Sleep(snake.speed_hor);
	}
}
void updateFood(struct Snake snake, struct Food_coord *food, struct Food_coord *bigFood)
{
callFood:
	food->coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
	food->coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
	for (i = 0; i < snake.length; i++)
	{
		if (food->coord.x == snake.bend[i].x && food->coord.y == snake.bend[i].y)
			goto callFood;
	}
	if (food->coord.x == bigFood->coord.x && food->coord.y == bigFood->coord.y)
		goto callFood;
	food->score = 1;
	if (count == 5)
	{
	callBigFood:
		bigFood->coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
		bigFood->coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
		for (i = 0; i < snake.length; i++)
		{
			if (bigFood->coord.x == snake.bend[i].x && bigFood->coord.y == snake.bend[i].y)
				goto callBigFood;
		}
		if (bigFood->coord.x == food->coord.x && bigFood->coord.y == food->coord.y)
			goto callBigFood;
		bigFood->score = 5;
		count = 0;
		temp = true;
		for (i = 0; i < 87; i++)
		{
			TextColor(ColorCode_Red);
			gotoXY(3 + i, CONSOLE_BOTTOM);
			putchar(254);
		}
	}
}
void update_snake_classic(struct Snake *snake, struct Food_coord *food, struct Food_coord *bigFood)
{
	if (snake->bend[0].x == food->coord.x && snake->bend[0].y == food->coord.y)
	{
		PlaySound(TEXT("ClassicFood_SpecialFood.wav"), NULL, SND_ASYNC);
		for (i = snake->length + 1; i > 0; i--)
		{
			snake->bend[i] = snake->bend[i - 1];
		}
		snake->length++;

		if (snake->direc == UP)
		{
			snake->bend[0].y--;
		}
		else if (snake->direc == DOWN)
		{
			snake->bend[0].y++;
		}
		else if (snake->direc == LEFT)
		{
			snake->bend[0].x--;
		}
		else if (snake->direc == RIGHT)
		{
			snake->bend[0].x++;
		}
		count++;
		updateFood(*snake, food, bigFood);
	}
	if (snake->bend[0].x == bigFood->coord.x && snake->bend[0].y == bigFood->coord.y)
	{
		PlaySound(TEXT("ClassicBigFood.wav"), NULL, SND_ASYNC);
		for (i = snake->length + 1; i > 0; i--)
		{
			snake->bend[i] = snake->bend[i - 1];
		}
		snake->length++;

		if (snake->direc == UP)
		{
			snake->bend[0].y--;
		}
		else if (snake->direc == DOWN)
		{
			snake->bend[0].y++;
		}
		else if (snake->direc == LEFT)
		{
			snake->bend[0].x--;
		}
		else if (snake->direc == RIGHT)
		{
			snake->bend[0].x++;
		}
		temp = false;
		deleteBigFood(bigFood);
	}
}
void declere_food_classic(struct Food_coord *food, struct Snake snake)
{
declereFood:
	food->coord.x = CONSOLE_LEFT + 2 + rand() % (CONSOLE_RIGHT - CONSOLE_LEFT - 4);
	food->coord.y = CONSOLE_TOP + 2 + rand() % (CONSOLE_BOTTOM - CONSOLE_TOP - 3);
	for (i = 0; i < snake.length; i++)
	{
		if (food->coord.x == snake.bend[i].x && food->coord.y == snake.bend[i].y)
			goto declereFood;
	}
	food->score = 1;
}
void drawFood(struct Food_coord food)
{
	TextColor(ColorCode_Yellow);
	gotoXY(food.coord.x, food.coord.y);
	putchar(233);
}
void drawBigFood(struct Food_coord bigFood)
{
	i = rand() % 15 + 1;
	TextColor(i);
	gotoXY(bigFood.coord.x, bigFood.coord.y);
	putchar(36);
}
void deleteBigFood(struct Food_coord *bigFood)
{
	gotoXY(bigFood->coord.x, bigFood->coord.y);
	printf(" ");
	for (i = 3; i < 90 - times; i++)
	{
		gotoXY(i, CONSOLE_BOTTOM);
		printf(" ");
	}
	bigFood->coord.x = 0;
	bigFood->coord.y = 0;
	times = 0;
}
void snakeScore(struct Snake *snake, struct Food_coord food, struct Food_coord bigFood)
{
	if (snake->bend[0].x == food.coord.x && snake->bend[0].y == food.coord.y)
	{
		snake->score += food.score;
	}
	else if (snake->bend[0].x == bigFood.coord.x && snake->bend[0].y == bigFood.coord.y)
	{
		snake->score += bigFood.score;
	}
	TextColor(144);
	gotoXY(CONSOLE_RIGHT + 6, CONSOLE_TOP + 3);
	printf("Your score:");
	TextColor(default_ColorCode);
	printf(" ");
	TextColor(ColorCode_Cyan);
	printf("%d", snake->score);
}
void throughWall(struct Snake *snake)
{
	TextColor(default_ColorCode);
	if (snake->bend[0].x < CONSOLE_LEFT + 1)
	{
		snake->bend[0].x = CONSOLE_RIGHT - 2;
		gotoXY(CONSOLE_LEFT, snake->bend[0].y);
		putchar(186);
	}
	else if (snake->bend[0].x > CONSOLE_RIGHT - 2)
	{
		snake->bend[0].x = CONSOLE_LEFT + 1;
		gotoXY(CONSOLE_RIGHT - 1, snake->bend[0].y);
		putchar(186);
	}
	else if (snake->bend[0].y < CONSOLE_TOP + 1)
	{
		snake->bend[0].y = CONSOLE_BOTTOM - 2;
		gotoXY(snake->bend[0].x, CONSOLE_TOP);
		putchar(205);
	}
	else if (snake->bend[0].y > CONSOLE_BOTTOM - 2)
	{
		snake->bend[0].y = CONSOLE_TOP + 1;
		gotoXY(snake->bend[0].x, CONSOLE_BOTTOM - 1);
		putchar(205);
	}
}
void inGameClassicInstruction(int key)
{
	TextColor(64);
	gotoXY(CONSOLE_RIGHT + 6, CONSOLE_TOP + 1);
	printf("Best score:");
	TextColor(ColorCode_DarkRed);
	printf(" %d", highScore[key].score);
	TextColor(160);
	gotoXY(CONSOLE_RIGHT + 6, CONSOLE_TOP + 5);
	printf("CONTROL:");
	gotoXY(CONSOLE_RIGHT + 6, CONSOLE_TOP + 7);
	TextColor(ColorCode_Yellow);
	printf("UP:    upward arrow    / w");
	TextColor(ColorCode_Pink);
	gotoXY(CONSOLE_RIGHT + 6, CONSOLE_TOP + 9);
	printf("DOWN:  downward arrow  / s");
	TextColor(ColorCode_Red);
	gotoXY(CONSOLE_RIGHT + 6, CONSOLE_TOP + 11);
	printf("LEFT:  leftward arrow  / a");
	TextColor(ColorCode_Cyan);
	gotoXY(CONSOLE_RIGHT + 6, CONSOLE_TOP + 13);
	printf("RIGHT: rightward arrow / d");
	TextColor(ColorCode_Blue);
	gotoXY(CONSOLE_RIGHT + 6, CONSOLE_TOP + 16);
	printf("0: 1 point        %c: 5 points", 36);
	TextColor(ColorCode_White);
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 20);
	printf("(     Press Space to pause     )");
}
void inGameSpecialInstruction(int key)
{
	TextColor(64);
	gotoXY(CONSOLE_RIGHT + 13, CONSOLE_TOP + 3);
	printf("Best score:");
	TextColor(ColorCode_DarkRed);
	printf(" %d", highScore[key].score);
	TextColor(ColorCode_White);
	gotoXY(CONSOLE_RIGHT + 5, CONSOLE_TOP + 12);
	printf("*TRICK:");
	gotoXY(CONSOLE_RIGHT + 6, CONSOLE_TOP + 13);
	printf("Snake will die");
	gotoXY(CONSOLE_RIGHT + 6, CONSOLE_TOP + 14);
	printf("if you touch red snake!");
	gotoXY(CONSOLE_RIGHT + 6, CONSOLE_TOP + 15);
	printf("Snake can teleport between");
	gotoXY(CONSOLE_RIGHT + 6, CONSOLE_TOP + 16);
	printf("the bottom of 2 tubes!");
	gotoXY(CONSOLE_RIGHT + 1, CONSOLE_TOP + 18);
	printf("BE A REAL SNAKE AND ADVOID ALL DANGER!");
	gotoXY(CONSOLE_RIGHT + 4, CONSOLE_TOP + 20);
	printf("(     Press Space to pause     )");
}