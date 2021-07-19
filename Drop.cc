#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "Create.h"

//basic info is not deleted
void freeTableData(Table& T) {
	if (T.data == NULL) {
		printf("Error in free table.\n");
		system("pause");
		exit(1);
	}
	node* ptr = T.data->next;
	for (; ptr;) {
		T.data->next = ptr->next;
		free(ptr->content);
		free(ptr);
		ptr = T.data->next;
	}
	return;
}



void deleteTable(Table& T) {
	free(T.column);
	freeTableData(T);
	return;
}



void renewDataFile(void) {
	FILE* fp = fopen("database.txt", "w");
	if (fp == NULL) {
		printf("Cannot Open database.txt");
		system("pause");
		exit(1);
	}
	char temp[LEN] = "";
	for (int i = 0; i < curTabNum; i++) {
		strcpy(temp, tableArray[i].tableName);
		encode(temp);
		fprintf(fp, "%s ", temp);
	}
	fclose(fp);
	return;
}


void Drop(void) {
	char temp[LEN] = "";
	cin >> temp;
	if (strcmp(temp, "TABLE") && strcmp(temp, "table") && strcmp(temp, "Table")) {
		printf("Invalid Input. Cannot identify '%s'. Do you mean 'DROP TABLE'?\n", temp);
		return;
	}
	cin >> temp;

	//the semicolon
	int ll = strlen(temp) - 1;
	if (temp[ll] == ';') temp[ll] = 0;

	int tabIndex = findTableIndex(temp);
	if (tabIndex < 0) return;

	deleteTable(tableArray[tabIndex]);

	for (int t = tabIndex + 1; t < curTabNum; t++) {
		tableArray[t - 1] = tableArray[t];
	}

	curTabNum--;
	renewDataFile();

	printf("Table %s has been deleted successfully.\n", temp);
	return;
}
