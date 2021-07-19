#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>

#ifndef _CREATE_H_
#define _CREATE_H_
#include "Create.h"
#endif


static void deleteLine(node*& pre, node*& ptr) {
	if (pre == NULL || ptr == NULL) {
		printf("ERROR in the function 'deleteLine': Null Pointer.\n");
		system("pause");
		exit(1);
	}
	pre->next = ptr->next;
	free(ptr->content);
	free(ptr);
	ptr = pre->next;
	return;
}


void Delete(void) {
	char ret[LEN][LEN] = { "" };
	int lastIndex = 0, tabIndex = 0, type = 0;
	char(*condition)[LEN] = (char(*)[LEN])malloc(sizeof(char[LEN]) * LEN);
	if (condition == NULL) {
		printf("out of space\n");
		system("pause");
		exit(1);
	}
	
	if (readLine(stdin, ret, &lastIndex) == false) return;
	lastIndex--;

	if (strcmp(ret[0], "FROM") && strcmp(ret[0], "from")) {
		printf("Invalid command. Cannot Identify '%s'. Do you mean 'FROM'?\n", ret[0]);
		free(condition);
		return;
	}
	
	tabIndex = findTableIndex(ret[1]);
	if (tabIndex < 0) {   //Cannot find that table
		free(condition);
		return;
	}

	load_all_data_of_one_table(tabIndex);


	if (1 == lastIndex) type = NO_CONDITION;
	else {
		if (strcmp(ret[2], "WHERE") != 0 && strcmp(ret[2], "where") != 0) {
			printf("Cannot Identify '%s'. Do you mean 'WHERE'?\n", ret[2]);
			return;
		}
		else type = readCondition(ret + 2, lastIndex - 1, condition, tableArray[tabIndex]);
	}

	if (type == INVALID_CONDITION) return;

	node* pre = tableArray[tabIndex].data, * ptr = pre->next;
	if (pre == NULL || ptr == NULL) {
		printf("Table %s is empty.\n", ret[1]);
		return;
	}
	bool deleted = false;
	for (; ptr;) {
		if (conditionCheck(ptr->content, condition, tableArray[tabIndex].cNum, type)) {
			deleteLine(pre, ptr);
			deleted = true;
		}
		else {
			ptr = ptr->next;
			pre = pre->next;
		}
	}
	renewTableFile(tableArray[tabIndex]);

	freeTableData(tableArray[tabIndex]);

	free(condition);

	if (deleted) printf("Deleted successfully.\n");
	else printf("No line is deleted\n");

	return;
}

