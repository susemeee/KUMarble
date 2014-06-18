#include "Var.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "BasicIO.h"
#include "SurfaceIO.h"
#include "Marble.h"


void SIO_InitBoard ()
{
	SIO_TurnColor(BG);
	printf("����������������������������������������������������������\n"
		   "��      ��      ��      ��      ��      ��      ��      ��\n"
		   "��      ��      ��      ��      ��      ��      ��      ��\n"
		   "��      ��      ��      ��      ��      ��      ��      ��\n"
		   "����������������������������������������������������������\n"
		   "��      ��                                      ��      ��\n"
		   "��      ��                                      ��      ��\n"
		   "��      ��                                      ��      ��\n"
		   "����������                                      ����������\n"
		   "��      ��                                      ��      ��\n"
		   "��      ��                                      ��      ��\n"
		   "��      ��                                      ��      ��\n"
		   "����������                                      ����������\n"
		   "��      ��                                      ��      ��\n"
		   "��      ��                                      ��      ��\n"
		   "��      ��                                      ��      ��\n"
		   "����������                                      ����������\n"
		   "��      ��                                      ��      ��\n"
		   "��      ��                                      ��      ��\n"
		   "��      ��                                      ��      ��\n"
		   "����������                                      ����������\n"
		   "��      ��                                      ��      ��\n"
		   "��      ��                                      ��      ��\n"
		   "��      ��                                      ��      ��\n"
		   "����������������������������������������������������������\n"
		   "��      ��      ��      ��      ��      ��      ��      ��\n"
		   "��      ��      ��      ��      ��      ��      ��      ��\n"
		   "��      ��      ��      ��      ��      ��      ��      ��\n"
		   "����������������������������������������������������������\n");

/*
	printf("01��������������������������������������������������������\n"
		   "��23    ��      ��      ��      ��      ��      ��      ��\n"
		   "�����������Ź����� �Ͻ� �� �뺧 ���̺����������������а���\n"
		   "��    67��      ��      ��      ��      ��      ��      ��\n"
		   "����������������������������������������������������������\n"
		   "��      ��10                                    ��      ��\n"
		   "����������  12                                  �����а���\n"
		   "��      ��    14                                ��      ��\n"
		   "����������      16                              ����������\n"
		   "��      ��        18                            ��      ��\n"
		   "���������          20                          �� ȭ�� ��\n"
		   "��      ��            22                        ��      ��\n"
		   "����������              24                      ����������\n"
		   "��      ��                26                    ��      ��\n"
		   "������禢                  28                  ��â�ǰ���\n"
		   "��      ��                    30                ��      ��\n"
		   "����������                      32              ����������\n"
		   "��      ��                        34            ��      ��\n"
		   "�����а���                          36          ����Ȱ����\n"
		   "��      ��                            38        ��      ��\n"
		   "����������                              40      ����������\n"
		   "��      ��                                42    ��      ��\n"
		   "���������                                  44  ������ķ��\n"
		   "��      ��                                    46��      ��\n"
		   "����������������������������������������������������������\n"
		   "��      ��      ��      ��      ��      ��      ��50    ��\n"
		   "�����п��� �α� �� �߱� �����п��� ���� �� ���� �� ���� ��\n"
		   "��      ��      ��      ��      ��      ��      ��      ��\n"
		   "����������������������������������������������������������\n");
*/

}

