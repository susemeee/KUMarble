#include "Var.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

#include "BasicIO.h"
#include "SurfaceIO.h"
#include "Marble.h"
#include "Mouse.h"


void KUMarble ()
{
// 변수 선언
	int turn, key;
	int i, loopin,  around, nowpos;
	PLAYER player[PLAYER_NUMBER];
//	CITY city[CITY_NUMBER];
	UNIV univ[PLAYER_NUMBER];

//변수 초기화
	turn = 0; // 플레이어 turn의 턴
	key = 0;
	i = 0; // 임시변수
	nowpos = 0; // 현재 위치
	around = 0; // 한 바퀴 돌았는가 검사
	loopin = 0; // while 문 안을 계속 돌지의 여부
	for (i = 0; i < PLAYER_NUMBER; i++)
	{
		InitPlayerStruct(&player[i]);
		InitUnivStruct(&univ[i], i);
	}
	for (i = 0; i < CITY_NUMBER; i++)
		InitCityStruct(&board[i], i);

// 게임 루프 시작
	turn = 0;
	loopin = 1;
	timepass = clock();
	while (loopin)
	{
		system("cls");
// 초기화
		SIO_InitBoard();		  // 보드를 그리고
		SIO_DrawBoard();		  // 건물색 칠한다
		SIO_PrtPlayer(player);	  // 말을 그린다.
		SIO_PrtInfo(player, univ);// 돈 현황 표시
		SIO_PrtLogo(univ);		  //대학 현황 표시
		//SIO_PrtMinigameBase();

		// 대학 로고 레벨 검사
		ML_UnivLevelUp(turn, player, univ);
		SIO_TurnColor(turn);

		if(player[turn].goza > 0)
		{
			gotoxy(12,6);	printf("이번 턴은 병원에서 보냅니다.");
			player[turn].goza--;
			if(player[turn].goza == 0)
			{
				gotoxy(12,7);	printf("다음 턴부터 활동 가능합니다.");
			}
			else
			{
				gotoxy(12,7);	printf("%d턴 더 쉬어야 합니다.", player[turn].goza);
			}
			Delay(WAIT * 2);
		}
		else
		{
			key = ML_ThrowDice(turn, player[turn].dice_limit--); // 주사위를 굴린다
			if (key == QUIT_ESC) // 종료
				return;
			else if (key == CHEAT) // 치트
			{
				player[turn].money += 300; // 돈을 더해주고
				SIO_PrtInfo(player, univ); // 정보 갱신
			}
	#ifdef DEBUG
		key = 6;
	#endif

	// 플레이어를 이동한다
			around = SIO_MovePlayerEffect(&player[turn], turn, key);
			gotoxy(14, 8); printf("   ");
			if (around) // 한바퀴 돌았을 경우 (= 시작을 지났을 경우)
				ML_RoundMoney(turn, player, univ); // 장학금 지급

	// 땅 구매 or 수업료 뜯어먹기
	// 황금열쇠 process 먼저
			nowpos = player[turn].pos;

			if(strcmp(board[nowpos].name, GOLDEN_KEY) == 0)
			{ // 황금열쇠 칸을 밟았을 경우
				ML_ProcessGoldenKey(turn, nowpos, player, univ);
			}
			else if(IsSpecialCity(nowpos) != 0)
			{
				ML_ProcessSpecial(turn, nowpos, player, univ);
			}
			else if (board[nowpos].owner == -1 && IsSpecialCity(nowpos) == 0)
			{// 정복되지 않은 땅 & 구매 가능한 땅이면
				ML_BuyCity(turn, nowpos, player, univ);	// 땅을 산다
			}
			else if (board[nowpos].owner == turn && board[nowpos].level < 3)
			{ // 자기 땅이고, 풀업 아닌 경우
				ML_UpgradeCity(turn, nowpos, player, univ);	// 건물 업그레이드
			}
			else if (board[nowpos].owner != turn && board[nowpos].owner != -1)
			{ // 남의 땅이고, 구매된 경우만
				ML_PayLessonFee(turn, nowpos, player, univ); // 수업료를 지불한다
			}
		}
		turn = ML_ChangeTurn(turn); // 차례를 바꿔준다

		if (player[P1].round > 16 || player[P2].round > 16 || univ[P1].level == 5 || univ[P2].level == 5) // 게임 종료 조건 - 16바퀴를 돌아야 한다. 또는 대학 레벨이 5가 되면 승리한다
			loopin = 0;
	}
	ML_Ending(player, univ); // 승패 판단
}


