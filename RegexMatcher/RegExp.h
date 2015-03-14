#pragma once

#include <string>

#include "NFA.h"
#include "DFA.h"

class RegExp
{
public:
	RegExp(std::string regExp);
	~RegExp();
	//if s is matched return true
	bool match(std::string s);
	void makeAutomata();

protected:
	std::string reg;
	void makePostfix();
	bool makedAutomata;
	std::string postfix;
	DFA dfa;

private: 
	std::string toPostfix(std::string s, int (*priority)(char t) );
};

