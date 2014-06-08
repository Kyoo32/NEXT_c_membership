
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

//����, ���ڻ� ����
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

	printf("ȸ�� ���� ���α׷� ");

	setfgcolor(dark_gray);
	printf("%c\n", 14);

	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);

	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 1,6,6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 2);
	printf("\t%c   1. ȸ�� ���   %c   5. ȸ�� ����   %c\n", 5, 14, 5);
	printf("\t%c   2. ȸ�� ����   %c   6. ȸ�� �˻�   %c\n", 5, 14, 5);
	printf("\t%c   3. ȸ�� ����   %c                  %c\n", 5, 14, 5);
	printf("\t%c   4. ���� �ϱ�   %c   7. ���� �ϱ�   %c\n", 5, 14, 5);
	printf("\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n", 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4);
	printf("\t%c ��ȣ�� �Է��ϼ���~ ", 14);

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
	case 2:
		editMember();
		break;
	//case 3:
		//eraseMember();
		//break;

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

	printf("\n\t%c 0�� �����ø� ���� ȭ������ ���ư��ϴ�. ", 14);

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
	printf("�߰��� ȸ���� ȸ����ȣ : %d", arr[count]->numId);
	
	while (getchar() != '\n');
	setfgcolor(dark_gray);
	printf("\n\t%c ",14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("�߰��� ȸ���� �̸��� �Է��ϼ���: ");
	gets(arr[count]->name);

	
	setfgcolor(dark_gray);
	printf("\t%c ",14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("�߰��� ȸ���� �ּ��� �Է��ϼ���. ");
	gets(arr[count]->address);

	
	setfgcolor(dark_gray);
	printf("\t%c ",14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("�߰��� ȸ���� ��ȣ��ȣ�� �Է��ϼ���. ");
	gets(arr[count]->phone);

	count++;

	printf("\n\t%c 0�� �����ø� ���� ȭ������ ���ư��ϴ�. ", 14);

}

void saveEdit(void)
{
	FILE *fp = fopen("data.txt", "r+");
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

	printf("\t%c ����ƽ��ϴ�.\n\t%c 0�� �����ø� ���� ȭ������ ���ư��ϴ�. ", 14, 14);
}

void editMember(void)
{
	int initial_fg_color = getfgcolor();
	int initial_bg_color = getbgcolor();
	
	int whichNum;
	int whoId=0;
	char who[200];
	
	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("������ ȸ���� ã�� ����� �Է��ϼ���. \n\n\t1��: ȸ�� �̸�\n\t2��: ȸ�� ��ȣ\n\t3��: ȸ�� �ּ�\n\t4��: ȸ�� ��ȭ��ȣ\n\t");

	scanf_s("%d", &whichNum, 1);

	switch(whichNum)
	{
	case 1:
		printf("\tȸ���� �̸��� �Է��ϼ���. ");
		scanf_s("%s", who, 30);
		searchByName(who);
		break;
	case 2:
		printf("\tȸ���� ȸ����ȣ�� �Է��ϼ���. ");
		scanf_s("%d",&whoId, 1);
		searchById(whoId);
		break;
	case 3:
		printf("\tȸ���� �ּҸ� �Է��ϼ���. ");
		scanf_s("%s",who,200);
		searchByAddress(who);
		break;
	case 4:
		printf("\tȸ���� ��ȭ��ȣ�� �Է��ϼ���. ");
		scanf_s("%s",who, 20);
		searchByPhone(who);
		break;
	}
	printf("\n\n");
	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("������ ȸ���� ������ �Է��ϼ���.\n\n\t1��: ȸ�� �̸�\n\t2��: ȸ����ȣ\n\t3��: ȸ�� �ּ�\n\t4��: ȸ�� ��ȭ��ȣ\n\t");

	scanf_s("%d", &whichNum, 1);

	printf("\t������ ������ �Է��ϼ���.  ");
	switch(whichNum)
	{
	case 1:
		scanf_s("%s",who,30);
		strcpy(arr[i]->name, who);
		break;
	case 2:
		scanf_s("%d", &whoId, 1);
		arr[i]->numId = whoId;
		break;
	case 3:
		gets(who);
		strcpy(arr[i]->address, who);
		break;
	case 4:
		gets(who);
		strcpy(arr[i]->phone,who);
		break;
	}

	printf("\n\tȸ�������� �����Ǿ����ϴ�. \n\t%c 0�� �����ø� ���� ȭ������ ���ư��ϴ�. ", 14);

} 

void whoIs(int i)
{
	int initial_fg_color = getfgcolor();
	int initial_bg_color = getbgcolor();

	setfgcolor(dark_gray);
	printf("\n\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("ã���ô� ȸ���� �����Դϴ�. \n\n");
	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("ȸ�� �̸�: %s\n", arr[i]->name);
	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("ȸ�� ��ȣ: %d\n", arr[i]->numId);
	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("ȸ�� �ּ�: %s\n", arr[i]->address);
	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("��ȭ ��ȣ: %s\n", arr[i]->phone);

}
void searchById(int whoId)
{
	i = 0;
	for (i = 0; arr[i]->numId != whoId; i++);

	whoIs(i);

}
void searchByName(char* who)
{
	i = 0;
	int c = 1;
	for (i = 0;; i++){
		c = strcmp(who, arr[i]->name);
		if (c == 0) break;
	}


	whoIs(i);
}
void searchByAddress(char* who)
{
	i = 0;
	int c = 1;
	for (i = 0;; i++){
		c = strcmp(who, arr[i]->address);
		if (c == 0) break;
	}
	whoIs(i);
}
void searchByPhone(char* who)
{
	i = 0;
	int c = 1;
	for (i = 0;; i++){
		c = strcmp(who, arr[i]->phone);
		if (c == 0) break;
	}
	whoIs(i);
}






/*

void eraseMember(void)
{ }

*/