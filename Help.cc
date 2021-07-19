#include "Create.h"


void Help(void) {
	printf("\n\n***********************************************************\n"
		"This is a Database Software(x86).\n"
		"The database language is very similar to SQL (but with fewer functions).\n"
		"Here I am going to introduce all the functions of this database.\n"
		"***********************************************************\n\n"
		"In this database software, there is only one Data Type - String.\n"
		"That's to say, all the data are considered as strings.\n"
		"Incidentally, all strings shouldn't have more than 100 characters and don't contain any space.\n"
		"The keywords of SQL (SELECT, INSERT, etc) can also be lower-case.\n"
		"Please finish every command in one line.\n"
		"This program doesn't have a complicated Data Structure but it remains efficient when the data amount is not huge.\n"
		"The maximum of tables is %d.\n\n", MAX_TAB_NUM);
	
	for (;;) {

		fflush(stdin);

		printf("Choose what you want to know about: \n"
			"1. CREATE TABLE\t2. INSERT\t3. SELECT\t4. DELETE\n"
			"5. UPDATE\t6. ALTER\t7. SHOW TABLES"
			"\t8. DROP\n9. DESC   \t10. IMPORT FILE\t11. EXIT\n"
			"12. Go back to the database interface\n" 
			"13. About the author\n");

		int op = 0;
		std::cin >> op;
		fflush(stdin);
		switch (op) {


		case 1:
			printf("***********************************************************\n"
				"CREATE TABLE:\n"
				"By entering 'CREATE TABLE', you can create a new table in this database.\n"
				"Name of each table should be different from other tables (This software is NOT necessarily case-sensitive).\n"
				"By typing 'PRIMARY_KEY' after the name of a column, you can let this column become the primary key.\n"
				"When a column becomes primary key, it means all data under this column should be different.\n"
				"Remember, there can only be zero or one primary key in a table.\n"
				"And there should be at least one column in a table.\n"
				"\nFor example, create a table without any primary key:\n"
				"CREATE TABLE name_of_table ( name_of_column1, name_of_column2, ...); (end with a semicolon)\n"
				"\nCreate a table with a primary key(column2):\n"
				"CREATE TABLE name_of_table ( name_of_column1, name_of_column2 PRIMARY_KEY, ...);\n");
			system("pause");
			system("cls");
			break;


		case 2:
			printf("\n***********************************************************\n"
				"INSERT:\n"
				"You can insert a line of data into a table with the sentence below:\n"
				"INSERT INTO table_name VALUES (column1_data, column2_data, ...);\n"
				"Remember, the number of inserted strings should correspond with the columns of this table.\n"
				"You can not really insert any empty string.\n"
				"Also, inserted data should strictly obey the primary constrain, if any.\n");
			system("pause");
			system("cls");
			break;


		case 3:
			printf("\n***********************************************************\n"
				"SELECT:\nSELECT is going to display data from the table according to your requirements.\n"
				"Remember, SELECT this function is not going to change the data per se.\n"
				"It just visually displays them.\n"
				"\nLet's see some examples:\n"
				"SELECT a, b, c FROM student;\n"
				"SELECT b, a, c FROM student;   (the order of the displayed columns can be different)\n"
				"\nDISTINCT means that repeated data is not going to be printed on screen.\n"
				"SELECT DISTINCT a, b, c FROM student;\n"
				"\nAn asterisk means that all columns are selected.\n"
				"SELECT DISTINCT * FROM student;\n"
				"SELECT * FROM student;\n"
				"\nWHERE means that only lines with the following condition are selected.\n"
				"SELECT * FROM student WHERE a = Zhang;\n"
				"SELECT * FROM student WHERE a = Zhang AND b = NanJing;\n"
				"SELECT * FROM student WHERE a = Zhang OR b = BeiJing;\n"
				"\nUnfortunately, more than one 'AND's or 'OR's are not allowed in logic expressions.\n"
				"\nSELECT 12*(8-5)+7/(9-3)\n"
				"Here I also write a built-in calculator in SELECT.\n"
				"By entering a math expression after SELECT, the value of the expression will be calculated.\n");
			system("pause");
			system("cls");
			break;


		case 4:
			printf(
				"DELETE:\nDelete lines from a table\n"
				"Let's see some examples:\n"
				"DELETE FROM student;  (it means delete all data in this table)\n"
				"DELETE FROM student WHERE a = test;\n"
				"DELETE FROM student WHERE a = test AND b = test;\n"
				"DELETE FROM student WHERE a = test OR b = test;\n"
				"The logic expressions here are just like those in 'SELECT'.\n");
			system("pause");
			system("cls");
			break;


		case 5:
			printf(
				"UPDATE:\n"
				"Several Examples:\n"
				"UPDATE student SET a = new_data;\n"
				"UPDATE student SET a = new_data WHERE b = some_data;\n"
				"UPDATE student SET a = new_data WHERE b = some_data AND c = some_data;\n"
				"UPDATE student SET a = new_data WHERE b = some_data OR c = some_data;\n"
				"Attention: UPDATE shouldn't violate the primary key constrain.\n");
			system("pause");
			system("cls");
			break;


		case 6:
			printf(
				"ALTER:\n"
				"You can alter(add or drop) one column of the table.\n"
				"Newly added column will be empty.\n"
				"ALTER TABLE student ADD gender;\n"
				"ALTER TABLE student DROP birth_place;\n"
				"\nYou can also change the primary key of the table(if the constrain won't be violated)\n"
				"For example:\n"
				"ALTER TABLE employee ADD PRIMARY_KEY (gender);\n"
				"ALTER TABLE employee ADD PRIMARY_KEY (name);\n"
				"Please be sure that there's a space between 'PRIMARY_KEY' and the primary-key-to-be column\n");
			system("pause");
			system("cls");
			break;


		case 7:
			printf("\n***********************************************************\n");
			printf("SHOW TABLES:\nEnter 'SHOW TABLES;' to see all tables you've defined\n");
			system("pause");
			system("cls");
			break;


		case 8:
			printf("\n***********************************************************\n");
			printf("DROP:\nYou can delete a table by entering 'DROP TABLE table_name;'\n");
			system("pause");
			system("cls");
			break;


		case 11:
			printf("\n***********************************************************\n");
			printf("EXIT:\nYou can quit this program by entering EXIT. All data will be stored in files.\n"
				"You can see them next time you open this program\n");
			system("pause");
			system("cls");
			break;


		case 12:
			system("pause");
			system("cls");
			return;


		case 13:
			printf("\n***********************************************************\n"
				"About the author:\n"
				"Author: Weitian Chen			Nanjing University\n"
				"Email: weitian.chen@qq.com		Feel free to contact if there's any problem.\n\n"
				"Description: School work for fundamental of programming\n"
				"Date: May 3rd, 2021\n"
				"Last Update: July 11th, 2021\n"
				"All right reserved.\n");
			system("pause");
			system("cls");
			break;


		case 9:
			printf("\n***********************************************************\n");
			printf("DESC is going to show the structure of a table.\nDESC table_name;\n");
			system("pause");
			system("cls");
			break;


		case 10:
			printf("\n***********************************************************\n");
			printf("IMPORT FILE:\nIMPORT FILE file_name INTO table_name;\n"
				"With this method, you will be able to import data from a file without the hustle and bustle of inserting every line repectively.\n"
				"The table should be created in advance.\n"
				"The strings in the file should be separated with space or newline mark so that it can be identified.\n"
				"Please be very careful about the imported file because the column number and validity of words won't be examined at all.\n"
				"The strings will be automatically separated to each column by order(line by line).\n"
				"Null strings will be applied at the last row if it is unfinished.\n"
				"Attention: You cannot import file into a table which has a primary key constrain.\n");
			system("pause");
			system("cls");
			break;


		default:
			printf("Wrong Input. Please enter the ordinal number.\n");
			system("pause");
			system("cls");
		}
	}
}