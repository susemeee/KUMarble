#ifndef __BasicInput_h
#define __BasicInput_h

#ifdef _MSC_VER // Visual C++������ �����ϵǴ� �ڵ�
#pragma warning(disable:4996)
#endif // _MSC_VER

#include <time.h>

int scanfile (const char name[]); // ������ ���� ���� �˻�
char* scanstr (int strlong, char *str); // ���ڿ��� �����÷ο���� �ʴ� scanf ��� �Լ�
char* fscanstr (int strlong, FILE* fp, char *str); // ���Ͽ��� ���� �о���� �Լ�
void pause ();
void gotoxy(int x, int y);
void cursorinit ();
int getx(); // Ŀ���� x ��ǥ ������
int gety(); // Ŀ���� y ��ǥ ������
int WhatBitOS (int print); // ���Ʈ �������ΰ� �˾Ƴ���
int RandNum (int first, int last);
void Delay(clock_t wait);
void TextColor(unsigned char fcolor); // fcolor�� RGB8�� ���
void BGColor(unsigned char bcolor); // bcolor�� RGB8�� ���


//srand ((unsigned int) time(NULL));
#define RGB8(R, G, B, I) (((I) * 8) + ((R) * 4) + ((G) * 2) + (B)) // �ڷ������� char ���
#define BIN(X) (((X) % 256) + ((X) % 128) + ((X) % 64) + ((X) % 32) + ((X) % 16) + ((X) % 8) + ((X) % 4) + ((X) % 2))) // 1����Ʈ ������ 0, 1�� �̷ξ��� �������� �������� �ٲ��ش�.


#define ms2rsec(X) ((X) / 1000)
#define ms2rmin(X) ((X) / 1000 / 60)
#define ms2rhour(X) ((X) / 1000 / 60 / 60)

#define ms2sec(X) (((X) / 1000) % 60)
#define ms2min(X) (((X) / 1000 / 60) % 60)
#define ms2hour(X) (((X) / 1000 / 60 / 60) % 60)

#define rsec2sec(X) ((X) % 60)
#define rsec2min(X) ((X) / 60)
#define rsec2hour(X) ((X) / 60 / 60)




#define WINDOWS
//#define LINUX

#endif