char* CityName(const int whatuniv, const int pos)
{
	char* result = IsSpecialCity(pos);
	if(result != 0)
	{
		return result;
	}

	if (whatuniv == P1)
	{
		if (pos == 1)
			return P1_CITY_01;
		else if (pos == 2)
			return P1_CITY_02;
		else if (pos == 3)
			return P1_CITY_03;
		else if (pos == 4)
			return P1_CITY_04;
		else if (pos == 5)
			return P1_CITY_05;
		else if (pos == 6)
			return P1_CITY_06; // 6 왼쪽 아래 모서리
		else if (pos == 7)
			return P1_CITY_07;
		else if (pos == 9)
			return P1_CITY_09;
		else if (pos == 10)
			return P1_CITY_10;
		else if (pos == 11)
			return P1_CITY_11;
		else if (pos == 13)
			return P1_CITY_13;
		else if (pos == 14)
			return P1_CITY_14;
		else if (pos == 16)
			return P1_CITY_16;
		else if (pos == 17)
			return P1_CITY_17;
		else if (pos == 18)
			return P1_CITY_18; // 18 오른쪽 위 모서리
		else if (pos == 19)
			return P1_CITY_19;
		else if (pos == 21)
			return P1_CITY_21;
		else if (pos == 22)
			return P1_CITY_22;
		else if (pos == 23)
			return P1_CITY_23;
	}
	else if (whatuniv == P2)
	{
		if (pos == 1)
			return P2_CITY_01;
		else if (pos == 2)
			return P2_CITY_02;
		else if (pos == 3)
			return P2_CITY_03;
		else if (pos == 4)
			return P2_CITY_04;
		else if (pos == 5)
			return P2_CITY_05;
		else if (pos == 6)
			return P2_CITY_06; // 6 왼쪽 아래 모서리
		else if (pos == 7)
			return P2_CITY_07;
		else if (pos == 9)
			return P2_CITY_09;
		else if (pos == 10)
			return P2_CITY_10;
		else if (pos == 11)
			return P2_CITY_11;
		else if (pos == 13)
			return P2_CITY_13;
		else if (pos == 14)
			return P2_CITY_14;
		else if (pos == 16)
			return P2_CITY_16;
		else if (pos == 17)
			return P2_CITY_17;
		else if (pos == 18)
			return P2_CITY_18; // 18 오른쪽 위 모서리
		else if (pos == 19)
			return P2_CITY_19;
		else if (pos == 21)
			return P2_CITY_21;
		else if (pos == 22)
			return P2_CITY_22;
		else if (pos == 23)
			return P2_CITY_23;
	}
	return NULL;
}


// 변수 초기화 및 정보 담당
void InitPlayerStruct (PLAYER *player)
{
	player->pos = 0;
	player->money = 100;
	player->round = 0;
}

void InitCityStruct (CITY* city, const int pos)
{
	char* temp_name = IsSpecialCity(pos);
	city->cost = 0;
	city->name[0] = '\0';
	if(temp_name != '\0')
	{//중립 건물은 내부적으로 이름 미리 등록
		strncpy(city->name, temp_name, 32);
	}
	city->owner = -1;
	city->level = -1;
}

void InitUnivStruct (UNIV *univ, const int whatuniv)
{
	univ->money = 0;
	univ->level = 1;
	univ->city_count = 0;
	if (whatuniv == P1) // 고대라면
	{
		strncpy(univ->name, "고려", 6);
		univ->name[4] = '\0';
	}
	else if (whatuniv == P2) // 연대라면
	{
		strncpy(univ->name, "연세", 6);
		univ->name[4] = '\0';
	}
	// 굳이 strcpy를 안 쓴 이유 : 오버플로우 방지
}

char* IsSpecialCity(int city) // 중립 지역이라면 이름을 반환
{
	switch (city)
	{
	case 0: // 시작지
		return "START";
	case 8: // 황금열쇠
	case 15: // 황금열쇠
	case 20: // 황금열쇠
		return GOLDEN_KEY;
	case 6: // 대학원 (모서리)
		return ACADEMY;
	case 18: // 엠티 (모서리)
		return MT;
	case 12: // 병원 (모서리)
		return HOSPITAL;
	default:
		return '\0';
	}
}

void PrtBasic()
{ //기본틀
	gotoxy(12,14); printf("  │  │");
	gotoxy(12,15); printf("┌┘  └┐");
	gotoxy(12,16); printf("│      │");
	gotoxy(12,17); printf("│      │");
	gotoxy(12,18); printf("│●●●│");
	gotoxy(12,19); printf("│●●●│");
	gotoxy(12,20); printf("└───┘");
}

int DiceEffect(int dice_limit)
{
	int x,y;
	int i,j;
	int dice;
	PrtBasic();
	for ( i=1; i<=20; i++ )
	{
		for ( j=1; j<=5; j++ )
		{ //틀안에 원 무작위 출력
			x = RandNum(14,18);
			y = RandNum(16,19);
			gotoxy(x,y); printf("●");
		}
		Sleep(50);
		gotoxy(12,16); printf("│      │"); //지우고
		gotoxy(12,17); printf("│      │");
		gotoxy(12,18); printf("│      │");
		gotoxy(12,19); printf("│      │");
	}
	Sleep(75);
	gotoxy(12,14); printf("  │  │");//기본틀출력
	gotoxy(12,15); printf("┌┘●└┐");
	gotoxy(12,16); printf("│      │");
	gotoxy(12,17); printf("│   ● │");
	gotoxy(12,18); printf("│●    │");
	gotoxy(12,19); printf("│ ● ●│");
	gotoxy(12,20); printf("└───┘");


	Sleep(75);
	gotoxy(12,14); printf("  │●│");//기본틀출력
	gotoxy(12,15); printf("┌┘  └┐");
	gotoxy(12,16); printf("│      │");
	gotoxy(12,17); printf("│   ● │");
	gotoxy(12,18); printf("│●    │");
	gotoxy(12,19); printf("│ ● ●│");
	gotoxy(12,20); printf("└───┘");

	Sleep(75);
	gotoxy(16,12); printf("●");
	gotoxy(12,14); printf("  │  │");//기본틀출력
	gotoxy(12,15); printf("┌┘  └┐");
	gotoxy(12,16); printf("│      │");
	gotoxy(12,17); printf("│   ● │");
	gotoxy(12,18); printf("│●    │");
	gotoxy(12,19); printf("│ ● ●│");
	gotoxy(12,20); printf("└───┘");

	Sleep(75);
	gotoxy(16,12); printf("◐");
	Sleep(75);
	if(dice_limit > 0)
	{
		dice = RandNum(1,6);
	}
	else
	{
		dice = RandNum(1,12);
	}
	gotoxy(16,12);
	switch(dice) {
		case 1: printf("①"); break;
		case 2: printf("②"); break;
		case 3: printf("③"); break;
		case 4: printf("④"); break;
		case 5: printf("⑤"); break;
		case 6: printf("⑥"); break;
		case 7: printf("⑦"); break;
		case 8: printf("⑧"); break;
		case 9: printf("⑨"); break;
		case 10: printf("⑩"); break;
		case 11: printf("⑪"); break;
		case 12: printf("⑫"); break;
	}
	return dice;
}