void SIO_DrawBoard ()
{
	clock_t time_tmp = clock();

	// �ǹ� ��� ����
	SIO_TurnColor(BG);
	gotoxy(50, 25);	SIO_PrtBuilding(0);	// 0 - 5
	gotoxy(42, 25);	SIO_PrtBuilding(1);
	gotoxy(34, 25);	SIO_PrtBuilding(2);
	gotoxy(26, 25);	SIO_PrtBuilding(3);
	gotoxy(18, 25);	SIO_PrtBuilding(4);
	gotoxy(10, 25);	SIO_PrtBuilding(5);
	gotoxy(2, 25);	SIO_PrtBuilding(6);	// 6 - 11
	gotoxy(2, 21);	SIO_PrtBuilding(7);
	gotoxy(2, 17);	SIO_PrtBuilding(8);
	gotoxy(2, 13);	SIO_PrtBuilding(9);
	gotoxy(2, 9);	SIO_PrtBuilding(10);
	gotoxy(2, 5);	SIO_PrtBuilding(11);
	gotoxy(2, 1);	SIO_PrtBuilding(12);	// 12 - 17
	gotoxy(10, 1);	SIO_PrtBuilding(13);
	gotoxy(18, 1);	SIO_PrtBuilding(14);
	gotoxy(26, 1);	SIO_PrtBuilding(15);
	gotoxy(34, 1);	SIO_PrtBuilding(16);
	gotoxy(42, 1);	SIO_PrtBuilding(17);
	gotoxy(50, 1);	SIO_PrtBuilding(18);	// 18 - 23
	gotoxy(50, 5);	SIO_PrtBuilding(19);
	gotoxy(50, 9);	SIO_PrtBuilding(20);
	gotoxy(50, 13);	SIO_PrtBuilding(21);
	gotoxy(50, 17);	SIO_PrtBuilding(22);
	gotoxy(50, 21);	SIO_PrtBuilding(23);

	// ���� �̸� ���
	gotoxy(50, 26);	SIO_PrtCityName(0);	// 0 - 5
	gotoxy(42, 26);	SIO_PrtCityName(1);
	gotoxy(34, 26);	SIO_PrtCityName(2);
	gotoxy(26, 26);	SIO_PrtCityName(3);
	gotoxy(18, 26);	SIO_PrtCityName(4);
	gotoxy(10, 26);	SIO_PrtCityName(5);
	gotoxy(2, 26);	SIO_PrtCityName(6);	// 6 - 11
	gotoxy(2, 22);	SIO_PrtCityName(7);
	gotoxy(2, 18);	SIO_PrtCityName(8);
	gotoxy(2, 14);	SIO_PrtCityName(9);
	gotoxy(2, 10);	SIO_PrtCityName(10);
	gotoxy(2, 6);	SIO_PrtCityName(11);
	gotoxy(2, 2);	SIO_PrtCityName(12);	// 12 - 17
	gotoxy(10, 2);	SIO_PrtCityName(13);
	gotoxy(18, 2);	SIO_PrtCityName(14);
	gotoxy(26, 2);	SIO_PrtCityName(15);
	gotoxy(34, 2);	SIO_PrtCityName(16);
	gotoxy(42, 2);	SIO_PrtCityName(17);
	gotoxy(50, 2);	SIO_PrtCityName(18);	// 18 - 23
	gotoxy(50, 6);	SIO_PrtCityName(19);
	gotoxy(50, 10);	SIO_PrtCityName(20);
	gotoxy(50, 14);	SIO_PrtCityName(21);
	gotoxy(50, 18);	SIO_PrtCityName(22);
	gotoxy(50, 22);	SIO_PrtCityName(23);

	SIO_TurnColor(CL_BT);

	gotoxy(60, 26);	printf("%d�� %d�� ���", (int) ms2min(time_tmp - timepass), (int) ms2sec(time_tmp - timepass)); // �ð� �帧 ǥ��
	gotoxy(60, 25); printf(" ESC : ����");

	SIO_TurnColor(BG);
	gotoxy(12, 22);
	if (difficulty == GAME_EASY)
		printf("        KUMarble : ����          ");
	else if (difficulty == GAME_HARD)
		printf("     KUMarble : ������ ����      ");
}

void SIO_PrtInfo(const PLAYER *player, const UNIV *univ)
{
	// �ܾ� ��Ȳ
	SIO_TurnColor(P1);
	gotoxy(60, 1);	printf(" ������б�");
	SIO_TurnColor(P1_SEMI);
	gotoxy(60, 2);	printf("%7d����", univ[P1].money);
	gotoxy(60, 3);	printf("%7d����", univ[P1].city_count);

	SIO_TurnColor(P1);
	gotoxy(60, 5);	printf("     ����");
	SIO_TurnColor(P1_SEMI);
	gotoxy(60, 6);	printf("%7d����", player[P1].money);
	gotoxy(60, 7);	printf("%7d����", player[P1].round);

	SIO_TurnColor(P2);
	gotoxy(60, 10);	printf(" �������б�");
	SIO_TurnColor(P2_SEMI);
	gotoxy(60, 11);	printf("%7d����", univ[P2].money);
	gotoxy(60, 12);	printf("%7d����", univ[P2].city_count);

	SIO_TurnColor(P2);
	gotoxy(60, 14);	printf("     �����");
	SIO_TurnColor(P2_SEMI);
	gotoxy(60, 15);	printf("%7d����", player[P2].money);
	gotoxy(60, 16);	printf("%7d����", player[P2].round);
}

