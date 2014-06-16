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
	int turn, dice[2], key;
	int i, loopin,  around, nowpos;
	PLAYER player[PLAYER_NUMBER];
//	CITY city[CITY_NUMBER];
	UNIV univ[PLAYER_NUMBER];

//변수 초기화
	turn = 0; // 플레이어 turn의 턴
	dice[0] = 0; // 주사위 굴려서 이동하는 정도
	dice[1] = 0;
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
	{
		InitCityStruct(&board[i], P1, i);
		InitCityStruct(&board[i], P2, i);
	}

// 게임 루프 시작
	turn = 0;
	loopin = 1;
	timepass = clock();
	while (loopin)
	{
		system("cls");
// 초기화
		SIO_InitBoard(); // 보드를 그리고
		SIO_DrawBoard(); // 건물색 칠한다
		SIO_PrtPlayer(player); // 말을 그린다.
		SIO_PrtInfo(player, univ); // 돈, 대학 현황 표시

		// 대학 로고 레벨 검사
		ML_UnivLevelUp(turn, player, univ);

		key = ML_ThrowDice(turn, dice); // 주사위를 굴린다
		if (key == QUIT_ESC) // 종료
			return;
		else if (key == CHEAT) // 치트
		{
			player[turn].money += 300; // 돈을 더해주고
			SIO_PrtInfo(player, univ); // 정보 갱신
		}

// 플레이어를 이동한다
		around = SIO_MovePlayerEffect(&player[turn], turn, dice[0] + dice[1]);
		gotoxy(14, 8); printf("   ");
		if (around) // 한바퀴 돌았을 경우 (= 시작을 지났을 경우)
			ML_RoundMoney(turn, player, univ); // 장학금 지급

// 땅 구매 or 수업료 뜯어먹기
		nowpos = player[turn].pos;
		if (board[nowpos].owner == -1 && IsSpecialCity(nowpos) == 0)
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
		turn = ML_ChangeTurn(turn); // 차례를 바꿔준다

		if (player[P1].round > 16 || player[P2].round > 16) // 게임 종료 조건 - 16바퀴를 돌아야 한다.
			loopin = 0;
	}
	ML_Ending(player, univ); // 승패 판단
}


