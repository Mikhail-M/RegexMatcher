#include "NFA.h"
const char eps = 0;
#include <stack>
#include <map>
#include <iostream>


NFA::NFA()
{
}


NFA::~NFA()
{
}


state NFA::buildInit() {
	nodes.push_back(std::vector<Link>());
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
	start = buildInit();

	std::stack<piece> st;
	for (auto& c : postfix){
		if (c == '?') {
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

//from node by link into set of nodes
std::vector<state> NFA::justMove(std::vector <state> &states, char c) {
	std::vector<state> ans;

	for (auto& n : states)
		for (auto& link : nodes[n])
			if (link.c == c) {
				ans.push_back(link.to);
			}

	return ans;
}

//use axiom of choice
std::vector <state> NFA::withoutEpsilons(std::vector <state> &states) {
	std::vector<state> ans;
	std::map<state, bool> was;
	std::stack<state> st;

	for (auto& n : states) {
		ans.push_back(n);
		was[n] = true;
		st.push(n);
	}
	while (!st.empty()) {
		state cur = Pop(st);
		was[cur] = true;
		for (auto& n : nodes[cur]) {
			if (n.c == eps && was.find(n.to) == was.end()){
				st.push(n.to);
				ans.push_back(n.to);

			}
		}

		return ans;
	}
}

std::vector <state> NFA::move(std::vector <state> &states, char c) {
	std::vector<state> res = justMove(states, c);
	return withoutEpsilons(res);
}

