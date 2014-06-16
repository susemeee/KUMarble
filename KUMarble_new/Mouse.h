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

#define C_X(X) ((X) * 8) // Mouse.h에 쓰는것.
#define C_Y(Y) (((Y)-1)*16+8)
#define C__Y(Y) (((Y)+1)*16+8)

BUTTON *CreateButton ( char n[], int x, int y );
void PrtButton( BUTTON *b );
int ChkButton ( BUTTON *b );
void FreeButton ( BUTTON *a );

/*
사용법


버튼만들기
Button *버튼이름 = CreateButton("버튼에들어갈내용",x좌표,y좌표); 크기는 자동, 들어갈 내용은 한국어만, 기호안됨
or
BT 버튼이름 = CreateButton("버튼에들어갈내용",x좌표,y좌표); 위에방법추천, 이건 편이를 위해 만듬.
ex) Button *BEW = CreateButton("클릭",10,10);
or
BT BEW = CreateButton("클릭",10,10);

만든버튼출력
PrtButton(버튼이름);
ex) PrtButton(BEW);

버튼클릭체크
PrtButton(버튼이름); <- 이거 반드시 해줘야함
while(1) {
	if ( CLICK_LEFT && ChkButton(버튼이름)) {
		버튼이 클릭될 경우
	}
}
ex)
PrtButton(BEW);
while(1) {
	if ( CLICK_LEFT && ChkButton(BEW)) {
		printf("뷰");
		break;
	}
}

두가지 이상의 버튼을 동시에 할때
PrtButton(버튼이름1); PrtButton(버튼이름2); ...
while(1) {
	if ( CLICK_LEFT && ChkButton(버튼이름1)) {
		버튼1이 클릭될 경우
	}
	if ( CLICK_LEFT && ChkButton(버튼이름2)) { <- else if 가 아니라 if 임
		버튼2이 클릭될 경우
	}
	...
}
*/



#endif // MOUSE_H_INCLUDED
