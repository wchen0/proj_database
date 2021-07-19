#include "Create.h"
#include <stack>
#include <cmath>

/*
* Use suffix expression to calculate
*/


double suffix_expr_calculate(expr_node* suffix, int len) {   //返回INF代表无效
	std::stack<double> s;
	for (int i = 0; i < len; i++) {
		if (suffix[i].type == Optr) {
			if (suffix[i].str[0] == '*') {
				if (s.empty()) { printf("Invalid Input\n"); return __INF__; }
				double a = s.top();
				s.pop();
				if (s.empty()) { printf("Invalid Input\n"); return __INF__; }
				double b = s.top();
				s.pop();
				s.push(a * b);
			}
			else if (suffix[i].str[0] == '/') {
				if (s.empty()) { printf("Invalid Input\n"); return __INF__; }
				double a = s.top();
				s.pop();
				if (s.empty()) { printf("Invalid Input\n"); return __INF__; }
				double b = s.top();
				s.pop();
				if (fabs(a) < __EPS__) {
					printf("Invalid Input: Denominator is zero\n");
					return __INF__;
				}
				s.push(b / a);
			}
			else if (suffix[i].str[0] == '+') {
				if (s.empty()) { printf("Invalid Input\n"); return __INF__; }
				double a = s.top();
				s.pop();
				if (s.empty()) { printf("Invalid Input\n"); return __INF__; }
				double b = s.top();
				s.pop();
				s.push(a + b);
			}
			else if (suffix[i].str[0] == '-') {
				if (s.empty()) { printf("Invalid Input\n"); return __INF__; }
				double a = s.top();
				s.pop();
				if (s.empty()) { printf("Invalid Input\n"); return __INF__; }
				double b = s.top();
				s.pop();
				s.push(b - a);
			}
		}
		else s.push(suffix[i].value);
	}
	if (s.empty()) { printf("Invalid Input\n"); return __INF__; }
	return s.top();
}


double calculate(char* expr) {
	int ansl = 0;
	expr_node* arr = str_to_arr(expr, &ansl);
	if (arr == NULL) return __INF__;
	arr = inffix_to_suffix(arr, ansl, &ansl);
	if (arr == NULL) return __INF__;
	return suffix_expr_calculate(arr, ansl);
}