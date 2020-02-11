#pragma once
#include "NewGame.h"



char MSSV[9] = "18120537";


bool kt_hople(Screen screen, int x, int y)
{
	for (int i = 0; i < screen.size; i++) {
		if (screen.dot[i].x == x && screen.dot[i].y == y) return false;
	}
	return true;
}

void tao_thucan(Screen &screen)
{
	int x, y;
	srand(time(NULL));
	do {
		x = rand() % (WIDTH_CONSOLE - 3) + WIDTH_CORNER + 2;
		y = rand() % (HEIGHT_CONSOLE - 3) + HEIGHT_CORNER + 2;
	} while (!kt_hople(screen, x, y));
	screen.food = { x, y };
}

void tao_cong(Screen& scr)
{
	int x, y;
	srand(time(NULL));
	do {
		x = rand() % (WIDTH_CONSOLE - 3) + WIDTH_CORNER + 2;
		y = rand() % (HEIGHT_CONSOLE - 6) + HEIGHT_CORNER + 3;
	} while (!kt_hople(scr, x, y));
	scr.gate = { x, y };
}


void khoitao_dulieu(Screen& scr, char load_file[])
{
	if (strlen(load_file) >1 ) {
		FILE* f = fopen(load_file, "rb");
		fscanf(f, "%d   \n", &scr.size);
		for (int i = 0; i < scr.size; i++)  fscanf(f, "%d %d  ", &scr.dot[i].x, &scr.dot[i].y);
		fscanf(f, "\n%c %c", &scr.direct, &scr.lock_direct);
		fscanf(f, "%d   \n", &scr.speed);
		fscanf(f, "%d %d   \n", &scr.food.x, &scr.food.y);
		fscanf(f, "%d   \n", &scr.food_index);
		fscanf(f, "%d  %d\n", &scr.gate.x, &scr.gate.y);
		fscanf(f, "%d", &scr.upgrade);
		fscanf(f, "%d", &scr.state);
		fclose(f);
	}
	else {
		scr.size = 6;
		scr.dot[0] = { 10, 5 }; scr.dot[1] = { 11, 5 };
		scr.dot[2] = { 12, 5 }; scr.dot[3] = { 13, 5 };
		scr.dot[4] = { 14, 5 }; scr.dot[5] = { 15, 5 };
		for (int i = 0; i < scr.size; i++) {
			scr.dot[i].x += WIDTH_CORNER;
			scr.dot[i].y += HEIGHT_CORNER;
		}
		scr.direct = 'D';
		scr.lock_direct = 'A';
		scr.food_index = 0;
		scr.speed = 1;
		scr.state = 1;
		scr.gate = { -1,-1 };
		scr.upgrade = false;
		tao_thucan(scr);
	}
	
}

void batdau_game(Screen& scr, char load_file[])
{
	clrscr();
	khoitao_dulieu(scr, load_file);
	ve_khung(WIDTH_CORNER, HEIGHT_CORNER, WIDTH_CONSOLE, HEIGHT_CONSOLE, "game");
	color_text(DARKGREEN);
	gotoXY(2, HEIGHT_CONSOLE + 1);
	cout << "Thuc an: ";
	gotoXY(40, HEIGHT_CONSOLE + 1);
	cout << "Level: ";
	color_text(DARKWHITE);
	cap_nhat(scr);
}

void cap_nhat(Screen scr)
{
	gotoXY(11, HEIGHT_CONSOLE + 1);
	cout << scr.food_index;
	gotoXY(47, HEIGHT_CONSOLE + 1);
	cout << scr.speed;
}


void thoat_game(HANDLE h) 
{
	clrscr();
	TerminateThread(h, 0);
}

int hoi_thoat_game()
{
	int X = WIDTH_CORNER + WIDTH_CONSOLE / 2 - 15;
	int Y = HEIGHT_CORNER + HEIGHT_CONSOLE / 2 - 4;
	return khung_yesno(X, Y, "Ban co muon thoat game?");
}

void pause_game(HANDLE h, Screen scr)
{
	xoa_snakeandfood(scr);
	SuspendThread(h);
	SuspendThread(h);
}


bool kt_cham_cong(Screen scr)
{
	if (scr.upgrade == false) return false;
	if (scr.dot[scr.size - 1].x == scr.gate.x && scr.dot[scr.size - 1].y == scr.gate.y) return true;
	if (scr.dot[scr.size - 1].x == scr.gate.x + 1 && scr.dot[scr.size - 1].y == scr.gate.y) return true;
	if (scr.dot[scr.size - 1].x == scr.gate.x - 1 && scr.dot[scr.size - 1].y == scr.gate.y) return true;
	if (scr.dot[scr.size - 1].x == scr.gate.x + 1 && scr.dot[scr.size - 1].y == scr.gate.y - 1) return true;
	if (scr.dot[scr.size - 1].x == scr.gate.x - 1 && scr.dot[scr.size - 1].y == scr.gate.y - 1) return true;
	return false;
}

