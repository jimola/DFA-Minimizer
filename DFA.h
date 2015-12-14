#include <vector>
#include <unordered_map>
#include <stdio.h>
//This is my representation of a DFA. It uses unordered maps so it can also be a partial DFA
class DFA{
	//number of states
	int Q;
	//whether a state is final
	std::vector<bool> final;
	//starting state
	int q0;
	//size of alphabet; an letter is an integer from 0 to alph_size-1
	int alph_size;
	// transitions[i] maps j to k iff there exists a transition from i to k under letter j
public:
	std::vector<std::unordered_map<int, int> > transitions;
	DFA(int num_states, int alph_size, int start_index, std::vector<bool> finals, std::vector<std::unordered_map<int, int> > trans);
	//returns the number of states
	int num_states();
	//returns whether a given state is final
	bool is_final(int state);
	//returns the starting state
	int get_start();
	//returns the alphabet size
	int alphabet_size();
	//returns the next state
	int get_next(int state, int letter);
	void print_DFA();
};