// 게임 로직 담당
int ML_ChangeTurn(int turn)
{
	if (turn == P1)
		return P2;
	else if (turn == P2)
		return P1;
	return 0;
}

void ML_UnivLevelUp(int turn, PLAYER player[], UNIV univ[])	// 대학 레벨업 여부
{
	int i = 0, need = 0;
	static int lastuniv[PLAYER_NUMBER] = {1, 1}; // 지난번 대학 레벨을 저장

	SIO_TurnColor(turn); // 누구의 턴인지에 따라 안내문의 색을 다르게 한다
	for (i = P1; i <= P2; i++)
	{ // 여기 값을 조정하면 대학 레벨의 기준을 조정할 수 있다.
		if (difficulty == GAME_EASY)
		{
			if (univ[i].money < 50)
				univ[i].level = 1;
			else if (univ[i].money < 250)
				univ[i].level = 2;
			else if (univ[i].money < 500)
				univ[i].level = 3;
			else if (univ[i].money < 1000)
				univ[i].level = 4;
			else
				univ[i].level = 5;
		}
		else if (difficulty == GAME_HARD)
		{
			if (univ[i].money < 100)
				univ[i].level = 1;
			else if (univ[i].money < 800)
				univ[i].level = 2;
			else if (univ[i].money < 1600)
				univ[i].level = 3;
			else if (univ[i].money < 3200)
				univ[i].level = 4;
			else
				univ[i].level = 5;
		}

		if (lastuniv[i] < univ[i].level)
		{ // 장학금 지급
			if (difficulty == GAME_EASY)
				need = 75 * lastuniv[i];
			else if (difficulty == GAME_HARD)
				need = 150 * lastuniv[i];
			gotoxy(12, 6);	printf("%s대학교의 레벨이 상승하였습니다!", univ[i].name);
			gotoxy(12, 7);	printf("장학금 %3d만원이 지급되었습니다.", need);
			player[i].money += need;
			SIO_PrtInfo(player, univ); // 정보 갱신
			SIO_PrtLogo(univ);
			Delay(WAIT * 2);
		}
		lastuniv[i] = univ[i].level;
	}
}

int ML_ThrowDice(int turn, int dice_limit) // 주사위 굴리기
{
	int key = 0;
	if (turn == P1)
	{
		gotoxy(12, 6);	printf("고대생 차례입니다!                 ");
		gotoxy(12, 7);	printf("주사위를 굴리세요.                 ");
		gotoxy(12, 8);	printf("Press any key to continue...");
		key = getch(); // 키 입력을 받는다
		gotoxy(12, 8);	printf("                                   ");
	}
	else if (turn == P2)
	{
		gotoxy(12, 6);	printf("연대생 차례입니다!                 ");
		gotoxy(12, 7);	printf("주사위를 굴립니다.                 ");
		Delay(200);
	}

// 치트 : Ctrl + Alt
	if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_MENU))
	{
		gotoxy(12, 6);	printf("치트를 사용하였습니다.             ");
		gotoxy(12, 7);	printf("300만원이 입금됩니다.              ");
		Delay(WAIT);
		return CHEAT;
	}

// 키 입력을 받고 Ctrl+C, ESC 입력이면 종료
	if (key == 0x1B)
		return QUIT_ESC;

// 주사위 굴림 효과
	/*SIO_TurnColor(CL_BT);
	for (i = 0; i < 30; i++)
	{
		dice[0] = RandNum(1, 6);
		dice[1] = RandNum(1, 6);
		gotoxy(14, 8);
		printf("%d %d", dice[0], dice[1]);
		Delay(i);
	}*/
	return DiceEffect(dice_limit);
}

