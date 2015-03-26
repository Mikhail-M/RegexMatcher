#include <iostream> 
#include <string> 
#include <fstream> 

#include "RegExp.h"

using namespace std; 

string to_norm(string s) {
	string temp = "";
	for (int i = 0; i < s.size() - 1; i++){
		char t1 = s[i];
		temp += t1;
		char t2 = s[i + 1];
		if (t1 != '(' && t1 != '|' && t2 != ')' && t2 != '|' && t2 != '.' && t2 != '*'){
			temp += '.';
		}
	}
	temp += s[s.size() - 1];
	return temp;

}
int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");
	string regExp;
	in >> regExp;
	regExp = to_norm(regExp);
	RegExp matcher(regExp);
	int m;
	in >> m;
	for (int i = 0; i < m; i++){
		string test;
		in >> test;

		if (matcher.match(test))
			out << "YES" << endl;
		else 
			out << "NO" << endl;	
	}


	return 0;
}