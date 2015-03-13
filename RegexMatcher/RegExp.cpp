#include "RegExp.h"
#include <stack>
#include <iostream>


RegExp::RegExp(std::string regExp) : reg(regExp), makedAutomata(false)
{
}


RegExp::~RegExp()
{
}

//��������� ��������
//todo: ���������� �� ���������� ��������
int priority(char c) {
	if (c == '(') {
		return 1;
	}
	else if (c == '|') {
		return 2;
	}
	else if (c == '.')
		return 3;
	else if (c == '*' || c == '+' || c == '?')
		return 4;
	else return 42;
}

void RegExp::makeAutomata() {
	makedAutomata = true;



}


void RegExp::makePostfix() {
	postfix = toPostfix(reg, priority);
}


std::string RegExp::toPostfix(std::string s, int(*priority)(char t)) {
	std::string answer = "";
	std::stack<char> st;

	for (auto &c : s) {
		if (c == '(')  {
			st.push(c);
		}
		else if (c == ')') {
			while (!st.empty() && st.top() != '(') {
				answer.push_back(st.top());
				st.pop();
			}
			if (!st.empty())
				st.pop();
			else
			{
				//������ ���� exception
				std::cout << "Kakoi-to kosyak" << std::endl;
				return answer;
			}
		}
		else while (!st.empty()) {
			char lst = st.top();
			if (priority(lst) >= priority(c))
			{
				answer.push_back(lst);
				st.pop();
			}
			else {
				break;
			}
			st.push(c);
		}
	}
	while (!st.empty()) {
		answer.push_back(st.top());
		st.pop();
	}
	
	return answer;
}