void ML_RoundMoney(int turn, PLAYER player[], UNIV univ[]) // 한 바퀴 돌면 주는 장학금
{
	int need = 0;
	static int morefee[2] = {1, 1};

	player[turn].round++; // 바퀴 카운트 올리고
	if (difficulty == GAME_HARD && player[turn].round >= 8 && morefee[turn]) // 어려움 난이도에서 수강료의 인상
	{
		morefee[turn] = 0;
		gotoxy(12, 6);	printf("%s대가 수업료를 인상했습니다!     ", univ[turn].name);
		gotoxy(12, 7);	printf("                                    ");
		Delay(WAIT * 4);
	}

	// 쉬움   장학금 = 기본금 * (대학레벨 * 0.7) * (1 + (자신이 회전한 바퀴 수 * 0.25))
	// 어려움 장학금 = 기본금 * 대학레벨 * (1 + (자신이 회전한 바퀴 수 * 0.70))
	if (difficulty == GAME_EASY)
		need = (int) (MONEY_BASE * ((double) univ[turn].level * 0.7) * (1 + (double) player[turn].round * 0.25));
	else if (difficulty == GAME_HARD)
		need = (int) (MONEY_BASE * univ[turn].level * (1 + (double) player[turn].round * 0.70));
	gotoxy(12, 6);	printf("한바퀴를 돌아 %d쿼터째입니다!     ", player[turn].round);
	gotoxy(12, 7);	printf("장학금 %d만원을 받았습니다.       ", need);
	player[turn].money += need;
	Delay(WAIT);

	if (player[turn].money < 0) // 마이너스 통장이라면?
	{
		double ftmp = 1.1; // 이자율
		player[turn].money = (int) (player[turn].money * ftmp); // 이자가 빠져나간 후의 돈
		gotoxy(11, 6);	printf("마이너스 통장에서 이자를 떼어갑니다!");
		gotoxy(11, 7);	printf("이자 : %d만원                 ", (int) (player[turn].money / 11));

	}
	Delay(WAIT);
	gotoxy(11, 6);	printf("                                    ");
	gotoxy(11, 7);	printf("                                    ");
	SIO_PrtInfo(player, univ); // 돈, 대학 현황 다시 표시
	SIO_PrtLogo(univ);
}

void ML_BuyCity(int turn, int nowpos, PLAYER player[], UNIV univ[])  // 건물 짓기
{
	int key = 0, need = 0;

	// 건설비용 = 건설비 * (1 + (자신이 회전한 바퀴 수 * 0.20))
	need = (int) ((double) ML_CityCost(turn, nowpos) * (1 + (double) player[turn].round * 0.20));
	SIO_TurnColor(turn);
	if (player[turn].money < need) // 마이너스이거나, 돈이 부족
	{
		gotoxy(12, 6);	printf("돈이 부족합니다!                   ");
		gotoxy(12, 7);	printf("%s을(를) 지을 수 없습니다.", CityName(turn, nowpos));
	}
	else
	{
		if (turn == P1) // 고대생 (플레이어)
		{
			gotoxy(12, 6);	printf("%s을(를) 지으시겠습니까?   ", CityName(turn, nowpos));
			gotoxy(12, 7);	printf("                                   ");
			gotoxy(12, 7);	printf("비용 : %d만원 [Y/N] ", need);

			do{
				key = getch();
			}while(key != 'Y' && key != 'y' && key != 'N' && key != 'n');
		}
		else if (turn == P2) // 연대생 (AI)
		{
			gotoxy(12, 6);	printf("                                   ");
			gotoxy(12, 7);	printf("                                   ");
			key = 'Y';
		}


		if (key == 'Y' || key == 'y') // 구매
		{
			board[nowpos].level = 0;
			board[nowpos].owner = turn;
			player[turn].money -= need;
			univ[turn].city_count++;
			SIO_PrtInfo(player, univ);
			SIO_PrtLogo(univ);

			SIO_TurnColor(turn);
			gotoxy(12, 6);	printf("%s을(를) 지었습니다!        ", CityName(turn, nowpos));
			gotoxy(12, 7);	printf("비용 : %d만원                ", need);
			strcpy(board[nowpos].name, CityName(turn, nowpos));
		}
	}
	Delay(WAIT);
}

void ML_UpgradeCity(int turn, int nowpos, PLAYER player[], UNIV univ[])  // 건물 업그레이드
{
	int key = 0, need = 0;

	SIO_TurnColor(turn);
	// 증축비용 = 건설비 + (증축할 레벨 + 1) * (1 + (자신이 회전한 바퀴 수 * 0.20))
	need = (int) ((double) ML_CityCost(turn, nowpos) * (board[nowpos].level + 2) * (1 + (double) player[turn].round * 0.20));
	if (player[turn].money < need) // 마이너스이거나, 돈이 부족
	{
		gotoxy(11, 6);	printf("돈이 부족합니다!                    ");
		gotoxy(11, 7);	printf("%s을(를) 증축할 수 없습니다.", CityName(turn, nowpos));
	}
	else
	{
		if (turn == P1) // 고대생 (플레이어)
		{
			gotoxy(11, 6);	printf("%s을(를) 증축하시겠습니까? ", CityName(turn, nowpos));
			gotoxy(11, 7);	printf("                                    ");
			gotoxy(11, 7);	printf("비용 : %d만원 [Y/N] ", need);

			do{
				key = getch();
			}while(key != 'Y' && key != 'y' && key != 'N' && key != 'n');
		}
		else if (turn == P2) // 연대생 (AI)
		{
			gotoxy(11, 6);	printf("                                    ");
			gotoxy(11, 7);	printf("                                    ");
			key = 'Y';
		}

		if (key == 'Y' || key == 'y') // 업그레이드
		{
			board[nowpos].level++;
			board[nowpos].owner = turn;
			player[turn].money -= need;

			gotoxy(11, 6);	printf("%s을(를) 증축하였습니다!  ", CityName(turn, nowpos));
			gotoxy(11, 7);	printf("비용 : %d만원                 ", need);
		}
	}
	Delay(WAIT);
}

