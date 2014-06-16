#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "BasicIO.h"
#include "SurfaceIO.h"
#include "Var.h"
#include "Mouse.h"

BUTTON* CreateButton ( char n[], int x, int y )
{ // 보류
	BUTTON *b = (BUTTON *)malloc(sizeof(BUTTON));
	b->x = x;
	b->y = y;
	strcpy(b->name,n);
	return b;
}

void PrtButton( BUTTON *b )
{ //버튼출력함수
	int i;
	COLOR_BUTTON; //버튼색
	gotoxy(b->x, b->y); printf("┌");
	for ( i=1; i<=strlen(b->name)/2; i++ ) printf("─");
	printf("┐");
	gotoxy(b->x,b->y+1); printf("│%s│",b->name);
	gotoxy(b->x,b->y+2); printf("└");
	for ( i=1; i<=strlen(b->name)/2; i++ ) printf("─");
	printf("┘");
}

int ChkButton ( BUTTON *b )
{ //마우스좌표가 버튼 위에 있는지 없는지 확인하는 함수
	HWND h;
	POINT a;
	GetCursorPos(&a);
	h = WindowFromPoint(a);
	ScreenToClient(h,&a);
	if ( C_X(b->x)<=a.x && a.x<=C_X(b->x+strlen(b->name)+2) && C_Y(b->y)<=a.y && a.y<=C__Y(b->y) ) {
		PrtButton(b);
		return 1;
	}
	else {
		PrtButton(b);
		return 0;
	}
}

void FreeButton ( BUTTON *a )
{ //위에서 malloc 쓸경우
	free(a);
}



