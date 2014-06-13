


typedef struct person{
	char Id[7];
	int numId;
	char name[14];
	char address[200];
	char phone[20];
}Person;


//배경색, 글자색 지정
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



//검색기능
void searchByName(char*);

void searchById(int);

void searchByAddress(char*);

void searchByPhone(char*);

void whoIs(int);
// 



void editMember(void);

void eraseMember(void);

void searchMember(void);

void endProgram(void);








