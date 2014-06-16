#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#define CLICK_LEFT GetAsyncKeyState(0x01)
#define BT BUTTON*


typedef struct JUSTITIA
{
	char name[100];
	int x;
	int y;
} BUTTON;

#define C_X(X) ((X) * 8) // Mouse.h�� ���°�.
#define C_Y(Y) (((Y)-1)*16+8)
#define C__Y(Y) (((Y)+1)*16+8)

BUTTON *CreateButton ( char n[], int x, int y );
void PrtButton( BUTTON *b );
int ChkButton ( BUTTON *b );
void FreeButton ( BUTTON *a );

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
		��ư�� Ŭ���� ���
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



#endif // MOUSE_H_INCLUDED
