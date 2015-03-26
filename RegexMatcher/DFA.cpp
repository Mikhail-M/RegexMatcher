#include "DFA.h"
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;
DFA::DFA()
{
}


DFA::~DFA()
{
}

bool DFA::match(string s) {
	state _state = 0;
	int check = 0;
	int iter = 1;

	for (auto& c : s) {
		if (states[_state].transition.find(c) == states[_state].transition.end()) 
			return 0;
		
		if ((states[states[_state].transition[c]].isFinalState()))
			check = iter;

		_state = states[_state].transition[c];
		iter++;
	}

	return check == s.size();

}

bool DFA::StateDFA::isEqual(StateDFA &a){

	if (states.size() != a.states.size()) 
		return false; 
	for (size_t i = 0; i < states.size(); i++) {
		if (states[i] != a.states[i])
			return false;
	}
	return true;
}

DFA::StateDFA::StateDFA(vector<state> _states, state final) : finalState(false) {
	states = _states;
	sort(states.begin(), states.end());

	for (auto &n : states) 
		finalState = (n == final ? true: false);
	

	
}

//Tompson algorithm
void DFA::build(NFA &a) {

	vector<state> first_node = {a.startState};

	states.push_back(StateDFA(a.moveWithoutEpsilons(first_node), a.finalState));

	stack<state> st;
	st.push(0);

	while (!st.empty()) {

		state current = st.top();
		st.pop();
		
		for (char c = 'a'; c <= 'z'; c++) {
			
			vector<int> temp_ids = a.move(states[current].states, c);
			if (temp_ids.size())
			{
				StateDFA temp(temp_ids, a.finalState);

				int pos = -1;
				for (size_t i = 0; i < states.size(); i++)
					if (states[i].isEqual(temp)) {
						pos = i;
						break;
					}

				if (pos == -1) {
					states.push_back(temp);
					st.push(states.size() - 1);
					pos = st.top();
				}
				states[current].addLink(pos, c);
			}
		}
	}	
}
