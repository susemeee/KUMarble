#ifndef MOUSE_H
#define MOUSE_H

/*

����


��ư�����
Button *��ư�̸� = CreateButton("��ư��������",x��ǥ,y��ǥ); ũ��� �ڵ�, �� ������ �ѱ��, ��ȣ�ȵ�
or
BT ��ư�̸� = CreateButton("��ư��������",x��ǥ,y��ǥ); ���������õ, �̰� ���̸� ���� ����.
ex) Button *BEW = CreateButton("Ŭ��",10,10);
or
BT BEW = CreateButton("Ŭ��",10,10);

�����ư���
PrtButton(��ư�̸�);
ex) PrtButton(BEW);

��ưŬ��üũ
PrtButton(��ư�̸�); <- �̰� �ݵ�� �������
while(1) {
	if ( CLICK_LEFT && ChkButton(��ư�̸�)) {
	
1	��ư�� Ŭ���� ���
	}
}
ex)
PrtButton(BEW);
while(1) {
	if ( CLICK_LEFT && ChkButton(BEW)) {
		printf("��");
		break;
	}
}

�ΰ��� �̻��� ��ư�� ���ÿ� �Ҷ�
PrtButton(��ư�̸�1); PrtButton(��ư�̸�2); ...
while(1) {
	if ( CLICK_LEFT && ChkButton(��ư�̸�1)) {
		��ư1�� Ŭ���� ���
	}
	if ( CLICK_LEFT && ChkButton(��ư�̸�2)) { <- else if �� �ƴ϶� if ��
		��ư2�� Ŭ���� ���
	}
	...
}
*/

#include<string.h>

#define CLICK_LEFT GetAsyncKeyState(0x01)

#define BT BUTTON*

__inline int C_X ( int x ) { return (x+1)*8; } // Mouse.h�� ���°�.
__inline int C_Y ( int y ) { return y*16+8; }
__inline int C__Y ( int y ) { return (y+2)*16+8; }

typedef struct JUSTITIA {
	char name[100];
	int x;
	int y;
}BUTTON;

BUTTON *CreateButton ( char n[], int x, int y );
void PrtButton( BUTTON *b );
int ChkButton ( BUTTON *b );

/*void DeleteButton ( BUTTON *a ) { //������ malloc �����
	free(a);
} �����غ��ϱ� �ʿ���� */ 

/*int ChkBoard() { //����
	HWND h;
	POINT a;
	GetCursorPos(&a);
	h = WindowFromPoint(a);
	ScreenToClient(h,&a);
	if( 8<=a.x && a.x<=72 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("�Ź��а�       ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("������                  ");
		return 1;
	}
	if( 72<=a.x && a.x<=72+64 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("�ֱ��         ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("�ڿ����л����� �޽İ���    ");
		return 1;
	}
	if( 72+64<=a.x && a.x<=72+64*2 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("������а�      ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("�������� ����            ");
		return 1;
	}
	if( 72+64*2<=a.x && a.x<=72+64*3 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("���а�          ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("�������� ��� �𸣰ڴ�");
		return 1;
	}
	if( 72+64*3<=a.x && a.x<=72+64*4 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("���а�          ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("����� ��ġ             ");
		return 1;
	}
	if( 72+64*4<=a.x && a.x<=72+64*5 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("���к���          ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("���밡��               ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("���к���          ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("�����밡��            ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8+64<=a.y && a.y<=72+64 ) { // 
		gotoxy(20,10); printf("�뺧�ö���        ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("���                  ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8+64*2<=a.y && a.y<=72+64*2 ) { // 
		gotoxy(20,10); printf("���ֱ���          ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("�����                  ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8+64*3<=a.y && a.y<=72+64*3 ) { // 
		gotoxy(20,10); printf("���ֳ���Ｚ��  ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("����                 ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8+64*4<=a.y && a.y<=72+64*4 ) { // 
		gotoxy(20,10); printf("ȭ��ü����         ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("����� ����            ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8+64*5<=a.y && a.y<=72+64*5 ) { // 
		gotoxy(20,10); printf("�����                   ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("�Ȼ�ƺ��� �𸣰ڴ�     ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("����                     ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("���ٶ�µ�             ");
		return 1;
	}
	if( 72+64*4<=a.x && a.x<=72+64*5 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("����                     ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("������ ����            ");
		return 1;
	}
	if( 72+64*3<=a.x && a.x<=72+64*4 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("��������(����)             ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("�̰ź��� ����         ");
		return 1;
	}
	if( 72+64*2<=a.x && a.x<=72+64*3 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("���п�                   ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("����� ��¡            ");
		return 1;
	}
	if( 72+64*1<=a.x && a.x<=72+64*2 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("�߾ӱ���                     ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("�̰ź��� ����2           ");
		return 1;
	}
	if( 72<=a.x && a.x<=72+64*1 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("���������ڰ濵��             ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("��������ʹ�              ");
		return 1;
	}
	if( 72-64<=a.x && a.x<=72 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("�����ڵ����濵��           ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("������                     ");
		return 1;
	}
	if( 72-64<=a.x && a.x<=72 && 8+64*5<=a.y && a.y<=72+64*5 ) { // 
		gotoxy(20,10); printf("��米���                ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("����                     ");
		return 1;
	}
	if( 72-64<=a.x && a.x<=72 && 8+64*4<=a.y && a.y<=72+64*4 ) { // 
		gotoxy(20,10); printf("����������Ű�             ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("÷������! �������!      ");
		return 1;
	}
	if( 72-64<=a.x && a.x<=72 && 8+64*3<=a.y && a.y<=72+64*3 ) { // 
		gotoxy(20,10); printf("�ƻ����а�               ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("�������� ������� �ʹ�    ");
		return 1;
	}
	if( 72-64<=a.x && a.x<=72 && 8+64*2<=a.y && a.y<=72+64*2 ) { // 
		gotoxy(20,10); printf("������                 ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("��Ƽ�� ���� ��          ");
		return 1;
	}
	if( 72-64<=a.x && a.x<=72 && 8+64<=a.y && a.y<=72+64*1 ) { // 
		gotoxy(20,10); printf("�ϳ�������              ");
		gotoxy(20,11); printf("�÷��̾� %d ����",1);
		gotoxy(20,12); printf("�̰����� ������          ");
		return 1;
	}
}*/
#endif 