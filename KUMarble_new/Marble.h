#ifndef MARBLE_H_INCLUDED
#define MARBLE_H_INCLUDED

// ������ ����
void KUMarble ();

// ���� �ʱ�ȭ �� ���� ���
char* CityName(const int whatuniv, const int pos);
void InitPlayerStruct (PLAYER *player);
void InitCityStruct (CITY* city, const int whatuniv, const int pos);
void InitUnivStruct (UNIV *univ, const int whatuniv);
char* IsSpecialCity(int nowpos);

// fancy dice rolling
void PrtBasic();
int DiceEffect();

// ���� ���� ���
int ML_ChangeTurn(int turn);
void ML_UnivLevelUp(int turn, PLAYER player[], UNIV univ[]); // ���� ������ ����
int ML_ThrowDice(int turn, int  dice[]);	// �ֻ��� ������
void ML_RoundMoney(int turn, PLAYER player[], UNIV univ[]);	// �� ���� ���� �ִ� ���б�
void ML_BuyCity(int turn, int nowpos, PLAYER player[], UNIV univ[]);	// �ǹ� ����
void ML_UpgradeCity(int turn, int nowpos, PLAYER player[], UNIV univ[]);	// �ǹ� ���׷��̵�
void ML_PayLessonFee(int turn, int nowpos, PLAYER player[], UNIV univ[]);	// ������ ����
void ML_Ending(PLAYER player[], UNIV univ[]);	// ���� �Ǵ�
void ML_ProcessSpecial(int turn, int nowpos, PLAYER player[], UNIV univ[]);
void ML_ProcessGoldenKey(int turn, int nowpos, PLAYER player[], UNIV univ[]);

void ML_PrintStory();


#endif // MARBLE_H_INCLUDED
