//Implementacja funkcji z klasy Solutions
#include "pch.h"
#include "Solutions.h"

//Funkcja szukaj¹ca rozwi¹zania naiwnie - najmniejsza odleg³oœæ od danego miasta
void Solutions::naive_search()
{
	int res = 0, min, index = 0;
	int temp = 0;
	int rem = ext - 1;
	vector<bool> visited(ext);
	for (int i = 1; i < ext; i++) visited[i] = false;
	visited[0] = true;
	while (rem != 0)
	{
		min = INT_MAX;
		for (int i = 1; i < ext; i++)
		{
			if (!visited[i])
			{
				if (tab[temp][i] < min)
				{
					index = i;
					min = tab[temp][i];
				}
			}
		}
		visited[index] = true;
		res = res + min;
		rem--;
	}
	result = res + tab[index][0];
}

//Funkcja szukaj¹ca rozwi¹zania poprzez tabu search
void Solutions::tabu_search()
{
	int counter = 0;
	int parent;
	result = limits;
	vector<bool> visited(ext);
	for (int i = 0; i < ext; i++) visited[i] = false;
	tabu_list.push_back(new Node(0, visited, 0));
	Node *candidate;
	Node *best = tabu_list[0];
	Node *temp;
	while (counter != ext)
	{
		counter++;
		parent = best->current;
		candidate = find_candidate(best);
		for (int i = 0; i < ext; i++)
		{
			//if (!candidate->visited[i])
			{
				if (!contains(i) && (best->cost > (candidate->cost + tab[parent][i])))
				{
					temp = new Node(i, best->visited, (candidate->cost + tab[parent][i]));
					//delete best;
					best = temp;
				}
			}
		}
		tabu_list.push_back(best);
		if (tabu_list.size() > max_tabu)
		{
			tabu_list.erase(tabu_list.begin() + 0);
		}
	}
	if (best->cost < result) result = best->cost;
}

//Funkcja sprawdzaj¹ca czy dany wêze³ znajduje siê na liœcie tabu
bool Solutions::contains(int index)
{
	for (int i = 0; i < tabu_list.size(); i++)
	{
		if (tabu_list[i]->current = index) return true;
	}
	return false;
}

//Funkcja wybieraj¹ca kandydata
Node* Solutions::find_candidate(Node* best)
{
	for (int i = 0; i < ext; i++)
	{
		if (!contains(i))
		{
			return new Node(i, best->visited, (best->cost + tab[best->current][i]));
		}
	}
}