bool kt_cham_than(Screen scr)
{
	for (int i = 0; i < scr.size - 1; i++) {
		if (scr.dot[scr.size - 1].x == scr.dot[i].x && scr.dot[scr.size - 1].y == scr.dot[i].y)
			return true;
	}
	return false;
}

void hieuung_chet(Screen scr)
{
	for (int i = 0; i < 6; i++) {
		ve_snakeandfood(scr);
		Sleep(150);
		xoa_snakeandfood(scr);
		Sleep(150);
	}
}

void xuli_chet(Screen& scr)
{
	scr.state = 0;
	hieuung_chet(scr);
}

void xuli_cham_than(Screen& scr)
{
	if (kt_cham_than(scr)) {
		xuli_chet(scr);
	}
}


void ve_cong(Screen scr, bool in = true)
{
	if (in == true) {
		gotoXY(scr.gate.x - 1, scr.gate.y - 1);
		printf("%c %c", 219, 219);
		gotoXY(scr.gate.x - 1, scr.gate.y);
		printf("%c%c%c", 219, 219, 219);
	}
	else {
		gotoXY(scr.gate.x - 1, scr.gate.y);
		printf("%c %c", 219, 219);
		gotoXY(scr.gate.x - 1, scr.gate.y-1);
		printf("%c%c%c", 219, 219, 219);
	}
	gotoXY(WIDTH_CORNER, HEIGHT_CORNER);

}

void xoa_cong(Screen& scr, bool in = true)
{
	if (in == true) {
		gotoXY(scr.gate.x - 1, scr.gate.y - 1);
		printf("   ");
		gotoXY(scr.gate.x - 1, scr.gate.y);
		printf("   ");
	}
	else {
		gotoXY(scr.gate.x - 1, scr.gate.y);
		printf("   ");
		gotoXY(scr.gate.x - 1, scr.gate.y - 1);
		printf("   ");
	
	}
}

void ve_snakeandfood(Screen& scr)
{
	for (int i = 0; i < scr.size; i++) {
		if (i == scr.size - 1) {
			color_text(YELLOW);
			gotoXY(scr.dot[i].x, scr.dot[i].y);
			putchar(254);
		}
		else {
			color_text(DARKWHITE);
			gotoXY(scr.dot[i].x, scr.dot[i].y);
			putchar(MSSV[i % 8]);
		}
	}
	color_text(DARKWHITE);
	if (scr.upgrade == false) {
		if (scr.dot[0].x == scr.dot[1].x && scr.dot[0].y == scr.dot[1].y) ve_cong(scr, false);
		else {
			if (scr.gate.x != -1) {
				xoa_cong(scr, false);
				scr.gate.x = -1;
			}
			gotoXY(scr.food.x, scr.food.y);
			if (scr.food_index == MAX_SIZE_FOOD - 1) color_text(RED);
			putchar(FOOD_SYMBOL);
			color_text(DARKWHITE);

		}
	}
	else ve_cong(scr);
}

void xoa_snakeandfood(Screen scr)
{
	for (int i = 0; i < scr.size; i++) {
		del_text(scr.dot[i].x, scr.dot[i].y, 1);
	}
	if (scr.upgrade == false) del_text(scr.food.x, scr.food.y, 1);
}


void an(Screen& screen)
{
	screen.dot[screen.size] = screen.food;
	screen.size++;
	if (screen.food_index == MAX_SIZE_FOOD - 1) {
		screen.food_index = 0;
		gotoXY(11, HEIGHT_CONSOLE + 1);
		cout << '4';
		screen.upgrade = true;
		tao_cong(screen);
		ve_cong(screen);
	}
	else {
		screen.food_index++;
		tao_thucan(screen);
		cap_nhat(screen);
	}
}

void upgrade(Screen& scr)
{
	Screen temp = scr;
	ve_cong(temp);
	while (temp.size != 0) {
		xoa_snakeandfood(temp);
		xoa_cong(temp);
		for (int i = 0; i < temp.size - 1; i++)
			temp.dot[i] = temp.dot[i + 1];
		temp.size--;
		ve_snakeandfood(temp);
		color_text(temp.size % 12 + 2);
		ve_cong(temp);
		color_text(DARKWHITE);
		Sleep(180 - 35 * temp.speed);
	}

	for (int i = 0; i < scr.size; i++) {
		ve_cong(scr);
		Sleep(50);
		xoa_cong(scr);
		Sleep(50);
	}
	temp.size = scr.size;
	scr = temp;
	scr.upgrade = false;
	if (scr.speed == MAX_SPEED) {
		scr.speed = 1;
		scr.size = 6;
	}
	else scr.speed++;
	tao_thucan(scr);
	cap_nhat(scr);
}


