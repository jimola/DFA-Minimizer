#include "DFA.h"

DFA::DFA(int num_states, int alph, int start_index, std::vector<bool> finals, std::vector<std::unordered_map<int, int> > trans){
	transitions = trans;
	Q = num_states;
	alph_size = alph;
	q0 = start_index;
	final = finals;
	prev = std::vector<std::unordered_map<int, std::vector<int> > > (Q, std::unordered_map<int, std::vector<int> > (0));
	for(int i = 0; i<trans.size(); i++){
		for(int j = 0; j<alph_size; j++){
			auto t = trans[i].find(j);
			if(t != trans[i].end()){
				//then there exists a transition from state i to t->second under letter j
				auto x = prev[t->second].find(j);
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
int DFA::num_states(){
	return Q;
}
bool DFA::is_final(int state){
	return final[state];
}
int DFA::get_start(){
	return q0;
}
int DFA::alphabet_size(){
	return alph_size;
}
int DFA::get_next(int state, int letter){
	auto t = transitions[state].find(letter);
	if(t != transitions[state].end()){
		return t->second;
	}else
		return -1;
}
std::vector<int> DFA::get_prev_states(int state, int letter){
	auto t = prev[state].find(letter);
	if(t != prev[state].end())
		return t->second;
	else
		return std::vector<int> (0);
}
void DFA::print_DFA(){
	printf("There are %d states\n", Q);
	printf("The starting state is %d\n", q0);
	printf("The final states are: ");
	for(int i = 0; i<Q; i++){
		if(final[i])
			printf("%d ", i);
	}
	printf("\nThe alphabet size is %d\n", alph_size);
	printf("The transitions are:\n");
	for(int i = 0; i<Q; i++){
		printf("%d transitions to: ", i);
		for(auto x = transitions[i].cbegin(); x!=transitions[i].cend(); x++){
			printf("(%d %d) ", x->first, x->second);
		}
		printf("\n");
	}
}