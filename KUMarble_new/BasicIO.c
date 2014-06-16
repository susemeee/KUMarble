#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "BasicIO.h"

#define WINDOWS

#ifdef WINDOWS
#include <windows.h>
#endif
#ifdef LINUX
#include <curses.h>
#endif // LINUX

int scanfile (const char name[]) // 파일의 존재 여부 검사
{
	FILE *fp;
	int tmp = 1;

    fp = fopen(name, "r");
	if (fp == NULL)
		tmp = 0;
	else
		fclose(fp);
	return tmp;
}

char* scanstr (int strlong, char *str) // 문자열이 오버플로우되지 않는 scanf 대용 함수
{ // 실제로 입력되는 문자열 길이는 strlong - 2. \n과 NULL 문자 때문이다.
	size_t lentmp;
	fgets(str, strlong, stdin);
	lentmp = strlen(str);
	str[lentmp - 1] = '\0';
	return str;
}

char* fscanstr(int strlong, FILE* fp, char *str) // 파일에서 내용 읽어오는 함수
{
	size_t lentmp;
	fgets(str, strlong, fp);
	lentmp = strlen(str);
	str[lentmp - 1] = '\0';
	return str;
}

void pause ()
{
	printf("Press any key to continue...\n");
	getch();
}

void cursorinit ()
{
	#ifdef WINDOWS
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	if (BufInfo.dwCursorPosition.Y >= BufInfo.dwSize.Y)
		system("cls");
	#endif

	#ifdef LINUX
//	initscr();
	#endif
}

void gotoxy (int x, int y) //커서 이동하는 함수.
{
	#ifdef WINDOWS
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};
    SetConsoleCursorPosition(hStdout, pos);
	#endif

	#ifdef LINUX
//	printf("\x1B[%d;%df",y,x);
	initscr();
	wmove(stdscr, x, y);
	refresh();
	endwin();
	#endif
}

int getx() // 커서의 x,y 좌표 얻어오기
{
	#ifdef WINDOWS
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	return BufInfo.dwCursorPosition.X;
	#endif

	#ifdef LINUX
	int x = 0, y = 0;
	initscr();
	getyx(stdscr, y, x);
	endwin();
	return x;
	#endif
}

int gety() // 커서의 y 좌표 얻어오기
{
	#ifdef WINDOWS
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	return BufInfo.dwCursorPosition.Y;
	#endif

	#ifdef LINUX
	int x = 0, y = 0;
	initscr();
	getyx(stdscr, y, x);
	endwin();
	return y;
	#endif
}

int WhatBitOS (int print) // 몇비트 컴파일인가 알아내기
{
    if (print)
    {
        if (sizeof(int*) == 4)
        {
            printf("This is 32bit Program!\n");
            return 32;
        }
        else if (sizeof(int*) == 8)
        {
            printf("This is 64bit Program!\n");
            return 64;
        }
        else
        {
			printf("This is %Iubit Program!\n", sizeof(int*) * 8);
            return (sizeof(int*) * 8);
        }
    }
    else
    {
        if (sizeof(int*) == 4)
            return 32;
        else if (sizeof(int*) == 8)
            return 64;
        else
            return (sizeof(int*) * 8);
    }
}

void TextColor(unsigned char fcolor) // fcolor는 RGB8를 사용
{
	WORD attr, bcolor;
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	attr = 0;
	bcolor = 0;


	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	bcolor = BufInfo.wAttributes;

// 배경색을 원래의 배경색으로 설정
	if (bcolor & BACKGROUND_RED) // 배경색에 RED 존재시
		attr = attr | BACKGROUND_RED;
	if (bcolor & BACKGROUND_GREEN) // 배경색에 GREEN 존재시
		attr = attr | BACKGROUND_GREEN;
	if (bcolor & BACKGROUND_BLUE) // 배경색에 BLUE 존재시
		attr = attr | BACKGROUND_BLUE;
	if (bcolor & BACKGROUND_INTENSITY) // 배경색에 INTENSITY 존재시
		attr = attr | BACKGROUND_INTENSITY;

// 전경색 설정
	if (fcolor & FOREGROUND_RED)
		attr = attr | FOREGROUND_RED;
	if (fcolor & FOREGROUND_GREEN)
		attr = attr | FOREGROUND_GREEN;
	if (fcolor & FOREGROUND_BLUE)
		attr = attr | FOREGROUND_BLUE;
	if (fcolor & FOREGROUND_INTENSITY)
		attr = attr | FOREGROUND_INTENSITY;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr); // 마지막으로, 색상 지정!
}

void BGColor(unsigned char bcolor) // bcolor는 RGB8를 사용
{
	WORD attr, fcolor;
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	attr = 0;
	fcolor = 0;

	bcolor = bcolor << 4; // FOREGROUND 기준으로 된 RGB8을 4비트 왼쪽으로 밀어서 BACKGROUND로 맞춘다.
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	fcolor = BufInfo.wAttributes;

// 배경색 설정
	if (bcolor & BACKGROUND_RED) // 배경색에 RED 존재시
		attr = attr | BACKGROUND_RED;
	if (bcolor & BACKGROUND_GREEN) // 배경색에 RED 존재시
		attr = attr | BACKGROUND_GREEN;
	if (bcolor & BACKGROUND_BLUE) // 배경색에 RED 존재시
		attr = attr | BACKGROUND_BLUE;
	if (bcolor & BACKGROUND_INTENSITY) // 배경색에 RED 존재시
		attr = attr | BACKGROUND_INTENSITY;

// 전경색을 원래의 배경색으로 설정
	if (fcolor & FOREGROUND_RED)
		attr = attr | FOREGROUND_RED;
	if (fcolor & FOREGROUND_GREEN)
		attr = attr | FOREGROUND_GREEN;
	if (fcolor & FOREGROUND_BLUE)
		attr = attr | FOREGROUND_BLUE;
	if (fcolor & FOREGROUND_INTENSITY)
		attr = attr | FOREGROUND_INTENSITY;


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr); // 마지막으로, 색상 지정!
}

void Delay (clock_t wait)
{

	#ifdef WINDOWS
	Sleep(wait);
	#endif

	#ifdef LINUX
	// wait ms 만큼 대기
	clock_t goal;
	goal = wait + clock();
	while (goal > clock());
	#endif
}

int RandNum (int first, int last)
{
	return (rand() % (last - first + 1) + first);
}



//void Sleep ()
