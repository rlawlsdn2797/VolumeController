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
vector<int> type;
int PosX = 0, PosY = 3;
int Score = 20;

HANDLE hConsole;

bool GameOver = false;

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

//블럭 움직이기. 
void BlockMove() {
	int i;
	
	for(i = 0; i < arr.size(); i++) {
		arr[i].first -= 2;
		
		if(arr[i].first < 0) {
			gotoxy(0, arr[i].second);
			printf("  ");
			arr.erase(arr.begin());
			type.erase(type.begin());
		}
		else {
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			gotoxy(arr[i].first + 2, arr[i].second);
			printf("  ");
			
			gotoxy(arr[i].first, arr[i].second);
			
			if(type[i] == 1 || type[i] == 4) {
    			SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
				printf("＋");
			}
			else if(type[i] == 2) {
    			SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
				printf("－");
			}
			else if(type[i] == 3) {
    			SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
				printf("×");
			}
		}
	}
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	gotoxy(PosX, PosY);
	printf("♡");
}

//블럭 생성하기. 
void MakeBlock() {	
	arr.push_back({30, rand() % 5 + 1});
	type.push_back(rand() % 4 + 1);
	
	BlockMove();
}

//맵 테투리 그리기. 
void DrawMap() {
	gotoxy(0, 0);
	int i = 0, Length = 14;
	for(i = 0; i <= Length; i++) {
		printf("▩");
	}
	
	gotoxy(0, 6);
	for(i = 0; i <= Length; i++) {
		printf("▩");
	}
}

//캐릭터가 블럭과 닿았는지 확인하기 
void Check() {
	int i;
	for(i = 0; i < arr.size(); i++) {
		if(arr[i].first == PosX && arr[i].second == PosY) {
			if(type[i] == 1 || type[i] == 4) {
				Score += 2;
				
				if(Score == 100) {
					GameOver = true;
				}
			}
			else if(type[i] == 2) {
				Score -= 2;
				
				if(Score < 0) Score = 0;
			}
			else if(type[i] == 3){
				Score = 0;
			}
			
			type[i] = 0;
		}
	}
	
	gotoxy(20, 7);
	printf("Volume : %3d", Score);
}

int main() {
	int a, delay = 0, SpawnDelay = 25;
	
	CursorView(0);
	DrawMap();
	
	gotoxy(PosX, PosY);
	printf("♡");
	
	gotoxy(20, 7);
	printf("Volume : %3d%%", Score);
	
	SetConsoleTitle("VolumeController");
	
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//GameOver가 True가 되면 while문 종료. 
	while(!GameOver) {
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
			if(PosX > 28) PosX = 28;
			if(PosY < 1) PosY = 1;
			if(PosY > 5) PosY = 5;
			
			gotoxy(PosX, PosY);
			printf("♡");
		}
		
		Check();
		
		SpawnDelay = 10 + (100 - Score) / 5;
		
		delay++;
		if(delay >= SpawnDelay) {
			delay = 0;
			MakeBlock();
		}
	}
	
	gotoxy(0, 10);
	
	return 0;
}
