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
// ���� ����
	int turn, dice[2], key;
	int i, loopin,  around, nowpos;
	PLAYER player[PLAYER_NUMBER];
//	CITY city[CITY_NUMBER];
	UNIV univ[PLAYER_NUMBER];

//���� �ʱ�ȭ
	turn = 0; // �÷��̾� turn�� ��
	dice[0] = 0; // �ֻ��� ������ �̵��ϴ� ����
	dice[1] = 0;
	key = 0;
	i = 0; // �ӽú���
	nowpos = 0; // ���� ��ġ
	around = 0; // �� ���� ���Ҵ°� �˻�
	loopin = 0; // while �� ���� ��� ������ ����
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

// ���� ���� ����
	turn = 0;
	loopin = 1;
	timepass = clock();
	while (loopin)
	{
		system("cls");
// �ʱ�ȭ
		SIO_InitBoard(); // ���带 �׸���
		SIO_DrawBoard(); // �ǹ��� ĥ�Ѵ�
		SIO_PrtPlayer(player); // ���� �׸���.
		SIO_PrtInfo(player, univ); // ��, ���� ��Ȳ ǥ��

		// ���� �ΰ� ���� �˻�
		ML_UnivLevelUp(turn, player, univ);

		key = ML_ThrowDice(turn, dice); // �ֻ����� ������
		if (key == QUIT_ESC) // ����
			return;
		else if (key == CHEAT) // ġƮ
		{
			player[turn].money += 300; // ���� �����ְ�
			SIO_PrtInfo(player, univ); // ���� ����
		}

// �÷��̾ �̵��Ѵ�
		around = SIO_MovePlayerEffect(&player[turn], turn, dice[0] + dice[1]);
		gotoxy(14, 8); printf("   ");
		if (around) // �ѹ��� ������ ��� (= ������ ������ ���)
			ML_RoundMoney(turn, player, univ); // ���б� ����

// �� ���� or ������ ���Ա�
		nowpos = player[turn].pos;
		if (board[nowpos].owner == -1 && IsSpecialCity(nowpos) == 0)
		{// �������� ���� �� & ���� ������ ���̸�
			ML_BuyCity(turn, nowpos, player, univ);	// ���� ���
		}
		else if (board[nowpos].owner == turn && board[nowpos].level < 3)
		{ // �ڱ� ���̰�, Ǯ�� �ƴ� ���
			ML_UpgradeCity(turn, nowpos, player, univ);	// �ǹ� ���׷��̵�
		}
		else if (board[nowpos].owner != turn && board[nowpos].owner != -1)
		{ // ���� ���̰�, ���ŵ� ��츸
			ML_PayLessonFee(turn, nowpos, player, univ); // �����Ḧ �����Ѵ�
		}
		turn = ML_ChangeTurn(turn); // ���ʸ� �ٲ��ش�

		if (player[P1].round > 16 || player[P2].round > 16) // ���� ���� ���� - 16������ ���ƾ� �Ѵ�.
			loopin = 0;
	}
	ML_Ending(player, univ); // ���� �Ǵ�
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
			return P1_CITY_06; // 6 ���� �Ʒ� �𼭸�
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
			return P1_CITY_18; // 18 ������ �� �𼭸�
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
			return P2_CITY_06; // 6 ���� �Ʒ� �𼭸�
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
			return P2_CITY_18; // 18 ������ �� �𼭸�
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


