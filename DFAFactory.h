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
	//generates an exponential (in n) DFA that accepts only a string of n 0s.
	DFA *exponential_DFA(int n, int alph_size);
};