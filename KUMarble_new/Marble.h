#ifndef MARBLE_H
#define MARBLE_H

// ������ ����
void KUMarble ();

// ���� �ʱ�ȭ �� ���� ���
char* CityName(const int whatuniv, const int pos);
void InitPlayerStruct (PLAYER *player);
void InitCityStruct (CITY* city, const int pos);
void InitUnivStruct (UNIV *univ, const int whatuniv);
int ML_CityCost (int whatuniv, int pos);
char* IsSpecialCity(int nowpos);

// fancy dice rolling
void PrtBasic();
int DiceEffect(int dice_limit);

// ���� ���� ���
int ML_ChangeTurn(int turn);
void ML_UnivLevelUp(int turn, PLAYER player[], UNIV univ[]); // ���� ������ ����
int ML_ThrowDice(int turn, int dice_limit);	// �ֻ��� ������
void ML_RoundMoney(int turn, PLAYER player[], UNIV univ[]);	// �� ���� ���� �ִ� ���б�
void ML_BuyCity(int turn, int nowpos, PLAYER player[], UNIV univ[]);	// �ǹ� ����
void ML_UpgradeCity(int turn, int nowpos, PLAYER player[], UNIV univ[]);	// �ǹ� ���׷��̵�
void ML_PayLessonFee(int turn, int nowpos, PLAYER player[], UNIV univ[]);	// ������ ����
void ML_Ending(PLAYER player[], UNIV univ[]);	// ���� �Ǵ�

void ML_ProcessSpecial(int turn, int nowpos, PLAYER player[], UNIV univ[]);	//Ȳ�ݿ��� ĭ ó��
void ML_ProcessGoldenKey(int turn, int nowpos, PLAYER player[], UNIV univ[]);	//Ư���� ĭ ó��
void ML_ChamChamCham(int turn, PLAYER player[], UNIV univ[]); //������ ����

void ML_PrintStory();


#endif // MARBLE_H_INCLUDED
