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
			printf("\t �߸��� ��ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �Է��ϼ���. ");
			continue;
		}
		system("cls");
		chooseNum(userNum);
	} while (userNum!=7);
	

	system("cls");
	printf("\t���α׷��� �����մϴ�. ");
	freeStructure();
	return 0;
}