// ���� �ʱ�ȭ �� ���� ���
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
		switch (pos) // ��� ��� �ǹ��� ���� ������ ���⼭
		{
		case 14: // �Ͻ�
		case 21: // �����
			city->cost = 30;
			break;
		case 9: // ȭ��
			city->cost = 20;
			break;
		default: // ������ ��� �ǹ�
			city->cost = 10;
			break;
		}
	}
	else if (whatuniv == P2)
	{
		switch (pos) // ���� ��� �ǹ��� ���� ������ ���⼭
		{
		case 10: // �ٴ尡
		case 14: // ����
		case 22: // ������
			city->cost = 30;
			break;
		default: // ������ ���� �ǹ�
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
	if (whatuniv == P1) // �����
	{
		strncpy(univ->name, "���", 6);
		univ->name[4] = '\0';
	}
	else if (whatuniv == P2) // ������
	{
		strncpy(univ->name, "����", 6);
		univ->name[4] = '\0';
	}
	// ���� strcpy�� �� �� ���� : �����÷ο� ����
}

int IsSpecialCity(int city) // �߸� ����
{
	int i = 0;
	switch (city)
	{
	case 0: // ������
	case 6: // (�𼭸�)
	case 8: // Ȳ�ݿ���
	case 12: // ���� (�𼭸�)
	case 15: // Ȳ�ݿ���
	case 18: // (�𼭸�)
	case 20: // Ȳ�ݿ���
		i = 1;
		break;
	default:
		i = 0;
		break;
	}
	return i;
}


// ���� ���� ���
int ML_ChangeTurn(int turn)
{
	if (turn == P1)
		return P2;
	else if (turn == P2)
		return P1;
	return 0;
}

void ML_UnivLevelUp(int turn, PLAYER player[], UNIV univ[])	// ���� ������ ����
{
	int i = 0, need = 0;
	static int lastuniv[PLAYER_NUMBER] = {1, 1}; // ������ ���� ������ ����

	SIO_TurnColor(turn); // ������ �������� ���� �ȳ����� ���� �ٸ��� �Ѵ�
	for (i = P1; i <= P2; i++)
	{ // ���� ���� �����ϸ� ���� ������ ������ ������ �� �ִ�.
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
		{ // ���б� ����
			if (difficulty == GAME_EASY)
				need = 75 * lastuniv[i];
			else if (difficulty == GAME_HARD)
				need = 150 * lastuniv[i];
			gotoxy(12, 6);	printf("%s���б��� ������ ����Ͽ����ϴ�!", univ[i].name);
			gotoxy(12, 7);	printf("���б� %3d������ ���޵Ǿ����ϴ�.", need);
			player[i].money += need;
			SIO_PrtInfo(player, univ); // ���� ����
			Delay(WAIT * 2);
		}
		lastuniv[i] = univ[i].level;
	}
}

int ML_ThrowDice(int turn, int dice[]) // �ֻ��� ������
{
	int key = 0, i = 0;

	SIO_TurnColor(turn);
	if (turn == P1)
	{
		gotoxy(12, 6);	printf("���� �����Դϴ�!                 ");
		gotoxy(12, 7);	printf("�ֻ����� ��������.                 ");
		gotoxy(12, 8);	printf("Pres any key to continue...");
		key = getch(); // Ű �Է��� �޴´�
		gotoxy(12, 8);	printf("                                   ");
	}
	else if (turn == P2)
	{
		gotoxy(12, 6);	printf("����� �����Դϴ�!                 ");
		gotoxy(12, 7);	printf("�ֻ����� �����ϴ�.                 ");
		Delay(200);
	}

// ġƮ : Ctrl + Alt
	if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_MENU))
	{
		gotoxy(12, 6);	printf("ġƮ�� ����Ͽ����ϴ�.             ");
		gotoxy(12, 7);	printf("300������ �Աݵ˴ϴ�.              ");
		Delay(WAIT);
		return CHEAT;
	}

// Ű �Է��� �ް� Ctrl+C, ESC �Է��̸� ����
	if (key == 0x1B)
		return QUIT_ESC;

// �ֻ��� ���� ȿ��
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

void ML_RoundMoney(int turn, PLAYER player[], UNIV univ[]) // �� ���� ���� �ִ� ���б�
{
	int i = 0, need = 0;
	static int morefee = 1;

	player[turn].round++; // ���� ī��Ʈ �ø���
	if (difficulty == GAME_HARD && player[turn].round >= 8 && morefee) // ����� ���̵����� �������� �λ�
	{
		morefee = 0;
		gotoxy(12, 6);	printf("%s�밡 �����Ḧ �λ��߽��ϴ�!     ", univ[turn].name);
		Delay(WAIT * 4);
	}


	i = 30; // �ѹ��� ���� �ִ� �⺻��

	// ����   ���б� = �⺻�� * (���з��� * 0.7) * (1 + (�ڽ��� ȸ���� ���� �� * 0.25))
	// ����� ���б� = �⺻�� * ���з��� * (1 + (�ڽ��� ȸ���� ���� �� * 0.70))
	if (difficulty == GAME_EASY)
		need = (int) (i * ((double) univ[turn].level * 0.7) * (1 + (double) player[turn].round * 0.25));
	else if (difficulty == GAME_HARD)
		need = (int) (i * univ[turn].level * (1 + (double) player[turn].round * 0.70));
	gotoxy(12, 6);	printf("�ѹ����� ���� %d����°�Դϴ�!     ", player[turn].round);
	gotoxy(12, 7);	printf("���б� %d������ �޾ҽ��ϴ�.       ", need);
	player[turn].money += need;
	Delay(WAIT);

	if (player[turn].money < 0) // ���̳ʽ� �����̶��?
	{
		double ftmp = 1.1; // ������
		player[turn].money = (int) (player[turn].money * ftmp); // ���ڰ� �������� ���� ��
		gotoxy(11, 6);	printf("���̳ʽ� ���忡�� ���ڸ� ����ϴ�!");
		gotoxy(11, 7);	printf("���� : %d����                 ", (int) (player[turn].money / 11));

	}
	Delay(WAIT);
	gotoxy(11, 6);	printf("                                    ");
	gotoxy(11, 7);	printf("                                    ");
	SIO_PrtInfo(player, univ); // ��, ���� ��Ȳ �ٽ� ǥ��
}

