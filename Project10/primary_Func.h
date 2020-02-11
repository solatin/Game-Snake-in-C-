#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <thread>
#include <iostream>
using namespace std;

#define Back			0
#define DARKBLUE		1
#define DARKGREEN		2
#define DARKCYAN		3
#define DARKRED		    4
#define DARKPINK		5
#define DARKYELLOW	    6
#define DARKWHITE		7
#define GREY			8
#define BLUE			9
#define GREEN			10
#define CYAN			11
#define RED			    12
#define PINK			13
#define YELLOW		    14
#define WHITE			15

#define MUITEN        175

#define TREN_TRAI_DAY 201
#define TREN_PHAI_DAY 187
#define DUOI_TRAI_DAY 200
#define DUOI_PHAI_DAY 188
#define DOC_DAY       186
#define NGANG_DAY     205

#define TREN_TRAI_MONG 218
#define TREN_PHAI_MONG 191
#define DUOI_TRAI_MONG 192
#define DUOI_PHAI_MONG 217
#define DOC_MONG        179
#define NGANG_MONG      196


#define DOC_GAME         219
#define NGANG_TREN_GAME  223  
#define NGANG_DUOI_GAME  220

#define ENTER     13
#define BACKSPACE 8
#define ESC       27

void FixConsoleWindow();

void SetWindow();

void Nocursortype();

void SetWinPos();

void clrscr();

void gotoXY(int, int);

void color_text(int);

void del_text(int, int, int);

bool khung_yesno(int, int, const char*);

void ve_khung(int, int, int, int, const char*);

void xoa_chuoi(char[], int&, int&);

void chen_chuoi(char a[], int &t, int &vtr, char x);

bool kt_file_chuatontai(char s[]);

bool kt_file_hople(char s[]);
