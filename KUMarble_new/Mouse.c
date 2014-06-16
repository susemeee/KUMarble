#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "BasicIO.h"
#include "SurfaceIO.h"
#include "Var.h"
#include "Mouse.h"

BUTTON* CreateButton ( char n[], int x, int y )
{ // ����
	BUTTON *b = (BUTTON *)malloc(sizeof(BUTTON));
	b->x = x;
	b->y = y;
	strcpy(b->name,n);
	return b;
}

void PrtButton( BUTTON *b )
{ //��ư����Լ�
	int i;
	COLOR_BUTTON; //��ư��
	gotoxy(b->x, b->y); printf("��");
	for ( i=1; i<=strlen(b->name)/2; i++ ) printf("��");
	printf("��");
	gotoxy(b->x,b->y+1); printf("��%s��",b->name);
	gotoxy(b->x,b->y+2); printf("��");
	for ( i=1; i<=strlen(b->name)/2; i++ ) printf("��");
	printf("��");
}

int ChkButton ( BUTTON *b )
{ //���콺��ǥ�� ��ư ���� �ִ��� ������ Ȯ���ϴ� �Լ�
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
{ //������ malloc �����
	free(a);
}



