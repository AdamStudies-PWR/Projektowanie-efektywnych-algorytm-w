//Implementacja funkcji z klasy Solutions
#include "pch.h"
#include "Solutions.h"

//Funkcja inicuj¹j¹ca dzia³anie algorytmu genetycznego
void Solutions::genetic_setup()
{
	int *path = new int;
	vector<Genes*> pops(population);
	pops[0] = new Genes(natural_route(path), *path);
	pops[1] = new Genes(naive_route(path), *path);
	for (int i = 2; i < population; i++)
	{
		pops[i] = new Genes(random_route(path), *path);
	}
	genetic_algorithm(pops);
}

//G³ówna pêtla algorytmu genetycznego
void Solutions::genetic_algorithm(vector<Genes*> pops)
{
	system("cls");
	for (int i = 0; i < population; i++)
	{
		cout << "\nScie¿ka:" << endl;
		for (int j = 0; j < pops[i]->path.size(); j++)
		{
			cout << pops[i]->path[j] << ", ";
		}
		cout << "\nD³ugoœæ: " << pops[i]->fitnes << endl;
	}
	_getche();
}

//Gettery i settery

//Funkcja zwracaj¹ca wartoœæ koñcow¹ algorytmu
int Solutions::getResult() { return result; }

//Generowanie pocz¹tkowej trasy

//Trasa naturalna
vector<int> Solutions::natural_route(int *path)
{
	vector<int> line;
	*path = limits;
	for (int i = 0; i < ext; i++) line.push_back(i);
	line.push_back(0);
	return line;
}

//Trasa naturalna
vector<int> Solutions::naive_route(int *path)
{
	vector<int> line;
	*path = 0;
	int min, index = 0;
	int temp = 0;
	int rem = ext - 1;
	vector<bool> visited(ext);
	for (int i = 1; i < ext; i++) visited[i] = false;
	visited[0] = true;
	line.push_back(0);
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
		temp = index;
		line.push_back(index);
		visited[index] = true;
		*path = *path + min;
		rem--;
	}
	line.push_back(0);
	*path = *path + tab[index][0];
	return line;
}

//Trasa losowa
vector<int> Solutions::random_route(int *path)
{
	vector<int> line;
	*path = 0;
	int index;
	int fate, counter;
	int rem = ext;
	int temp = rand() % rem;
	int last = temp;
	rem--;
	vector<bool> visited(ext);
	for (int i = 0; i < ext; i++) visited[i] = false;
	visited[temp] = true;
	line.push_back(temp);
	while (rem != 0)
	{
		fate = rand() % rem;
		rem--;
		for (int i = 0, counter = 0; i < ext; i++)
		{
			if (!visited[i]) counter++;
			index = i;
			if (counter == fate) break;
		}
		line.push_back(index);
		visited[index] = true;
		*path = *path + tab[temp][index];
		temp = index;
	}
	line.push_back(last);
	*path = *path + tab[index][last];
	return line;
}