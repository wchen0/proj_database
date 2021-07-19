#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "Create.h"


static void displayColumns(int* outputOrder, const Table& T) {
	for (int order = 1; order <= T.cNum; order++) {
		for (int i = 0; i < T.cNum; i++) {
			if (outputOrder[i] == order) {
				printf("%-15s", T.column[i]);
				break;
			}
		}
	}
	putchar('\n');
	return;
}



int readCondition(const char(*ret)[LEN], const int strNum, char(*condition)[LEN], const Table& T) {
	//ret[0] is 'WHERE'

	for (int i = 0; i < T.cNum; strcpy(condition[i++], ""));

	int i = 0, type = 0;

	for (i = 0; i < T.cNum; i++) {
		if (strcmp(ret[1], T.column[i]) == 0) {
			strcpy(condition[i], ret[2]);
			break;
		}
	}
	if (i == T.cNum) {
		printf("Cannot Find Column '%s'.\n", ret[1]);
		return INVALID_CONDITION;
	}
	
	if (strNum == 3) return AND;
	
	if (strcmp(ret[3], "AND") == 0 || strcmp(ret[3], "and") == 0) type = AND;
	else if (strcmp(ret[3], "OR") == 0 || strcmp(ret[3], "or") == 0) type = OR;
	else {
		printf("Wrong Input. Cannot Identify '%s'\n", ret[3]);
		return INVALID_CONDITION;
	}
	for (i = 0; i < T.cNum; i++) {
		if (strcmp(ret[4], T.column[i]) == 0) {
			strcpy(condition[i], ret[5]);
			break;
		}
	}
	if (i == T.cNum) {
		printf("Cannot Find Column '%s'.\n", ret[4]);
		return INVALID_CONDITION;
	}
	return type;
}



static bool conditionAND(char(*data)[LEN], char(*condition)[LEN], int cNum) {
	for (int i = 0; i < cNum; i++) {
		if (strcmp(condition[i], "") == 0) continue;
		else if (strcmp(condition[i], data[i]) != 0) return false;
	}
	return true;
}

static bool conditionOR(char(*data)[LEN], char(*condition)[LEN], int cNum) {
	for (int i = 0; i < cNum; i++) {
		if (strcmp(condition[i], "") == 0) continue;
		else if (strcmp(condition[i], data[i]) == 0) return true;
	}
	return false;
}


bool conditionCheck(char(*data)[LEN], char(*condition)[LEN], int cNum, int type) {
	if (type == NO_CONDITION) return true;
	else if (type == AND) return conditionAND(data, condition, cNum);
	else if (type == OR) return conditionOR(data, condition, cNum);
	else {
		system("pause");
		exit(1);
	}
}


void printLine(char(*data)[LEN], int cNum, int* outputOrder) {
	bool empty = true;
	for (int order = 1; order <= cNum; order++) {
		for (int k = 0; k < cNum; k++) {
			if (outputOrder[k] == order) {
				if (strcmp(data[k], "") != 0) {
					if (strcmp(data[k], nullString) == 0) printf("%-15s", "");
					else printf("%-15s", data[k]);
					empty = false;
				}
			}
		}
	}
	if (empty == false) putchar('\n');
	return;
}


static int cmp(char(*a)[LEN], char(*b)[LEN], int cNum) {
	for (int curCol = 0; curCol < cNum;) {
		if (strcmp(a[curCol], b[curCol]) > 0) return 1;
		else if (strcmp(a[curCol], b[curCol]) < 0) return -1;
		else curCol++;
	}
	return 0;
}


