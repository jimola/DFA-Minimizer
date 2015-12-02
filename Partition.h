#include <vector>
//This is the partition refinement data structure used in both algorithms.
//The code for this data structure is stolen from the pseudocode in the Valmari-Lehtinen paper except I use zero-indexing and half-open intervals
class Partition{
	int sets;//the number of sets or partitions
	int max; //the number of elements in all the sets
	vector<int> elems; //the actual ordering of the elements where elements in the same set are grouped together and all marked elements are on the left side
	vector<int> locs; //locs[e] contains the index of e in elems
	vector<int> sidx; //sidx[e] is the index of the set that e belongs to
	vector<int> first; //first[s] is the j such that elems[j] is the first element of s
	vector<int> end; //end[s] is the j such that elems[j-1] is the last element of s
	vector<int> mid; //mid[s] is the j such that everything from mid[s] to end[s] non-inclusive is not marked.
public:
	Partition(int m);
	//returns the number of elements in set s
	int size(int set);

	//finds the set that the given element belongs to
	int set(int elem);

	//returns the first element in a given set
	int first(int set);

	//returns the next element in the same set as the given element or 0 if there is none
	int next(int elem);

	//marks an element to be split
	void mark(int elem);

	//if none or all of the elements of the set have been split, then do nothing. Otherwise, split the set into two new sets, split and not-split. At the end, unmark everything
	int split(int set);

	//returns whether any of the elements have been marked
	bool no_marks(int set);
};