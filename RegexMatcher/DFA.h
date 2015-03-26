#pragma once

#include <vector>
#include <map>

#include "NFA.h"

#define state int

class DFA
{
public:
	DFA();
	~DFA();
	void build(NFA &a);
	bool match(std::string s);

private:
	
	class StateDFA {
	public:
		StateDFA(std::vector<state> ids, state end);
		
		//transition function  
		std::map<char, unsigned int> transition;
		std::vector<state> states;
		
		inline void addLink(state to, char c) {
			transition[c] = to;
		}
		bool isEqual(StateDFA &a);
	    bool isFinalState(){
			return finalState;
		}
	private:
		bool finalState;
	};
	std::vector<StateDFA> states;
};

