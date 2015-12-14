#include "DFAFactory.h"
#include <math.h>
DFA DFAFactory::endsIn01_inefficient(){
	int num_states = 6;
	int alph_size = 2;
	int start_index = 0;
	std::vector<bool> finals (6, 0);
	finals[2] = 1;
	std::vector<std::unordered_map<int, int> > trans (6, std::unordered_map<int, int> (0));
	trans[0] = {{0, 1}, {1, 0}};
	trans[1] = {{0, 1}, {1, 2}};
	trans[2] = {{0, 5}, {1, 3}};
	trans[3] = {{0, 4}, {1, 3}};
	trans[4] = {{0, 4}, {1, 2}};
	trans[5] = {{0, 5}, {1, 2}};
	return DFA(num_states, alph_size, start_index, finals, trans);
}

DFA DFAFactory::exponential_DFA(int n, int alph_size){
	int num_states = 1;
	std::vector<std::unordered_map<int, int> > trans (0);
	for(int i = 0; i<n; i++){
		for(int j = 0; j<pow(alph_size, i); j++){
			std::unordered_map<int, int> x (0);
			for(int k = 0; k<alph_size; k++){
				x.insert({k, num_states+j*alph_size+k});
			}
			trans.push_back(x);
		}
		num_states+=pow(alph_size, i+1);
	}
	for(int i = 0; i<=pow(alph_size, n); i++){
		std::unordered_map<int, int> x(0);
		for(int k = 0; k<alph_size; k++)
			x.insert({k, num_states});
		trans.push_back(x);
	}
	num_states++;
	std::vector<bool> finals(num_states, 0);
	finals[num_states-2] = 1;
	return DFA(num_states, alph_size, 0, finals, trans);
}