#include "partition.h"

Partition::size(int m){
	max = m;
	elems = vector<int> (m, 0);
	locs = vector<int> (m, 0);
	for(int i = 0; i<m; i++){
		elems[i] = i;
		locs[i] = i;
	}
	
}