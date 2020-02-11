#pragma once
#include "Menu.h"

void resume(char load_file[])
{
	int x = 1;
	int y = 10;
	int doc = 7;
	int ngang = 51;
	ve_khung(x, y, ngang, doc, "big");
	gotoXY(x + ngang / 2 - 2, y);
	printf("RESUME");
	gotoXY(x + ngang / 2 - 7, y + doc - 1);
	printf("Nhan Esc de thoat");


	int so_file;
	FILE *f = fopen("Resume.txt", "r");
	fscanf(f, "%d ", &so_file);
	
	if (so_file == 0) {
		color_text(DARKGREEN);
		gotoXY(x + ngang / 2 - 10, y + 3);
		printf("Khong co file tai len");
		color_text(DARKWHITE);
		while (1) {
			char key = toupper(_getch());
			if (key == ESC) {
				clrscr();
				return ;
			}
		}
	}
	color_text(DARKGREEN);
	gotoXY(x + ngang / 2 - 10, y + 1);
	printf("Chon file ban muon mo:");
	color_text(DARKWHITE);

	char** ten_file;
	ten_file = new char*[so_file];
	for (int i = 0; i < so_file; i++) {
		ten_file[i] = new char[20];
	}
	for (int i = 0; i < so_file; i++){
			fgets(ten_file[i], 20, f);
			ten_file[i][strlen(ten_file[i])-1] = '\0';
		}
	fclose(f);
	
	int so_hienthi = 4;
	int i = 0; 
	while (i < so_file && i < so_hienthi) {
		if (i == 0) {
			gotoXY(x + ngang / 2 - 6, y + 2);
			color_text(DARKYELLOW);
			putchar(MUITEN);
		}
		gotoXY(x + ngang / 2 - 5, y + 2 + i);
		cout << ten_file[i];
		color_text(DARKWHITE);
		i++;
	}
	gotoXY(x + ngang / 2 - 2, y + doc - 1);
	
	
	int chon = 0;
	int batdau = 0;
	while (1){
		char key = toupper(_getch());
		_getch();
		
		if (key == 'S') {
			if (chon < so_file-1) {
				if (chon == batdau + so_hienthi-1) batdau++;
				chon++;
			}
		}
		else if (key == 'W') {
			if (chon > 0) {
				if (chon == batdau) batdau--;
				chon--;
			}
		}
		else if (key == ESC) {
			break;
		}
		else if (key == ENTER) {
			strcpy(load_file, ten_file[chon]);
			break;
		}
		for (int i = 0; i <= so_hienthi-1; i++) {
			del_text(x + 1, y + 2 + i, 40);
		}
		int y_cur = y + 2;
		int i = batdau;
		while(i < so_file && i <= batdau + so_hienthi-1){
			if (i == chon) {
				gotoXY(x + ngang / 2 - 6, y_cur);
				color_text(DARKYELLOW);
				putchar(MUITEN);
			}
			gotoXY(x + ngang / 2 - 5, y_cur);
			cout<<ten_file[i];
			color_text(DARKWHITE);
			y_cur++;
			i++;
		}
		gotoXY(x + ngang / 2 - 2, y + doc - 1);
	}
	clrscr();
	for (int i = 0; i < so_file; i++) delete[]ten_file[i];
	delete[]ten_file;
	return ;
}

void ve_logo() {
	FILE* f = fopen("chu_snake.txt", "rb");
	if (f == NULL) return;
	char temp;
	srand(time(NULL));
	int y_cur = 2;
	int x_cur = 7;
	gotoXY(x_cur, y_cur);
	while (!feof(f)) {
		temp = fgetc(f);
		if (temp == '\n') {
			gotoXY(x_cur, ++y_cur);
			continue;
		}
		putchar(temp);
	}
	for (int i = 0; i < 37; i++) {
		gotoXY(++x_cur, 8);
		putchar(NGANG_DAY);
	}
	fclose(f);
}

int menu()
{
	POINT option[3];
	char tag[3][10];
	ve_logo();
	strcpy(tag[0], "RESUME");
	strcpy(tag[1], "NEW GAME");
	strcpy(tag[2], "QUIT");

	for (int i = 0; i < 3; i++){
		option[i].x = 25;
		option[i].y = 12 + 2 * i;
	}
	for (int i = 0; i < 3; i++){
		if (i == 0) {
			gotoXY(option[i].x - 1, option[i].y);
			color_text(DARKRED);
			putchar(MUITEN);
			cout << tag[i];
			color_text(DARKWHITE);
		}
		else {
			gotoXY(option[i].x, option[i].y);
			color_text(DARKGREEN);
			cout << tag[i];
			color_text(DARKWHITE);
		}
	}

	int choosing = 0;

	while (1){
		char key = toupper(_getch());
		if (key == 'W' && choosing > 0) choosing--;
		else if (key == 'S' && choosing < 2) choosing++;
		else if (key == ENTER) {
			_getch();		
			del_text(0,12 , 2000);
			color_text(DARKWHITE);
			return choosing;
		}

		for (int i = 0; i < 3; i++){
			if (choosing == i) {
				color_text(DARKRED);
				gotoXY(option[i].x - 1, option[i].y);
				putchar(MUITEN);
				cout << tag[i];
				color_text(DARKWHITE);
			}
			else {
				gotoXY(option[i].x - 1, option[i].y);
				color_text(DARKGREEN);
				cout<<" "<<tag[i];
			}
		}
	}
}