#include <iostream> 
#include <string> 
#include "RegExp.h"

using namespace std; 


int main() {
	string regExp = "(a.a.a)*";
	string test = "aaaaaa";

	RegExp r(regExp);
	cout << r.match(test);


	return 0;
}