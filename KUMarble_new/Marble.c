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
	int turn, key;
	int i, loopin,  around, nowpos;
	PLAYER player[PLAYER_NUMBER];
//	CITY city[CITY_NUMBER];
	UNIV univ[PLAYER_NUMBER];

//���� �ʱ�ȭ
	turn = 0; // �÷��̾� turn�� ��
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
		InitCityStruct(&board[i], i);

// ���� ���� ����
	turn = 0;
	loopin = 1;
	timepass = clock();
	while (loopin)
	{
		system("cls");
// �ʱ�ȭ
		SIO_InitBoard();		  // ���带 �׸���
		SIO_DrawBoard();		  // �ǹ��� ĥ�Ѵ�
		SIO_PrtPlayer(player);	  // ���� �׸���.
		SIO_PrtInfo(player, univ);// �� ��Ȳ ǥ��
		SIO_PrtLogo(univ);		  //���� ��Ȳ ǥ��
		//SIO_PrtMinigameBase();

		// ���� �ΰ� ���� �˻�
		ML_UnivLevelUp(turn, player, univ);
		SIO_TurnColor(turn);

		if(player[turn].goza > 0)
		{
			gotoxy(12,6);	printf("�̹� ���� �������� �����ϴ�.");
			player[turn].goza--;
			if(player[turn].goza == 0)
			{
				gotoxy(12,7);	printf("���� �Ϻ��� Ȱ�� �����մϴ�.");
			}
			else
			{
				gotoxy(12,7);	printf("%d�� �� ����� �մϴ�.", player[turn].goza);
			}
			Delay(WAIT * 2);
		}
		else
		{
			key = ML_ThrowDice(turn, player[turn].dice_limit--); // �ֻ����� ������
			if (key == QUIT_ESC) // ����
				return;
			else if (key == CHEAT) // ġƮ
			{
				player[turn].money += 300; // ���� �����ְ�
				SIO_PrtInfo(player, univ); // ���� ����
			}
	#ifdef DEBUG
		key = 6;
	#endif

	// �÷��̾ �̵��Ѵ�
			around = SIO_MovePlayerEffect(&player[turn], turn, key);
			gotoxy(14, 8); printf("   ");
			if (around) // �ѹ��� ������ ��� (= ������ ������ ���)
				ML_RoundMoney(turn, player, univ); // ���б� ����

	// �� ���� or ������ ���Ա�
	// Ȳ�ݿ��� process ����
			nowpos = player[turn].pos;

			if(strcmp(board[nowpos].name, GOLDEN_KEY) == 0)
			{ // Ȳ�ݿ��� ĭ�� ����� ���
				ML_ProcessGoldenKey(turn, nowpos, player, univ);
			}
			else if(IsSpecialCity(nowpos) != 0)
			{
				ML_ProcessSpecial(turn, nowpos, player, univ);
			}
			else if (board[nowpos].owner == -1 && IsSpecialCity(nowpos) == 0)
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
		}
		turn = ML_ChangeTurn(turn); // ���ʸ� �ٲ��ش�

		if (player[P1].round > 16 || player[P2].round > 16 || univ[P1].level == 5 || univ[P2].level == 5) // ���� ���� ���� - 16������ ���ƾ� �Ѵ�. �Ǵ� ���� ������ 5�� �Ǹ� �¸��Ѵ�
			loopin = 0;
	}
	ML_Ending(player, univ); // ���� �Ǵ�
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

