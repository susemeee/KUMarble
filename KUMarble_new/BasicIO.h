#ifndef __BasicInput_h
#define __BasicInput_h

#ifdef _MSC_VER // Visual C++에서만 컴파일되는 코드
#pragma warning(disable:4996)
#endif // _MSC_VER

#include <time.h>

int scanfile (const char name[]); // 파일의 존재 여부 검사
char* scanstr (int strlong, char *str); // 문자열이 오버플로우되지 않는 scanf 대용 함수
char* fscanstr (int strlong, FILE* fp, char *str); // 파일에서 내용 읽어오는 함수
void pause ();
void gotoxy(int x, int y);
void cursorinit ();
int getx(); // 커서의 x 좌표 얻어오기
int gety(); // 커서의 y 좌표 얻어오기
int WhatBitOS (int print); // 몇비트 컴파일인가 알아내기
int RandNum (int first, int last);
void Delay(clock_t wait);
void TextColor(unsigned char fcolor); // fcolor는 RGB8를 사용
void BGColor(unsigned char bcolor); // bcolor는 RGB8를 사용


//srand ((unsigned int) time(NULL));
#define RGB8(R, G, B, I) (((I) * 8) + ((R) * 4) + ((G) * 2) + (B)) // 자료형으론 char 사용
#define BIN(X) (((X) % 256) + ((X) % 128) + ((X) % 64) + ((X) % 32) + ((X) % 16) + ((X) % 8) + ((X) % 4) + ((X) % 2))) // 1바이트 내외의 0, 1로 이로어진 십진수를 이진수로 바꿔준다.


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