char* CityName(const int whatuniv, const int pos)
{
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

void InitCityStruct (CITY* city, const int whatuniv, const int pos)
{
	city->pos = 0;
	city->name[0] = '\0';
	if (whatuniv == P1)
	{
		switch (pos) // 고대 비싼 건물의 가격 변경은 여기서
		{
		case 14: // 하스
		case 21: // 정통관
			city->cost = 30;
			break;
		case 9: // 화정
			city->cost = 20;
			break;
		default: // 나머지 고대 건물
			city->cost = 10;
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
			city->cost = 30;
			break;
		default: // 나머지 연대 건물
			city->cost = 10;
			break;
		}
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

int IsSpecialCity(int city) // 중립 지역
{
	int i = 0;
	switch (city)
	{
	case 0: // 시작지
	case 6: // (모서리)
	case 8: // 황금열쇠
	case 12: // 병원 (모서리)
	case 15: // 황금열쇠
	case 18: // (모서리)
	case 20: // 황금열쇠
		i = 1;
		break;
	default:
		i = 0;
		break;
	}
	return i;
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
			Delay(WAIT * 2);
		}
		lastuniv[i] = univ[i].level;
	}
}

int ML_ThrowDice(int turn, int dice[]) // 주사위 굴리기
{
	int key = 0, i = 0;

	SIO_TurnColor(turn);
	if (turn == P1)
	{
		gotoxy(12, 6);	printf("고대생 차례입니다!                 ");
		gotoxy(12, 7);	printf("주사위를 굴리세요.                 ");
		gotoxy(12, 8);	printf("Pres any key to continue...");
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
	SIO_TurnColor(CL_BT);
	for (i = 0; i < 30; i++)
	{
		dice[0] = RandNum(1, 6);
		dice[1] = RandNum(1, 6);
		gotoxy(14, 8);
		printf("%d %d", dice[0], dice[1]);
		Delay(i);
	}
	return key;
}

void ML_RoundMoney(int turn, PLAYER player[], UNIV univ[]) // 한 바퀴 돌면 주는 장학금
{
	int i = 0, need = 0;
	static int morefee = 1;

	player[turn].round++; // 바퀴 카운트 올리고
	if (difficulty == GAME_HARD && player[turn].round >= 8 && morefee) // 어려움 난이도에서 수강료의 인상
	{
		morefee = 0;
		gotoxy(12, 6);	printf("%s대가 수업료를 인상했습니다!     ", univ[turn].name);
		Delay(WAIT * 4);
	}


	i = 30; // 한바퀴 돌면 주는 기본급

	// 쉬움   장학금 = 기본금 * (대학레벨 * 0.7) * (1 + (자신이 회전한 바퀴 수 * 0.25))
	// 어려움 장학금 = 기본금 * 대학레벨 * (1 + (자신이 회전한 바퀴 수 * 0.70))
	if (difficulty == GAME_EASY)
		need = (int) (i * ((double) univ[turn].level * 0.7) * (1 + (double) player[turn].round * 0.25));
	else if (difficulty == GAME_HARD)
		need = (int) (i * univ[turn].level * (1 + (double) player[turn].round * 0.70));
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
}

void ML_BuyCity(int turn, int nowpos, PLAYER player[], UNIV univ[])  // 건물 짓기
{
	int key = 0, need = 0;

	// 건설비용 = 건설비 * (1 + (자신이 회전한 바퀴 수 * 0.20))
	need = (int) ((double) board[nowpos].cost * (1 + (double) player[turn].round * 0.20));
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
			}while(key == 'Y' || key == 'y' || key == 'N' || key == 'n');
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
	need = (int) ((double) board[nowpos].cost * (board[nowpos].level + 2) * (1 + (double) player[turn].round * 0.20));
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

			key = getch();
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

	SIO_PrtInfo(player, univ); // 정보 갱신
// 게임 종료. y를 계속 눌렀을 때를 대비해서 Enter 입력받기
	SIO_TurnColor(NEUTRAL);
	gotoxy(12, 6);	printf("게임이 끝났습니다!            ");
	gotoxy(12, 7);	printf("Enter키를 눌러 주세요...      ");
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
    	gotoxy(12, 9);	SIO_TurnColor(P1_SEMI);	printf("고려대학교의 승리입니다!         ");
    	gotoxy(12, 10);	SIO_TurnColor(P1_SEMI);	printf("축하합니다!                      ");
    	SIO_TurnColor(P1);
    }
    else if (win == GAME_DRAW) // 일어날 수는 없겠지만, 비김
    {
    	SIO_TurnColor(NEUTRAL);
    	gotoxy(12, 6);	printf("%s : %6d만원      ", stmp[P1], cmp_money[P1]);
    	gotoxy(12, 7);	printf("%s : %6d만원      ", stmp[P2], cmp_money[P2]);
    	gotoxy(12, 9);	printf("(일어날 수 없는 엔딩일텐데...)   ");
    	gotoxy(12, 10);	printf("비겼습니다!                      ");
    }
    else // if (win == GAME_LOSE) // 연대의 승리
    {
    	gotoxy(12, 6);	SIO_TurnColor(P2);	printf(stmp[P1]);	SIO_TurnColor(P2_SEMI);	printf("%6d만원       ", cmp_money[P1]);
    	gotoxy(12, 7);	SIO_TurnColor(P2);	printf(stmp[P2]);	SIO_TurnColor(P2_SEMI);	printf("%6d만원       ", cmp_money[P2]);
    	gotoxy(12, 9);	SIO_TurnColor(P2_SEMI);	printf("아카라카! 아라칭 아라쵸...       ");
    	gotoxy(12, 10);	SIO_TurnColor(P2_SEMI);	printf("패배하였습니다......             ");
    	SIO_TurnColor(P2);
    }
	gotoxy(12, 13);	printf("              The End              ");
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
"\"그럴 리가, 고려학교는 연세대학의 발끝만도 못 따라온다고!\n-연새대학교 학장 ???"
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