void ML_BuyCity(int turn, int nowpos, PLAYER player[], UNIV univ[])  // �ǹ� ����
{
	int key = 0, need = 0;

	// �Ǽ���� = �Ǽ��� * (1 + (�ڽ��� ȸ���� ���� �� * 0.20))
	need = (int) ((double) board[nowpos].cost * (1 + (double) player[turn].round * 0.20));
	SIO_TurnColor(turn);
	if (player[turn].money < need) // ���̳ʽ��̰ų�, ���� ����
	{
		gotoxy(12, 6);	printf("���� �����մϴ�!                   ");
		gotoxy(12, 7);	printf("%s��(��) ���� �� �����ϴ�.", CityName(turn, nowpos));
	}
	else
	{
		if (turn == P1) // ���� (�÷��̾�)
		{
			gotoxy(12, 6);	printf("%s��(��) �����ðڽ��ϱ�?   ", CityName(turn, nowpos));
			gotoxy(12, 7);	printf("                                   ");
			gotoxy(12, 7);	printf("��� : %d���� [Y/N] ", need);

			do{
			key = getch();
			}while(key == 'Y' || key == 'y' || key == 'N' || key == 'n');
		}
		else if (turn == P2) // ����� (AI)
		{
			gotoxy(12, 6);	printf("                                   ");
			gotoxy(12, 7);	printf("                                   ");
			key = 'Y';
		}


		if (key == 'Y' || key == 'y') // ����
		{
			board[nowpos].level = 0;
			board[nowpos].owner = turn;
			player[turn].money -= need;
			univ[turn].city_count++;
			SIO_PrtInfo(player, univ);

			SIO_TurnColor(turn);
			gotoxy(12, 6);	printf("%s��(��) �������ϴ�!        ", CityName(turn, nowpos));
			gotoxy(12, 7);	printf("��� : %d����                ", need);
			strcpy(board[nowpos].name, CityName(turn, nowpos));
		}
	}
	Delay(WAIT);
}

void ML_UpgradeCity(int turn, int nowpos, PLAYER player[], UNIV univ[])  // �ǹ� ���׷��̵�
{
	int key = 0, need = 0;

	SIO_TurnColor(turn);
	// ������ = �Ǽ��� + (������ ���� + 1) * (1 + (�ڽ��� ȸ���� ���� �� * 0.20))
	need = (int) ((double) board[nowpos].cost * (board[nowpos].level + 2) * (1 + (double) player[turn].round * 0.20));
	if (player[turn].money < need) // ���̳ʽ��̰ų�, ���� ����
	{
		gotoxy(11, 6);	printf("���� �����մϴ�!                    ");
		gotoxy(11, 7);	printf("%s��(��) ������ �� �����ϴ�.", CityName(turn, nowpos));
	}
	else
	{
		if (turn == P1) // ���� (�÷��̾�)
		{
			gotoxy(11, 6);	printf("%s��(��) �����Ͻðڽ��ϱ�? ", CityName(turn, nowpos));
			gotoxy(11, 7);	printf("                                    ");
			gotoxy(11, 7);	printf("��� : %d���� [Y/N] ", need);

			key = getch();
		}
		else if (turn == P2) // ����� (AI)
		{
			gotoxy(11, 6);	printf("                                    ");
			gotoxy(11, 7);	printf("                                    ");
			key = 'Y';
		}

		if (key == 'Y' || key == 'y') // ���׷��̵�
		{
			board[nowpos].level++;
			board[nowpos].owner = turn;
			player[turn].money -= need;

			gotoxy(11, 6);	printf("%s��(��) �����Ͽ����ϴ�!  ", CityName(turn, nowpos));
			gotoxy(11, 7);	printf("��� : %d����                 ", need);
		}
	}
	Delay(WAIT);
}

