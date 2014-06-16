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

int scanfile (const char name[]) // ������ ���� ���� �˻�
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

char* scanstr (int strlong, char *str) // ���ڿ��� �����÷ο���� �ʴ� scanf ��� �Լ�
{ // ������ �ԷµǴ� ���ڿ� ���̴� strlong - 2. \n�� NULL ���� �����̴�.
	size_t lentmp;
	fgets(str, strlong, stdin);
	lentmp = strlen(str);
	str[lentmp - 1] = '\0';
	return str;
}

char* fscanstr(int strlong, FILE* fp, char *str) // ���Ͽ��� ���� �о���� �Լ�
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

void gotoxy (int x, int y) //Ŀ�� �̵��ϴ� �Լ�.
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

int getx() // Ŀ���� x,y ��ǥ ������
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

int gety() // Ŀ���� y ��ǥ ������
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

int WhatBitOS (int print) // ���Ʈ �������ΰ� �˾Ƴ���
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

void TextColor(unsigned char fcolor) // fcolor�� RGB8�� ���
{
	WORD attr, bcolor;
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	attr = 0;
	bcolor = 0;


	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	bcolor = BufInfo.wAttributes;

// ������ ������ �������� ����
	if (bcolor & BACKGROUND_RED) // ������ RED �����
		attr = attr | BACKGROUND_RED;
	if (bcolor & BACKGROUND_GREEN) // ������ GREEN �����
		attr = attr | BACKGROUND_GREEN;
	if (bcolor & BACKGROUND_BLUE) // ������ BLUE �����
		attr = attr | BACKGROUND_BLUE;
	if (bcolor & BACKGROUND_INTENSITY) // ������ INTENSITY �����
		attr = attr | BACKGROUND_INTENSITY;

// ����� ����
	if (fcolor & FOREGROUND_RED)
		attr = attr | FOREGROUND_RED;
	if (fcolor & FOREGROUND_GREEN)
		attr = attr | FOREGROUND_GREEN;
	if (fcolor & FOREGROUND_BLUE)
		attr = attr | FOREGROUND_BLUE;
	if (fcolor & FOREGROUND_INTENSITY)
		attr = attr | FOREGROUND_INTENSITY;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr); // ����������, ���� ����!
}

void BGColor(unsigned char bcolor) // bcolor�� RGB8�� ���
{
	WORD attr, fcolor;
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	attr = 0;
	fcolor = 0;

	bcolor = bcolor << 4; // FOREGROUND �������� �� RGB8�� 4��Ʈ �������� �о BACKGROUND�� �����.
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	fcolor = BufInfo.wAttributes;

// ���� ����
	if (bcolor & BACKGROUND_RED) // ������ RED �����
		attr = attr | BACKGROUND_RED;
	if (bcolor & BACKGROUND_GREEN) // ������ RED �����
		attr = attr | BACKGROUND_GREEN;
	if (bcolor & BACKGROUND_BLUE) // ������ RED �����
		attr = attr | BACKGROUND_BLUE;
	if (bcolor & BACKGROUND_INTENSITY) // ������ RED �����
		attr = attr | BACKGROUND_INTENSITY;

// ������� ������ �������� ����
	if (fcolor & FOREGROUND_RED)
		attr = attr | FOREGROUND_RED;
	if (fcolor & FOREGROUND_GREEN)
		attr = attr | FOREGROUND_GREEN;
	if (fcolor & FOREGROUND_BLUE)
		attr = attr | FOREGROUND_BLUE;
	if (fcolor & FOREGROUND_INTENSITY)
		attr = attr | FOREGROUND_INTENSITY;


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr); // ����������, ���� ����!
}

void Delay (clock_t wait)
{

	#ifdef WINDOWS
	Sleep(wait);
	#endif

	#ifdef LINUX
	// wait ms ��ŭ ���
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
