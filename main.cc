#include <iostream>
#include <cstring>
#include "Create.h"

int main(void) {
	printf("Loading...\n");
	Load();
	system("cls");
	for (;;) {
		fflush(stdin);
		std::cout << "sql> ";

		char str[LEN] = "";
		std::cin >> str;

		if (strcmp(str, "CREATE") == 0 || strcmp(str, "create") == 0) {
			Create();
		}
		else if (strcmp(str, "INSERT") == 0 || strcmp(str, "insert") == 0) {
			Insert();
		}
		else if (strcmp(str, "DROP") == 0 || strcmp(str, "drop") == 0) {
			Drop();
		}
		else if (strcmp(str, "SHOW") == 0 || strcmp(str, "show") == 0) {
			Show();
		}
		else if (strcmp(str, "SELECT") == 0 || strcmp(str, "select") == 0) {
			Select();
		}
		else if (strcmp(str, "UPDATE") == 0 || strcmp(str, "update") == 0) {
			Update();
		}
		else if (strcmp(str, "DELETE") == 0 || strcmp(str, "delete") == 0) {
			Delete();
		}
		else if (strcmp(str, "ALTER") == 0 || strcmp(str, "alter") == 0) {
			Alter();
		}
		else if (strcmp(str, "EXIT") == 0 || strcmp(str, "exit") == 0 || strcmp(str, "Exit") == 0) {
			break;
		}
		else if (strcmp(str, "HELP") == 0 || strcmp(str, "help") == 0 || strcmp(str, "Help") == 0) {
			Help();
		}
		else if (strcmp(str, "DESC") == 0 || strcmp(str, "desc") == 0) {
			DESC();
		}
		else if (strcmp(str, "IMPORT") == 0 || strcmp(str, "import") == 0) {
			import_file();
		}
		else {
			std::cout << "Wrong Input. Cannot identify " << str << std::endl;
			std::cout << "Enter 'HELP' if you need any help. Enter 'EXIT' to quit." << std::endl;
			while (getchar() != '\n');
		}
	}
	system("pause");
	return 0;
}
