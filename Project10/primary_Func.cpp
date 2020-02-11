#pragma once
#include "primary_Func.h"

void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void SetWindow()
{
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 460, 325, TRUE);
}

void SetWinPos()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, 450, 150, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Nocursortype()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Info;
	GetConsoleCursorInfo(out, &Info);
	Info.bVisible = FALSE;
	SetConsoleCursorInfo(out, &Info);
}


void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, '  ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void del_text(int x, int y, int length)
{
	HANDLE	hConsoleOut;
	COORD	Home = { x,y };
	DWORD	dummy;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	FillConsoleOutputCharacter(hConsoleOut, ' ', length, Home, &dummy);
}

void gotoXY(int x, int y)
{
	/*
	Hàm di chuyển con trỏ tới tọa độ {x,y}
	Tham số: 
		x,y: tọa độ
	*/
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void color_text(int color)
{
	/*
	Hàm đặt màu cho chữ
	Tham số: 
		color: màu, được quy định ở "primary_Func.h"
	*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ve_khung(int x,int y, int ngang, int doc, const char* style)    
{
	/*
	Hàm vẽ một khung chiều ngang là ngang, chiều doc là doc
	Tham số:
		x,y       : tọa độ góc trên bên trái khung
		ngang, doc: độ dài chiều ngang, dọc của khung
		style     : "small": vẽ khung thành mỏng
                    "big"  : vẽ khung thành dày
			        "game" : vẽ khung game có hiệu ứng.
					"delete": xóa khung
	 */

	char TREN_TRAI, TREN_PHAI, DUOI_TRAI, DUOI_PHAI, DOC, NGANG;
	if (style == "game") {
		int x_cur = x;
		int y_cur = y;
		while (y_cur < y + doc)
		{
			gotoXY(x, y_cur);
			putchar(DOC_GAME);
			gotoXY(x + ngang, y_cur);
			putchar(DOC_GAME);
			Sleep(10);
			y_cur++;
		}
		while (x_cur <= x + ngang)
		{
			gotoXY(x_cur, y);
			putchar(NGANG_DUOI_GAME);
			gotoXY(2 * x + ngang - x_cur, y + doc);
			putchar(NGANG_TREN_GAME);
			Sleep(10);
			x_cur++;
		}
		return;
	}
	else if (style == "small") {
		TREN_TRAI = TREN_TRAI_MONG;
		TREN_PHAI = TREN_PHAI_MONG;
		DUOI_TRAI = DUOI_TRAI_MONG;
		DUOI_PHAI = DUOI_PHAI_MONG;
		DOC = DOC_MONG;
		NGANG = NGANG_MONG;
	}
	else if (style == "big") {
		TREN_TRAI = TREN_TRAI_DAY;
		TREN_PHAI = TREN_PHAI_DAY;
		DUOI_TRAI = DUOI_TRAI_DAY;
		DUOI_PHAI = DUOI_PHAI_DAY;
		DOC = DOC_DAY;
		NGANG = NGANG_DAY;
	}
	else if (style == "delete") {
		TREN_TRAI = TREN_PHAI = DUOI_TRAI = DUOI_PHAI = DOC = NGANG = ' ';
	}

	gotoXY(x, y);
	for (int j = 0; j < doc; j++)
	{
		gotoXY(x, y++);
		for (int i = 0; i < ngang; i++)
		{
			if (i == 0 && j == 0) putchar(TREN_TRAI);						
			else if (i == ngang-1 && j == 0) putchar(TREN_PHAI);					
			else if (i == 0 && j == doc-1) putchar(DUOI_TRAI);					
			else if (i == ngang-1 && j == doc-1) putchar(DUOI_PHAI);					
			else if (j != 0 && j != doc-1 && (i == 0 || i == ngang-1)) putchar(DOC); 
			else if (i != 0 && i != ngang-1 && (j == 0 || j == doc-1)) putchar(NGANG);	
			else printf(" ");
		}

	}
}


bool khung_yesno(int x, int y, const char* message)
{
	/*
	Hàm hiển thị khung với câu hỏi có không
	Tham số:
		x,y: tọa độ góc trên bên trái khung
		message: câu hỏi
	Trả về: 0 nếu không, 1 nếu có
	*/
	ve_khung(x, y, 30, 6, "big");
	
	int len = strlen(message);
	gotoXY(x+(32-len)/2, y+1);
	puts(message);

	gotoXY(x + 20, y + 3);
	printf("KHONG");
	gotoXY(x + 4, y + 3);
	color_text(4);
	putchar(MUITEN);
	printf("CO");
	color_text(DARKWHITE);

	POINT yes, no;
	yes.x = x + 5;
	yes.y = y + 3;
	no.x = x + 20;
	no.y = y + 3;

	int x_cur = yes.x;
	while (1)
	{
		char key = toupper(_getch());
		if (key == 'A') {
			if (x_cur != yes.x) {
				x_cur = yes.x;
				gotoXY(no.x - 1, no.y);
				printf(" KHONG");
				gotoXY(yes.x - 1, yes.y);
				color_text(DARKRED);
				putchar(MUITEN);
				printf("CO");
				color_text(DARKWHITE);
			}
		}
		else if (key == 'D') {
			if (x_cur != no.x) {
				x_cur = no.x;
				gotoXY(yes.x - 1, yes.y);
				printf(" CO");
				gotoXY(no.x - 1, no.y);
				color_text(DARKRED);
				putchar(MUITEN);
				printf("KHONG");
				color_text(DARKWHITE);
			}
		}
		else if (key == ENTER) {
			ve_khung(x, y, 30, 6, "delete");
			return x_cur == yes.x ? 1 : 0;
		}
	}
}

void xoa_chuoi(char a[], int &t, int &vtr)
{
	for (int i = vtr - 1; i <= t - 1; i++)
	{
		a[i] = a[i + 1];
	}
	t--;
	vtr--;
}

void chen_chuoi(char a[], int &t, int &vtr, char x)
{
	for (int i = t; i >= vtr; i--)
	{
		a[i + 1] = a[i];
	}
	a[vtr] = x;
	t++;
	vtr++;
}

bool kt_file_chuatontai(char s[])			
{
	FILE *f = fopen(s, "r");
	if (f == NULL) return 1;
	fclose(f);
	return 0;
}

bool kt_file_hople(char s[])
{
	FILE *f = fopen(s, "w");
	if (f == NULL) return 0;
	fclose(f);
	return 1;
}