void InitCityStruct (CITY* city, const int pos)
{
	char* temp_name = IsSpecialCity(pos);
	city->cost = 0;
	city->name[0] = '\0';
	if(temp_name != '\0')
	{//�߸� �ǹ��� ���������� �̸� �̸� ���
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

char* IsSpecialCity(int city) // �߸� �����̶�� �̸��� ��ȯ
{
	switch (city)
	{
	case 0: // ������
		return "START";
	case 8: // Ȳ�ݿ���
	case 15: // Ȳ�ݿ���
	case 20: // Ȳ�ݿ���
		return GOLDEN_KEY;
	case 6: // ���п� (�𼭸�)
		return ACADEMY;
	case 18: // ��Ƽ (�𼭸�)
		return MT;
	case 12: // ���� (�𼭸�)
		return HOSPITAL;
	default:
		return '\0';
	}
}

void PrtBasic()
{ //�⺻Ʋ
	gotoxy(12,14); printf("  ��  ��");
	gotoxy(12,15); printf("����  ����");
	gotoxy(12,16); printf("��      ��");
	gotoxy(12,17); printf("��      ��");
	gotoxy(12,18); printf("���ܡܡܦ�");
	gotoxy(12,19); printf("���ܡܡܦ�");
	gotoxy(12,20); printf("����������");
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
		{ //Ʋ�ȿ� �� ������ ���
			x = RandNum(14,18);
			y = RandNum(16,19);
			gotoxy(x,y); printf("��");
		}
		Sleep(50);
		gotoxy(12,16); printf("��      ��"); //�����
		gotoxy(12,17); printf("��      ��");
		gotoxy(12,18); printf("��      ��");
		gotoxy(12,19); printf("��      ��");
	}
	Sleep(75);
	gotoxy(12,14); printf("  ��  ��");//�⺻Ʋ���
	gotoxy(12,15); printf("�����ܦ���");
	gotoxy(12,16); printf("��      ��");
	gotoxy(12,17); printf("��   �� ��");
	gotoxy(12,18); printf("����    ��");
	gotoxy(12,19); printf("�� �� �ܦ�");
	gotoxy(12,20); printf("����������");


	Sleep(75);
	gotoxy(12,14); printf("  ���ܦ�");//�⺻Ʋ���
	gotoxy(12,15); printf("����  ����");
	gotoxy(12,16); printf("��      ��");
	gotoxy(12,17); printf("��   �� ��");
	gotoxy(12,18); printf("����    ��");
	gotoxy(12,19); printf("�� �� �ܦ�");
	gotoxy(12,20); printf("����������");

	Sleep(75);
	gotoxy(16,12); printf("��");
	gotoxy(12,14); printf("  ��  ��");//�⺻Ʋ���
	gotoxy(12,15); printf("����  ����");
	gotoxy(12,16); printf("��      ��");
	gotoxy(12,17); printf("��   �� ��");
	gotoxy(12,18); printf("����    ��");
	gotoxy(12,19); printf("�� �� �ܦ�");
	gotoxy(12,20); printf("����������");

	Sleep(75);
	gotoxy(16,12); printf("��");
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
		case 1: printf("��"); break;
		case 2: printf("��"); break;
		case 3: printf("��"); break;
		case 4: printf("��"); break;
		case 5: printf("��"); break;
		case 6: printf("��"); break;
		case 7: printf("��"); break;
		case 8: printf("��"); break;
		case 9: printf("��"); break;
		case 10: printf("��"); break;
		case 11: printf("��"); break;
		case 12: printf("��"); break;
	}
	return dice;
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
			SIO_PrtLogo(univ);
			Delay(WAIT * 2);
		}
		lastuniv[i] = univ[i].level;
	}
}