void SIO_PrtLogo(const UNIV *univ)
{
	// �ܰ躰 �ΰ�
	SIO_TurnColor(P1);
	gotoxy(76, 0);	printf("������б� Lv%d", univ[P1].level);
	SIO_TurnColor(P1_SEMI);
	if (univ[P1].level == 1)
	{
		gotoxy(78, 1);	printf("  �����                                ");
		gotoxy(78, 2);	printf("  ��������        ..                    ");
		gotoxy(78, 3);	printf("                 .r:                    ");
		gotoxy(78, 4);	printf("                 7,.:                   ");
		gotoxy(78, 5);	printf("                 r:.;:.                 ");
		gotoxy(78, 6);	printf("                :7:...:ri:::            ");
		gotoxy(78, 7);	printf("                XY..,,iE7jLvjv..    ..r,");
		gotoxy(78, 8);	printf("               iv:,riiuPrri:iU.iu7r;iL: ");
		gotoxy(78, 9);	printf("              .::::.::7.EXq1Mvi:.vviu:  ");
		gotoxy(78, 10);	printf("              2qv:,SBu .u2rrj,uO77vP7   ");
		gotoxy(78, 11);	printf("             .i,75i..2::r;B@BZ;5r.1r    ");
		gotoxy(78, 12);	printf("              rr: .: vBG@B::vii7BY      ");
		gotoxy(78, 13);	printf("               ..    .O7ijirk0v;BM      ");
	}
	else if (univ[P1].level == 2)
	{
		gotoxy(78, 1);	printf("  �����           Y$ov:                ");
		gotoxy(78, 2);	printf("  �߿˾߿�        :M$vYzC..     .;Y     ");
		gotoxy(78, 3);	printf("                  Y9;iCb#$$IiivcCI:     ");
		gotoxy(78, 4);	printf("                 vv::7C6$MW#n;IQ$Y      ");
		gotoxy(78, 5);	printf("                .B@X$MY.Wc7CC,ZMn       ");
		gotoxy(78, 6);	printf("                ,9b#U#i:.:QA,.Cb        ");
		gotoxy(78, 7);	printf("          .tb#bno$c  YM;:;IAX@Y         ");
		gotoxy(78, 8);	printf("         ;E;CSX;9$M0. .   ,CUo          ");
		gotoxy(78, 9);	printf("        XEY .in#W#@MM0SZEQE0#$.         ");
		gotoxy(78, 10);	printf("       iM$c:vz#b$QEWMMMMMM@@$Q.         ");
		gotoxy(78, 11);	printf("      :YI$C:tQC7X1Uo7nEbZZZZ2i          ");
		gotoxy(78, 12);	printf("    oEMM,Y1vC2i. ,;vC i86WQCUi          ");
		gotoxy(78, 13);	printf("    ;UQ#YA@MYCZWb7C;CYbMME7oSEo;        ");
	}
	else if (univ[P1].level == 3)
	{
		gotoxy(78, 1);	printf("        ��   ����  ����                  ");
		gotoxy(78, 2);	printf("        ��                               ");
		gotoxy(78, 3);	printf(" K   K    OOOO    RRR                    ");
		gotoxy(78, 4);	printf(" K   K   OO  OO   R  R                   ");
		gotoxy(78, 5);	printf(" K   K   O    O   R   R                  ");
		gotoxy(78, 6);	printf(" K  KK   O    O   R   R                  ");
		gotoxy(78, 7);	printf(" K KK    O    O   R  R                   ");
		gotoxy(78, 8);	printf(" KKK     O    O   RRR                    ");
		gotoxy(78, 9);	printf(" K KK    O    O   R  R                   ");
		gotoxy(78, 10);	printf(" K  KK   O    O   R   R                  ");
		gotoxy(78, 11);	printf(" K   K   O    O   R   R                  ");
		gotoxy(78, 12);	printf(" K   K   OO  OO   R   R                  ");
		gotoxy(78, 13);	printf(" K   K    OOOO    R   R                  ");
	}
	else if (univ[P1].level == 4)
	{
		gotoxy(78, 1);	printf("        ��   ����  ���� ����  ��         ");
		gotoxy(78, 2);	printf("        ��                ��  ��         ");
		gotoxy(78, 3);	printf(" K   K    OOOO    RRR     EEEEE          ");
		gotoxy(78, 4);	printf(" K   K   OO  OO   R  R    E              ");
		gotoxy(78, 5);	printf(" K   K   O    O   R   R   E              ");
		gotoxy(78, 6);	printf(" K  KK   O    O   R   R   E              ");
		gotoxy(78, 7);	printf(" K KK    O    O   R  R    E              ");
		gotoxy(78, 8);	printf(" KKK     O    O   RRR     EEEEE          ");
		gotoxy(78, 9);	printf(" K KK    O    O   R  R    E              ");
		gotoxy(78, 10);	printf(" K  KK   O    O   R   R   E              ");
		gotoxy(78, 11);	printf(" K   K   O    O   R   R   E              ");
		gotoxy(78, 12);	printf(" K   K   OO  OO   R   R   E              ");
		gotoxy(78, 13);	printf(" K   K    OOOO    R   R   EEEEE          ");
	}
	else if (univ[P1].level >= 5)
	{
		gotoxy(78, 1);	printf("        ��   ����  ���� ����  �� ||      ");
		gotoxy(78, 2);	printf("        ��                ��  �� ``      ");
		gotoxy(78, 3);	printf(" K   K    OOOO    RRR     EEEEE      A   ");
		gotoxy(78, 4);	printf(" K   K   OO  OO   R  R    E         A A  ");
		gotoxy(78, 5);	printf(" K   K   O    O   R   R   E        A   A ");
		gotoxy(78, 6);	printf(" K  KK   O    O   R   R   E       A     A");
		gotoxy(78, 7);	printf(" K KK    O    O   R  R    E       A     A");
		gotoxy(78, 8);	printf(" KKK     O    O   RRR     EEEEE   AAAAAAA");
		gotoxy(78, 9);	printf(" K KK    O    O   R  R    E       A     A");
		gotoxy(78, 10);	printf(" K  KK   O    O   R   R   E       A     A");
		gotoxy(78, 11);	printf(" K   K   O    O   R   R   E       A     A");
		gotoxy(78, 12);	printf(" K   K   OO  OO   R   R   E       A     A");
		gotoxy(78, 13);	printf(" K   K    OOOO    R   R   EEEEE   A     A");
	}
/*
�����

40*15�� �´� �׸��� ���.. �ϴ� KOREA ���ڷ�..
*/
	SIO_TurnColor(P2);
	gotoxy(76, 14);	printf("�������б� Lv%d", univ[P2].level);
	SIO_TurnColor(P2_SEMI);
	if (univ[P2].level == 1)
	{
		gotoxy(80, 15);	printf("                                       ");
		gotoxy(80, 16);	printf("    7a808r       ����                  ");
		gotoxy(80, 17);	printf("  2WMMBBMMM:      ±±                 ");
		gotoxy(80, 18);	printf("ZMMM8;i:X@MMi                          ");
		gotoxy(80, 19);	printf("r:i@Z   ..SMW                          ");
		gotoxy(80, 20);	printf("    Z,.,,SZZB8i                        ");
		gotoxy(80, 21);	printf("    i:;Z@ZZSZBB@WX,                    ");
		gotoxy(80, 22);	printf("    ii:8MBBBBW0WMMM@S:                 ");
		gotoxy(80, 23);	printf("     i:,X;7ZWB0Z8ZSZ@MWr               ");
		gotoxy(80, 24);	printf("     ,: X@MW80028B8Za8WMMZ,            ");
		gotoxy(80, 25);	printf("      ;:.,i;772SaZ000Z80@MM02a27;:     ");
		gotoxy(80, 26);	printf("       8@SiXXZZZ882Z8B82Xr7ri7Xa8@MMMM ");
		gotoxy(80, 27);	printf("      :MMMW00WMMMM@X,              :S0 ");
		gotoxy(80, 28);	printf("        :i0S @B:                       ");
		gotoxy(80, 29);	printf("        i :;i.                         ");
	}
	else if (univ[P2].level == 2)
	{
		gotoxy(80, 15);	printf("                     iir               ");
		gotoxy(80, 16);	printf("         �ߵѱ�    iOU8@L_             ");
		gotoxy(80, 17);	printf("       ��������    @PXB1               ");
		gotoxy(80, 18);	printf("                  MOkF@r               ");
		gotoxy(80, 19);	printf("                 0O22F8Z               ");
		gotoxy(80, 20);	printf("                :2uL55EB,              ");
		gotoxy(80, 21);	printf("             ..,:.iu1qO@B              ");
		gotoxy(80, 22);	printf("         :E: ,:i::ir7jZB@              ");
		gotoxy(80, 23);	printf("      ::BLBB ,iriivjjL2@:              ");
		gotoxy(80, 24);	printf("  :SBB@7@X.O@UL7uJ1uPB@r               ");
		gotoxy(80, 25);	printf("  0@B@B@B@BYXMEG8S5GMS                 ");
		gotoxy(80, 26);	printf(" 7@2;.:i:7XOXr;i;7ri                   ");
		gotoxy(80, 27);	printf("            :: ir.                     ");
		gotoxy(80, 28);	printf("             :;'i                      ");
		gotoxy(80, 29);	printf("             :; i                      ");
	}
	else if (univ[P2].level == 3)
	{
		gotoxy(80, 15);	printf("                             ");
		gotoxy(80, 16);	printf("                             ");
		gotoxy(80, 17);	printf("         ������              ");
		gotoxy(80, 18);	printf("   m      ����               ");
		gotoxy(80, 19);	printf("   MM               m        ");
		gotoxy(80, 20);	printf("   MMM            MMM        ");
		gotoxy(80, 21);	printf("    aMMM:       MMMM         ");
		gotoxy(80, 22);	printf("      BMMS,,rBMMMMM          ");
		gotoxy(80, 23);	printf("      rM@MM@MMMMM            ");
		gotoxy(80, 24);	printf("    @MMMMMMaMM@@MBi.ii:      ");
		gotoxy(80, 25);	printf("   SMi   XS0MM@BWMMMM        ");
		gotoxy(80, 26);	printf("           aMM888MM          ");
		gotoxy(80, 27);	printf("         irWS;aWM            ");
		gotoxy(80, 28);	printf("        ZM. X;M8             ");
		gotoxy(80, 29);	printf("        :.   @               ");
	}

	else if (univ[P2].level == 4)
	{
		gotoxy(80, 15);	printf("                             ");
		gotoxy(80, 16);	printf("  x     ���ƺ���             ");
		gotoxy(80, 17);	printf("  W8     ������       x      ");
		gotoxy(80, 18);	printf("  MMa                aM      ");
		gotoxy(80, 19);	printf("   MM0             wMMW      ");
		gotoxy(80, 20);	printf("   .MM@          aMMMa:      ");
		gotoxy(80, 21);	printf("     aMM:       MMMMM;       ");
		gotoxy(80, 22);	printf("      BMMS,,rBMMMMM0         ");
		gotoxy(80, 23);	printf("      rM@MM@MMMMMW;          ");
		gotoxy(80, 24);	printf("    @MMMMMMaMM@@MBi.ii:,,iXZ:");
		gotoxy(80, 25);	printf("   MMMWX7XS0MM@BWMMMMMMMMMMZ ");
		gotoxy(80, 26);	printf("  SMi      aMM888MMM@WMM@8   ");
		gotoxy(80, 27);	printf("      2@@irWS;aWMMMMM@2;     ");
		gotoxy(80, 28);	printf("      r ZM. X;M8ZMZ7;        ");
		gotoxy(80, 29);	printf("        :.   @M              ");
	}
	else if (univ[P2].level >= 5)
	{
		gotoxy(80, 15);	printf("  .                     Z    ");
		gotoxy(80, 16);	printf("  M     ��������       MW    ");
		gotoxy(80, 17);	printf("; WM     ������      .MM     ");
		gotoxy(80, 18);	printf(".ZaM8               XMMaS    ");
		gotoxy(80, 19);	printf("  MMM0             WMMW0i    ");
		gotoxy(80, 20);	printf("  ,MMM@          aMMMMMa:    ");
		gotoxy(80, 21);	printf("    aMMM:      2MMMMMM2      ");
		gotoxy(80, 22);	printf("      BMMS,,rBMMMMMM0,       ");
		gotoxy(80, 23);	printf("      rM@MM@MMMMMW;          ");
		gotoxy(80, 24);	printf("    @MMMMMMaMM@@MBi.ii:,,iXZ:");
		gotoxy(80, 25);	printf("   MMMWX7XS0MM@BWMMMMMMMMMMZ ");
		gotoxy(80, 26);	printf("  SMi      aMM888MMM@WMM@8   ");
		gotoxy(80, 27);	printf("      2@@irWS;aWMMMMM@2;     ");
		gotoxy(80, 28);	printf("      r ZM. X;M8ZMZ7;        ");
		gotoxy(80, 29);	printf("        :.   @M              ");
	}


/*
������

1�ܰ� : ����
2�ܰ� : ��ѱ�
3�ܰ� : ���� ������
4�ܰ� : �߰� ������
5�ܰ� : Ǯ ������
*/
}


