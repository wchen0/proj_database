#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "Create.h"



void Update(void) {
	char ret[LEN][LEN] = { "" }, newStr[LEN] = "";
	char (*condition)[LEN] = (char(*)[LEN])malloc(sizeof(char[LEN]) * LEN);

	if (condition == NULL) {
		printf("out of space.\n");
		system("pause");
		exit(1);
	}
	int lastIndex = 0, tabIndex = 0, targetCol = 0, type = 0;
	bool change = false;

	if (readLine(stdin, ret, &lastIndex) == false) {
		free(condition);
		system("pause");
		exit(EXIT_FAILURE);
	}
	lastIndex--;

	if (strcmp(ret[1], "SET") && strcmp(ret[1], "set")) {
		printf("Cannot identify '%s'. Do you mean 'SET'?\n", ret[1]);
		free(condition);
		return;
	}

	tabIndex = findTableIndex(ret[0]);
	if (tabIndex < 0) {
		free(condition);
		return;
	}
	
	load_all_data_of_one_table(tabIndex);

	for (targetCol = 0; targetCol < tableArray[tabIndex].cNum; targetCol++) {
		if (strcmp(tableArray[tabIndex].column[targetCol], ret[2]) == 0) break;
	}
	if (targetCol == tableArray[tabIndex].cNum) {
		printf("Cannot Find Column %s\n", ret[2]);
		free(condition);
		return;
	}
	
	if (invalidString(ret[3])) {
		printf("String '%s' is invalid.\n", ret[3]);
		free(condition);
		return;
	}
	strcpy(newStr, ret[3]);

	if (lastIndex == 3) type = NO_CONDITION;
	else {
		if (strcmp(ret[4], "WHERE") != 0 && strcmp(ret[4], "where") != 0) {
			printf("Cannot Identify '%s'. Do you mean 'WHERE'?\n", ret[4]);
			free(condition);
			return;
		}
		type = readCondition(ret + 4, lastIndex - 3, condition, tableArray[tabIndex]);
	}
	if (targetCol == tableArray[tabIndex].primaryKey) {
		int changeCnt = 0, sameStrCnt = 0;
		node* ptr = tableArray[tabIndex].data->next;
		for (; ptr; ptr = ptr->next) {
			if (conditionCheck(ptr->content, condition, tableArray[tabIndex].cNum, type)) {
				if (strcmp(ptr->content[targetCol], newStr) != 0) change = true;
				strcpy(ptr->content[targetCol], newStr);
				changeCnt++;
			}
			else if (strcmp(newStr, ptr->content[targetCol]) == 0) sameStrCnt++;
		}
		if (changeCnt > 1) {
			ShowTableFormat(tableArray[tabIndex]);
			printf("This operation is forbidden because the primary key constrain will be violated\n");
			freeTableData(tableArray[tabIndex]);
			free(condition);
			return;
		}
		if(sameStrCnt > 0) {
			ShowTableFormat(tableArray[tabIndex]);
			printf("This operation is forbidden because the primary key constrain will be violated.\n");
			freeTableData(tableArray[tabIndex]);
			free(condition);
			return;
		}
	}
	else {
		node* ptr = tableArray[tabIndex].data->next;
		for (; ptr; ptr = ptr->next) {
			if (conditionCheck(ptr->content, condition, tableArray[tabIndex].cNum, type)) {
				if (strcmp(ptr->content[targetCol], newStr) != 0) change = true;
				strcpy(ptr->content[targetCol], newStr);
			}
		}
	}
	renewTableFile(tableArray[tabIndex]);
	freeTableData(tableArray[tabIndex]);
	free(condition);

	if (change == true) printf("Table %s is update successfully.\n", tableArray[tabIndex].tableName);
	else printf("No updated line in table %s.\n", tableArray[tabIndex].tableName);
	return;
}

