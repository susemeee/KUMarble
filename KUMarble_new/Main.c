#include "Var.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "BasicIO.h"
#include "SurfaceIO.h"
#include "Marble.h"
#include "Mouse.h"

CITY board[CITY_NUMBER];
int difficulty;
clock_t timepass;

int main (int argc, char* argv[])
{
	int key = 0, loopin = 0;

// ȭ�� ����
	printf("Adjusting Screen...\n");
	SIO_InitConsoleSize(30); // â ũ�� ����
	SetConsoleTitleA("KUMarble : ����"); // â �̸� ����
	system("color 07"); // ���� ���� ���� ���
	//TextColor(RGB8(1, 1, 1, 0));
	BGColor(RGB8(0, 0, 0, 0));

// �õ� ����
	srand((unsigned int)time(NULL));

//  Ŀ����ġ ����
	cursorinit(); // Ŀ���� ���۸� �Ѿ�� gotoxy�� �����۵����� �ʴ´�.

#ifndef DEBUG
	ML_PrintStory();
#else
	TextColor(RGB8(1,0,0,1));
	printf("\nDebug mode activated. please turn of this before production.\n\n");
	TextColor(RGB8(1,1,1,1));
#endif

	loopin = 1;
	while (loopin) // ��带 ����� �� ������ ������
	{
	// ���α׷� ���� ���
		printf("KUMarble %.1lf                                          Build Date : %s\n"
				"Made by ������, �̼�ȣ, ���ξ�, �輺��, Yin Jin\n\n", KMVER, __DATE__);

		printf(	"\n���� ��带 ������      (Press 1 or 2)\n"
				"1. �뷱�� ��� (��õ)   -   ������ ������ �ε��Ҽ��� �¸�!\n"
				"2. ���� ��� (�����)   -   ���� �ִ��� �� ������ �¸�!\n\n"
				"����� ������? ");
		key = getch();
		if (key == '1')
		{
			loopin = 0;
			printf("\n\n���� ���̵�. �����մϴ�...\n");
			pause();
			difficulty = GAME_EASY;
			KUMarble();	// ���� KUMarble (����) ȣ��
		}
		else if (key == '2')
		{
			loopin = 0;
			SetConsoleTitleA("KUMarble : ������ ����"); // â �̸� ����
			printf("\n\n����� ���̵�.\n��ſ��Դ� ���̳ʽ� ������ �ֽ��ϴ�.\n�����ϴ� �����Ḧ �ߵ�������!\n�����մϴ�...\n");
			pause();
			difficulty = GAME_HARD;
			KUMarble();	// ���� KUMarble (�����) ȣ��
		}
		else
		{
			printf("\n\n�߸��� �Է��Դϴ�!\n\n");
			Delay(1000);
			system("CLS");
		}
	}

	return 0;
}

