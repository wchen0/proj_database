#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "Create.h"


void Alter(void) {
	char temp[LEN] = "";
	cin >> temp;
	if (strcmp(temp, "TABLE") && strcmp(temp, "table") && strcmp(temp, "Table")) {
		printf("Cannot Identify '%s'. Do you mean 'TABLE'?\n", temp);
		return;
	}
	cin >> temp;
	int tabIndex = findTableIndex(temp);
	if (tabIndex < 0) return;

	load_all_data_of_one_table(tabIndex);

	cin >> temp;
	if (strcmp(temp, "ADD") == 0 || strcmp(temp, "add") == 0) {
		cin >> temp;
		if (strcmp(temp, "PRIMARY_KEY") == 0 || strcmp(temp, "primary_key") == 0) {
			char cNm[LEN] = "", tc = 0;
			int cNmIndex = 0, col_idx_of_this_tab = 0;
			for (;;) {
				std::cin >> tc;
				if (tc == ';') break;
				if (tc == ')' || tc == ' ' || tc == '(' || tc == '`') continue;
				cNm[cNmIndex++] = tc;
			}
			cNm[cNmIndex] = 0;
			
			if (invalidString(cNm)) {
				printf("'%s' is not a valid column name.\n", cNm);
				freeTableData(tableArray[tabIndex]);
				return;
			}

			for (col_idx_of_this_tab = 0; col_idx_of_this_tab < tableArray[tabIndex].cNum; col_idx_of_this_tab++) {
				if (strcmp(tableArray[tabIndex].column[col_idx_of_this_tab], cNm) == 0) break;
			}
			if (col_idx_of_this_tab == tableArray[tabIndex].cNum) {
				printf("Cannot Find Column '%s'.\n", cNm);
				freeTableData(tableArray[tabIndex]);
				return;
			}
			else if (tableArray[tabIndex].rNum == 0 || tableArray[tabIndex].rNum == 1) {
				tableArray[tabIndex].primaryKey = col_idx_of_this_tab;
				printf("Primary key of the table %s has been altered to '%s'.\n", tableArray[tabIndex].tableName, cNm);
				freeTableData(tableArray[tabIndex]);
				return;
			}
			else {
				for (node* cur = tableArray[tabIndex].data->next; cur->next; cur = cur->next) {
					for (node* ptr = cur->next; ptr; ptr = ptr->next) {
						if (strcmp(ptr->content[col_idx_of_this_tab], cur->content[col_idx_of_this_tab]) == 0) {
							printf("Cannot let '%s' be the primary key because the constrain will be violated.\n", cNm);
							freeTableData(tableArray[tabIndex]);
							return;
						}
					}
				}
				tableArray[tabIndex].primaryKey = col_idx_of_this_tab;
				printf("Primary key of the table %s has been altered to '%s'.\n", tableArray[tabIndex].tableName, cNm);
				freeTableData(tableArray[tabIndex]);
				return;
			}
		}

		//when the string after ADD is not PRIMARY_KEY
		if (temp[strlen(temp) - 1] == ';') temp[strlen(temp) - 1] = 0;

		if (invalidString(temp)) {
			printf("'%s' is not a valid name for column.\n", temp);
			freeTableData(tableArray[tabIndex]);
			return;
		}

		for (int i = 0; i < tableArray[tabIndex].cNum; i++) {
			if (strcmp(tableArray[tabIndex].column[i], temp) == 0) {
				printf("Column name '%s' is unavailable. "
					"Columns from one table cannot have the same name.\n", temp);   //字段名称不可重複
				freeTableData(tableArray[tabIndex]);
				return;
			}
		}
		strcpy(tableArray[tabIndex].column[tableArray[tabIndex].cNum], temp);

		node* ptr = tableArray[tabIndex].data->next;
		for (; ptr; ptr = ptr->next) {
			strcpy(ptr->content[tableArray[tabIndex].cNum], nullString);
		}
		tableArray[tabIndex].cNum++;
	}
	if (strcmp(temp, "DROP") == 0 || strcmp(temp, "drop") == 0) {
		cin >> temp;
		temp[strlen(temp) - 1] = 0;
		strcpy(tableArray[tabIndex].column[tableArray[tabIndex].cNum], temp);
		int targetCol = 0;
		for (targetCol = 0; targetCol < tableArray[tabIndex].cNum; targetCol++) {
			if (strcmp(temp, tableArray[tabIndex].column[targetCol]) == 0) break;
		}
		if (strcmp(temp, "PRIMARY_KEY") == 0 || strcmp(temp, "primary_key") == 0) {
			tableArray[tabIndex].primaryKey = -1;
			printf("Primary key of table '%s' has been cancelled.\n", tableArray[tabIndex].tableName);
			freeTableData(tableArray[tabIndex]);
			return;
		}
		else if (targetCol == tableArray[tabIndex].cNum) {
			printf("Invalid Column Name: %s.\n", temp);
			freeTableData(tableArray[tabIndex]);
			return;
		}

		if (targetCol == tableArray[tabIndex].primaryKey) tableArray[tabIndex].primaryKey = -1;
		if (tableArray[tabIndex].cNum - 1 == tableArray[tabIndex].primaryKey) tableArray[tabIndex].primaryKey = targetCol;

		strcpy(tableArray[tabIndex].column[targetCol], tableArray[tabIndex].column[tableArray[tabIndex].cNum - 1]);

		node* ptr = tableArray[tabIndex].data->next;
		for (; ptr; ptr = ptr->next) {
			strcpy(ptr->content[targetCol], ptr->content[tableArray[tabIndex].cNum - 1]);
		}
		tableArray[tabIndex].cNum--;
	}

	renewTableFile(tableArray[tabIndex]);
	freeTableData(tableArray[tabIndex]);
	printf("Table %s has been altered sucessfully.\n",tableArray[tabIndex].tableName);
	return;
}
