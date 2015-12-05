#include "DFAFactory.h"

DFA DFAFactory::endsIn01_inefficient(){
	int num_states = 6;
	int alph_size = 2;
	int start_index = 0;
	std::vector<bool> finals = std::vector<bool>(6, 0);
	finals[2] = 1;
	std::vector<std::unordered_map<int, int> > trans = std::vector<std::unordered_map<int, int> > (6, std::unordered_map<int, int> (0));
	trans[0] = {{0, 1}, {1, 0}};
	trans[1] = {{0, 1}, {1, 2}};
	trans[2] = {{0, 5}, {1, 3}};
	trans[3] = {{0, 4}, {1, 3}};
	trans[4] = {{0, 4}, {1, 2}};
	trans[5] = {{0, 5}, {1, 2}};
	return DFA(num_states, alph_size, start_index, finals, trans);
}