void ML_PayLessonFee(int turn, int nowpos, PLAYER player[], UNIV univ[])	// 수업료 지불
{
	int need = 0;

	SIO_TurnColor(turn);
	if (turn == P1) // 고대생이 돈 내는 경우
	{
		gotoxy(12, 6);	printf("연세대 수업을 들었습니다!    ");
	}
	else if (turn == P2) // 연대생이 돈 내는 경우
	{
		gotoxy(12, 6);	printf("고려대 수업을 들었습니다!    ");
	}

	// 수업료 지불
	// 쉬움 수업료 = 건물 레벨 x (대학 레벨) x (1 + (상대방이 회전한 바퀴 수 * 0.10))
	// 어려움 수업료 = (건물 레벨 x (1 + 대학 레벨)^ (1 + 상대방이 회전한 바퀴 수 / 32))
	if (difficulty == GAME_EASY) // 쉬움
	{
		if (board[nowpos].level == 0) // 건물 레벨에 따른 수업료
			need = 5;
		else if (board[nowpos].level == 1)
			need = 15;
		else if (board[nowpos].level == 2)
			need = 30;
		else if (board[nowpos].level == 3) // 풀업
			need = 50;
		need = (int) ((double) need * univ[board[nowpos].owner].level * (1 + (double) player[board[nowpos].owner].round * 0.10)); // 수업료 공식 적용
	}
	else if (difficulty == GAME_HARD) // 어려움
	{
		if (player[board[nowpos].owner].round < 8)
		{
			if (board[nowpos].level == 0) // 건물 레벨에 따른 수업료
				need = 5;
			else if (board[nowpos].level == 1)
				need = 20;
			else if (board[nowpos].level == 2)
				need = 40;
			else if (board[nowpos].level == 3) // 풀업
				need = 60;
		}
		else
		{
			if (board[nowpos].level == 0) // 건물 레벨에 따른 수업료
				need = 40;
			else if (board[nowpos].level == 1)
				need = 60;
			else if (board[nowpos].level == 2)
				need = 80;
			else if (board[nowpos].level == 3) // 풀업
				need = 100;
		}

		need = (int) pow(((double) need * (1 + univ[board[nowpos].owner].level)), (1 + (double) player[board[nowpos].owner].round / 32)); // 수업료 공식 적용
	}

	player[turn].money -= need;
	univ[board[nowpos].owner].money += need;
	gotoxy(12, 7);	printf("                                   ");
	gotoxy(12, 7);  printf("수업료 %d만원를 지불합니다.", need);
	Delay(WAIT * 2);
	gotoxy(12, 7);	printf("                                   ");
}

