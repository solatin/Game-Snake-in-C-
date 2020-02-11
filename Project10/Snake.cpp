#pragma once
#include "Menu.h"
#include "NewGame.h"
#include "primary_Func.h"

void main()
{
	SetWinPos();
	SetWindow();
	SetConsoleTitle("Game Snake");
	FixConsoleWindow();
	Nocursortype();
	while (1) {
		char load_file[30] = ".";
		switch (menu()) {
		case 0: {
			resume(load_file);
			if (strlen(load_file)>1) newgame(load_file);
			break; 
		}
		case 1: newgame(load_file); break;
		case 2: exit(0);
		}
	}
}