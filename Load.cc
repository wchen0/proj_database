#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Create.h"


static void loadTableInfo(char* fileName, int tabIndex) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Cannot Open %s", fileName);
		system("pause");
		exit(1);
	}
	if (fscanf(fp, "%d", &tableArray[tabIndex].primaryKey) == EOF) {
		printf("Cannot read the primary key of %s.", fileName);
		system("pause");
		exit(1);
	}

	int i = 0;
	char ret[LEN][LEN] = { "" };
	if (readLine(fp, ret, &i) == false) {
		fclose(fp);
		system("pause");
		exit(1);
	}

	strcpy(tableArray[tabIndex].tableName, ret[0]);

	tableArray[tabIndex].cNum = i - 1;

	tableArray[tabIndex].column = (char(*)[LEN])malloc(sizeof(char[LEN]) * 30);
	if (tableArray[tabIndex].column == NULL) {
		printf("out of space");
		system("pause");
		exit(1);
	}
	for (int j = 1; j < i; j++) {
		strcpy(tableArray[tabIndex].column[j - 1], ret[j]);
	}
	
	initDataList(tableArray[tabIndex]);

	fclose(fp);
	return;
}



void load_all_data_of_one_table(int tabIndex) {
	char fileName[LEN] = "";
	
	strcpy(fileName,tableArray[tabIndex].tableName);

	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Cannot open the file %s", fileName);
		system("pause");
		exit(1);
	}
	char ret[LEN][LEN] = { "" };
	int row = 0, i = 0;
	fgets(ret[0], LEN, fp);
	for (;;) {
		if (readLine(fp, ret, &i) == false) break;
		insertLine(ret, tableArray[tabIndex]);
		row++;
	}
	tableArray[tabIndex].rNum = row;
	fclose(fp);
	return;
}


void Load(void) {
	FILE* fp = fopen("database.txt", "r");
	if (fp == NULL) {
		//cout << "Cannot open database.txt" << endl;
		FILE* p = fopen("database.txt", "w");
		//cout << "database.txt has been successfully created." << endl;
		fclose(p);
		return;
	}

	char fileName[LEN] = ""; 
	int tableIndex = 0;
	for (; !feof(fp);) {
		if (fscanf(fp, "%s", fileName) == EOF) break;
		decode(fileName);
		loadTableInfo(fileName, tableIndex);
		tableIndex++;
		if (tableIndex == LEN - 1) {
			system("pause");
			exit(1);
		}
	}
	curTabNum = tableIndex;
#ifdef DEBUG
	cout << "Current Table Number: " << tableIndex << endl;
#endif
	fclose(fp);
	return;
}


#define KEYLEN 4

const int key[KEYLEN] = { 3,2,0,9 };

void encode(char* str) {
	int idx = 0;
	for (; str[0]; str++) {
		str[0] += key[idx];
		idx = (idx + 1) % KEYLEN;
	}
}

void decode(char* str) {
	int idx = 0;
	for (; str[0]; str++) {
		str[0] -= key[idx];
		idx = (idx + 1) % KEYLEN;
	}
}