int ML_ThrowDice(int turn, int dice_limit) // �ֻ��� ������
{
	int key = 0;
	if (turn == P1)
	{
		gotoxy(12, 6);	printf("���� �����Դϴ�!                 ");
		gotoxy(12, 7);	printf("�ֻ����� ��������.                 ");
		gotoxy(12, 8);	printf("Press any key to continue...");
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

void ML_RoundMoney(int turn, PLAYER player[], UNIV univ[]) // �� ���� ���� �ִ� ���б�
{
	int need = 0;
	static int morefee[2] = {1, 1};

	player[turn].round++; // ���� ī��Ʈ �ø���
	if (difficulty == GAME_HARD && player[turn].round >= 8 && morefee[turn]) // ����� ���̵����� �������� �λ�
	{
		morefee[turn] = 0;
		gotoxy(12, 6);	printf("%s�밡 �����Ḧ �λ��߽��ϴ�!     ", univ[turn].name);
		gotoxy(12, 7);	printf("                                    ");
		Delay(WAIT * 4);
	}

	// ����   ���б� = �⺻�� * (���з��� * 0.7) * (1 + (�ڽ��� ȸ���� ���� �� * 0.25))
	// ����� ���б� = �⺻�� * ���з��� * (1 + (�ڽ��� ȸ���� ���� �� * 0.70))
	if (difficulty == GAME_EASY)
		need = (int) (MONEY_BASE * ((double) univ[turn].level * 0.7) * (1 + (double) player[turn].round * 0.25));
	else if (difficulty == GAME_HARD)
		need = (int) (MONEY_BASE * univ[turn].level * (1 + (double) player[turn].round * 0.70));
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
	SIO_PrtLogo(univ);
}

void ML_BuyCity(int turn, int nowpos, PLAYER player[], UNIV univ[])  // �ǹ� ����
{
	int key = 0, need = 0;

	// �Ǽ���� = �Ǽ��� * (1 + (�ڽ��� ȸ���� ���� �� * 0.20))
	need = (int) ((double) ML_CityCost(turn, nowpos) * (1 + (double) player[turn].round * 0.20));
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
			}while(key != 'Y' && key != 'y' && key != 'N' && key != 'n');
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
			SIO_PrtLogo(univ);

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
	need = (int) ((double) ML_CityCost(turn, nowpos) * (board[nowpos].level + 2) * (1 + (double) player[turn].round * 0.20));
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

			do{
				key = getch();
			}while(key != 'Y' && key != 'y' && key != 'N' && key != 'n');
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

	system("cls");
	SIO_InitBoard();		  // ���带 �׸���
	SIO_DrawBoard();		  // �ǹ��� ĥ�Ѵ�
	SIO_PrtPlayer(player);	  // ���� �׸���.
	SIO_PrtInfo(player, univ);// �� ��Ȳ ǥ��
	SIO_PrtLogo(univ);		  //���� ��Ȳ ǥ��
// ���� ����. y�� ��� ������ ���� ����ؼ� Enter �Է¹ޱ�
	SIO_TurnColor(NEUTRAL);
	gotoxy(12, 6);	printf("������ �������ϴ�!             ");
	gotoxy(12, 7);	printf("EnterŰ�� ���� �ּ���...       ");
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
    	gotoxy(12, 9);	SIO_TurnColor(P1_SEMI);	printf("����밡 �����븦 �μ��߽��ϴ�!  ");
    	gotoxy(12, 10);	SIO_TurnColor(P1_SEMI);	printf("����� ����ķ�۽��� ź���߽��ϴ�.");
    	gotoxy(12, 13);	printf("              You Win              ");
    	SIO_TurnColor(P1);
    }
    else if (win == GAME_DRAW) // �Ͼ ���� ��������, ���
    {
    	SIO_TurnColor(NEUTRAL);
    	gotoxy(12, 6);	printf("%s : %6d����      ", stmp[P1], cmp_money[P1]);
    	gotoxy(12, 7);	printf("%s : %6d����      ", stmp[P2], cmp_money[P2]);
    	gotoxy(12, 9);	printf("�ºθ� ������ ���߽��ϴ�.        ");
    	gotoxy(12, 10);	printf("�����ϴ�!                      ");
    	gotoxy(12, 13);	printf("              The End              ");
    }
    else // if (win == GAME_LOSE) // ������ �¸�
    {
    	gotoxy(12, 6);	SIO_TurnColor(P2);	printf(stmp[P1]);	SIO_TurnColor(P2_SEMI);	printf("%6d����       ", cmp_money[P1]);
    	gotoxy(12, 7);	SIO_TurnColor(P2);	printf(stmp[P2]);	SIO_TurnColor(P2_SEMI);	printf("%6d����       ", cmp_money[P2]);
    	gotoxy(12, 9);	SIO_TurnColor(P2_SEMI);	printf("�����밡 ����븦 �μ��Ͽ����ϴ�.");
    	gotoxy(12, 10);	SIO_TurnColor(P2_SEMI);	printf("�й��Ͽ����ϴ�...                ");
    	gotoxy(12, 13);	printf("              You Lose             ");
    	SIO_TurnColor(P2);
    }
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
"\"�׷� ����, ����б��� ���������� �߳����� �� ����´ٰ�!\n-�������б� ���� ������"
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

int ML_CityCost (int whatuniv, int pos)
{
	int cost = 0;
	if (whatuniv == P1)
	{
		switch (pos) // ��� ��� �ǹ��� ���� ������ ���⼭
		{
		case 14: // �Ͻ�
		case 21: // �����
			cost = 30;
			break;
		case 9: // ȭ��
			cost = 20;
			break;
		default: // ������ ��� �ǹ�
			cost = 10;
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
			cost = 30;
			break;
		default: // ������ ���� �ǹ�
			cost = 10;
			break;
		}
	}
	return cost;
}

void ML_ProcessGoldenKey(int turn, int nowpos, PLAYER player[], UNIV univ[])
{
	int amount = 0, rValue, i, loopin = 1;
	const char* wildlife_name[4] = {"õ�� �信�� ������ ����ȯ��", "��Ƣ �����ô� ���� ��������", "��û��û(������ �˰���?)��", "2�� ����� ������ 3������"};
	const char* univ_name[2] = {"���", "����"};
	gotoxy(12, 6);

	switch(rand()%5) //rand()%5
	{

	case 0:		//�����(�߻��� ������� ������!)
		gotoxy(11,6); printf("%s ������!", wildlife_name[rand()%4]);
		gotoxy(11,7); printf("������ ������ �ؼ� �̱�ٸ�");
		gotoxy(11,8); printf("ġ������ �� ����.");
		ML_ChamChamCham(turn, player, univ);
		break;
	case 1:		//���б� �ޱ�
		// ����   ���б� = �⺻�� * (���з��� * 0.7) * (1 + (�ڽ��� ȸ���� ���� �� * 0.25)) * (0.5~3.0 ����)
		// ����� ���б� = �⺻�� * ���з��� * (1 + (�ڽ��� ȸ���� ���� �� * 0.70)) * (0.5~3.0 ����)
		if (difficulty == GAME_EASY)
			amount = (int) (MONEY_BASE * ((double) univ[turn].level * 0.7) * (1 + (double) player[turn].round * 0.25) * (RandNum(1, 6) / 2.0));
		else if (difficulty == GAME_HARD)
			amount = (int) (MONEY_BASE * univ[turn].level * (1 + (double) player[turn].round * 0.70) * (RandNum(1, 6) / 2.0));
						printf("%s���� ������ ���� A+�� �޾�", univ_name[turn]);
		gotoxy(12,7);	printf("���б� %d������ �־������ϴ�.", amount);
		player[turn].money += amount;
		break;
	case 2:		//������ ������ ���� �Ǵ� ä��
		// ������ ����
		// ���� ������ = ((5~30 ����) * (���� ����) x (1 + (������ ȸ���� ���� �� * 0.10)
		// ����� ������ = ((5~30 or 40~60 ����) * (1 + ���� ����))^(1 + ������ ȸ���� ���� �� / 32)
		if (difficulty == GAME_EASY)
			amount = (int) ((double) RandNum(5, 30) * univ[ML_ChangeTurn(turn)].level * (1 + (double) player[ML_ChangeTurn(turn)].round * 0.10)); // ������ ���� ����
		else if (difficulty == GAME_HARD)
		{
			if (player[ML_ChangeTurn(turn)].round < 8) // ������ �λ� ��
				i = RandNum(5, 30);
			else // ������ �λ� ��
				i = RandNum(40, 60);
			amount = (int) pow(((i / 2.0) * univ[ML_ChangeTurn(turn)].level), (1 + (double) player[ML_ChangeTurn(turn)].round / 32));
		}
		SIO_TurnColor(turn); 
		if(turn == P1)
		{
						  printf("ä���� ������ϴ�!             ");
			gotoxy(12,7); printf("������� ���� ���             ");
			gotoxy(12,8); printf("%d������ ���������ϴ�.", amount);
			player[P1].money -= amount;
			player[P2].money += amount;
		}
		else if(turn == P2)
		{
						  printf("������ ������ ������ ������ϴ�!");
			gotoxy(12,7); printf("������ ���� ���              ");
			gotoxy(12,8); printf("%d������ �������ϴ�.         ", amount);
			player[P1].money += amount;
			player[P2].money -= amount;
		}

		break;

	case 3:		//��ǳ���� �ǹ� �������� �̺�Ʈ
						  printf("��ǳ ������;;�� �б��� ���ƽ��ϴ�!");
			gotoxy(12,7); printf("�ǹ� �ϳ��� �ı��˴ϴ�.");
			rValue = rand()%2;

			if (rValue == 0)		//�� ��� �� �ϳ��� ������� �ǹ� �����ϰ� ����
			{
				for (i=0; i < 24 && loopin; i++)
				{
					if (board[i].owner == turn && board[i].level > -1)
					{
						if(board[i].level == 0)		//�ǹ� ����
						{
							InitCityStruct(&board[i], i); 
							univ[turn].city_count--;
						}
						else
						{
							board[i].level--;
						}
						gotoxy(12,9); printf("%s��(��) �ı��Ǿ����ϴ�!", CityName(turn, i));
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
						if(board[i].level == 0)		//�ǹ� ����
						{
							InitCityStruct(&board[i], i); 
							univ[turn].city_count--;
						}
						else
						{
							board[i].level--;
						}
						gotoxy(12,9); printf("%s��(��) �ı��Ǿ����ϴ�!", CityName(turn, i));
						loopin = 0;
					}
				}
			}

		break;

	case 4:		//�ǹ� ������� �̺�Ʈ
						  printf("S�� ȸ�翡�� �б��� �������� �־���!");
			gotoxy(12,7); printf("�ǹ� �ϳ��� ���׷��̵�˴ϴ�.");
			rValue = rand()%2;

			if(rValue == 0)		//�� ��� �� �ϳ��� ������� �ǹ� �����ϰ� ����
			{
				for(i=0; i<24 && loopin; i++)
				{
					if(board[i].owner == turn && board[i].level < 3)
					{
						board[i].level++;
						gotoxy(12,9); printf("%s��(��) ����Ǿ����ϴ�!", CityName(turn, i));
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
						gotoxy(12,9); printf("%s��(��) ����Ǿ����ϴ�!", CityName(turn, i));
						loopin = 0;
					}
				}
			}
		break;
	}

	SIO_PrtInfo(player, univ);	//���� ����

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

		case 6: // ���п� (�𼭸�)
			gotoxy(12,6); printf("���п��� �����մϴ�!");
			gotoxy(12,7); printf("���ϴ� ĭ���� �̵��� �� �ֽ��ϴ�.");

			if(turn == P1)
			{
				gotoxy(12,8); printf("���ϴ� ĭ�� ���콺�� Ŭ���� �ּ���.");
				// ������ 24�� ��ư ����
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
							// ������ ��ġ�� �ٽ� �׷���
							SIO_JumpPlayerEffect(&player[P2], P2, player[P2].pos);
							
							SIO_TurnColor(turn);
							gotoxy(12,6); printf("%s(��)�� �̵��մϴ�!", CityName(turn, i));
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
				gotoxy(12,8); printf("%s(��)�� �̵��մϴ�!", CityName(turn, i));
				SIO_JumpPlayerEffect(&player[P2], turn, i);
			}
			break;
		case 18: // ��Ƽ (�𼭸�)
			gotoxy(12,6); printf("MT���� ���� ���ð� �������ϴ�!");
			gotoxy(12,7); printf("3�ϵ��� �ֻ��� ���ڰ� ���ѵ˴ϴ�.");
			player[turn].dice_limit = 2;
			break;
		case 12: // ���� (�𼭸�)
			goza = rand()%2+1;
			gotoxy(12,6); printf("�ƴ�... ���� ���ڶ��!");
			gotoxy(12,7); printf("%d�ϵ��� ������ �� �����ϴ�!", goza);
			player[turn].goza = goza;
			break;
	}

	SIO_PrtInfo(player, univ);	//���� ����
	Delay(WAIT * 2);
}


