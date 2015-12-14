#include "DFAFactory.h"
#include "Partition.h"
#include <stdio.h>
#include <chrono>
#include <utility>
#include "Valmari.cpp"
//converts a partition into a DFA. Both algorithms use this method
DFA complete(DFA &in, Partition &P){
	int num_states = P.num_sets();
	int alph_size = in.alphabet_size();
	int start_index = P.get_set(in.get_start());
	std::vector<bool>finals (num_states, 0);
	for(int i = 0; i<in.num_states(); i++){
		if(in.is_final(i)){
			finals[P.get_set(i)] = 1;
		}
	}
	std::vector<std::unordered_map<int, int> > trans (num_states, std::unordered_map<int, int> (0));
	for(int i = 0; i<num_states; i++){
		for(int j = 0; j<alph_size; j++){
			//for each state we connect the state it transitions to under letter j. We only need to look at one because they (better) have the same behavior
			int elem = P.get_first(i);
			int mapped_node = in.get_next(elem, j);
			if(mapped_node != -1)
				trans[i].insert({j, P.get_set(mapped_node)});
		}
	}
	return DFA(num_states, alph_size, start_index, finals, trans);
}

//This is the implementation of Hopcroft's algorithm.
DFA Hopcroft(DFA &in){
	//The partition of states into like behavior
	Partition P = Partition(in.num_states());
	for(int i = 0; i<in.num_states(); i++){
		if(in.is_final(i)){
			P.mark(i);
		}
	}
	P.split(0);
	//The schedule contains the set of partitions that might need further splitting. We only need to add half of these partitions due to a lemma by Hopcroft
	//schedule_members tells us whether a specific index is actually in the schedule. Index tells us where to start looking for the next schedule member; it only increases.
	int index = 1;
	std::vector<bool> schedule_members(2, 0);
	schedule_members[1] = 1;
	std::vector<std::vector<std::vector<int> > > prevs (in.num_states(), std::vector<std::vector<int> > (in.alphabet_size(), std::vector<int> (0)));
	for(int i = 0; i<in.num_states(); i++){
		for(int j = 0; j<in.alphabet_size(); j++)
			prevs[in.get_next(i, j)][j].push_back(i);
	}
	while(true){
		while(index<schedule_members.size() && !schedule_members[index]){
			index++;
		}
		if(index == schedule_members.size())
			break;
		//now we must have found something that is actually in the schedule
		schedule_members[index] = 0;
		for(int i = 0; i<in.alphabet_size(); i++){
			//find the preimage of the partition with the set index under letter i
			std::vector<bool> prev_map(in.num_states(), 0);
			//Each node in the previous map is considered only once => O(n) time.
			for(int pos = P.get_first(index); pos!=-1; pos = P.get_next(pos)){
				for(int node : prevs[pos][i])
					prev_map[node] = 1;
			}
			//iterating through P will never go through more than O(n) states
			for(int j = 0; j<P.num_sets(); j++){
				//Now we calculate the parts of prev_map that are in or out of each set of P
				std::vector<int> in_S;
				std::vector<int> out_S;
				for(int pos = P.get_first(j); pos!=-1; pos = P.get_next(pos)){
					if(prev_map[pos])
						in_S.push_back(pos);
					else
						out_S.push_back(pos);
				}
				if(in_S.size() > 0 && out_S.size() > 0){
					//Then the set j is not fine enough. We need to split this set
					if(in_S.size() < out_S.size()){
						for(int elem : in_S)
							P.mark(elem);
						P.split(j);
						// Now out is at the last index and in is at index j
						// we check if the partition at index j is in the schedule. If it is, then both in and out must be added.
						// If it isn't, then the out must be marked. Both cases simplify to simply marking out as marked
						// otherwise, 
						schedule_members.push_back(1);
					}else{
						//the other case
						for(int elem : out_S){
							P.mark(elem);
						}
						P.split(j);
						schedule_members.push_back(1);
					}
				}
			}
		}
	}
	//Now we have a suitable partition. We pass it to complete to produce a DFA.
	return complete(in, P);
}
/*
//This is my implementation of Valmari-Lehtinen. It isn't quite done because their paper is impossible to understand.
//Valmari's implementation is in Valmari.cpp
class Transition{
	int start;
	int letter;
	int end;
};
DFA *ValmariLehtinen(DFA *in){
	vector<Transition *> trans;
	Partition *P = new Partition(in.num_states());
	Partition *T = new Partition(trans.size());

	sort(trans.begin(), trans.end(), 
		[&](Transition *a, Transition *b){
			return a->letter < b->letter;
		}
	);
	//bucket sort trans
	for(int i = 0; i<in.num_states(); i++){
		if(in.is_final(i)){
			P.mark(i);
		}
	}
	//This keeps track of the set indices (of T) that each element of P maps to.
	vector<vector<int> > indices(P.num_sets(), vector<int> (0));
	//now, we split T based on letters
	for(int i = 0; i<in.alphabet_size(); i++){
		for(int j = T->get_start(0); j >= 0 && trans[j]->letter == i; j = T->get_next(j)){
			T->mark(j);
		}
		T->split(0);
		//The split elements were just moved to the end
		int end = T->num_sets()-1;
		//Now we must split depending on which set of P we are in
		for(int j = T->get_start(end); j>= 0; j = T->get_next(j)){
			if(P.get_set(trans[j]->end) == 1)
				T->mark(j);
		}
		T->split(end);
	}
	//Now, T has been initialized. We need to initialize indices
	for(int i = 0; i<T->num_sets(); i++){
		indices[P.get_set(trans[T->get_start(i)]->end)].push_back(i);
	}
	vector<pair<int, int> 
	while(true){
		int elem = indices[vert][horiz].first; //pick your favorite element of U
		//now we want to split the partitions of B using elem
		for(int j = T->get_start(elem); j >= 0; j = T->get_next(j)){
			P.mark(trans[j]->start);
		}
		int sets = P.num_sets();
		for(int i = 0; i<sets; i++){
			int s1 = P.get_size(i);
			int s2 = P.split(i);
			if(s1 != s2 && s2 > 0){
				//Then P just got split into two pieces, i and end
				int end = P.num_sets()-1;
				vector<pair<int, int> > s1_indices;
				vector<pair<int, int> > s2_indices;
				for(int x : indices[i])
			}
		}
	}
}
*/

int main(){
	printf("Welcome to the DFA minimizer\nWhich DFA would you like to minimize?\n");
	while(true){
		printf("(1) Exponential DFA of L letters accepting only the string 0^n\n");

		int x; scanf("%d", &x);
		switch(x){
			case 1:
			{
				printf("Enter n and L. (Warning: This DFA has size O(L^n): ");
				int sz, alpha; scanf("%d %d", &sz, &alpha);
				DFA x = DFAFactory::exponential_DFA(sz, alpha);
				printf("Timing begins now\n");
				auto start = std::chrono::high_resolution_clock::now();
				DFA y = Hopcroft(x);
				auto finish = std::chrono::high_resolution_clock::now();
				printf("Hopcroft took: ");
				printf("%li ns\n", std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count());

				start = std::chrono::high_resolution_clock::now();
				y = Valmari(x);
				finish = std::chrono::high_resolution_clock::now();
				printf("Valmari took: ");
				printf("%li ns\n", std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count());
				break;
			}
			default:
			{
				printf("Invalid number!\n");
				break;
			}
		}
	}
	return 0;
}