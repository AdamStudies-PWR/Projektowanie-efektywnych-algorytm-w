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

//Rekurencyjne rozwiniêcie tabu searcha
void Solutions::tabu_rec(int line, vector<bool> visited, int distance, int layer)
{
	tabu_list.push_back(line);
	if (tabu_list.size() > max_tabu)
	{
		tabu_list.erase(tabu_list.begin() + 0);
	}
	visited[line] = true;
	if (distance > result) return;
	if (layer != (ext - 1))
	{
		Node *temp;
		vector<Node*> solutions;
		for (int i = 1; i < ext; i++)
		{
			if (!visited[i] /*&& !contains(i)*/)
			{
				solutions.push_back(new Node(i, tab[0][i]));
			}
		}
		quick_sort(solutions, 0, (solutions.size() - 1));
		while (solutions.size() > 0)
		{
			temp = solutions.back();
			solutions.pop_back();
			if (contains(temp->index)) continue;
			tabu_rec(temp->index, visited, temp->cost, (layer + 1));
			delete temp;
		}
	}
	else if ((distance + tab[line][0]) < result)
	{
		result = distance + tab[line][0];
	}
	return;
}

//Funkcja szukaj¹ca rozwi¹zania poprzez tabu search
void Solutions::tabu_search()
{
	Node *temp;
	vector<Node*> solutions;
	result = limits;
	vector<bool> visited(ext);
	visited[0] = true;
	tabu_list.push_back(0);
	for (int i = 1; i < ext; i++)
	{
		visited[i] = false;
		solutions.push_back(new Node(i, tab[0][i]));
	}
	quick_sort(solutions, 0, (solutions.size() - 1));
	while(solutions.size() > 0)
	{
		temp = solutions.back();
		solutions.pop_back();
		tabu_rec(temp->index, visited, temp->cost, 1);
		delete temp;
	}
	tabu_list.clear();
}

//Funkcja sprawdzaj¹ca czy dany wêze³ znajduje siê na liœcie tabu
bool Solutions::contains(int index)
{
	for (int i = 0; i < tabu_list.size(); i++)
	{
		if (tabu_list[i] == index) return true;
	}
	return false;
}

//Funkcja obs³uguj¹ca Sumulowane wyzarzanie 
void Solutions::simulated_annealing()
{

}

//Utility
void Solutions::quick_sort(vector<Node*> &array, int left, int right)
{
	if (left < right)
	{
		Node *temp;
		int index = left + (right - left)/2;
		int part = array[index]->cost;
		int i = left, j = right;
		while (i <= j)
		{
			while (array[i]->cost > part) i++;
			while (array[j]->cost < part) j--;
			if (i <= j)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
				i++;
				j--;
			}
		}
		part = i;
		quick_sort(array, left, part - 1);
		quick_sort(array, part, right);
	}
}

//Gettery i settery
int Solutions::get_result() { return result; }