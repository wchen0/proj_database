#include <iostream>
#include "Create.h"

void Show(void) {
	char temp[LEN] = "";
	cin >> temp;
	if (temp[strlen(temp) - 1] == ';') temp[strlen(temp) - 1] = 0;
	if (strcmp(temp, "TABLES") != 0 && strcmp(temp, "tables") != 0) {
		printf("Cannot identify '%s'. Do you mean 'SHOW TABLES'?\n", temp);
		return;
	}
	cout << curTabNum << " table(s) " << "in total: " << endl;
	for (int tabIndex = 0; tabIndex < curTabNum; tabIndex++) {
		printf("%-8s", tableArray[tabIndex].tableName);
		printf(" (");
		for (int t = 0; t < tableArray[tabIndex].cNum; t++) {
			printf("%s", tableArray[tabIndex].column[t]);
			if (tableArray[tabIndex].primaryKey == t) printf(" PRIMARY_KEY");
			if (t != tableArray[tabIndex].cNum - 1) putchar(',');
		}
		printf(")\n");
	}
	return;
}

void ShowTableFormat(const Table& T) {
	printf("%s", T.tableName);
	printf(" (");
	for (int t = 0; t < T.cNum; t++) {
		printf("%s", T.column[t]);
		if (T.primaryKey == t) printf(" PRIMARY_KEY");
		if (t != T.cNum - 1) putchar(',');
	}
	printf(")\n");
	return;
}

void DESC(void) {
	char tableName[LEN] = "";
	std::cin >> tableName;

	int l = strlen(tableName) - 1;
	if (tableName[l] == ';') tableName[l] = 0;

	int tableIndex = findTableIndex(tableName);
	if (tableIndex < 0) return;
	
	ShowTableFormat(tableArray[tableIndex]);
}