void di_phai(Screen& scr)
{
	if (scr.dot[scr.size - 1].x + 1 >= WIDTH_CORNER + WIDTH_CONSOLE || kt_cham_cong(scr)) {
		xuli_chet(scr);
	}
	else {
		if (scr.upgrade == false && scr.gate.x==-1) {
			if (scr.dot[scr.size - 1].x + 1 == scr.food.x && scr.dot[scr.size - 1].y == scr.food.y) {
				an(scr);
			}
		}
		for (int i = 0; i < scr.size - 1; i++)
			scr.dot[i] = scr.dot[i + 1];
		scr.dot[scr.size - 1].x++;
	}
}

void di_trai(Screen& scr)
{
	if (scr.dot[scr.size - 1].x - 1 <= WIDTH_CORNER || kt_cham_cong(scr)) {
		xuli_chet(scr);
	}
	else {
		if (scr.upgrade == false && scr.gate.x == -1) {
			if (scr.dot[scr.size - 1].x - 1 == scr.food.x && scr.dot[scr.size - 1].y == scr.food.y) {
				an(scr);
			}
		}
		for (int i = 0; i < scr.size - 1; i++)
			scr.dot[i] = scr.dot[i + 1];
		scr.dot[scr.size - 1].x--;
	}
}

void di_len(Screen& scr)
{
	if (scr.dot[scr.size - 1].y - 1 <= HEIGHT_CORNER || kt_cham_cong(scr)) {
		xuli_chet(scr);
	}
	else {
		if (scr.upgrade == false && scr.gate.x == -1) {
			if (scr.dot[scr.size - 1].x == scr.food.x && scr.dot[scr.size - 1].y - 1 == scr.food.y) {
				an(scr);
			}
		}
		for (int i = 0; i < scr.size - 1; i++) {
			scr.dot[i].x = scr.dot[i + 1].x;
			scr.dot[i].y = scr.dot[i + 1].y;
		}
		scr.dot[scr.size - 1].y--;
	}
}

void di_xuong(Screen& scr)
{
	if (scr.dot[scr.size - 1].y + 1 >= HEIGHT_CORNER + HEIGHT_CONSOLE || kt_cham_cong(scr)) {
		xuli_chet(scr);
	}
	else {
		if (scr.upgrade == true) {
			if (scr.dot[scr.size - 1].x == scr.gate.x && scr.dot[scr.size - 1].y + 1 == scr.gate.y)
				upgrade(scr);
		}
		else if (scr.gate.x == -1)
				if (scr.dot[scr.size - 1].x == scr.food.x && scr.dot[scr.size - 1].y + 1 == scr.food.y) {
					an(scr);
				}
		for (int i = 0; i < scr.size - 1; i++)
			scr.dot[i] = scr.dot[i + 1];
		scr.dot[scr.size - 1].y++;
	}
}


void ghi_file(Screen scr, const char* tenfile)
{
	FILE* f = fopen(tenfile, "wb");
	fprintf(f, "%d   \n", scr.size);
	for (int i = 0; i < scr.size; i++)  fprintf(f, "%d %d  ", scr.dot[i].x, scr.dot[i].y);
	fprintf(f, "\n%c %c   \n", scr.direct, scr.lock_direct);
	fprintf(f, "%d   \n", scr.speed);
	fprintf(f, "%d %d   \n", scr.food.x, scr.food.y);
	fprintf(f, "%d   \n", scr.food_index);
	fprintf(f, "%d  %d   \n", scr.gate.x, scr.gate.y);
	fprintf(f, "%d   \n", scr.upgrade);
	fprintf(f, "%d", scr.state);
	fclose(f);

	FILE *g = fopen("Resume.txt", "r+b");
	fseek(g, 0L, SEEK_END);
	fprintf(g, "%s\n", tenfile);
	fseek(g, 0, SEEK_SET);
	int dem;
	fscanf(g, "%d", &dem);
	fseek(g, 0L, SEEK_SET);
	fprintf(g, "%d", dem + 1);
	fclose(g);
}

