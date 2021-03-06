#ifndef MARBLE_H
#define MARBLE_H

// 게임의 중추
void KUMarble ();

// 변수 초기화 및 정보 담당
char* CityName(const int whatuniv, const int pos);
void InitPlayerStruct (PLAYER *player);
void InitCityStruct (CITY* city, const int pos);
void InitUnivStruct (UNIV *univ, const int whatuniv);
int ML_CityCost (int whatuniv, int pos);
char* IsSpecialCity(int nowpos);

// fancy dice rolling
void PrtBasic();
int DiceEffect(int dice_limit);

// 게임 로직 담당
int ML_ChangeTurn(int turn);
void ML_UnivLevelUp(int turn, PLAYER player[], UNIV univ[]); // 대학 레벨업 여부
int ML_ThrowDice(int turn, int dice_limit);	// 주사위 굴리기
void ML_RoundMoney(int turn, PLAYER player[], UNIV univ[]);	// 한 바퀴 돌면 주는 장학금
void ML_BuyCity(int turn, int nowpos, PLAYER player[], UNIV univ[]);	// 건물 짓기
void ML_UpgradeCity(int turn, int nowpos, PLAYER player[], UNIV univ[]);	// 건물 업그레이드
void ML_PayLessonFee(int turn, int nowpos, PLAYER player[], UNIV univ[]);	// 수업료 지불
void ML_Ending(PLAYER player[], UNIV univ[]);	// 승패 판단

void ML_ProcessSpecial(int turn, int nowpos, PLAYER player[], UNIV univ[]);	//황금열쇠 칸 처리
void ML_ProcessGoldenKey(int turn, int nowpos, PLAYER player[], UNIV univ[]);	//특별한 칸 처리
void ML_ChamChamCham(int turn, PLAYER player[], UNIV univ[]); //참참참 게임

void ML_PrintStory();


#endif // MARBLE_H_INCLUDED
