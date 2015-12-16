#include "DFAFactory.h"
typedef long long ll;
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
	ll num_states = 0;
	ll layer = 1;
	std::vector<int> Tails;
	std::vector<int> Labels;
	std::vector<int> Heads;
	for(int i = 0; i<n; i++){
		for(int j = 0; j<layer; j++){
			for(int k = 0; k<alph_size; k++){
				Tails.push_back(num_states+j);
				Labels.push_back(k);
				Heads.push_back(num_states+layer+j*alph_size+k);
			}
		}
		num_states += layer;
		layer *= alph_size;
	}
	for(int i = 0; i<=layer; i++){
		for(int k = 0; k<alph_size; k++){
			Tails.push_back(num_states+i);
			Labels.push_back(k);
			Heads.push_back(num_states+layer);
		}
	}
	num_states += layer+1;
	std::vector<bool> finals(num_states, 0);
	return new DFA(num_states, alph_size, 0, finals, Tails, Labels, Heads);
}

DFA *DFAFactory::random(int n, int alph_size){
	std::vector<int> Tails;
	std::vector<int> Labels;
	std::vector<int> Heads;
	for(int i = 0; i<n; i++){
		Tails.push_back(i);
		Labels.push_back(0);
		Heads.push_back((i+1) % n);
	}
	for(int x = 1; x<alph_size; x++){
		for(int i = 0; i<n; i++){
			Tails.push_back(i);
			Labels.push_back(x);
			Heads.push_back(rand() % n);
		}
	}
	std::vector<bool> finals(n, 0);
	for(int i = 0; i<n; i++)
		finals[i] = rand() % 2;
	return new DFA(n, alph_size, 0, finals, Tails, Labels, Heads);
}

DFA *DFAFactory::repeating_01(int n){
	std::vector<int> Tails;
	std::vector<int> Labels;
	std::vector<int> Heads;
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			Tails.push_back(i*n+j);
			Labels.push_back(i%2);
			Heads.push_back(i*n+j+1);
			Tails.push_back(i*n+j);
			Labels.push_back((i+1)%2);
			Heads.push_back(n*(i+1));
		}
	}
	for(int i = 0; i<2; i++){
		Tails.push_back(n*n);
		Labels.push_back(i);
		Heads.push_back(n*n);
	}
	int num_states = n*n+1;
	std::vector<bool> finals(num_states, 1);
	finals.back() = 0;
	return new DFA(num_states, 2, 0, finals, Tails, Labels, Heads);
}