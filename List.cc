#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Create.h"
#include <ctype.h>

void initDataList(Table& T) {
	if (T.data != NULL) return;
	T.data = (node*)malloc(sizeof(node));
	if (T.data == NULL) {
		printf("out of space");
		system("pause");
		exit(1);
	}
	T.data->next = NULL;
	return;
}


void insertLine(char(*content)[LEN], Table& T) {
	if (T.data == NULL) initDataList(T);

	node* newNode = (node*)malloc(sizeof(node));
	if (newNode == NULL) {
		printf("out of space");
		system("pause");
		exit(1);
	}
	newNode->content = (char(*)[LEN])malloc(sizeof(char[LEN]) * 30);
	if (newNode->content == NULL) {
		printf("out of space");
		system("pause");
		exit(1);
	}
	/*for (int i = 0; i < T.cNum; i++) {
		if (strstr(newNode->content[i], nullString)) {
			printf("Strings shouldn't include '%s'", nullString);
			free(newNode);
			return;
		}
	}*/
	for (int i = 0; i < T.cNum; i++) {
		strcpy(newNode->content[i], content[i]);
	}

	node* lastNode = T.data;
	for (; lastNode->next; lastNode = lastNode->next);

	lastNode->next = newNode;
	newNode->next = NULL;
	return;
}


#define _INVALID_WORDS_NUM 30
const char invalid_words[_INVALID_WORDS_NUM + 1][LEN] = {
	nullString,
	"PRIMARY_KEY",
	"PRIMARYKEY",
	"PRIMARY",
	"FROM",
	"AND",
	"OR",
	"NOT",
	"WHERE",
	"INSERT",
	"INTO",
	"CREATE",
	"SELECT",
	"SET",
	"SHOW",
	"STRING",
	"DISTINCT" ,
	"DELETE",
	"DROP" ,
	"DATABASE",
	"UPDATE",
	"TABLE",
	"TABLES",
	"VALUES",
	"VALUE",
	"IMPORT",
	"FILE",
	"ALTER",
	"AS",
	"ADD" };

bool invalidString(char* real) {
	char str[LEN] = "";
	strcpy(str, real);
	for (int i = 0; str[i]; i++) {
		if (isdigit(str[i]) == false && isalpha(str[i]) == false && str[i] != '_') {
			return true;
		}
		str[i] = toupper(str[i]);
	}
	for (int i = 0; i < _INVALID_WORDS_NUM; i++) {
		if (strcmp(str, invalid_words[i]) == 0) {
			return true;
		}
	}
	return false;
}