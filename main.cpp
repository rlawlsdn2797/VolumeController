#include <stdio.h>

#include <conio.h>

#include <windows.h>

#include <stdlib.h>

#include <time.h>


#define LEFT 75

#define RIGHT 77

#define UP 72

#define DOWN 80


//해당 위치로 콘솔 이동. 
void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//커서 숨기기. 
void CursorView(char show) {
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

//맵 테투리 그리기. 
void DrawMap() {
	gotoxy(0, 0);
	int i = 0, Length = 20;
	for(i = 0; i <= Length; i++) {
		printf("▩");
	}
	
	gotoxy(40, 1);
	printf("■");
	gotoxy(40, 2);
	printf("■");
	gotoxy(40, 3);
	printf("■");
	gotoxy(40, 4);
	printf("■");
	gotoxy(40, 5);
	printf("■");
	
	gotoxy(0, 6);
	for(i = 0; i <= Length; i++) {
		printf("▩");
	}
}

int main() {
	int PosX = 0, PosY = 3, a;
	
	CursorView(0);
	DrawMap();
	
	gotoxy(PosX, PosY);
	printf("♡");
		
	while(1) {
		if(kbhit()) {
			
			a = getch();
			
			gotoxy(PosX, PosY);
			printf("  ");
			
			if(a == LEFT) PosX -= 2;
			if(a == RIGHT) PosX += 2;
			if(a == UP) PosY--;
			if(a == DOWN) PosY++;
			 
			if(PosX < 0) PosX = 0;
			if(PosX > 38) PosX = 38;
			if(PosY < 1) PosY = 1;
			if(PosY > 5) PosY = 5; 
			
			gotoxy(PosX, PosY);
			printf("♡");
		}
	}
		
	
	return 0;
}