void displayDistinct(int* outputOrder, const Table& T, char(*condition)[LEN] = NULL, int type = NO_CONDITION) {
	char(*tempArray)[LEN][LEN] = (char(*)[LEN][LEN])malloc(sizeof(char[LEN][LEN]) * LEN);
	if (tempArray == NULL) {
		printf("out of space\n");
		system("pause");
		exit(1);
	}
	for (int i = 0; i < LEN; i++) {
		for (int j = 0; j < LEN; j++) {
			strcpy(tempArray[i][j], "");
		}
	}

	node* p = T.data->next;
	int curRow = 0, curCol = 0;
	displayColumns(outputOrder, T);
	
	if (type == NO_CONDITION || condition == NULL) {
		for (curRow = 0; p != NULL; p = p->next, curRow++) {
			for (curCol = 0; curCol < T.cNum; curCol++) {
				if (outputOrder[curCol] > 0) {
					strcpy(tempArray[curRow][curCol], p->content[curCol]);
				}
			}
		}
	}
	else {
		for (curRow = 0; p != NULL; p = p->next, curRow++) {
			if (conditionCheck(p->content, condition, T.cNum, type)) {
				for (curCol = 0; curCol < T.cNum; curCol++) {
					if (outputOrder[curCol] > 0) {
						strcpy(tempArray[curRow][curCol], p->content[curCol]);
					}
				}
			}
		}
	}
	for (int i = 0; i < curRow; i++) {
		bool distinct_flag = true;
		for (int j = i + 1; j < curRow; j++) {
			if (cmp(tempArray[i], tempArray[j], T.cNum) == 0) {
				distinct_flag = false;
				break;
			}
		}
		if (distinct_flag) {   //if there are no same strings afterwards
			printLine(tempArray[i], T.cNum, outputOrder);
		}
	}
	free(tempArray);
	return;
}


//Type is NO_CONDITION by default
void displaySelected(int* outputOrder, const Table& T, bool distinct = false, char(*condition)[LEN] = NULL, int type = NO_CONDITION) {
	if (distinct == true) {
		displayDistinct(outputOrder, T, condition, type);
		return;
	}
	//when distinct is false


	node* p = T.data->next;
	
	displayColumns(outputOrder, T);
	
	if (type == NO_CONDITION || condition == NULL) {
		for (; p; p = p->next) {
			printLine(p->content, T.cNum, outputOrder);
		}
	}
	else if (type == AND) {
		for (; p != NULL; p = p->next) {
			if (conditionAND(p->content, condition, T.cNum)) 
				printLine(p->content, T.cNum, outputOrder);
		}
	}
	else if (type == OR) {
		for (; p != NULL; p = p->next) {
			if (conditionOR(p->content, condition, T.cNum)) 
				printLine(p->content, T.cNum, outputOrder);
		}
	}
	else {
		system("pause");
		exit(1);
	}
	return;
}



int divideStr(char* src, char(*ret)[LEN]) {
	int len = strlen(src), srcIndex = 0, j = 0, retStrIndex = 0;
	for (srcIndex = 0; srcIndex < len; srcIndex++) {
		if (src[srcIndex] == ',') {
			ret[j][retStrIndex] = 0;
			retStrIndex = 0;
			j++;
		}
		else ret[j][retStrIndex++] = src[srcIndex];
	}
	ret[j][retStrIndex] = 0;
	return j;
}



