#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define ColorCode_Back 0
#define ColorCode_DarkBlue 1
#define ColorCode_DarkGreen 2
#define ColorCode_DarkCyan 3
#define ColorCode_DarkRed 4
#define ColorCode_DarkPink 5
#define ColorCode_DarkYellow 6
#define ColorCode_DarkWhite 7
#define ColorCode_Grey 8
#define ColorCode_Blue 9
#define ColorCode_Green 10
#define ColorCode_Cyan 11
#define ColorCode_Red 12
#define ColorCode_Pink 13
#define ColorCode_Yellow 14
#define ColorCode_White 15

#define default_ColorCode 7

#define key_Up 1072
#define key_Down 1080
#define key_Left 1075
#define key_Right 1077
#define key_none -1

int inputKey();

//-------------------------Screen-------------------------
void clrscr();

//screen: goto [x,y]
void gotoXY(int column, int line);

//screen: get [x]
int whereX();

//screen: get [y]
int whereY();

void TextColor(int color);
// delete cursor
void noCursorType();
//end----------------------Screen----------------------end
int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224) // special key
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return key_none;
	}

	return key_none;
}

//-------------------------Screen-------------------------
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut;
	COORD Home = {0, 0};
	DWORD dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

//screen: goto [x,y]
void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//screen: get [x]
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

//screen: get [y]
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void noCursorType()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = FALSE;
	info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
