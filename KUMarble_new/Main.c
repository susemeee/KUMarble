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

// 화면 조정
	printf("Adjusting Screen...\n");
	SIO_InitConsoleSize(30); // 창 크기 조정
	SetConsoleTitleA("KUMarble : 고연전"); // 창 이름 조정
	system("color 07"); // 바탕 검정 전경 흰색
	//TextColor(RGB8(1, 1, 1, 0));
	BGColor(RGB8(0, 0, 0, 0));

// 시드 설정
	srand((unsigned int)time(NULL));

//  커서위치 조정
	cursorinit(); // 커서가 버퍼를 넘어가면 gotoxy가 정상작동하지 않는다.

#ifndef DEBUG
	ML_PrintStory();
#else
	TextColor(RGB8(1,0,0,1));
	printf("\nDebug mode activated. please turn of this before production.\n\n");
	TextColor(RGB8(1,1,1,1));
#endif

	loopin = 1;
	while (loopin) // 모드를 제대로 고를 때까지 뺑뺑이
	{
	// 프로그램 정보 출력
		printf("KUMarble %.1lf                                          Build Date : %s\n"
				"Made by 장하진, 이수호, 윤민아, 김성원, Yin Jin\n\n", KMVER, __DATE__);

		printf(	"\n게임 모드를 고르세요      (Press 1 or 2)\n"
				"1. 밸런스 모드 (추천)   -   대학의 통장이 두둑할수록 승리!\n"
				"2. 현실 모드 (어려움)   -   빚을 최대한 덜 가져야 승리!\n\n"
				"당신의 선택은? ");
		key = getch();
		if (key == '1')
		{
			loopin = 0;
			printf("\n\n적정 난이도. 시작합니다...\n");
			pause();
			difficulty = GAME_EASY;
			KUMarble();	// 게임 KUMarble (쉬움) 호출
		}
		else if (key == '2')
		{
			loopin = 0;
			SetConsoleTitleA("KUMarble : 통장의 고연전"); // 창 이름 조정
			printf("\n\n어려운 난이도.\n당신에게는 마이너스 통장이 있습니다.\n급증하는 수업료를 견뎌내세요!\n시작합니다...\n");
			pause();
			difficulty = GAME_HARD;
			KUMarble();	// 게임 KUMarble (어려움) 호출
		}
		else
		{
			printf("\n\n잘못된 입력입니다!\n\n");
			Delay(1000);
			system("CLS");
		}
	}

	return 0;
}

