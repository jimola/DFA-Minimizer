#include "Partition.h"
#include <stdio.h>
Partition::Partition(int m){
	sets = 1;
	max = m;
	elems = std::vector<int> (m, 0);
	locs = std::vector<int> (m, 0);
	sidx = std::vector<int> (m, 0);
	for(int i = 0; i<m; i++){
		elems[i] = i;
		locs[i] = i;
	}
	first = std::vector<int> (1, 0);
	end = std::vector<int>(1, m);
	mid = std::vector<int> (1, 0);
}

int Partition::get_size(int s){
	return end[s] - first[s];
}
int Partition::get_set(int e){
	return sidx[e];
}
int Partition::get_first(int s){
	return elems[first[s]];
}
int Partition::get_next(int e){
	if(locs[e] +1 >= end[sidx[e]]) // then this is the last element in its set
		return -1;
	else return elems[locs[e]+1];
}
void Partition::mark(int e){
	int s = sidx[e];
	int l = locs[e];
	int m = mid[s];
	if(m <= l){
		//Then the element is unmarked and needs to be swapped
		elems[l] = elems[m];
		locs[elems[l]] = l;
		elems[m] = e;
		locs[e] = m;
		mid[s]++;
	}
}
int Partition::split(int s){
	if(mid[s] == end[s]) // then everything is marked
		mid[s] = first[s];
	if(mid[s] == first[s]) // then nothing is marked
		return 0;
	//move the marked elements to the last set
	first.push_back(first[s]);
	mid.push_back(first[s]);
	end.push_back(mid[s]);
	first[s] = mid[s];
	for(int i = first[sets]; i<end[sets]; i++){
		sidx[elems[i]] = sets;
	}
	sets++;
	return end.back() - first.back();
}
bool Partition::no_marks(int s){
	return mid[s] == first[s];
}
int Partition::num_sets(){
	return sets;
}
void Partition::print(){
	printf("The sets look like:\n");
	for(int i = 0; i<num_sets(); i++){
		printf("(");
		for(int j = get_first(i); j!=-1; j = get_next(j))
			printf("%d ", j);
		printf(")\n");
	}
}