#include "DFA.h"
#include <cstdlib>
#include <ctime>
//This class generates some DFAs. Some of them are inefficient for testing purposes
class DFAFactory{
public:
	DFAFactory(){
		srand(time(NULL));
	}
	//generates a small DFA that accepts strings ending in 01. One can check that it is equivalent
	DFA *endsIn01_inefficient();
	//generates an exponential (in n) DFA with a tree-like structure.
	DFA *exponential_DFA(int n, int alph_size);
	//generates a random DFA (except on one alphabet track, to make sure the DFA is connected)
	DFA *random(int n, int alph_size);
	//generates a minimal DFA that accepts the language 0^{<n}1^{<n}0^{<n}1^{<n}...(repeating n times)
	DFA *repeating_01(int n);
};