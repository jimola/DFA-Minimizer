#include "DFA.h"
#include "Partition.h"
#include <stdio.h>
#include <chrono>
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
	//The schedule contains the set of partitions that need further splitting.
	std::vector<int> schedule(1, 1);
	while(schedule.size() > 0){
		int set_index = schedule.back(); schedule.pop_back();
		for(int i = 0; i<in.alphabet_size(); i++){
			//find the preimage of the partition with index set_index under letter i
			//Everything in here takes O(n) time
			vector<bool> prev_map(in.num_states(), 0);
			for(int pos = P->get_first(set_index); pos!=-1; pos = P->get_next(pos)){
				prev_map[P->get_transition(pos, i)] = 1;
			}
			//iterating through P will never go through more than O(n) states
			for(int j = 0; j<P->num_sets(); j++){
				//Now we calculate the parts of next_map that are in or out of each set of P
				//Everything in here better take ~constant time
				vector<int> in;
				vector<int> out;
				for(int pos = P->get_first(j); pos!=-1; pos = P->get_next(pos)){
					if(next_map[pos])
						in.push_back(pos);
					else
						out.push_back(pos);
				}
				if(in.size() > 0 && out.size() > 0){
					//we check if the partition at index j is in the schedule
					
				}
			}
		}
	}
}

//This is the implementation of Valmari-Lehtinen
DFA ValmariLehtinen(const DFA &in){

}
int main(){
	printf("Welcome to the DFA minimizer\n");
	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i<10000; i++);
	auto finish = std::chrono::high_resolution_clock::now();
    printf("%li ns\n", std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count());
	return 0;
}