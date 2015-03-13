#include "NFA.h"
const char eps = 0;
#include <stack>


NFA::NFA()
{
}


NFA::~NFA()
{
}


state NFA::buildInit() {
	return nodes.size() - 1;
}

piece NFA::buildSymbol(char c) {
	
    int start = buildInit(), end = buildInit();
    nodes[start].push_back(Link(end, c));
    return piece(start, end);
}


piece NFA::buildOneOrMore(piece a) {
	int startTemp = a.first, endTemp = a.second;
	int start = buildInit(), end = buildInit();
	nodes[endTemp].push_back(Link(startTemp, eps));
	nodes[start].push_back(Link(startTemp, eps));
	nodes[endTemp].push_back(Link(end, eps));
	return piece(start, end);
}

piece NFA::buildZeroOrMore(piece a) {
	piece b = buildOneOrMore(a);
	nodes[b.first].push_back(Link(b.second, eps));
	return b;
}

piece NFA::buildZeroOrOne(piece a) {
	int start = a.first, end = a.second;
	nodes[start].push_back(Link(end, eps));
	return piece(start, end);
}

piece NFA::buildOr(piece a, piece b) {
    int a_start = a.first, a_end = a.second;
    int b_start = b.first, b_end = b.second;
	int start = buildInit(), end = buildInit();
	nodes[start].push_back(Link(a_start, eps));
	nodes[start].push_back(Link(b_start, eps));
	nodes[b_end].push_back(Link(end, eps));
	nodes[a_end].push_back(Link(end, eps));

	return piece(start, end);
}

piece NFA::buildConcat(piece a, piece b) {
	int a_start = a.first, a_end = a.second;
	int b_start = b.first, b_end = b.second;
	nodes[a_end].push_back(Link(b_start, eps));
	return piece(a_start, b_end);
}
template<typename T>
T Pop(std::stack<T> &s){
	T temp = s.top();
	s.pop();
	return temp;
}
void NFA::build(std::string postfix) {
	start = 0;
	buildInit();
	std::stack<piece> st;
	for (auto& c : postfix){
		if (c == '?'){
			st.push(buildZeroOrOne(Pop<piece>(st)));
		}
		else if (c == '*') {
			st.push(buildZeroOrMore(Pop<piece>(st)));
		}
		else if (c == '+') {
			st.push(buildOneOrMore(Pop<piece>(st)));
		}
		else if (c == '.') {
			st.push(buildConcat(Pop<piece>(st), Pop<piece>(st)));
		}
		else if (c == '|') {
			st.push(buildOr(Pop<piece>(st), Pop<piece>(st)));
		}
		else {
			st.push(buildSymbol(c));
		}
	}
	if (st.empty()){
		return;
	}
	while (!st.empty()){
		start = st.top().first;
		end = st.top().second;
		st.pop();
	}
}