void ML_Ending(PLAYER player[], UNIV univ[])	// 승패 판단
{
	int i = 0, cmp_money[2] = {0, 0}, win = 0;
	char stmp[2][32];
	stmp[P1][0] = '\0';
	stmp[P2][0] = '\0';

	system("cls");
	SIO_InitBoard();		  // 보드를 그리고
	SIO_DrawBoard();		  // 건물색 칠한다
	SIO_PrtPlayer(player);	  // 말을 그린다.
	SIO_PrtInfo(player, univ);// 돈 현황 표시
	SIO_PrtLogo(univ);		  //대학 현황 표시
// 게임 종료. y를 계속 눌렀을 때를 대비해서 Enter 입력받기
	SIO_TurnColor(NEUTRAL);
	gotoxy(12, 6);	printf("게임이 끝났습니다!             ");
	gotoxy(12, 7);	printf("Enter키를 눌러 주세요...       ");
	gotoxy(12, 9);	while (getchar() != '\n');

// 정산을 해야 한다.
	if (difficulty == GAME_EASY) // 난이도 쉬움
	{
		for (i = P1; i <= P2; i++)
		{// 학생이 빚을 지고 있으면 그걸 학교 돈에서 뺀다
			if (player[i].money < 0)
				cmp_money[i] = univ[i].money + player[i].money; // += 하는 이유는 player[i].money는 음수라서
			else
				cmp_money[i] = univ[i].money;
		}
		strcpy(stmp[P1], "고려대학교 : ");
		strcpy(stmp[P2], "연세대학교 : ");

		if (cmp_money[P1] > cmp_money[P2]) // 고대의 승리!
			win = GAME_WIN;
		else if (cmp_money[P1] == cmp_money[P2]) // 일어날 수는 없겠지만, 비김
			win = GAME_DRAW;
		else // if (cmp_money[P1] < cmp_money[P2]) // 연대의 승리
			win = GAME_LOSE;
	}
	else if (difficulty == GAME_HARD) // 난이도 어려움
	{
		for (i = P1; i <= P2; i++)
		{
			if (player[i].money < 0) // 학생이 빚을 지고 있으면 반영
				cmp_money[i] = player[i].money * -1;
			else // 빚이 없으면 비김
				cmp_money[i] = 0;
		}
		strcpy(stmp[P1], "고대생의 빚 : ");
		strcpy(stmp[P2], "연대생의 빚 : ");

		if (cmp_money[P1] < cmp_money[P2]) // 빚이 더 적어서 고대의 승리!
			win = GAME_WIN;
		else if (cmp_money[P1] == cmp_money[P2]) // 일어날 수는 없겠지만, 비김
			win = GAME_DRAW;
		else // if (cmp_money[P1] > cmp_money[P2]) // 연대의 승리
			win = GAME_LOSE;
	}


// 승패를 가리기
    if (win == GAME_WIN) // 고대의 승리!
    {
    	gotoxy(12, 6);	SIO_TurnColor(P1);	printf(stmp[P1]);	SIO_TurnColor(P1_SEMI);	printf("%6d만원       ", cmp_money[P1]);
    	gotoxy(12, 7);	SIO_TurnColor(P1);	printf(stmp[P2]);	SIO_TurnColor(P1_SEMI);	printf("%6d만원       ", cmp_money[P2]);
    	gotoxy(12, 9);	SIO_TurnColor(P1_SEMI);	printf("고려대가 연세대를 인수했습니다!  ");
    	gotoxy(12, 10);	SIO_TurnColor(P1_SEMI);	printf("고려대 신촌캠퍼스가 탄생했습니다.");
    	gotoxy(12, 13);	printf("              You Win              ");
    	SIO_TurnColor(P1);
    }
    else if (win == GAME_DRAW) // 일어날 수는 없겠지만, 비김
    {
    	SIO_TurnColor(NEUTRAL);
    	gotoxy(12, 6);	printf("%s : %6d만원      ", stmp[P1], cmp_money[P1]);
    	gotoxy(12, 7);	printf("%s : %6d만원      ", stmp[P2], cmp_money[P2]);
    	gotoxy(12, 9);	printf("승부를 가리지 못했습니다.        ");
    	gotoxy(12, 10);	printf("비겼습니다!                      ");
    	gotoxy(12, 13);	printf("              The End              ");
    }
    else // if (win == GAME_LOSE) // 연대의 승리
    {
    	gotoxy(12, 6);	SIO_TurnColor(P2);	printf(stmp[P1]);	SIO_TurnColor(P2_SEMI);	printf("%6d만원       ", cmp_money[P1]);
    	gotoxy(12, 7);	SIO_TurnColor(P2);	printf(stmp[P2]);	SIO_TurnColor(P2_SEMI);	printf("%6d만원       ", cmp_money[P2]);
    	gotoxy(12, 9);	SIO_TurnColor(P2_SEMI);	printf("연세대가 고려대를 인수하였습니다.");
    	gotoxy(12, 10);	SIO_TurnColor(P2_SEMI);	printf("패배하였습니다...                ");
    	gotoxy(12, 13);	printf("              You Lose             ");
    	SIO_TurnColor(P2);
    }
	gotoxy(12, 15);	printf("     Press any key to exit...");
	getch();
}


void ML_PrintStory()
{
	char* story[6] = {
"서기 2300년...\n태풍 [[ㅇㅁㅇ;;]]의 영향으로 인해\n서울대 뒷편의 관악산이 무너졌다."
,
"패닉에 빠진 서울대생들은 전국 각각으로 뿔뿔이 흩어졌고,\n서울대는 몰락의 길을 걷게 된다."
,
"\"한국 원탑 대학교의 자리는 바로 나야!\"\n-고려대학교 학장 병처으리"
,
"\"그럴 리가, 고려학교는 연세대학의 발끝만도 못 따라온다고!\n-연새대학교 학장 가병이"
,
"한국 원탑 대학교의 자리를 놓고,\n두 대학의 사활을 건 전쟁이 시작된다!"
,
" - 마블의 고연전 - "
	};

	int i;

	for(i=0; i<6; i++)
	{
		SIO_PrintMsg(story[i]);
		printf("\n\n    >>다음");
		getch();
		system("CLS");
	}

}

int ML_CityCost (int whatuniv, int pos)
{
	int cost = 0;
	if (whatuniv == P1)
	{
		switch (pos) // 고대 비싼 건물의 가격 변경은 여기서
		{
		case 14: // 하스
		case 21: // 정통관
			cost = 30;
			break;
		case 9: // 화정
			cost = 20;
			break;
		default: // 나머지 고대 건물
			cost = 10;
			break;
		}
	}
	else if (whatuniv == P2)
	{
		switch (pos) // 연대 비싼 건물의 가격 변경은 여기서
		{
		case 10: // 바닷가
		case 14: // 새장
		case 22: // 선착장
			cost = 30;
			break;
		default: // 나머지 연대 건물
			cost = 10;
			break;
		}
	}
	return cost;
}