void ML_PayLessonFee(int turn, int nowpos, PLAYER player[], UNIV univ[])	// ������ ����
{
	int need = 0;

	SIO_TurnColor(turn);
	if (turn == P1) // ������ �� ���� ���
	{
		gotoxy(12, 6);	printf("������ ������ ������ϴ�!    ");
	}
	else if (turn == P2) // ������� �� ���� ���
	{
		gotoxy(12, 6);	printf("����� ������ ������ϴ�!    ");
	}

	// ������ ����
	// ���� ������ = �ǹ� ���� x (���� ����) x (1 + (������ ȸ���� ���� �� * 0.10))
	// ����� ������ = (�ǹ� ���� x (1 + ���� ����)^ (1 + ������ ȸ���� ���� �� / 32))
	if (difficulty == GAME_EASY) // ����
	{
		if (board[nowpos].level == 0) // �ǹ� ������ ���� ������
			need = 5;
		else if (board[nowpos].level == 1)
			need = 15;
		else if (board[nowpos].level == 2)
			need = 30;
		else if (board[nowpos].level == 3) // Ǯ��
			need = 50;
		need = (int) ((double) need * univ[board[nowpos].owner].level * (1 + (double) player[board[nowpos].owner].round * 0.10)); // ������ ���� ����
	}
	else if (difficulty == GAME_HARD) // �����
	{
		if (player[board[nowpos].owner].round < 8)
		{
			if (board[nowpos].level == 0) // �ǹ� ������ ���� ������
				need = 5;
			else if (board[nowpos].level == 1)
				need = 20;
			else if (board[nowpos].level == 2)
				need = 40;
			else if (board[nowpos].level == 3) // Ǯ��
				need = 60;
		}
		else
		{
			if (board[nowpos].level == 0) // �ǹ� ������ ���� ������
				need = 40;
			else if (board[nowpos].level == 1)
				need = 60;
			else if (board[nowpos].level == 2)
				need = 80;
			else if (board[nowpos].level == 3) // Ǯ��
				need = 100;
		}

		need = (int) pow(((double) need * (1 + univ[board[nowpos].owner].level)), (1 + (double) player[board[nowpos].owner].round / 32)); // ������ ���� ����
	}

	player[turn].money -= need;
	univ[board[nowpos].owner].money += need;
	gotoxy(12, 7);	printf("                                   ");
	gotoxy(12, 7);  printf("������ %d������ �����մϴ�.", need);
	Delay(WAIT * 2);
	gotoxy(12, 7);	printf("                                   ");
}