void SIO_PrtBuilding (int n)
{
	if (board[n].owner == BG)
		SIO_TurnColor(BG);
	else if (board[n].owner == P1)
		SIO_TurnColor(P1);
	else if (board[n].owner == P2)
		SIO_TurnColor(P2);
	else if (board[n].owner == CL_BT)
		SIO_TurnColor(CL_BT);

	if (board[n].level == 0)
		printf("����");
	else if (board[n].level == 1)
		printf("����");
	else if (board[n].level == 2)
		printf("����");
	else if (board[n].level == 3)
		printf("����");
}

void SIO_PrtCityName (int n)
{
	SIO_TurnColor(BG);
	if (n == 0)  // 0 �����ϴ� ��
		printf(" ���� ");
	else if (n == 6)
		printf(ACADEMY); // 6 ������ �Ʒ� �𼭸�
	else if (n == 12)
		printf(HOSPITAL); // 12 ���� �� �𼭸�
	else if (n == 18)
		printf(MT); // 18 ������ �� �𼭸�

	SIO_TurnColor(NEUTRAL);
	if (n == 8 || n == 15 || n == 20) // Ȳ�ݿ���
		printf(GOLDEN_KEY);

/*
���

����	�����	�Ͻ�	����	â�ǰ�	������
�濵��											���Ǵ�
���а�											����
ȭ��											�����
����											�����
�ǰ���											�뺧
		�̵��	��뻧	�����	������	���а�	����
*/
	if (board[n].owner == P1)
	{
		SIO_TurnColor(P1_SEMI);
		printf(CityName(P1, n));
	}
	else if (board[n].owner == P2)
	{
/*
����

����	���ǰ�	����	����	�����	������
������											��ȣ��
�ٴ尡											����
�밭��											������
����											������
�ǰ���											������
		õ����	����	�˷���	���а�	���а�	����
*/
		SIO_TurnColor(P2_SEMI);
		printf(CityName(P2, n));
	}
}

