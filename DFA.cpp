#include "DFA.h"

DFA::DFA(int num_states, int alph, int start_index, std::vector<bool> finals, std::vector<std::unordered_map<int, int> > trans){
	transitions = trans;
	Q = num_states;
	alph_size = alph;
	q0 = start_index;
	final = finals;
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