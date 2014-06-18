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
	size_t i, prtlen, len;
	COLOR_BUTTON; //��ư��
	len = strlen(b->name);
	if (len % 2 == 0) // ¦��
		prtlen = len / 2;
	if (len % 2 == 1) // Ȧ��
		prtlen = (len + 1) / 2;

	gotoxy(b->x, b->y); printf("��");
	for (i = 1; i <= prtlen / 2; i++)
		printf("��");
	printf("��");
	gotoxy(b->x,b->y+1);
	if (len % 2 == 0) // ¦��
		printf("��%s��",b->name);
	if (len % 2 == 1) // Ȧ��
		printf("��%s ��", b->name);
	gotoxy(b->x,b->y+2); printf("��");
	for (i = 1; i <= prtlen / 2; i++)
		printf("��");
	printf("��");
}

int ChkButton ( BUTTON *b )
{ //���콺��ǥ�� ��ư ���� �ִ��� ������ Ȯ���ϴ� �Լ�
	HWND h;
	POINT a;
	GetCursorPos(&a);
	h = WindowFromPoint(a);
	ScreenToClient(h,&a);
	if (C_X(b->x) <= (unsigned)a.x && (unsigned)a.x <= C_X(b->x + strlen(b->name) + 2) && C_Y(b->y) <= (unsigned)a.y && (unsigned) a.y <= C__Y(b->y)) {
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



