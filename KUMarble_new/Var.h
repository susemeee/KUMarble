#ifndef MACROVAR_H_INCLUDED
#define MACROVAR_H_INCLUDED

#include <time.h>

#define DEBUG

#define KMVER 1.0
#define KMDATE "2014.05.21"

#define TRUE 1
#define FALSE 0

#define WAIT 800
#define PLAYER_NUMBER 2
#define CITY_NUMBER 24


#define GAME_EASY 1
#define GAME_HARD 2
#define GAME_WIN 10
#define GAME_DRAW 11
#define GAME_LOSE 12


#define CHEAT -30
#define QUIT_ESC -20

#define BG -1
#define NEUTRAL -10
#define P1 0
#define P2 1
#define P1_SEMI 10
#define P2_SEMI 11
#define CL_BT 50

// ����ü
struct player_info
{
	int pos;
	int money;
	int round;
};
typedef struct player_info PLAYER;

struct city_info
{
	int pos;
	int cost;
	char name[32];
	int owner;
    int level;
};
typedef struct city_info CITY;

struct univ_info
{
	int money;
	int level;
	int city_count;
	char name[32];
};
typedef struct univ_info UNIV;

extern CITY board[CITY_NUMBER];
extern int difficulty;
extern clock_t timepass;

// �ǹ� �̸���
#define GOLDEN_KEY	"���׼�"
#define HOSPITAL " ���� "
#define ACADEMY "���п�"
#define MT "  MT  "

// ���ǹ�
#define P1_CITY_01	"���а�"
#define P1_CITY_02	"������"
#define P1_CITY_03	"������"
#define P1_CITY_04	"��뻧"
#define P1_CITY_05	"�̵��"
#define P1_CITY_06	ACADEMY
#define P1_CITY_07	"�̰���"
#define P1_CITY_08	GOLDEN_KEY
#define P1_CITY_09	" ȭ�� "
#define P1_CITY_10	"���а�"
#define P1_CITY_11	"�濵��"
#define P1_CITY_12	HOSPITAL
#define P1_CITY_13	"�����"
#define P1_CITY_14	" �Ͻ� "
#define P1_CITY_15	GOLDEN_KEY
#define P1_CITY_16	"â�ǰ�"
#define P1_CITY_17	"������"
#define P1_CITY_18	MT
#define P1_CITY_19	"���Ǵ�"
#define P1_CITY_20	GOLDEN_KEY
#define P1_CITY_21	"�����"
#define P1_CITY_22	"�����"
#define P1_CITY_23	" �뺧 "

// ����ǹ�
#define P2_CITY_01	"���а�"
#define P2_CITY_02	"���а�"
#define P2_CITY_03	"�ʰ���"
#define P2_CITY_04	"������"
#define P2_CITY_05	"õ����"
#define P2_CITY_06	ACADEMY
#define P2_CITY_07	"�̰���"
#define P2_CITY_08	GOLDEN_KEY
#define P2_CITY_09	"�밭��"
#define P2_CITY_10	"�ٴ尡"
#define P2_CITY_11	"������"
#define P2_CITY_12	HOSPITAL
#define P2_CITY_13	"���ǰ�"
#define P2_CITY_14	"�����"
#define P2_CITY_15	GOLDEN_KEY
#define P2_CITY_16	"�����"
#define P2_CITY_17	"������"
#define P2_CITY_18	MT
#define P2_CITY_19	"��ȣ��"
#define P2_CITY_20	GOLDEN_KEY
#define P2_CITY_21	"������"
#define P2_CITY_22	"������"
#define P2_CITY_23	"������"

// ����
#define P_POS player[turn].pos
#define P_MONEY player[turn].money //������ �����ϴٰ� �ڵ尡 �ʹ� ������°� ���Ƽ�

#define COLOR_P1 SIO_TurnColor(P1); //�÷��̾�1 �� //���⼭����
#define COLOR_P2 SIO_TurnColor(P2); //2 ��
#define COLOR_BOARD SIO_TurnColor(BG); // �� ��
#define COLOR_BUTTON SIO_TurnColor(CL_BT); //��ư ��
#define XMONEY 60 // �ǹ��� ���� ��
#define BONUS_MONEY 100 // �ѹ������� �޴� ��
#define BMONEY 70 // �ǹ�����

#endif // MACROVAR_H_INCLUDED
