#include <vector>

//This is my representation of a DFA. It also includes some functions that will generate DFAs automatically.
typedef pair<int, int> transition;
class DFA{
public:
	int Q;
	vector<int> final;
	int q0;
	int alphabet;
	vector<vector<transition> > transitions;
	DFA();
};