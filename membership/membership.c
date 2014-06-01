#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <stdlib.h>
#include "head.h"

int main(void)
{
	int userNum;
	saveStructure();

	printMain();

	do{
		scanf_s("%d", &userNum, 1);
		system("cls");
		chooseNum(userNum);
	} while (userNum != 7);
	

	
	freeStructure();
	return 0;
}