void Select(void) {
	char* firstStr = (char*)malloc(sizeof(char) * LEN), (*ret)[LEN] = (char(*)[LEN])malloc(sizeof(char[LEN]) * LEN);
	if (ret == NULL) {
		printf("out of space.\n");
		system("pause");
		exit(1);
	}
	if (firstStr == NULL) {
		printf("out of space.\n");
		system("pause");
		exit(1);
	}
	for (int i = 0; i < LEN; strcpy(ret[i++], ""));
	for (int i = 0; i < LEN; firstStr[i++] = 0);

	bool distinct = false;
	int lastIndex = 0, FromIndex = 0, outputOrder[LEN] = { 0 }, i = 0, k = 0, tabIndex = 0;

	cin >> firstStr;
	if (strcmp(firstStr, "DISTINCT") == 0 || strcmp(firstStr, "distinct") == 0) distinct = true;


	char* original_expression = new char[LEN];
	readLine(ret, &lastIndex, original_expression);
	lastIndex--;

	char first_copy[LEN] = "";
	strcpy(first_copy, firstStr);

	original_expression = strcat(firstStr, original_expression);   //because the first string has been read before
	if (original_expression[strlen(original_expression) - 1] == '\n') 
		original_expression[strlen(original_expression) - 1] = 0;

	//I do not want to change the original first string
	strcpy(firstStr, first_copy);


	for (FromIndex = 0; FromIndex <= lastIndex; FromIndex++) {
		if (strcmp(ret[FromIndex], "FROM") == 0 || strcmp(ret[FromIndex], "from") == 0) break;
	}
	if (FromIndex == lastIndex + 1 && strcmp(firstStr, "*") != 0 && strcmp(firstStr, "DISTINCT") && strcmp(firstStr, "distinct")) {
		//FromIndex is the index of the string "FROM"
		//String 'FROM' or 'from' doesn't exist in SELECT command.
		//So we assume there is an expression after the word 'SELECT'
		//calculate it
		if (original_expression[strlen(original_expression) - 1] == ';')
			original_expression[strlen(original_expression) - 1] = 0;

		double temp = calculate(original_expression);
		delete[] original_expression;
		if (fabs(temp - __INF__) < __EPS__) {
			printf("Cannot calculate the expression %s", original_expression);
		}
		else std::cout << temp << std::endl;
		
		//free(firstStr);
		free(ret);
		return;
	}

	tabIndex = findTableIndex(ret[FromIndex + 1]);
	if (tabIndex < 0) {
		free(firstStr);
		free(ret);
		return;
	}

	load_all_data_of_one_table(tabIndex);

	if (distinct == false) {
		if (strcmp(firstStr, "*") == 0) {
			for (int i = 0; i < tableArray[tabIndex].cNum; i++) {
				outputOrder[i] = i + 1;
			}
		}
		else {
			char(*tempret)[LEN] = (char(*)[LEN])malloc(sizeof(char[LEN]) * LEN);
			if (tempret == NULL) {
				printf("out of space.\n");
				system("pause");
				exit(1);
			}
			for (int i = 0; i < LEN; strcpy(tempret[i++], ""));

			int lastIndexTempRet = divideStr(firstStr, tempret);
			for (k = 0; k <= lastIndexTempRet; k++) {
				for (i = 0; i < tableArray[tabIndex].cNum; i++) {
					if (outputOrder[i] > 0) continue;
					if (strcmp(tableArray[tabIndex].column[i], tempret[k]) == 0) {
						outputOrder[i] = k + 1;
						break;
					}
				}
				if (i == tableArray[tabIndex].cNum) {
					printf("Cannot Find Column %s.\n", tempret[k]);
					freeTableData(tableArray[tabIndex]);
					free(firstStr);
					free(ret);
					free(tempret);
					return;
				}
			}
		}
	}
	else {
		//distinct == true
		if (strcmp("*", ret[0]) == 0) {
			for (int i = 0; i < tableArray[tabIndex].cNum; i++) {
				outputOrder[i] = i + 1;
			}
		}
		else {
			for (k = 0; k < FromIndex; k++) {
				for (i = 0; i < tableArray[tabIndex].cNum; i++) {
					if (outputOrder[i] > 0) continue;
					if (strcmp(tableArray[tabIndex].column[i], ret[k]) == 0) {
						outputOrder[i] = k + 1;
						break;
					}
				}
				if (i == tableArray[tabIndex].cNum) {
					printf("Cannot Find Column %s.\n", ret[k]);
					freeTableData(tableArray[tabIndex]);
					free(firstStr);
					free(ret);
					return;
				}
			}
		}
	}
	if (FromIndex == lastIndex - 1) {   //There's no any condition
		displaySelected(outputOrder, tableArray[tabIndex], distinct);
	}
	else {   //There's a condition
		char condition[LEN][LEN] = { "" };
		if (strcmp(ret[FromIndex + 2], "WHERE") != 0 && strcmp(ret[FromIndex + 2], "where") != 0) {
			printf("Cannot Identify '%s'. Do you mean 'WHERE'?\n", ret[FromIndex + 2]);
			freeTableData(tableArray[tabIndex]);
			free(firstStr);
			free(ret);
			return;
		}
		int ANDOR = readCondition(ret + FromIndex + 2, lastIndex - FromIndex - 1, condition, tableArray[tabIndex]);
		if (ANDOR == INVALID_CONDITION) {
			freeTableData(tableArray[tabIndex]);
			free(firstStr);
			free(ret);
			return;
		}
		displaySelected(outputOrder, tableArray[tabIndex], distinct, condition, ANDOR);
	}
	printf("No More Results.\n");

	freeTableData(tableArray[tabIndex]);
	free(firstStr);
	free(ret);
	return;
}