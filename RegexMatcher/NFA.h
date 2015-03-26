#pragma once
#include <string>
#include <vector>
#include <stack>

//this is abstraction for finite path from a to b
typedef std::pair<int, int> piece;
#define state int

class NFA
{
public:
	NFA();
	~NFA();
	void build(std::string postfix);

	struct Link {
		state to;
		char c;
		Link(int _to, char _c) : to(_to), c(_c)
		{}
	};

	std::vector <state> move(std::vector <state> &fromStates, char c);
	std::vector <state> moveWithoutEpsilons(std::vector <state> &fromStates);

	std::vector<std::vector <Link> > states;
	state startState;
	state finalState;
	
protected: 
	std::vector <state> justMove(std::vector <state> &fromStates, char c);
	std::stack<int> renumbering;
	piece buildOr(piece a, piece b);
	piece buildConcat(piece a, piece b);
	piece buildSymbol(char c);
	piece buildKleene—losure(piece a);
	state buildInit();
	piece buildEpsilon();



};

