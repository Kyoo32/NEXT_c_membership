
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <stdlib.h>
#include "head.h"

int i = 0;
int count = 0;
int save = 0;
char buf[100];
Person *arr[255];

//배경색, 글자색 지정
enum
{
	black,
	dark_blue,
	dark_green,
	dark_cyan,
	dark_red,
	dark_magenta,
	dark_yellow,
	light_gray,
	dark_gray,
	light_blue,
	light_green,
	light_cyan,
	light_red,
	light_magenta,
	light_yellow,
	white
};

int getcolors()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
		);
	return csbi.wAttributes;
}

int getfgcolor()
{
	return getcolors() & 0x0F;
}

int getbgcolor()
{
	return getcolors() >> 4;
}

void setfgcolor(int color)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		(getcolors() & 0xF0) | (color & 0x0F)
		);
}

void setbgcolor(int color)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		((color & 0x0F) << 4) | (getcolors() & 0x0F)
		);
}

void setcolors(int fg, int bg)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		((bg & 0x0F) << 4) | (fg & 0x0F)
		);
}

//


void printMain(void)
{
	int initial_fg_color = getfgcolor();
	int initial_bg_color = getbgcolor();

	setfgcolor(dark_gray);
	printf("\n\t\t %c ", 14);

	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);

	printf("회원 관리 프로그램 ");

	setfgcolor(dark_gray);
	printf("%c\n", 14);

	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);

	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 1,6,6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 2);
	printf("\t%c   1. 회원 등록   %c   5. 회원 보기   %c\n", 5, 14, 5);
	printf("\t%c   2. 회원 수정   %c   6. 회원 검색   %c\n", 5, 14, 5);
	printf("\t%c   3. 회원 삭제   %c                  %c\n", 5, 14, 5);
	printf("\t%c   4. 저장 하기   %c   7. 종료 하기   %c\n", 5, 14, 5);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n", 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4);
	printf("\t%c 번호를 입력하세요~ ", 14);

}

void chooseNum(int num)
{
	switch(num)
	{
	case 5:
		printMember();
		break;
	case 0:
		printMain();
		break;
	case 1:
		addMember();
		break;
	case 4:
		saveEdit();
		break;

	}
}

void saveStructure(void){

	for (i = 0; i < 255; i++){
		arr[i] = (Person *)malloc(sizeof(Person));
	}

	FILE *fp = fopen("data.txt", "rt");
	if (fp == NULL){
		puts("file open error \n");
		return -1;
	}

	fgets(buf, sizeof(buf), fp);
	for (i = 0;; i++){
		if (fscanf(fp, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", arr[i]->Id, arr[i]->name, arr[i]->address, arr[i]->phone) == EOF)
			break;
		count++;
	};

	for (i = 0; i < count; i++){
		arr[i]->numId = atoi(arr[i]->Id);
	}

	fclose(fp);

	save = count;
}

void freeStructure(void)
{
	for (i = 0; i < 255; i++){
		free(arr[i]);
	}
}

int findMax(void){
	int max = 0;
	int i = 0;

	for (i = 0; i < count; i++){
		max = (max>(arr[i]->numId)) ? max : arr[i]->numId;
	}
	
	return max;
}

void printMember(void)
{
	int initial_fg_color = getfgcolor();
	int initial_bg_color = getbgcolor();

	setfgcolor(dark_gray);
	printf(" \t%c ID %c\t %c NAME %c\t\t%c ADDRESS %c\t\t%c PHONE %c\n\n", 14, 14, 14, 14, 14, 14, 14, 14);
	setfgcolor(initial_fg_color);

	setcolors(initial_fg_color, initial_bg_color);

	for (i = 0; i < count; i++){

		printf("\t%d\t %3s     \t%s\t %s \n", arr[i]->numId, arr[i]->name, arr[i]->address, arr[i]->phone);
	}

	printf("\n\t%c 0을 누르시면 메인 화면으로 돌아갑니다. ", 14);

}

void addMember()
{
	
	int initial_fg_color = getfgcolor();
	int initial_bg_color = getbgcolor();

	
	arr[count]->numId = findMax();
	arr[count]->numId += 1;
	_itoa(arr[count]->numId, arr[count]->Id, 10);

	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("추가할 회원의 회원번호 : %d", arr[count]->numId);
	
	while (getchar() != '\n');
	setfgcolor(dark_gray);
	printf("\n\t%c ",14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("추가할 회원의 이름을 입력하세요: ");
	gets(arr[count]->name);

	
	setfgcolor(dark_gray);
	printf("\t%c ",14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("추가할 회원의 주소을 입력하세요. ");
	gets(arr[count]->address);

	
	setfgcolor(dark_gray);
	printf("\t%c ",14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("추가할 회원의 전호번호을 입력하세요. ");
	gets(arr[count]->phone);

	count++;

	printf("\n\t%c 0을 누르시면 메인 화면으로 돌아갑니다. ", 14);

}

void saveEdit(void)
{
	FILE *fp = fopen("data.txt", "at");
	if (fp == NULL){
		puts("file open error \n");
		return -1;
	}

	for (; save < count; save++){
		fputs(arr[save]->Id, fp);
		fputs("\t", fp);
		fputs(arr[save]->name, fp);
		fputs("\t", fp);
		fprintf(fp, "%s", arr[save]->address);
		fputs("\t", fp);
		fputs(arr[save]->phone, fp);
		fputs("\n", fp);
	}


	fclose(fp);

	printf("\t%c 저장됐습니다.\n\t%c 0을 누르시면 메인 화면으로 돌아갑니다. ", 14, 14);
}
