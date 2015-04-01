#pragma once

#include <vector>
#include <map>
#include <set>


#include "NFA.h"

#define state int
using namespace std;

class DFA
{
public:
	DFA();
	~DFA();
	void build(NFA &a);
	bool match(std::string s);
	void minimize();
	void dot(std::ostream& output);


private:
	
	class StateDFA {
	public:
		StateDFA(std::vector<state> ids, state end);
		StateDFA(){
			finalState = false;
		}
		//transition function  
		std::map<char, int> transition;
		std::vector<state> states;
		
		inline void addLink(state to, char c) {
			transition[c] = to;
		}
		bool isEqual(StateDFA &a);
	    bool isFinalState(){
			return finalState;
		}
	
		bool finalState;
	};
	std::vector<StateDFA> states;
	void dfs(state start, std::vector<bool> &used);
	void buildTransition();
	bool isExistDevilState();
	bool existDevilState;

	std::map<int, std::map<char, int>> transition;
	vector< vector<bool> > buildTable(int n, vector<bool> isTerminal, map<int, map<char, set<int> > > reverseTransition);
	void buildDFA(vector<int> &component, vector<bool> isTerminal);
	int startState;
};

