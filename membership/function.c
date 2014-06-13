
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
	case 2:
		editMember();
		break;
	case 3:
		eraseMember();
		break;
	case 6:
		searchMember();
		break;
	case 7:
		endProgram();
		break;
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

		if (arr[i]->numId == 0)continue;
		printf("\t%d\t %3s     \t%s\t %s \n", arr[i]->numId, arr[i]->name, arr[i]->address, arr[i]->phone);
	}

	printf("\n\t%c 0을 누르시면 메인 화면으로 돌아갑니다. ", 14);

}

void addMember(void)
{
	int len;
	int initial_fg_color = getfgcolor();
	int initial_bg_color = getbgcolor();
	char buffer[15];
	int i = 0;
	int flag = 0;

	arr[count]->numId = findMax();
	arr[count]->numId += 1;
	_itoa(arr[count]->numId, arr[count]->Id, 10);

	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("추가할 회원의 회원번호 : %d", arr[count]->numId);
	
	
	fflush(stdin);
	do{
		setfgcolor(dark_gray);
		printf("\n\t%c ", 14);
		setfgcolor(initial_fg_color);
		setcolors(initial_fg_color, initial_bg_color);
		printf("추가할 회원의 이름을 입력하세요. ");
		fgets(arr[count]->name, 8, stdin);
	} while ((strlen(arr[count]->name) == 1));
	len = strlen(arr[count]->name)-1;
	arr[count]->name[len] = '\0';
	
	fflush(stdin);
	do{
		setfgcolor(dark_gray);
		printf("\t%c ", 14);
		setfgcolor(initial_fg_color);
		setcolors(initial_fg_color, initial_bg_color);
		printf("추가할 회원의 주소을 입력하세요. ");
		fgets(arr[count]->address, 30, stdin);
	} while ((strlen(arr[count]->address) == 1));
	len = strlen(arr[count]->address)-1;
	arr[count]->address[len] = '\0';

	fflush(stdin);
	
	flag = 0;
	while (1){
		do{
			if (flag == 0){

				setfgcolor(dark_gray);
				printf("\t%c ", 14);
				setfgcolor(initial_fg_color);
				setcolors(initial_fg_color, initial_bg_color);
				printf("추가할 회원의 전화번호을 입력하세요. ");
			}
			flag = 0;
			fgets(buffer, 15, stdin);
		} while (strlen(buffer) == 1);
		len = strlen(buffer) - 1;
		buffer[len] = '\0';
		fflush(stdin);

		for (i = 0; i < strlen(buffer); i++){
	
			if (buffer[i] < 48 || buffer[i] > 57){
				if (buffer[i] == '-') break;
				printf("\t입력된 정보가 잘못되었습니다.숫자만 입력하세요(-입력 가능)");
				getOut();
				flag = 1;
				break;	
			}
		}

		if (flag == 0) break;
	}

	strcpy(arr[count]->phone,buffer);
	//len = strlen(arr[count]->phone) - 1;
	//arr[count]->phone[len] = '\0';
	//fflush(stdin);

	count++;

	printf("\n\t%c 0을 누르시면 메인 화면으로 돌아갑니다. ", 14);

}