void ML_ChamChamCham(int turn, PLAYER player[], UNIV univ[])
{
	char ch;
	int cham[2] = {0,};
	int amount;
	SIO_PrtMinigameBase();
	gotoxy(80, 5); printf("������ ����");
	if(turn == P1)
	{
		gotoxy(80, 6); printf("������ A, �������� D");
		gotoxy(80, 7); printf("�����Ϸ��� �ƹ� Ű�� ��������.");
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
	//������ ���
	if(cham[P1] == cham[P2])
	{
		if (difficulty == GAME_EASY)
			amount = (int) (MONEY_BASE * ((double) univ[turn].level * 0.7) * (1 + (double) player[turn].round * 0.25) * (RandNum(1, 6) / 2.0));
		else if (difficulty == GAME_HARD)
			amount = (int) (MONEY_BASE * univ[turn].level * (1 + (double) player[turn].round * 0.70) * (RandNum(1, 6) / 2.0));

		gotoxy(78,25); printf("����.. ���� �̰屺");
		gotoxy(78,26); printf("%d������ �ֵ��� ����.", amount);

		player[turn].money += amount;
		SIO_PrtInfo(player, univ);
	}
	else
	{
		gotoxy(78,26); printf("���� �־��� ���� �ּ���");
		gotoxy(78,26); printf("���� �׳� ����...");
	}

	Delay(WAIT*2);
}