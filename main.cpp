#include <iostream>

#include <conio.h>

#include <windows.h>

#include <stdlib.h>

#include <time.h>

#include <vector>


#define LEFT 75

#define RIGHT 77

#define UP 72

#define DOWN 80

using namespace std;

vector<pair<int, int> > arr;
int PosX = 0, PosY = 3;

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

void BlockMove() {
	int i;
	
	for(i = 0; i < arr.size(); i++) {
		arr[i].first -= 2;
		
		if(arr[i].first < 0) {
			gotoxy(0, arr[i].second);
			printf("  ");
			arr.erase(arr.begin());
		}
		else {
			gotoxy(arr[i].first + 2, arr[i].second);
			printf("  ");
			
			gotoxy(arr[i].first, arr[i].second);
			printf("☆");
		}
	}
}

void MakeBlock() {
	srand(time(NULL));
	
	int a = rand() % 5 + 1;
	
	arr.push_back({30, a});
	
	BlockMove();
}

//맵 테투리 그리기. 
void DrawMap() {
	gotoxy(0, 0);
	int i = 0, Length = 15;
	for(i = 0; i <= Length; i++) {
		printf("▩");
	}
	
	gotoxy(30, 1);
	printf("■");
	gotoxy(30, 2);
	printf("■");
	gotoxy(30, 3);
	printf("■");
	gotoxy(30, 4);
	printf("■");
	gotoxy(30, 5);
	printf("■");
	
	gotoxy(0, 6);
	for(i = 0; i <= Length; i++) {
		printf("▩");
	}
}

void Check() {
	int i;
	for(i = 0; i < arr.size(); i++) {
		if(arr[i].first == PosX && arr[i].second == PosY) {
			exit(0);
		}
	}
}

int main() {
	int a, delay = 0, SpawnDelay = 50;
	
	CursorView(0);
	DrawMap();
	
	gotoxy(PosX, PosY);
	printf("♡");
			
	while(1) {
		Sleep(1);
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
		
		Check();
		
		delay++;
		if(delay >= SpawnDelay) {
			delay = 0;
			MakeBlock();
		}
	}
	
	return 0;
}