void ML_ProcessGoldenKey(int turn, int nowpos, PLAYER player[], UNIV univ[])
{
	int amount = 0, rValue, i, loopin = 1;
	const char* wildlife_name[4] = {"천사 뷰에게 경고받은 조민환을", "출튀 잡으시는 정빈 교수님을", "아청아청(누군지 알겠지?)을", "2반 배신의 아이콘 3지석을"};
	const char* univ_name[2] = {"고대", "연대"};
	gotoxy(12, 6);

	switch(rand()%5) //rand()%5
	{

	case 0:		//히어로(야생의 임재민을 만났다!)
		gotoxy(11,6); printf("%s 만났다!", wildlife_name[rand()%4]);
		gotoxy(11,7); printf("참참참 게임을 해서 이긴다면");
		gotoxy(11,8); printf("치느님을 사 주지.");
		ML_ChamChamCham(turn, player, univ);
		break;
	case 1:		//장학금 받기
		// 쉬움   장학금 = 기본금 * (대학레벨 * 0.7) * (1 + (자신이 회전한 바퀴 수 * 0.25)) * (0.5~3.0 사이)
		// 어려움 장학금 = 기본금 * 대학레벨 * (1 + (자신이 회전한 바퀴 수 * 0.70)) * (0.5~3.0 사이)
		if (difficulty == GAME_EASY)
			amount = (int) (MONEY_BASE * ((double) univ[turn].level * 0.7) * (1 + (double) player[turn].round * 0.25) * (RandNum(1, 6) / 2.0));
		else if (difficulty == GAME_HARD)
			amount = (int) (MONEY_BASE * univ[turn].level * (1 + (double) player[turn].round * 0.70) * (RandNum(1, 6) / 2.0));
						printf("%s생이 미적과 물리 A+를 받아", univ_name[turn]);
		gotoxy(12,7);	printf("장학금 %d만원이 주어졌습니다.", amount);
		player[turn].money += amount;
		break;
	case 2:		//성인지 감수성 교육 또는 채플
		// 수업료 지불
		// 쉬움 수업료 = ((5~30 사이) * (대학 레벨) x (1 + (상대방이 회전한 바퀴 수 * 0.10)
		// 어려움 수업료 = ((5~30 or 40~60 사이) * (1 + 대학 레벨))^(1 + 상대방이 회전한 바퀴 수 / 32)
		if (difficulty == GAME_EASY)
			amount = (int) ((double) RandNum(5, 30) * univ[ML_ChangeTurn(turn)].level * (1 + (double) player[ML_ChangeTurn(turn)].round * 0.10)); // 수업료 공식 적용
		else if (difficulty == GAME_HARD)
		{
			if (player[ML_ChangeTurn(turn)].round < 8) // 수업료 인상 전
				i = RandNum(5, 30);
			else // 수업료 인상 후
				i = RandNum(40, 60);
			amount = (int) pow(((i / 2.0) * univ[ML_ChangeTurn(turn)].level), (1 + (double) player[ML_ChangeTurn(turn)].round / 32));
		}
		SIO_TurnColor(turn); 
		if(turn == P1)
		{
						  printf("채플을 들었습니다!             ");
			gotoxy(12,7); printf("연대생이 삥을 뜯어             ");
			gotoxy(12,8); printf("%d만원을 가져갔습니다.", amount);
			player[P1].money -= amount;
			player[P2].money += amount;
		}
		else if(turn == P2)
		{
						  printf("성인지 감수성 교육을 들었습니다!");
			gotoxy(12,7); printf("고대생이 삥을 뜯어              ");
			gotoxy(12,8); printf("%d만원을 가져습니다.         ", amount);
			player[P1].money += amount;
			player[P2].money -= amount;
		}

		break;

	case 3:		//태풍으로 건물 무너지는 이벤트
						  printf("태풍 ㅇㅁㅇ;;이 학교를 덮쳤습니다!");
			gotoxy(12,7); printf("건물 하나가 파괴됩니다.");
			rValue = rand()%2;

			if (rValue == 0)		//두 방법 중 하나의 방법으로 건물 랜덤하게 결정
			{
				for (i=0; i < 24 && loopin; i++)
				{
					if (board[i].owner == turn && board[i].level > -1)
					{
						if(board[i].level == 0)		//건물 삭제
						{
							InitCityStruct(&board[i], i); 
							univ[turn].city_count--;
						}
						else
						{
							board[i].level--;
						}
						gotoxy(12,9); printf("%s이(가) 파괴되었습니다!", CityName(turn, i));
						loopin = 0;
					}
				}
			}
			else
			{
				for (i=0; i<24 && loopin; i++)
				{
					if (board[i].owner == turn && board[i].level > -1)
					{
						if(board[i].level == 0)		//건물 삭제
						{
							InitCityStruct(&board[i], i); 
							univ[turn].city_count--;
						}
						else
						{
							board[i].level--;
						}
						gotoxy(12,9); printf("%s이(가) 파괴되었습니다!", CityName(turn, i));
						loopin = 0;
					}
				}
			}

		break;

	case 4:		//건물 무상업글 이벤트
						  printf("S모 회사에서 학교에 지원금을 주었다!");
			gotoxy(12,7); printf("건물 하나가 업그레이드됩니다.");
			rValue = rand()%2;

			if(rValue == 0)		//두 방법 중 하나의 방법으로 건물 랜덤하게 결정
			{
				for(i=0; i<24 && loopin; i++)
				{
					if(board[i].owner == turn && board[i].level < 3)
					{
						board[i].level++;
						gotoxy(12,9); printf("%s이(가) 증축되었습니다!", CityName(turn, i));
						loopin = 0;
					}
				}
			}
			else
			{
				for(i=23; i>=0 && loopin; i--)
				{
					if(board[i].owner == turn && board[i].level < 3)
					{
						board[i].level++;
						gotoxy(12,9); printf("%s이(가) 증축되었습니다!", CityName(turn, i));
						loopin = 0;
					}
				}
			}
		break;
	}

	SIO_PrtInfo(player, univ);	//정보 갱신

	Delay(WAIT * 2);
}

