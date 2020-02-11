#pragma once
#include "primary_Func.h"


#define HEIGHT_CORNER 0
#define WIDTH_CORNER 1
#define WIDTH_CONSOLE 50
#define HEIGHT_CONSOLE 15
#define MAX_SIZE_SNAKE 20
#define MAX_SIZE_FOOD 4
#define MAX_SPEED 3


#define FOOD_SYMBOL 232
struct _POINT
{
	int x, y, c;
};

struct Screen {
	int size;
	POINT dot[MAX_SIZE_SNAKE];
	char direct;
	char lock_direct;
	int speed;
	POINT food;
	int food_index;
	POINT gate;
	int state;	
	bool upgrade;
};



void FixConsoleWindow();





void ve_snakeandfood(Screen&);
void xoa_snakeandfood(Screen);
void cap_nhat(Screen);
void batdau_game(Screen&, char load_file[]);
void newgame(char load_file[]);
void hieuung_chet(Screen);