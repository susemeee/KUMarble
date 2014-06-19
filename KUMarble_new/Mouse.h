#ifndef MOUSE_H
#define MOUSE_H

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
	
1	버튼이 클릭될 경우
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

#include<string.h>

#define CLICK_LEFT GetAsyncKeyState(0x01)

#define BT BUTTON*

__inline int C_X ( int x ) { return (x+1)*8; } // Mouse.h에 쓰는것.
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

/*void DeleteButton ( BUTTON *a ) { //위에서 malloc 쓸경우
	free(a);
} 생각해보니까 필요없음 */ 

/*int ChkBoard() { //보류
	HWND h;
	POINT a;
	GetCursorPos(&a);
	h = WindowFromPoint(a);
	ScreenToClient(h,&a);
	if( 8<=a.x && a.x<=72 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("신법학관       ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("연상고법                  ");
		return 1;
	}
	if( 72<=a.x && a.x<=72+64 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("애기능         ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("자연계학생들의 휴식공간    ");
		return 1;
	}
	if( 72+64<=a.x && a.x<=72+64*2 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("생명과학관      ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("쓸데없이 많음            ");
		return 1;
	}
	if( 72+64*2<=a.x && a.x<=72+64*3 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("산학관          ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("가본적이 없어서 모르겠다");
		return 1;
	}
	if( 72+64*3<=a.x && a.x<=72+64*4 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("공학관          ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("고대의 수치             ");
		return 1;
	}
	if( 72+64*4<=a.x && a.x<=72+64*5 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("공학별관          ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("연대가라               ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8<=a.y && a.y<=72 ) { // 
		gotoxy(20,10); printf("이학별관          ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("연세대가라            ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8+64<=a.y && a.y<=72+64 ) { // 
		gotoxy(20,10); printf("노벨플라자        ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("밥약                  ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8+64*2<=a.y && a.y<=72+64*2 ) { // 
		gotoxy(20,10); printf("민주광장          ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("배고파                  ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8+64*3<=a.y && a.y<=72+64*3 ) { // 
		gotoxy(20,10); printf("백주년기념삼성관  ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("졸려                 ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8+64*4<=a.y && a.y<=72+64*4 ) { // 
		gotoxy(20,10); printf("화정체육관         ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("고대의 성지            ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8+64*5<=a.y && a.y<=72+64*5 ) { // 
		gotoxy(20,10); printf("기숙사                   ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("안살아봐서 모르겠다     ");
		return 1;
	}
	if( 72+64*5<=a.x && a.x<=72+64*6 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("시작                     ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("뭘바라는데             ");
		return 1;
	}
	if( 72+64*4<=a.x && a.x<=72+64*5 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("본관                     ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("가볼일 없음            ");
		return 1;
	}
	if( 72+64*3<=a.x && a.x<=72+64*4 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("문과대학(서관)             ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("이거보고 고대옴         ");
		return 1;
	}
	if( 72+64*2<=a.x && a.x<=72+64*3 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("대학원                   ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("고대의 상징            ");
		return 1;
	}
	if( 72+64*1<=a.x && a.x<=72+64*2 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("중앙광장                     ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("이거보고 고대옴2           ");
		return 1;
	}
	if( 72<=a.x && a.x<=72+64*1 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("엘지포스코경영관             ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("문과가고싶다              ");
		return 1;
	}
	if( 72-64<=a.x && a.x<=72 && 8+64*6<=a.y && a.y<=72+64*6 ) { // 
		gotoxy(20,10); printf("현대자동차경영관           ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("돈낭비                     ");
		return 1;
	}
	if( 72-64<=a.x && a.x<=72 && 8+64*5<=a.y && a.y<=72+64*5 ) { // 
		gotoxy(20,10); printf("우당교양관                ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("보류                     ");
		return 1;
	}
	if( 72-64<=a.x && a.x<=72 && 8+64*4<=a.y && a.y<=72+64*4 ) { // 
		gotoxy(20,10); printf("우정정보통신관             ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("첨단정통! 백야컴통!      ");
		return 1;
	}
	if( 72-64<=a.x && a.x<=72 && 8+64*3<=a.y && a.y<=72+64*3 ) { // 
		gotoxy(20,10); printf("아산이학관               ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("딴데서좀 수업듣고 싶다    ");
		return 1;
	}
	if( 72-64<=a.x && a.x<=72 && 8+64*2<=a.y && a.y<=72+64*2 ) { // 
		gotoxy(20,10); printf("국제관                 ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("스티븐 조지 뷰          ");
		return 1;
	}
	if( 72-64<=a.x && a.x<=72 && 8+64<=a.y && a.y<=72+64*1 ) { // 
		gotoxy(20,10); printf("하나스퀘어              ");
		gotoxy(20,11); printf("플레이어 %d 소유",1);
		gotoxy(20,12); printf("이공계의 자존심          ");
		return 1;
	}
}*/
#endif 