void SIO_TurnColor(int n)
{
	if (n == BG)
		TextColor(RGB8(0, 0, 0, 0)); // WHITE
	else if (n == NEUTRAL)
		TextColor(RGB8(0, 1, 0, 0)); // GREEN
	else if (n == P1)
		TextColor(RGB8(1, 0, 0, 1)); // RED
	else if (n == P2)
		TextColor(RGB8(0, 0, 1, 1)); // BLUE
	else if (n == P1_SEMI)
		TextColor(RGB8(1, 0, 0, 0)); // DARK RED
	else if (n == P2_SEMI)
		TextColor(RGB8(0, 0, 1, 0)); // DARK BLUE
	else if (n == CL_BT)
		TextColor(RGB8(0, 1, 0, 0)); // GREEN
}

void SIO_PrtPlayer(const PLAYER *p)
{
// ���� ���� �� �ʱ�ȭ
	int x, y, turn;
	x = 0;
    y = 0;
    turn = 0;

    for (turn = P1; turn <= P2; turn++)
	{ // �� �÷��̾��� ���� ǥ�����ְ� �ٸ� �÷��̾ ������
		SIO_CalcPos(p[turn].pos, &x, &y);

		gotoxy(x + (turn) * 4, y); // (turn - 1) * 2�� �÷��̾�� x��ǥ ���̳���
		SIO_TurnColor(turn);
		printf("��");
	}

	/* �����ڵ�
	int Dir[4][2] = { { -8, 0 }, { 0, -4 }, { 8, 0 }, { 0, 4 } }; // ����, ����, ������, �Ʒ���
	int x = 50, y = 27;
	int turn, i;
	for (turn = 1; turn <= 3; turn++)
	{
		x = 50, y = 27;
		for (i = 1; i <= p[turn].pos; i++)
		{
			x = x + Dir[(i - 1) / 6][0];
			y = y + Dir[(i - 1) / 6][1];
		}
		gotoxy(x + (turn - 1) * 2, y);
		SIO_TurnColor(turn);
		printf("��");
	}
	*/
}

