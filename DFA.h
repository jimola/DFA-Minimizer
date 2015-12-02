#include <vector>

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