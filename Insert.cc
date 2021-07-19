#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Create.h"
#include <cstring> 
#include <cstdlib>


//renew the file with data in table
void renewTableFile(const Table& T) {
	FILE* fp = fopen(T.tableName, "w");
	fprintf(fp, "%d %s ", T.primaryKey, T.tableName);
	for (int i = 0; i < T.cNum; i++) {
		fprintf(fp, "%s ", T.column[i]);
	}
	fputc('\n', fp);
	for (node* temp = T.data->next; temp != NULL; temp = temp->next) {
		for (int i = 0; i < T.cNum; i++) {
			fprintf(fp, "%s ", temp->content[i]);
		}
		fputc('\n', fp);
	}
	fclose(fp);
	return;
}


//check whether this table obeys the primary key constrain
bool primaryKeyCheck(int tableIndex, char(*ret)[LEN]) {
	//if the table is empty
	if (tableArray[tableIndex].data == NULL) return true;
	//if the table doesn't have a primary key(-1)
	if (tableArray[tableIndex].primaryKey < 0) return true;

	node* temp = tableArray[tableIndex].data->next;
	for (; temp != NULL; temp = temp->next) {
		if (strcmp(temp->content[tableArray[tableIndex].primaryKey], ret[tableArray[tableIndex].primaryKey]) == 0) return false;
	}
	return true;
}


void Insert(void) {
	char temp[10] = "";
	cin >> temp;
	if (strcmp(temp, "INTO") && strcmp(temp, "into")) {
		printf("Invalid Input. Cannot identify '%s'. Do you mean 'INSERT INTO'?\n", temp);
		return;
	}
	cin >> temp;
	int tabIndex = findTableIndex(temp);
	if (tabIndex < 0) return;

	cin >> temp;
	if (strcmp(temp, "VALUES") && strcmp(temp, "values") && strcmp(temp,"Values")) {
		printf("Invalid Input. Cannot identify '%s'. Do you mean 'VALUES'?\n", temp);
		return;
	}
	int i = 0;
	char ret[LEN][LEN] = { "" };
	
	if (readLine(stdin, ret, &i) == false) {
		system("pause");
		exit(1);
	}

	if (i == 0) {
		printf("Inserted data should not be null.\n");
		return;
	}
	else if (i != tableArray[tabIndex].cNum) {
		printf("Table %s has a different number of columns.\nFormat of Table %s:\n", tableArray[tabIndex].tableName, tableArray[tabIndex].tableName);
		ShowTableFormat(tableArray[tabIndex]);
		return;
	}
	
	for (int ii = 0; ii < i; ii++) {
		if (invalidString(ret[ii])) {
			printf("String '%s' is invalid\n", ret[ii]);
			return;
		}
	}
	
	load_all_data_of_one_table(tabIndex);
	
	
	if (primaryKeyCheck(tabIndex, ret) == false) {
		printf("Violation the primary key constrain of table %s.\nFormat of Table %s:\n", tableArray[tabIndex].tableName, tableArray[tabIndex].tableName);
		ShowTableFormat(tableArray[tabIndex]);
		freeTableData(tableArray[tabIndex]);   //DON'T FORGET
		return;
	}
	insertLine(ret, tableArray[tabIndex]);
	renewTableFile(tableArray[tabIndex]);

	freeTableData(tableArray[tabIndex]);

	printf("Data Inserted Successfully.\n");
	return;
}

