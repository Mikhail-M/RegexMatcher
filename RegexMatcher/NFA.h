#pragma once
#include <string>
#include <vector>

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
	std::vector <state> move(std::vector <state> &states, char c);
	std::vector <state> moveWithoutEpsilons(std::vector <state> &states);

	std::vector<std::vector <Link> > nodes;
	state startState;
	state finalState;
	
protected: 
	std::vector <state> justMove(std::vector <state> &states, char c);

	piece buildOr(piece a, piece b);
	piece buildConcat(piece a, piece b);
	piece buildSymbol(char c);
	piece buildZeroOrMore(piece a);
	piece buildOneOrMore(piece a);
	piece buildZeroOrOne(piece a);
	state buildInit();


};

