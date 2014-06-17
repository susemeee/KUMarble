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

// 구조체
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

// 건물 이름들
#define GOLDEN_KEY	"열§쇠"
#define HOSPITAL " 병원 "
#define ACADEMY "대학원"
#define MT "  MT  "

// 고대건물
#define P1_CITY_01	"공학관"
#define P1_CITY_02	"국제관"
#define P1_CITY_03	"유자유"
#define P1_CITY_04	"고대빵"
#define P1_CITY_05	"미디어"
#define P1_CITY_06	ACADEMY
#define P1_CITY_07	"이과대"
#define P1_CITY_08	GOLDEN_KEY
#define P1_CITY_09	" 화정 "
#define P1_CITY_10	"이학관"
#define P1_CITY_11	"경영관"
#define P1_CITY_12	HOSPITAL
#define P1_CITY_13	"교양관"
#define P1_CITY_14	" 하스 "
#define P1_CITY_15	GOLDEN_KEY
#define P1_CITY_16	"창의관"
#define P1_CITY_17	"도서관"
#define P1_CITY_18	MT
#define P1_CITY_19	"보건대"
#define P1_CITY_20	GOLDEN_KEY
#define P1_CITY_21	"정통관"
#define P1_CITY_22	"기숙사"
#define P1_CITY_23	" 노벨 "

// 연대건물
#define P2_CITY_01	"공학관"
#define P2_CITY_02	"신학관"
#define P2_CITY_03	"초가집"
#define P2_CITY_04	"연세유"
#define P2_CITY_05	"천문대"
#define P2_CITY_06	ACADEMY
#define P2_CITY_07	"이과대"
#define P2_CITY_08	GOLDEN_KEY
#define P2_CITY_09	"대강당"
#define P2_CITY_10	"바닷가"
#define P2_CITY_11	"지혜관"
#define P2_CITY_12	HOSPITAL
#define P2_CITY_13	"음악관"
#define P2_CITY_14	"양계장"
#define P2_CITY_15	GOLDEN_KEY
#define P2_CITY_16	"정빈관"
#define P2_CITY_17	"도서관"
#define P2_CITY_18	MT
#define P2_CITY_19	"간호대"
#define P2_CITY_20	GOLDEN_KEY
#define P2_CITY_21	"자유관"
#define P2_CITY_22	"선착장"
#define P2_CITY_23	"진리관"

// 성원
#define P_POS player[turn].pos
#define P_MONEY player[turn].money //일일이 쓰려하다가 코드가 너무 길어지는것 같아서

#define COLOR_P1 SIO_TurnColor(P1); //플레이어1 색 //여기서부터
#define COLOR_P2 SIO_TurnColor(P2); //2 색
#define COLOR_BOARD SIO_TurnColor(BG); // 판 색
#define COLOR_BUTTON SIO_TurnColor(CL_BT); //버튼 색
#define XMONEY 60 // 건물당 받은 돈
#define BONUS_MONEY 100 // 한바퀴돌때 받는 돈
#define BMONEY 70 // 건물가격

#endif // MACROVAR_H_INCLUDED
