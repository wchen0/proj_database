#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Create.h"


Table tableArray[MAX_TAB_NUM];
int curTabNum;


//通过表的名字，获得表在数组中的下標
int findTableIndex(char* tabName) {
	int tabIndex = 0;
	for (tabIndex = 0; tabIndex < curTabNum; tabIndex++) {
		if (strcmp(tabName, tableArray[tabIndex].tableName) == 0) return tabIndex;
	}
	//when tabIndex == curTabNum
	printf("Cannot Find Table %s.\n", tabName);
	return -1;   //-1 is an invalid value
}


static char* to_upper_str(char* str) {
	char* newStr = new char[LEN];
	int i = 0;
	for (; str[i]; i++) {
		newStr[i] = toupper(str[i]);
	}
	newStr[i] = 0;
	return newStr;
}

static bool validTableName(char* newName) {
	char* upper_new_name = to_upper_str(newName);
	char* temp = 0;
	for (int i = 0; i < curTabNum; i++) {
		temp = to_upper_str(tableArray[i].tableName);
		if (strcmp(temp, upper_new_name) == 0) {
			delete[] upper_new_name;
			delete[] temp;
			return false;
		}
		delete[] temp;
	}
	if(invalidString(newName)) return false;
	return true;
}



//在database.txt中登记新文件的名字。创建新文件，写入表的基本信息
static void createTableFile(Table T) {
	char fileName[LEN] = "";

	strcpy(fileName, T.tableName);

	FILE* fp = fopen("database.txt", "a");

	encode(fileName);

	fprintf(fp, "%s ", fileName);
	fclose(fp);

	decode(fileName);

	fp = fopen(fileName, "w");
	fprintf(fp, "%d %s ", T.primaryKey, T.tableName);

	for (int i = 0; i < T.cNum; i++) {
		fprintf(fp, "%s ", T.column[i]);
	}
	fprintf(fp, "\n");
	fclose(fp);

#ifdef DEBUG
	printf("Create:\nTable Name: %s\n", T.tableName);
	printf("Column Number: %d\nRow Number: %d\nPrimary Key: %d\nColumn: ", T.cNum, T.rNum, T.primaryKey);
	for (int i = 0; i < tabArray[curTabNum].cNum; i++) {
		cout << tabArray[curTabNum].column[i] << " ";
	}
	putchar('\n');
#endif
	return;
}



void Create(void) {
	char ret[LEN][LEN] = { "" };
	int l = 0;
	if (readLine(stdin, ret, &l) == false) {
		system("pause");
		exit(1);
	}

	if (curTabNum == MAX_TAB_NUM) {
		std::cout << "The maximum of the number of tables is " << MAX_TAB_NUM << "." << std::endl;
		std::cout << "Cannot create more tables." << std::endl;
		return;
	}


	if (l < 3) {
		printf("Invalid Input. Incompleted Command.\n");
		return;
	}
	else if (strcmp(ret[0], "TABLE") != 0 && strcmp(ret[0], "table") != 0) {
		printf("Invalid Input. Cannot identify '%s'. Do you mean 'CREATE TABLE'?\n", ret[0]);
		return;
	}
	else if (validTableName(ret[1]) == false) {
		printf("Table's name %s is inavailable.\n", ret[1]);
		return;
	}
	//"CREATE" was read in main function
	//ret[0] is "TABLE" or "table"
	//ret[1] is the name of the table
	strcpy(tableArray[curTabNum].tableName, ret[1]);

	//there are no name of column before ret[2]
	if (strcmp(ret[2], "PRIMARY_KEY") == 0 || strcmp(ret[2], "primary_key") == 0) {
		printf("Invalid Primary Key.\n");
		return;
	}

	//primary key is -1 by default
	tableArray[curTabNum].primaryKey = -1;
	
	//data type of column is pointer(array) of char[LEN]
	tableArray[curTabNum].column = (char(*)[LEN])malloc(sizeof(char[LEN]) * 20);
	if (tableArray[curTabNum].column == NULL) {
		printf("out of space\n");
		system("pause");
		exit(1);
	}

	//检查主键个数是否超过一个
	for (int it = 2, cnt = 0; it < l; it++) {
		if (strcmp(ret[it], "PRIMARY_KEY") == 0 || strcmp(ret[it], "primary_key") == 0) {
			cnt++;
			if (cnt > 1) {
				printf("Invalid Input. There can only be one primary key in a table.\n");
				free(tableArray[curTabNum].column);
				return;
			}
		}
	}
	//检查字段是否重名
	for (int it = 2; it < l; it++) {
		for (int itt = it + 1; itt < l; itt++) {
			if (strcmp(ret[it], ret[itt]) == 0) {
				printf("Columns should have different names. Column name '%s' is repeated\n", ret[it]);
				free(tableArray[curTabNum].column);
				return;
			}
		}
	}
	int i = 2, cNum = 0;
	for (i = 2; i < l; i++) {
		if (strcmp(ret[i], "PRIMARY_KEY") == 0 || strcmp(ret[i], "primary_key") == 0) {
			tableArray[curTabNum].primaryKey = i - 3;
			continue;
		}
		else {
			//"PRIMARY_KEY" or "primary_key" is included in invalid_words array
			if (invalidString(ret[i]) == true) {
				printf("String '%s' is invalid.\n", ret[i]);
				free(tableArray[curTabNum].column);
				return;
			}
			strcpy(tableArray[curTabNum].column[cNum], ret[i]);
			cNum++;
		}
	}
	tableArray[curTabNum].cNum = cNum;
	tableArray[curTabNum].rNum = 0;

	createTableFile(tableArray[curTabNum]);

	curTabNum++;

	initDataList(tableArray[curTabNum - 1]);

	printf("Table %s has been successfully created.\n", ret[1]);
	return;
}


