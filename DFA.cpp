#include "DFA.h"

DFA::DFA(int num_states, int alph_size, int start_index, std::vector<bool> finals, std::vector<std::unordered_map<int, int> > trans){
	transitions = trans;
	Q = num_states;
	alph_size = alph_size;
	q0 = start_index;
	final = finals;
	prev = std::vector<std::unordered_map<int, std::vector<int> > > (Q, std::unordered_map<int, std::vector<int> > (0));
	for(int i = 0; i<trans.size(); i++){
		for(int j = 0; j<alph_size; j++){
			std::unordered_map<int, int>::const_iterator t = trans[i].find(j);
			if(t != trans[i].end()){
				//then there exists a transition from state i to t->second under letter j
				std::unordered_map<int, std::vector<int> >::iterator x = prev[t->second].find(j);
				if(x != prev[t->second].end()){
					//then an entry for letter j already exists
					x->second.push_back(i);
				}else{
					prev[t->second].insert({j, std::vector<int> (1, i)});
				}
			}
		}
	}
}
int DFA::num_states() const{
	return Q;
}
bool DFA::is_final(int state) const{
	return final[state];
}
int DFA::get_start() const{
	return q0;
}
int DFA::alphabet_size() const{
	return alph_size;
}
int DFA::get_next(int state, int letter) const{
	std::unordered_map<int, int>::const_iterator t = transitions[state].find(letter);
	if(t != transitions[state].end()){
		return t->second;
	}else
		return -1;
}
std::vector<int> DFA::get_prev_states(int state, int letter) const{
	std::unordered_map<int, std::vector<int> >::const_iterator t = prev[state].find(letter);
	if(t != prev[state].end())
		return t->second;
	else
		return std::vector<int> (0);
}