#include <vector>
//This is my representation of a DFA. It uses unordered maps so it can also be a partial DFA
class DFA{
public:
	DFA(int num_states, int alph_size, int start_index, std::vector<bool> finals, std::vector<int> H, std::vector<int> L, std::vector<int> T);
	void print_DFA();
	//number of states
	int Q;
	//whether a state is final
	std::vector<bool> final;
	//starting state
	int q0;
	//size of alphabet; a letter is an integer from 0 to alph_size-1
	int alph_size;
	// transitions[i] maps j to k iff there exists a transition from i to k under letter j
	std::vector<int> Heads;
	std::vector<int> Labels;
	std::vector<int> Tails;
};