void saveEdit(void)
{
	FILE *fp = fopen("data.txt", "wt");
	if (fp == NULL){
		puts("file open error \n");
		return -1;
	}

	fputs("회원 아이디\t회원 이름\t회원주소\t핸드폰 번호\n", fp);
	for (save=0; save < count; save++){
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






void whoIs(int i)
{
	int initial_fg_color = getfgcolor();
	int initial_bg_color = getbgcolor();

	setfgcolor(dark_gray);
	printf("\n\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("찾으시는 회원의 정보입니다. \n\n");
	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("회원 이름: %s\n", arr[i]->name);
	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("회원 번호: %d\n", arr[i]->numId);
	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("회원 주소: %s\n", arr[i]->address);
	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("전화 번호: %s\n", arr[i]->phone);

}
void searchById(int whoId)
{
	i = 0;
	int retry = 0;
	for (i = 0; i < 255; i++){
		if (arr[i]->numId == whoId){
			whoIs(i);
			return;
		}
	}

	printf("\t없는 번호 입니다. 다시 입력해 주세요.");
	scanf_s("%d", &retry, 1);
	searchById(retry);
	

}
void searchByName(char* who)
{
	i = 0;
	int c = 1;
	char retry[30];
	for (i = 0;i<255; i++){
		c = strcmp(who, arr[i]->name);
		if (c == 0){
			whoIs(i);
			return;
		}
	}
	
	while (getchar() != '\n');
	printf("\t없는 이름 입니다. 다시 입력해 주세요. ");
	scanf_s("%s", retry, 30);
	searchByName(retry);
}
void searchByAddress(char* who)
{
	i = 0;
	int c = 1;
	char retry[200];
	for (i = 0;i<255; i++){
		c = strcmp(who, arr[i]->address);
		if (c == 0){
			whoIs(i);
			return;
		}
	}
	
	while (getchar() != '\n');
	printf("\t없는 주소 입니다. 다시 입력해 주세요.");
	scanf_s("%s", retry, 200);
	searchByAddress(retry);
}
void searchByPhone(char* who)
{
	i = 0;
	int c = 1;
	char retry[20];
	for (i = 0;i<255; i++){
		c = strcmp(who, arr[i]->phone);
		if (c == 0){
			whoIs(i);
			return;
		}
	}

	while (getchar() != '\n');
	printf("\t없는 번호 입니다. 다시 입력해 주세요.");
	scanf_s("%s", retry, 20);
	searchByPhone(retry);
}






void editMember(void)
{
	int initial_fg_color = getfgcolor();
	int initial_bg_color = getbgcolor();

	int whichNum;
	int whoId = 0;
	char who[200];

	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("수정할 회원을 찾을 방법을 입력하세요. \n\n\t1번: 회원 이름\n\t2번: 회원 번호\n\t3번: 회원 주소\n\t4번: 회원 전화번호\n\t");

	scanf_s("%d", &whichNum, 1);
	while (whichNum > 4){
		printf("\t잘못 입력하셨습니다. 정확한 숫자를 넣어주세요. ");
		scanf_s("%d", &whichNum, 1);
	}

	switch (whichNum)
	{
	case 1:
		printf("\t회원의 이름을 입력하세요. ");
		scanf_s("%s", who, 30);
		searchByName(who);
		break;
	case 2:
		printf("\t회원의 회원번호를 입력하세요. ");
		scanf_s("%d", &whoId, 1);
		searchById(whoId);
		break;
	case 3:
		printf("\t회원의 주소를 입력하세요. ");
		scanf_s("%s", who, 200);
		searchByAddress(who);
		break;
	case 4:
		printf("\t회원의 전화번호를 입력하세요. ");
		scanf_s("%s", who, 20);
		searchByPhone(who);
		break;
	}
	printf("\n\n");
	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("수정할 회원의 정보를 입력하세요.\n\n\t1번: 회원 이름\n\t2번: 회원번호\n\t3번: 회원 주소\n\t4번: 회원 전화번호\n\t");

	
	scanf_s("%d", &whichNum, 1);

	printf("\t수정된 정보를 입력하세요.  ");
	while (getchar() != '\n');
	switch (whichNum)
	{
	case 1:
		scanf_s("%s", who, 30);
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
		strcpy(arr[i]->phone, who);
		break;
	}

	printf("\n\t회원정보가 수정되었습니다. \n\t%c 0을 누르시면 메인 화면으로 돌아갑니다. ", 14);

}

void eraseMember(void)
{
	int initial_fg_color = getfgcolor();
	int initial_bg_color = getbgcolor();

	int whichNum;
	int whoId = 0;
	char who[200];

	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("삭제할 회원을 찾을 방법을 입력하세요. \n\n\t1번: 회원 이름\n\t2번: 회원 번호\n\t3번: 회원 주소\n\t4번: 회원 전화번호\n\t");

	scanf_s("%d", &whichNum, 1);
	while (whichNum > 4||whichNum==0){
		printf("\t잘못 입력하셨습니다. 정확한 숫자를 넣어주세요. ");
		scanf_s("%d", &whichNum, 1);
	}

	switch (whichNum)
	{
	case 1:
		printf("\t회원의 이름을 입력하세요. ");
		scanf_s("%s", who, 30);
		searchByName(who);
		break;
	case 2:
		printf("\t회원의 회원번호를 입력하세요. ");
		scanf_s("%d", &whoId, 1);
		searchById(whoId);
		break;
	case 3:
		printf("\t회원의 주소를 입력하세요. ");
		scanf_s("%s", who, 200);
		searchByAddress(who);
		break;
	case 4:
		printf("\t회원의 전화번호를 입력하세요. ");
		scanf_s("%s", who, 20);
		searchByPhone(who);
		break;
	}

	arr[i]->numId = NULL;
	strcpy(arr[i]->Id, " ");
	strcpy(arr[i]->name, " ");
	strcpy(arr[i]->address,"");
	strcpy(arr[i]->phone, " ");

	printf("\n\t회원정보가 삭제되었습니다. \n\t%c 0을 누르시면 메인 화면으로 돌아갑니다. ", 14);
}

void searchMember(void){
	int initial_fg_color = getfgcolor();
	int initial_bg_color = getbgcolor();

	int whichNum;
	int whoId = 0;
	char who[200];

	setfgcolor(dark_gray);
	printf("\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("검색할 회원을 찾을 방법을 입력하세요. \n\n\t1번: 회원 이름\n\t2번: 회원 번호\n\t3번: 회원 주소\n\t4번: 회원 전화번호\n\t");


	scanf_s("%d", &whichNum, 1);
	while (whichNum > 4){
		printf("\t잘못 입력하셨습니다. 정확한 숫자를 넣어주세요. ");
		scanf_s("%d", &whichNum, 1);
	}

	switch (whichNum)
	{
	case 1:
		printf("\t회원의 이름을 입력하세요. ");
		scanf_s("%s", who, 30);
		searchByName(who);
		break;
	case 2:
		printf("\t회원의 회원번호를 입력하세요. ");
		scanf_s("%d", &whoId, 1);
		searchById(whoId);
		break;
	case 3:
		printf("\t회원의 주소를 입력하세요. ");
		scanf_s("%s", who, 200);
		searchByAddress(who);
		break;
	case 4:
		printf("\t회원의 전화번호를 입력하세요. ");
		scanf_s("%s", who, 20);
		searchByPhone(who);
		break;
	}


	printf("\n\t%c 0을 누르시면 메인 화면으로 돌아갑니다. ", 14);
	
}

void endProgram(void){
	char userInput;

	printf("\t회원정보 변경내용을 저장하시겠습니까? (s:저장, q:저장 안함) ");
	
	scanf_s("%c", &userInput, 1);
	fflush(stdin);
	while (userInput != 's' && userInput != 'q'){
		printf("\n\t잘못 입력하셨습니다. 다시 입력하세요. ");
		scanf_s("%c", &userInput, 1);
		getchar();
	}

	if (userInput == 's') {
		saveEdit();
		
	}
}

/*
void getOut(void){

	int initial_fg_color = getfgcolor();
	int initial_bg_color = getbgcolor();
	char out;

	setfgcolor(dark_gray);
	printf("\n\t%c ", 14);
	setfgcolor(initial_fg_color);
	setcolors(initial_fg_color, initial_bg_color);
	printf("메인화면으로 나가시려면 q을 눌러주세요. ");
	scanf_s("%c", &out, 1);
	
	if (out == 'q') chooseNum(out);
	
}
*/