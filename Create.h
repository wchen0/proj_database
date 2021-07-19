#include <iostream>

#define _CRT_SECURE_NO_WARNINGS

#pragma once


#define LEN 100
#define MAX_TAB_NUM 10

#define DEBUG
#undef DEBUG

#define nullString "#"

using namespace std;

struct node {
	char (*content)[LEN];
	node* next;
};

struct Table {
	char tableName[LEN];
	char (*column)[LEN];
	node* data;
	int primaryKey;
	int cNum;
	int rNum;
};

extern Table tableArray[MAX_TAB_NUM];
extern int curTabNum;

//List.cc

void initDataList(Table& T);   //initialize the data list of one table with a dummy node

void insertLine(char(*content)[LEN], Table& T);   //insert a line of data(char[][]) ito one table

//Create.cc

void Create(void);

int findTableIndex(char* tabName);

void readLine(char(*ret)[LEN], int* elemNum, char* original);

bool readLine(FILE* fp, char(*ret)[LEN], int* elemNum);

//Insert.cc

void Insert(void);

void renewTableFile(const Table& T);

//Show.cc

void Show(void);

void ShowTableFormat(const Table& T);

//Drop.cc

void Drop(void);

void freeTableData(Table& T);

//Update.cc

void Update(void);

//Delete.cc

void Delete(void);

//Alter.cc

void Alter(void);

//Load.cc

void Load(void);

void load_all_data_of_one_table(int tabIndex);


//Select.cc

#define AND 0
#define OR 1
#define NO_CONDITION 2
#define INVALID_CONDITION -1

void Select(void);

int readCondition(const char(*ret)[LEN], const int strNum, char(*condition)[LEN], const Table& T);

bool conditionCheck(char(*data)[LEN], char(*condition)[LEN], int cNum, int type);

bool invalidString(char* str);


void Help(void);

void DESC(void);

void import_file(void);



//THE EXPRESSION CALCULATE MODULE

//#define DEBUG

#define __STRLEN__ 100
#define __LEN__ 3
#define __INF__ 1000000000.0
#define __EPS__ 1e-3

enum node_type { Optr, Cons };
//Optr: Operant
//Cons: Constant

struct expr_node {
	node_type type;
	double value;
	char str[__LEN__];
};

expr_node* str_to_arr(char* src, int* ansLen);

expr_node* inffix_to_suffix(expr_node* src, int len, int* newLen);

double calculate(char* expr);





void encode(char* str);

void decode(char* str);
