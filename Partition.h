#include <vector>
//This is the partition refinement data structure used in both algorithms.
//The code for this data structure is taken from the pseudocode in the Valmari-Lehtinen paper except I use zero-indexing.
class Partition{
private:
	int sets;//the number of sets or partitions
	int max; //the number of elements in all the sets
	std::vector<int> elems; //the actual ordering of the elements where elements in the same set are grouped together and all marked elements are on the left side
	std::vector<int> locs; //locs[e] contains the index of e in elems
	std::vector<int> sidx; //sidx[e] is the index of the set that e belongs to
	std::vector<int> first; //first[s] is the index j such that elems[j] is the first element of s
	std::vector<int> end; //end[s] is the index j such that elems[j-1] is the last element of s
	std::vector<int> mid; //mid[s] is the index j such that everything from mid[s] to end[s] non-inclusive is unmarked in set s.
public:
	Partition(int m);
	//returns the number of elements in set s
	int get_size(int s);

	//finds the set that the given element belongs to
	int get_set(int e);

	//returns the first element in a given set
	int get_first(int s);

	//returns the next element in the same set as the given element or 0 if there is none
	int get_next(int e);

	//marks an element to be split
	void mark(int e);

	//if none or all of the elements of the set have been split, then do nothing. Otherwise, split the set into two new sets, split and not-split.
	//return the size of the new created set
	// The split elements must be moved to the new set with the largest index!
	int split(int s);

	//returns whether any of the elements have been marked
	bool no_marks(int s);

	//returns the number of sets in P
	int num_sets();

	//for testing purposes
	void print();
};