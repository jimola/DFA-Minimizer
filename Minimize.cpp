#include "DFAFactory.h"
#include "Partition.h"
#include <stdio.h>
#include <chrono>
#include <utility>
#include <unordered_set>
#include "Valmari.cpp"
//converts a partition into a DFA. Both algorithms use this method
DFA *complete(const DFA *in, Partition &P){
	int num_states = P.num_sets();
	int alph_size = in->alph_size;
	int start_index = P.get_set(in->q0);
	std::vector<bool>finals (num_states, 0);
	for(int i = 0; i<in->Q; i++){
		if(in->final[i]){
			finals[P.get_set(i)] = 1;
		}
	}
	std::vector<int> Tails(num_states*alph_size, 0);
	std::vector<int> Labels(num_states*alph_size, 0);
	std::vector<int> Heads(num_states*alph_size, 0);
	for(int i = 0; i<in->Heads.size(); i++){
		int t = P.get_set(in->Tails[i]);
		int l = in->Labels[i];
		int h = P.get_set(in->Heads[i]);
		int m = t*alph_size+l;
		Tails[m] = t;
		Labels[m] = l;
		Heads[m] = h;
	}
	return new DFA(num_states, alph_size, start_index, finals, Tails, Labels, Heads);
}

//This is the implementation of Hopcroft's algorithm.
DFA *Hopcroft(const DFA *in){
	//The partition of states into like behavior
	Partition P = Partition(in->Q);
	for(int i = 0; i<in->Q; i++){
		if(in->final[i]){
			P.mark(i);
		}
	}
	P.split(0);
	//The schedule contains the set of partition indices that might need further splitting. We only need to add half of these partitions due to a lemma by Hopcroft
	std::unordered_set<int> schedule;
	schedule.insert(1);
	//prevs[i][j] contains the set of nodes that map to i under letter j
	std::vector<std::vector<std::vector<int> > > prevs (in->Q, std::vector<std::vector<int> > (in->alph_size, std::vector<int> (0)));
	for(int i = 0; i<in->Heads.size(); i++){
		prevs[in->Heads[i]][in->Labels[i]].push_back(in->Tails[i]);
	}
	while(!schedule.empty()){
		int index = *(schedule.cbegin());
		schedule.erase(index);
		//now we must have found something that is actually in the schedule
		//This needs to take O(a) time!
		std::vector<int> examine;	
		for(int i = 0; i<in->alph_size; i++){
			//find the preimage of the partition with the set index under letter i
			std::vector<bool> prev_map(in->Q, 0);
			//Each node in the previous map is considered only once => O(n) time.
			for(int pos = P.get_first(index); pos!=-1; pos = P.get_next(pos)){
				for(int node : prevs[pos][i]){
					//prev_map[node] = 1;
					P.mark(node);
					examine.push_back(P.get_set(node));
				}
			}
			for(int x : examine){
				int sz = P.get_size(x);
				int sz_1 = P.split(x); // the size of the elements that were just split to the back
				if(sz_1 > 0){
					if(schedule.find(x) == schedule.end())
						if(sz_1 <= sz/2){
							//then the last set is the one we should add to the schedule
							schedule.insert(P.num_sets()-1);
						}else{
							schedule.insert(x);
						}
					else{
						//add both 
						schedule.insert(P.num_sets()-1);
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
DFA ValmariLehtinen(DFA in){
	vector<Transition> trans;
	Partition P = new Partition(in->num_states());
	Partition T = new Partition(trans.size());

	std::vector<std::vector<std::pair<int, int> > tr(in->alph_size(), std::vector<std::pair<int, int> > (0));
	//bucket sort trans
	for(int i = 0; i<in->num_states(); i++){
		for(auto x = in->transitions[i].cbegin(); x!=in->transitions[i].cend(); x++){
			tr[x->first].push_back({i, x->second});
		}
	}
	for(int i = 0; i<in->num_states(); i++){
		if(in->is_final(i)){
			P.mark(i);
		}
	}
	//This keeps track of the set indices (of T) that each element of P maps to.
	vector<vector<int> > indices(P.num_sets(), vector<int> (0));
	//now, we split T based on letters
	for(std::vector<pair
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
	DFAFactory df = DFAFactory ();
	printf("(1) Exponential DFA of L letters accepting only the string 0^n\n");
	printf("(2) Exponential DFA of L letters accepting all strings longer than length n\n");
	printf("(3) Exponential DFA of L letters accepting random strings with length less than or equal to n\n");
	printf("(4) A mostly random DFA of L letters and Q states\n");
	printf("(5) A DFA that accepts the language 0^{<n=}1^{<=n}0^{<=n}... (n times) (This is a minimal DFA)\n");
	printf("(6) A small DFA that accepts all strings ending in 01 (for correctness testing)\n");
	int x; scanf("%d", &x);
	DFA *d;
	switch(x){
		case 1:
		{
			printf("Enter L and n. (Warning: This DFA has size O(L^n)): ");
			int sz, alpha; scanf("%d %d", &alpha, &sz);
			d = df.exponential_DFA(sz, alpha);
			d->final[d->Q-2] = 1;
			break;
		}
		case 2:
		{
			printf("Enter L and n. (Warning: This DFA has size O(L^n)): ");
			int sz, alpha; scanf("%d %d", &alpha, &sz);
			d = df.exponential_DFA(sz, alpha);
			d->final[d->Q-1] = 1;
			break;
		}
		case 3:
		{	
			printf("Enter L and n. (Warning: This DFA has size O(L^n)): ");
			int sz, alpha; scanf("%d %d", &alpha, &sz);
			d = df.exponential_DFA(sz, alpha);
			for(int i = 0; i<d->Q-1; i++){
				d->final[i] = rand() % 2;
			}
			break;
		}
		case 4:
		{
			printf("Enter L and Q: ");
			int Q, alpha; scanf("%d %d", &alpha, &Q);
			d = df.random(Q, alpha);
			break;
		}
		case 5:
		{
			printf("Enter n: (This DFA has size O(n^2)): ");
			int n; scanf("%d", &n);
			d = df.repeating_01(n);
			break;
		}
		case 6:
		{
			d = df.endsIn01_inefficient();
			break;
		}
		default:
		{
			printf("Invalid number!\n");
			return 0;
		}
	}
	printf("Timing begins now\n");
	auto start = std::chrono::high_resolution_clock::now();
	DFA *y = Hopcroft(d);
	auto finish = std::chrono::high_resolution_clock::now();
	printf("Hopcroft took: ");
	printf("%li ms\n", std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() / 1000000);
	start = std::chrono::high_resolution_clock::now();
	DFA *z = Valmari(d);
	finish = std::chrono::high_resolution_clock::now();
	printf("Valmari-Lehtinen took: ");
	printf("%li ms\n", std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() / 1000000);
	printf("Print the input DFA? (Enter a Boolean. Warning: it could be huge): ");
	int p; scanf("%d", &p);
	if(p){
		printf("Input DFA:\n");
		d->print_DFA();
	}
	printf("Print the output DFA? (Enter a Boolean. Warning: They could be huge): ");
	scanf("%d", &p); 
	if(p){
		printf("Hopcroft DFA:\n");
		y->print_DFA();
		printf("Valmari-Lehtinen DFA:\n");
		z->print_DFA();
	}
	delete(d);
	delete(y);
	delete(z);
	return 0;
}