void ML_Ending(PLAYER player[], UNIV univ[])	// ���� �Ǵ�
{
	int i = 0, cmp_money[2] = {0, 0}, win = 0;
	char stmp[2][32];
	stmp[P1][0] = '\0';
	stmp[P2][0] = '\0';

	SIO_PrtInfo(player, univ); // ���� ����
// ���� ����. y�� ��� ������ ���� ����ؼ� Enter �Է¹ޱ�
	SIO_TurnColor(NEUTRAL);
	gotoxy(12, 6);	printf("������ �������ϴ�!            ");
	gotoxy(12, 7);	printf("EnterŰ�� ���� �ּ���...      ");
	gotoxy(12, 9);	while (getchar() != '\n');

// ������ �ؾ� �Ѵ�.
	if (difficulty == GAME_EASY) // ���̵� ����
	{
		for (i = P1; i <= P2; i++)
		{// �л��� ���� ���� ������ �װ� �б� ������ ����
			if (player[i].money < 0)
				cmp_money[i] = univ[i].money + player[i].money; // += �ϴ� ������ player[i].money�� ������
			else
				cmp_money[i] = univ[i].money;
		}
		strcpy(stmp[P1], "������б� : ");
		strcpy(stmp[P2], "�������б� : ");

		if (cmp_money[P1] > cmp_money[P2]) // ����� �¸�!
			win = GAME_WIN;
		else if (cmp_money[P1] == cmp_money[P2]) // �Ͼ ���� ��������, ���
			win = GAME_DRAW;
		else // if (cmp_money[P1] < cmp_money[P2]) // ������ �¸�
			win = GAME_LOSE;
	}
	else if (difficulty == GAME_HARD) // ���̵� �����
	{
		for (i = P1; i <= P2; i++)
		{
			if (player[i].money < 0) // �л��� ���� ���� ������ �ݿ�
				cmp_money[i] = player[i].money * -1;
			else // ���� ������ ���
				cmp_money[i] = 0;
		}
		strcpy(stmp[P1], "������ �� : ");
		strcpy(stmp[P2], "������� �� : ");

		if (cmp_money[P1] < cmp_money[P2]) // ���� �� ��� ����� �¸�!
			win = GAME_WIN;
		else if (cmp_money[P1] == cmp_money[P2]) // �Ͼ ���� ��������, ���
			win = GAME_DRAW;
		else // if (cmp_money[P1] > cmp_money[P2]) // ������ �¸�
			win = GAME_LOSE;
	}


// ���и� ������
    if (win == GAME_WIN) // ����� �¸�!
    {
    	gotoxy(12, 6);	SIO_TurnColor(P1);	printf(stmp[P1]);	SIO_TurnColor(P1_SEMI);	printf("%6d����       ", cmp_money[P1]);
    	gotoxy(12, 7);	SIO_TurnColor(P1);	printf(stmp[P2]);	SIO_TurnColor(P1_SEMI);	printf("%6d����       ", cmp_money[P2]);
    	gotoxy(12, 9);	SIO_TurnColor(P1_SEMI);	printf("������б��� �¸��Դϴ�!         ");
    	gotoxy(12, 10);	SIO_TurnColor(P1_SEMI);	printf("�����մϴ�!                      ");
    	SIO_TurnColor(P1);
    }
    else if (win == GAME_DRAW) // �Ͼ ���� ��������, ���
    {
    	SIO_TurnColor(NEUTRAL);
    	gotoxy(12, 6);	printf("%s : %6d����      ", stmp[P1], cmp_money[P1]);
    	gotoxy(12, 7);	printf("%s : %6d����      ", stmp[P2], cmp_money[P2]);
    	gotoxy(12, 9);	printf("(�Ͼ �� ���� �������ٵ�...)   ");
    	gotoxy(12, 10);	printf("�����ϴ�!                      ");
    }
    else // if (win == GAME_LOSE) // ������ �¸�
    {
    	gotoxy(12, 6);	SIO_TurnColor(P2);	printf(stmp[P1]);	SIO_TurnColor(P2_SEMI);	printf("%6d����       ", cmp_money[P1]);
    	gotoxy(12, 7);	SIO_TurnColor(P2);	printf(stmp[P2]);	SIO_TurnColor(P2_SEMI);	printf("%6d����       ", cmp_money[P2]);
    	gotoxy(12, 9);	SIO_TurnColor(P2_SEMI);	printf("��ī��ī! �ƶ�Ī �ƶ���...       ");
    	gotoxy(12, 10);	SIO_TurnColor(P2_SEMI);	printf("�й��Ͽ����ϴ�......             ");
    	SIO_TurnColor(P2);
    }
	gotoxy(12, 13);	printf("              The End              ");
	gotoxy(12, 15);	printf("     Press any key to exit...");
	getch();
}


void ML_PrintStory()
{
	char* story[6] = {
"���� 2300��...\n��ǳ [[������;;]]�� �������� ����\n����� ������ ���ǻ��� ��������."
,
"�дп� ���� ���������� ���� �������� �Ի��� �������,\n������ ������ ���� �Ȱ� �ȴ�."
,
"\"�ѱ� ��ž ���б��� �ڸ��� �ٷ� ����!\"\n-������б� ���� ��ó����"
,
"\"�׷� ����, ����б��� ���������� �߳����� �� ����´ٰ�!\n-�������б� ���� ???"
,
"�ѱ� ��ž ���б��� �ڸ��� ����,\n�� ������ ��Ȱ�� �� ������ ���۵ȴ�!"
,
" - ������ ���� - "
	};

	int i;

	for(i=0; i<6; i++)
	{
		SIO_PrintMsg(story[i]);
		printf("\n\n    >>����");
		getch();
		system("CLS");
	}

}