void nhap_tenfile(int x, int y, int khung_len, char tenfile[])
{
	ve_khung(x - 2, y - 4, 30, 9, "big");
	while (1) {
		gotoXY(x, y - 2);
		cout << "Nhap ten file: ";
		ve_khung(x, y, khung_len, 3, "small");
		_getch();
		strcpy(tenfile, ".txt");
		int ten_len = strlen(tenfile);		
		gotoXY(x + 2, y + 1);
		cout << tenfile;
		int x_cur = 0; //vị trí hiện hành của con trỏ trong chuỗi
		gotoXY(x + 1, y + 1);

		while (1) {
			char key = _getch();
			_getch();
			if (key == ENTER) {
				break;
			}
			else if (key == BACKSPACE){
				if (ten_len == 4) continue;
				xoa_chuoi(tenfile, ten_len, x_cur);
			}
			else {
				chen_chuoi(tenfile, ten_len, x_cur, key);
			}
			del_text(x + 1, y + 1, 24);
			gotoXY(x + 1, y + 1);
			cout << tenfile;
			gotoXY(x + 1 + ten_len - 4, y + 1);
		}
		if (!kt_file_chuatontai(tenfile)) {
			gotoXY(x + 1, y + 3);
			color_text(DARKRED);
			cout << "File da ton tai!";
			color_text(DARKWHITE);
			_getch();
			del_text(x + 1, y + 3, 24);
			continue;
		}
		if (!kt_file_hople(tenfile)) {
			gotoXY(x + 1, y + 3);
			color_text(DARKRED);
			cout << "Ten file khong hop le!";
			color_text(DARKWHITE);
			_getch();
			del_text(x + 1, y + 3, 24);
			continue;
		}
		gotoXY(x, y+3);
		color_text(DARKGREEN);
		cout << "Luu thanh cong!";
		color_text(DARKWHITE);
		_getch();
		ve_khung(x - 2, y - 4, 30, 9, "delete");
		return;
	}
}

void luu_game(Screen& scr)
{
	int X = WIDTH_CORNER + WIDTH_CONSOLE / 2 - 15;
	int Y = HEIGHT_CORNER + HEIGHT_CONSOLE / 2 - 4;
	char tenfile[50];
	switch (khung_yesno(X, Y, "Ban co muon luu game?")) {
	case 1: {
		nhap_tenfile(X + 2, Y + 4, 26, tenfile);
		ghi_file(scr, tenfile);
		return;
	}
	case 0: return;
	}
}


void ThreadFunc(Screen &scr)
{
	while (1) {
		if (scr.state == 1) {
			xoa_snakeandfood(scr);
			switch (scr.direct) {
			case 'A': di_trai(scr); break;
			case 'D': di_phai(scr); break;
			case 'W': di_len(scr); break;
			case 'S': di_xuong(scr); break;
			}
			xuli_cham_than(scr);
			ve_snakeandfood(scr);
			Sleep(180 - 30 * scr.speed);
		}
	}

}

void newgame(char load_file[])
{
	Screen scr;
	batdau_game(scr, load_file);
	thread t1(ThreadFunc, ref(scr));
	HANDLE handle_t1 = t1.native_handle();	
	char temp;
	while (1) {
		temp = toupper(_getch());
		if (scr.state == 1) {
			if (temp == 'P') {
				pause_game(handle_t1, scr);
				gotoXY(15, HEIGHT_CONSOLE+1);
				cout << "Nhan ENTER de tiep tuc";
				_getch();
			}
			else if (temp == ESC) {
				pause_game(handle_t1, scr);
				if (hoi_thoat_game() == 1) {
					thoat_game(handle_t1);
					t1.join();
					return;
				}
			}
			else if (temp == 'L') {
				pause_game(handle_t1, scr);
				luu_game(scr);
			}
			else {
				del_text(15, HEIGHT_CONSOLE +1, 25);
				ResumeThread(handle_t1);
				if ((temp != scr.lock_direct) && (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S'))
				{
					if (temp == 'D') scr.lock_direct = 'A';
					else if (temp == 'A') scr.lock_direct = 'D';
					else if (temp == 'S') scr.lock_direct = 'W';
					else if (temp == 'W') scr.lock_direct = 'S';
					scr.direct = temp;
				}
			}
		}
		else {
			hieuung_chet(scr);
			pause_game(handle_t1, scr);
			int X = WIDTH_CORNER + WIDTH_CONSOLE / 2 - 15;
			int Y = HEIGHT_CORNER + HEIGHT_CONSOLE / 2 - 4;
			if (khung_yesno(X, Y, "Ban co muon choi tiep?") == 1){
				batdau_game(scr, load_file);
			}
			else {
				thoat_game(handle_t1);
				t1.join();
				return;
			}
		}
	}
}
