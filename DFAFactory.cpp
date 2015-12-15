#include "DFAFactory.h"
#include <math.h>
DFA *DFAFactory::endsIn01_inefficient(){
	int num_states = 6;
	int alph_size = 2;
	int start_index = 0;
	std::vector<bool> finals (6, 0);
	finals[2] = 1;
	std::vector<int> Tails = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
	std::vector<int> Labels = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
	std::vector<int> Heads = {1, 0, 1, 2, 5, 3, 4, 3, 4, 2, 5, 2};
	return new DFA(6, 2, 0, finals, Tails, Labels, Heads);
}

DFA *DFAFactory::exponential_DFA(int n, int alph_size){
	int num_states = 1;
	std::vector<int> Tails;
	std::vector<int> Labels;
	std::vector<int> Heads;
	for(int i = 0; i<n; i++){
		for(int j = 0; j<pow(alph_size, i); j++){
			for(int k = 0; k<alph_size; k++){
				Tails.push_back(i);
				Labels.push_back(k);
				Heads.push_back(num_states+j*alph_size+k);
			}
		}
		num_states+=pow(alph_size, i+1);
	}
	for(int i = 0; i<=pow(alph_size, n); i++){
		for(int k = 0; k<alph_size; k++){
			Tails.push_back(i);
			Labels.push_back(k);
			Heads.push_back(num_states);
		}
	}
	num_states++;
	std::vector<bool> finals(num_states, 0);
	finals[num_states-2] = 1;
	return new DFA(num_states, alph_size, 0, finals, Tails, Labels, Heads);
}
