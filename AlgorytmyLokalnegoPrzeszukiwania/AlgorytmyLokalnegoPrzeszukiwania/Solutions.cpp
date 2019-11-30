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
void Solutions::tabu_setup()
{
	result = limits;
	tabu = new int*[ext];
	for (int i = 0; i < ext; i++)
	{
		tabu[i] = new int[ext];
		for (int j = 0; j < ext; j++)tabu[i][j] = 0;
		line.push_back(i);
	}
	line.push_back(0);
	tabu_search();
	for (int i = 0; i < ext; i++)
	{
		delete[] tabu[i];
	}
	delete[] tabu;
	line.clear();
}

//Funkcja szukaj¹ca rozwi¹zania poprzez tabu search
void Solutions::tabu_search()
{
	int x, y;
	int cost, temp;
	int best, index;
	vector<int> proxy;
	for (int i = 0; i < iterations; i++)
	{
		best = INT_MAX;
		cost = result;
		for (x = (current - 1), y = (current + 1); x > (current - 4); x--, y++)
		{
			if (x > 0) proxy.push_back(x);
			if (y < (line.size() - 1)) proxy.push_back(y);
		}
		for (int j = 0; j < proxy.size(); j++)
		{
			if ((proxy[j] + 1) == current)
			{
				temp = cost - tab[line[proxy[j] - 1]][line[proxy[j]]] - tab[line[proxy[j]]][line[current]] - tab[line[current]][line[current + 1]];
				temp = temp + tab[line[proxy[j] - 1]][line[current]] + tab[line[current]][line[proxy[j]]] + tab[line[proxy[j]]][line[current + 1]];
			}
			else if ((proxy[j] - 1) == current)
			{
				temp = cost - tab[line[current - 1]][line[current]] - tab[line[current]][line[proxy[j]]] - tab[line[proxy[j]]][line[proxy[j] + 1]];
				temp = temp + tab[line[current - 1]][line[proxy[j]]] + tab[line[proxy[j]]][line[current]] + tab[line[current]][line[proxy[j] + 1]];
			}
			else
			{
				temp = cost - tab[line[proxy[j] - 1]][line[proxy[j]]] - tab[line[proxy[j]]][line[proxy[j] + 1]] - tab[line[current - 1]][line[current]] - tab[line[current]][line[current + 1]];
				temp = temp + tab[line[proxy[j] - 1]][line[current]] + tab[line[current]][line[proxy[j] + 1]] + tab[line[current - 1]][line[proxy[j]]] + tab[line[proxy[j]]][line[current + 1]];
			}
			if (temp < best) best = temp, index = proxy[j];
		}
		if (best < result)
		{
			result = best;
			temp = line[index];
			line[index] = line[current];
			line[current] = temp;
			current = index;
		}
		else current = (rand() % (ext - 1)) + 1;
		proxy.clear();
	}
}


//Funkcja obs³uguj¹ca Sumulowane wyzarzanie 
void Solutions::simulated_annealing()
{

}

/*//Utility
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
}*/

//Gettery i settery
int Solutions::get_result() { return result; }