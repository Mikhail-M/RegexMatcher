#pragma once

#include <string>

class RegExp
{
public:
	RegExp(std::string regExp);
	~RegExp();
	//if s is matched return true
	bool match(std::string s);

protected: 
	std::string reg;
	void makeAutomata();
	void makePostfix();
	bool makedAutomata;
	std::string postfix;
private: 
	std::string toPostfix(std::string s, int (*priority)(char t) );

};

