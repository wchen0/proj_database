#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stack>   //STL
#include <cstring>
#include <cctype>
#include "Create.h"


//.2 and 2. are valid
double str_to_float(const char* s) {
	int len = strlen(s), dotIndex = 0, integer = 0;
	double decimal = 0;
	for (dotIndex = 0; s[dotIndex] != '.' && dotIndex < len; dotIndex++);
	for (int j = 0; j < dotIndex; j++) {
		integer = integer * 10 + s[j] - '0';
	}
	if (dotIndex != len) {
		for (int j = len - 1; j > dotIndex; j--) {
			decimal += s[j] - '0';
			decimal /= 10;
		}
	}
	return decimal + 1.0 * integer;
}

bool isoptr(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

static void unary_operator_scan(expr_node* a, int& len);

//separate the oprators and operants
expr_node* str_to_arr(char* src, int* ansLen) {
	int index = 0, len = strlen(src);
	expr_node* a = new expr_node[100];
	for (int i = 0; i < len; i++) {
		if (src[i] == ' ') continue;   //space is allowed between operants and operators
		else if (isoptr(src[i])) {
			a[index].str[0] = src[i];
			a[index].str[1] = 0;
			a[index].type = Optr;
			index++;
		}
		else if (isdigit(src[i]) || src[i] == '.') {
			char tempStr[__STRLEN__] = "";
			int tempIndex = 0, j = i;
			for (j = i; (isdigit(src[j]) || src[j] == '.') && j < len; j++) {
				tempStr[tempIndex++] = src[j];
			}
			tempStr[tempIndex] = 0;
			a[index].value = str_to_float(tempStr);
			a[index].type = Cons;
			index++;
			i = j - 1;
		}
		else {
			//variables are not allowed in this calculator
			printf("Invalid Input. Cannot Identify the character '%c'\n", src[i]);
			delete[] a;
			return NULL;
		}
	}

	unary_operator_scan(a, index);

	*ansLen = index;

	return a;
}



expr_node* inffix_to_suffix(expr_node* src, int len, int* newLen) {
	std::stack<expr_node> ans_stack;
	std::stack<expr_node> optr_stack;
	for (int i = 0; i < len; i++) {
		if (src[i].type == Cons) ans_stack.push(src[i]);
		else if (src[i].str[0] == '(') optr_stack.push(src[i]);
		else if (src[i].str[0] == ')') {
			while (optr_stack.empty() == false && optr_stack.top().str[0] != '(') {
				ans_stack.push(optr_stack.top());
				optr_stack.pop();
			}
			if (optr_stack.empty()) {
				printf("Invalid Input. Closing bracket is missing\n");
				return NULL;
			}
			else optr_stack.pop();
		}
		else if (optr_stack.empty() == true) optr_stack.push(src[i]);
		else if (src[i].str[0] == '*' || src[i].str[0] == '/') {
			while (optr_stack.empty() == false && optr_stack.top().str[0] != '+' && optr_stack.top().str[0] != '-' && optr_stack.top().str[0] != '(') {
				ans_stack.push(optr_stack.top());
				optr_stack.pop();
			}
			optr_stack.push(src[i]);
		}
		else if (src[i].str[0] == '+' || src[i].str[0] == '-') {
			while (optr_stack.empty() == false && optr_stack.top().str[0] != '(') {
				ans_stack.push(optr_stack.top());
				optr_stack.pop();
			}
			optr_stack.push(src[i]);
		}
	}

	while (optr_stack.empty() == false) {
		ans_stack.push(optr_stack.top());
		optr_stack.pop();
	}
	expr_node* tempArray = new expr_node[__STRLEN__];
	int index = 0;
	while (ans_stack.empty() == false) {
		tempArray[index++] = ans_stack.top();
		ans_stack.pop();
	}
	for (int i = 0; i < index / 2; i++) {
		expr_node tempNode = tempArray[i];
		tempArray[i] = tempArray[index - 1 - i];
		tempArray[index - 1 - i] = tempNode;
	}
	*newLen = index;
	return tempArray;
}





//find unary operators in inffix expression

static void deleteNode(expr_node* a, int& len, int target) {
	for (int t = target; t < len - 1; t++) {
		a[t] = a[t + 1];
	}
	len--;
}


static void unary_operator_scan(expr_node* a, int& len) {
	if (a[0].str[0] == '+') {
		deleteNode(a, len, 0);
	}
	else if (a[0].str[0] == '-') {
		a[1].value *= (-1);
		deleteNode(a, len, 0);
	}
	for (int i = 0; i < len - 2; i++) {
		if (a[i].type == Optr && a[i+1].type == Optr) {
			if (a[i].str[0] == '+' || a[i].str[0] == '-' || a[i].str[0] == '*' || a[i].str[0] == '/' || a[i].str[0] == '(') {
				if (a[i + 1].str[0] == '-') {
					a[i + 2].value *= (-1);
					deleteNode(a, len, i + 1);
				}
				else if (a[i + 1].str[0] == '+') {
					deleteNode(a, len, i + 1);
				}
			}
		}
	}
}
