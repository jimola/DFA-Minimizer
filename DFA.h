#include <vector>
#include <unordered_map>
//This is my representation of a DFA. It also includes some functions that will generate DFAs automatically.
class DFA{
	int Q;
	std::vector<bool> final;
	int q0;
	int alph_size;
	// transitions[i] maps j to k iff there exists a transition from i to k under letter j
	std::vector<std::unordered_map<int, int> > transitions;
	// the list of every node that maps to a given state under a certain transition
	std::vector<std::unordered_map<int, std::vector<int> > > prev;
public:
	int num_states() const;
	bool is_final(int state) const;
	int get_start() const;
	int alphabet_size() const;
	int get_next(int state, int letter) const;
	std::vector<int> get_prev_states(int state, int letter) const;
	DFA(int num_states, int alph_size, int start_index, std::vector<bool> finals, std::vector<std::unordered_map<int, int> > trans);
};