#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <stdlib.h>
#include "head.h"

int main(void)
{
	int userNum=0;
	saveStructure();

	printMain();

	do{
		
		scanf_s("%d", &userNum, 1);
		getchar();
		
		if (userNum > 7){
			printf("\t 잘못된 번호를 입력하셨습니다. 다시 입력하세요. ");
			continue;
		}
		system("cls");
		chooseNum(userNum);
	} while (userNum!=7);
	

	system("cls");
	printf("\t프로그램을 종료합니다. ");
	freeStructure();
	return 0;
}