void ML_ProcessSpecial(int turn, int nowpos, PLAYER player[], UNIV univ[])
{
	BT button[24];
	int goza, i;
	int loopin = 1;
	int x = 0, y = 0;
	switch(nowpos)
	{

		case 6: // 대학원 (모서리)
			gotoxy(12,6); printf("대학원에 진학합니다!");
			gotoxy(12,7); printf("원하는 칸으로 이동할 수 있습니다.");

			if(turn == P1)
			{
				gotoxy(12,8); printf("원하는 칸을 마우스로 클릭해 주세요.");
				// 가상의 24개 버튼 생성
				for(i=0; i<24; i++)
				{
					SIO_CalcPos(i, &x, &y);
					button[i] = CreateButton("  ", x, y-2);
					PrtButton(button[i]);
				}
				while(loopin)
				{
					for(i=0; i<24; i++)
					{
						if ( CLICK_LEFT && ChkButton(button[i]))
						{
							gotoxy(0,0);
							SIO_InitBoard();
							SIO_DrawBoard();
							// 상대방의 위치를 다시 그려줌
							SIO_JumpPlayerEffect(&player[P2], P2, player[P2].pos);
							
							SIO_TurnColor(turn);
							gotoxy(12,6); printf("%s(으)로 이동합니다!", CityName(turn, i));
							SIO_JumpPlayerEffect(&player[P1], turn, i);
							loopin = 0;
							break;
						}
					}
				}
			}
			else
			{
				Delay(WAIT);
				i = rand()%24;
				gotoxy(12,8); printf("%s(으)로 이동합니다!", CityName(turn, i));
				SIO_JumpPlayerEffect(&player[P2], turn, i);
			}
			break;
		case 18: // 엠티 (모서리)
			gotoxy(12,6); printf("MT에서 술을 마시고 뻗었습니다!");
			gotoxy(12,7); printf("3턴동안 주사위 숫자가 제한됩니다.");
			player[turn].dice_limit = 2;
			break;
		case 12: // 병원 (모서리)
			goza = rand()%2+1;
			gotoxy(12,6); printf("아니... 내가 고자라니!");
			gotoxy(12,7); printf("%d턴동안 움직일 수 없습니다!", goza);
			player[turn].goza = goza;
			break;
	}

	SIO_PrtInfo(player, univ);	//정보 갱신
	Delay(WAIT * 2);
}


void ML_ChamChamCham(int turn, PLAYER player[], UNIV univ[])
{
	char ch;
	int cham[2] = {0,};
	int amount;
	SIO_PrtMinigameBase();
	gotoxy(80, 5); printf("참참참 게임");
	if(turn == P1)
	{
		gotoxy(80, 6); printf("왼쪽은 A, 오른쪽은 D");
		gotoxy(80, 7); printf("시작하려면 아무 키나 누르세요.");
		getch();
	}
	SIO_TurnColor(turn);
	SIO_PrintCham(CHAM_TOP);
	Delay(WAIT);
	SIO_PrtMinigameBase();
	Delay(WAIT);
	SIO_PrintCham(CHAM_TOP);
	if(turn == P1)
	{
		do{
			ch = getch();
		}while(ch != 'A' && ch != 'a' && ch != 'D' && ch != 'd');

		if(ch == 'A' || ch == 'a')
		{
			cham[P1] = CHAM_LEFT;
		}
		else if(ch == 'D' || ch == 'd')
		{
			cham[P1] = CHAM_RIGHT;
		}
	}
	else
	{
		cham[P1] = rand()%2+1;
	}
	//1 or 2
	cham[P2] = rand()%2+1;
	SIO_PrintCham(cham[P2]);
	
	Delay(WAIT);
	//맞췄을 경우
	if(cham[P1] == cham[P2])
	{
		if (difficulty == GAME_EASY)
			amount = (int) (MONEY_BASE * ((double) univ[turn].level * 0.7) * (1 + (double) player[turn].round * 0.25) * (RandNum(1, 6) / 2.0));
		else if (difficulty == GAME_HARD)
			amount = (int) (MONEY_BASE * univ[turn].level * (1 + (double) player[turn].round * 0.70) * (RandNum(1, 6) / 2.0));

		gotoxy(78,25); printf("좋아.. 나를 이겼군");
		gotoxy(78,26); printf("%d만원을 주도록 하지.", amount);

		player[turn].money += amount;
		SIO_PrtInfo(player, univ);
	}
	else
	{
		gotoxy(78,26); printf("아직 멀었군 ㅎㅎ 애송이");
		gotoxy(78,26); printf("에휴 그냥 가라...");
	}

	Delay(WAIT*2);
}