#define _CRT_SECURE_NO_WARNINGS

#include "Create.h"


void import_file(void) {
	char temp[LEN] = "";
	std::cin >> temp;
	if (strcmp(temp, "FILE") && strcmp(temp, "file") && strcmp(temp, "File")) {
		std::cout << "Cannot identify '" << temp << "'. Do you mean 'IMPORT FILE'?" << std::endl;
		return;
	}

	std::cin >> temp;
	FILE* fp = fopen(temp, "r");
	if (fp == NULL) {
		printf("Cannot find the file %s\n", temp);
		fflush(stdin);
		return;
	}

	std::cin >> temp;
	if (strcmp(temp, "INTO") && strcmp(temp, "into")) {
		std::cout << "Cannot identify '" << temp << "'. Do you mean 'IMPORT FILE file_name INTO'?" << std::endl;
		fclose(fp);
		fflush(stdin);
		return;
	}

	std::cin >> temp;
	if (temp[strlen(temp) - 1] == ';') temp[strlen(temp) - 1] = 0;
	int tabIdx = findTableIndex(temp);
	if (tabIdx < 0) {
		fclose(fp);
		fflush(stdin);
		return;
	}

	if (tableArray[tabIdx].primaryKey >= 0) {
		printf("File cannot be imported into a table which has a primary key constrain.\n"
			"You can cancelled the primary key constrain to solve this problem.\n");
		fclose(fp);
		fflush(stdin);
		return;
	}

	int curCol = 0;

	FILE* tab_p = fopen(tableArray[tabIdx].tableName, "a");

	for (; !feof(fp);) {
		if (fscanf(fp, "%s", temp) == EOF) break;
		
		fprintf(tab_p, "%s ", temp);
		
		curCol++;   //curCol is the column printed just now
		
		if (curCol == tableArray[tabIdx].cNum) {
			curCol = 0;
			tableArray[tabIdx].rNum++;
			fprintf(tab_p, "\n");
		}
	}

	//×îºóÓÃ¿Õ²¹×ã
	if (curCol != 0) {
		for (; curCol != tableArray[tabIdx].cNum;) {
			fprintf(tab_p, "%s ", nullString);
			curCol++;
		}
		fprintf(tab_p, "\n");
		tableArray[tabIdx].rNum++;
	}

	fclose(fp);
	fclose(tab_p);

	printf("File has been imported into table %s.\n", tableArray[tabIdx].tableName);

	return;
}