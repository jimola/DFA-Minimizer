#include <vector>
#include <unordered_map>
#include <stdio.h>
//This is my representation of a DFA. It can also be a partial DFA
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
	std::vector<std::unordered_map<int, int> > transitions;
	// the list of every node that maps to a given state under a certain transition
	std::vector<std::unordered_map<int, std::vector<int> > > prev;
public:
	DFA(int num_states, int alph_size, int start_index, std::vector<bool> finals, std::vector<std::unordered_map<int, int> > trans);
	int num_states() const;
	bool is_final(int state) const;
	int get_start() const;
	int alphabet_size() const;
	int get_next(int state, int letter) const;
	std::vector<int> get_prev_states(int state, int letter) const;
	void print_DFA();
};