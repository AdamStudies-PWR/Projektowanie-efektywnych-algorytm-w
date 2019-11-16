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