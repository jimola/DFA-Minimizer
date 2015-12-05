#include "DFAFactory.h"
#include "Partition.h"
#include <stdio.h>
#include <chrono>

//converts a partition into a DFA. Both algorithms use this method
DFA complete(const DFA &in, Partition *P){
	int num_states = P->num_sets();
	int alph_size = in.alphabet_size();
	int start_index = P->get_set(in.get_start());
	std::vector<bool>finals (num_states, 0);
	for(int i = 0; i<in.num_states(); i++){
		if(in.is_final(i)){
			finals[P->get_set(i)] = 1;
		}
	}
	std::vector<std::unordered_map<int, int> > trans (num_states, std::unordered_map<int, int> (0));
	for(int i = 0; i<num_states; i++){
		for(int j = 0; j<alph_size; j++){
			//for each state we connect the state it transitions to under letter j. We only need to look at one because they (better) have the same behavior
			int elem = P->get_first(i);
			int mapped_node = in.get_next(elem, j);
			if(mapped_node != -1)
				trans[elem].insert({j, P->get_set(mapped_node)});
		}
	}
	free(P);
	return DFA(num_states, alph_size, start_index, finals, trans);
}

//This is the implementation of Hopcroft's algorithm.
DFA Hopcroft(const DFA &in){
	//The partition of states into like behavior
	Partition *P = new Partition(in.num_states());
	for(int i = 0; i<in.num_states(); i++){
		if(in.is_final(i)){
			P->mark(i);
		}
	}
	P->split(0);
	//The schedule contains the set of partitions that might need further splitting. We only need to add half of these partitions due to a lemma by Hopcroft
	//schedule_members tells us whether a specific index is actually in the schedule. Index tells us where to start looking for the next schedule member; it only increases.
	int index = 1;
	std::vector<bool> schedule_members(2, 0);
	schedule_members[1] = 1;
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
			for(int pos = P->get_first(index); pos!=-1; pos = P->get_next(pos)){
				for(int node : in.get_prev_states(pos, i))
					prev_map[node] = 1;
			}
			//iterating through P will never go through more than O(n) states
			for(int j = 0; j<P->num_sets(); j++){
				//Now we calculate the parts of prev_map that are in or out of each set of P
				std::vector<int> in;
				std::vector<int> out;
				for(int pos = P->get_first(j); pos!=-1; pos = P->get_next(pos)){
					if(prev_map[pos])
						in.push_back(pos);
					else
						out.push_back(pos);
				}
				if(in.size() > 0 && out.size() > 0){
					//Then the set j is not fine enough. We need to split this set
					if(in.size() < out.size()){
						for(int elem : in)
							P->mark(elem);
						P->split(j);
						// Now out is at the last index and in is at index j
						// we check if the partition at index j is in the schedule. If it is, then both in and out must be added.
						// If it isn't, then the out must be marked. Both cases simplify to simply marking out as marked
						// otherwise, 
						schedule_members.push_back(1);
					}else{
						//the other case
						for(int elem : out){
							P->mark(elem);
						}
						P->split(j);
						schedule_members.push_back(1);
					}
				}
			}
		}
	}
	//Now we have a suitable paritition. We pass it to complete to produce a DFA.
	return complete(in, P);
}
//This is the implementation of Valmari-Lehtinen
DFA ValmariLehtinen(const DFA &in){

}
int main(){
	printf("Welcome to the DFA minimizer\n");
	DFA x = DFAFactory::endsIn01_inefficient();
	printf("Timing begins now\n");
	auto start = std::chrono::high_resolution_clock::now();
	x.print_DFA();
	DFA y = Hopcroft(x);
	y.print_DFA();
	auto finish = std::chrono::high_resolution_clock::now();
    printf("%li ns\n", std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count());
	return 0;
}