int SIO_MovePlayerEffect(PLAYER *p, int turn, int dice)
{
	int x, y, i, recent, around;
	x = 0;
	y = 0;
	i = 0;
	around = 0; // �ѹ����� ���Ҵ°�
	recent = p->pos; // ���� �ð��� �׸� �ø� �����ش�
	for (i = (p->pos + 1); i <= (p->pos + dice); i++)
	{
		// ���� �ִ� �� �����
		SIO_CalcPos(recent % 24, &x, &y);
		gotoxy(x + (turn) * 4, y);
		printf("  ");

		// �� �տ� �ٽ� �׸���
		SIO_CalcPos(i % 24, &x, &y);
		gotoxy(x + (turn) * 4, y);
		SIO_TurnColor(turn);
		printf("��");

		recent = i;
		Delay(100);
	}
	p->pos += dice;

	if ((p->pos / 24) >= 1)
	{ // �ѹ��� ���Ҵ°� �˻�
		p->pos %= 24;
		around = 1;
	}
	return around;


	/* �����ڵ�
	int Dir[4][2] = { { -8, 0 }, { 0, -4 }, { 8, 0 }, { 0, 4 } };
	int x, y, i;
	x = 50;
	y = 27;

	for ( i = 1; i < p->pos; i++)
	{
		x = x + Dir[(i - 1) / 6][0];
		y = y + Dir[(i - 1) / 6][1];
	}

	for ( i = 0; i < dice; i++)
	{
		gotoxy(x + (turn - 1) * 2, y);
		SIO_TurnColor(turn);
		printf(" ");

		x = x + Dir[(p->pos - 1) / 6][0];
		y = y + Dir[(p->pos - 1) / 6][1];

		gotoxy(x + (turn - 1) * 2, y);
		SIO_TurnColor(turn);
		printf("��");

		p->pos++;
		p->pos %= 24;
		Delay(200);
	}
	*/
}

