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
	/*for (int i = 0; i < ext; i++)
	{
		cout << line[i];
	}*/
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
	int best, index, temp, cost, up;
	for (int i = 0; i < iterations; i++)
	{
		cost = result;
		best = INT_MAX;
		index = -1;
		if ((current + 1 == ext)) up = 0;
		else up = current + 1;
		for (int j = (current - 1); j > 0 && j > (current - 4); j--)
		{
			if (tabu[line[current]][line[j]] == 0)
			{
				if ((j + 1) == current)
				{
					temp = cost - tab[line[j]][line[current]] - tab[line[current]][line[up]] - tab[line[j - 1]][line[j]];
					temp = temp + tab[line[current]][line[j]] + tab[line[j]][line[up]] + tab[line[j - 1]][line[current]];
				}
				else
				{
					temp = cost - tab[line[current - 1]][line[current]] - tab[line[current]][line[up]] - tab[line[j - 1]][line[j]] - tab[line[j]][line[j + 1]];
					temp = temp + tab[line[current - 1]][line[j]] + tab[line[j]][up] + tab[line[j - 1]][line[current]] + tab[line[current]][line[j + 1]];
				}
				if (temp < best)
				{
					index = j;
					best = temp;
				}
			}
		}
		for (int j = (current +  1); j < ext && j < (current + 4); j++)
		{
			if ((j + 1 == ext)) up = 0;
			else up = j + 1;
			if (tabu[line[current]][line[j]] == 0)
			{
				if ((j - 1) == current)
				{
					temp = cost - tab[line[current]][line[j]] - tab[line[current - 1]][line[current]] - tab[line[j]][line[up]];
					temp = temp + tab[line[j]][line[current]] + tab[line[current - 1]][line[j]] + tab[line[current]][line[up]];
				}
				else
				{
					temp = cost - tab[line[current - 1]][line[current]] - tab[line[current]][line[current + 1]] - tab[line[j - 1]][line[j]] - tab[line[j]][line[up]];
					temp = temp + tab[line[current - 1]][line[j]] + tab[line[j]][line[current + 1]] + tab[line[j - 1]][line[current]] + tab[line[current]][line[up]];
				}
				if (temp < best)
				{
					index = j;
					best = temp;
				}
			}
		}
		if (best < result && index != -1)
		{
			result = best;
			tabu[line[current]][line[index]] = lock;
			//tabu[line[index]][line[current]] = lock;
			temp = line[current];
			line[current] = line[index];
			line[index] = temp;
			current = index;
		}
		else current = (rand() % (ext - 2) + 1);
		for (int j = 0; j < ext; j++)
		{
			for (int z = 0; z < ext; z++)
			{
				if (tabu[j][z] != 0) tabu[j][z]--;
			}
		}
		/*cout << "\nResult: " << result << ", path: ";
		for (int i = 0; i < ext; i++)
		{
			cout << line[i] << ", ";
		}
		cout << "0, Current: "<<current;
		_getche();*/
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