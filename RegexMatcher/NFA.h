#pragma once
#include <string>
#include <vector>

//this is abstraction for finite path from a to b
typedef std::pair<int, int> piece;
typedef int state;
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

	std::vector<std::vector <Link> > nodes;

	state start;
	state end;
	
protected: 
	
	piece buildOr(piece a, piece b);
	piece buildConcat(piece a, piece b);
	piece buildOr(piece a, piece b);
	piece buildSymbol(char c);
	piece buildZeroOrMore(piece a);
	piece buildOneOrMore(piece a);
	piece buildZeroOrOne(piece a);
	state buildInit();


};