/*
There are two readLine functons here.

One for reading data from any file(or stdin) such as database file.
Another one for reading data from stdin but keep the original in an argument char array in case there's an expression.

*/



//从fp中，以' ', ',', ';', '(', ')', '=', '`'为分隔读入一组字符串，and store them in a two-dimensional char array
//index range from zero to elemNum - 1
//fp应当为stdin
//字符串数组长度位elemNum

void readLine(char(*ret)[LEN], int* elemNum, char* original) {
	char key[LEN][LEN] = { "" }, buff[LEN] = "", line[LEN] = "";
	int lineIndex = 0, buffIndex = 0, keyIndex = 0, retIndex = 0;

	if (fgets(line, LEN, stdin) == NULL) {
		printf("ERROR in the function 'readLine'. Fail to read from stdin\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	strcpy(original, line);   //keep the original string for good measure

	int lineLen = strlen(line);
	for (lineIndex = 0; lineIndex < lineLen; lineIndex++) {
		if (line[lineIndex] == ' ' || line[lineIndex] == ',' || line[lineIndex] == ';' || line[lineIndex] == '(' || line[lineIndex] == ')' || line[lineIndex] == '=' || line[lineIndex] == '`') {
			strcpy(key[keyIndex++], buff);
			strcpy(buff, "");
			buffIndex = 0;
			continue;
		}
		buff[buffIndex++] = line[lineIndex];
		buff[buffIndex] = 0;
	}

	int lastKeyIndex = keyIndex;
	for (lastKeyIndex = keyIndex; lastKeyIndex >= 0 && strcmp(key[lastKeyIndex], "") == 0; lastKeyIndex--);

	for (retIndex = 0, keyIndex = 0; keyIndex <= lastKeyIndex; keyIndex++) {
		if (strcmp(key[keyIndex], "") == 0) continue;
		else strcpy(ret[retIndex++], key[keyIndex]);
	}
	*elemNum = retIndex;
	return;
}

bool readLine(FILE* fp, char(*ret)[LEN], int* elemNum) {
	char key[LEN][LEN] = { "" }, buff[LEN] = "", line[LEN] = "";
	int lineIndex = 0, buffIndex = 0, keyIndex = 0, retIndex = 0;

	if (fgets(line, LEN, fp) == NULL) {
		//主要针对文件的读入，可能无法读入
		return false;
	}

	int lineLen = strlen(line);
	for (lineIndex = 0; lineIndex < lineLen; lineIndex++) {
		if (line[lineIndex] == ' ' || line[lineIndex] == ',' || line[lineIndex] == ';' || line[lineIndex] == '(' || line[lineIndex] == ')' || line[lineIndex] == '=' || line[lineIndex] == '`') {
			strcpy(key[keyIndex++], buff);
			strcpy(buff, "");
			buffIndex = 0;
			continue;
		}
		buff[buffIndex++] = line[lineIndex];
		buff[buffIndex] = 0;
	}

	int lastKeyIndex = keyIndex;
	for (lastKeyIndex = keyIndex; lastKeyIndex >= 0 && strcmp(key[lastKeyIndex], "") == 0; lastKeyIndex--);

	for (retIndex = 0, keyIndex = 0; keyIndex <= lastKeyIndex; keyIndex++) {
		if (strcmp(key[keyIndex], "") == 0) continue;
		else strcpy(ret[retIndex++], key[keyIndex]);
	}
	*elemNum = retIndex;
	return true;
}