void SIO_CalcPos(const int pos, int *x, int *y)
{
	int line = pos / 6;
	if (line == 0)
	{ // �Ʒ��ʺ�
		*x = 50 - (pos * 8);
		*y = 27;
	}
	else if (line == 1)
	{ // ���ʺ�
		*x = 2;
		*y = 27 - ((pos - 6) * 4);
	}
	else if (line == 2)
	{ // ���ʺ�
		*x = 2 + ((pos - 12) * 8);
		*y = 3;
	}
	else
	{ // �����ʺ�
		*x = 50;
		*y = 3 + ((pos - 18) * 4);
	}
}

void SIO_InitConsoleSize (int y)
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	COORD pos;
	char adjust[80];

	// Console�� �ѱ� ���ڿ� ����
	sprintf(adjust, "mode con cols=120 lines=%d", y);

	// COORD ����ü�� (120, ��������) �Է�
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	pos.X = 120;
	pos.Y = BufInfo.dwSize.Y;

	// �ܼ� ũ��� ���۸� ����
	system(adjust); // ũ�� ����
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), pos); // �ܼ� ���ۿ� ������ �ش� (gotoxy ���۵� ����)
}


//An alternative to the SIO_PrintLogo
void SIO_PrtMinigameBase()
{
	int i;

	gotoxy(76, 0);
	printf("���������������� �̴�  ���� ����������������");
	for(i=1; i<=28; i++)
	{
		gotoxy(76, i); printf("��");
		gotoxy(118, i); printf("��");
	}
	gotoxy(76, 29);
	printf("��������������������������������������������");

}

void SIO_PrintMsg(char* msg)
{
	int msg_len = strlen(msg);
	int x = 60 - msg_len/2;
	int y = 10;
	int i, ctr=1;

	gotoxy(x, y);
	for(i=0; i<msg_len; i++)
	{
		printf("%c", msg[i]);
		if(msg[i] == '\n')
		{
			gotoxy(x,y+(ctr*2));
			ctr++;
		}
		Delay(30);
	}
}

