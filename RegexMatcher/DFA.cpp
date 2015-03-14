#include "DFA.h"
#include <algorithm>
#include <stack>
#include <iostream>

DFA::DFA()
{
}


DFA::~DFA()
{
}

bool DFA::match(std::string s) {
	state _state = 0;
	int check = 0;
	int iter = 1;
	for (auto& c : s){
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

	if (states.size() != a.states.size()) { return false; }
	for (int i = 0; i < states.size(); i++) {
		if (states[i] != a.states[i])
			return false;
	}
	return true;
}

DFA::StateDFA::StateDFA(std::vector<state> _states, state final) : finalState(false) {
	states = _states;
	std::sort(states.begin(), states.end());

	for (auto &n : states) 
		finalState = (n == final ? true: false);
	

	
}

//Tompson algorithm
void DFA::build(NFA &a) {

	std::vector<state> first_node = {a.startState};

	states.push_back(StateDFA(a.moveWithoutEpsilons(first_node), a.finalState));

	std::stack<state> st;
	st.push(0);

	
	while (!st.empty()){

		state current = st.top();
		st.pop();
		
		for (char c = 'a'; c <= 'z'; c++){
			std::vector<int> temp_ids = a.move(states[current].states, c);


			StateDFA temp(temp_ids, a.finalState);
			if (!temp_ids.size()){
				
				continue;
			}

			int pos = -1;
			for(int i = 0; i < states.size(); ++i){
				if (states[i].isEqual(temp) ){
					
					pos = i;
					break;
				}
			}

			if (pos < 0){
				states.push_back(temp);
				st.push(states.size() - 1);
				pos = st.top();
			}
			states[current].addLink(pos, c);

		}
	}	
}
