


typedef struct person{
	char Id[7];
	int numId;
	char name[30];
	char address[200];
	char phone[20];
}Person;


//����, ���ڻ� ����
int getcolors();

int getfgcolor();

int getbgcolor();

void setfgcolor(int color);

void setbgcolor(int color);

void setcolors(int fg, int bg);


void printMain(void);

void chooseNum(int);

void printMember(void);

void saveStructure(void);

void freeStructure(void);

int findMax(void);

void addMember(void);

void saveEdit(void);