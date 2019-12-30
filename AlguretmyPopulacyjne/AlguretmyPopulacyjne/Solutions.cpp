//Implementacja funkcji z klasy Solutions
#include "pch.h"
#include "Solutions.h"

//Funkcja inicuj¹j¹ca dzia³anie algorytmu genetycznego
void Solutions::genetic_setup()
{
	result = INT_MAX;
	int *path = new int;
	vector<Genes*> pops(population);
	pops[0] = new Genes(natural_route(path), *path);
	pops[1] = new Genes(naive_route(path), *path);
	for (int i = 2; i < population; i++)
	{
		pops[i] = new Genes(random_route(path), *path);
	}
	genetic_algorithm(pops);
	delete path;
	//for (int i = 0; i < population; i++) delete pops[i];
	pops.clear();
}

//G³ówna pêtla algorytmu genetycznego
void Solutions::genetic_algorithm(vector<Genes*> pops)
{
	vector<Genes*> temp;
	int p1 = -1, p2, min;
	for (int i = 0; i < sim; i++)
	{
		min = INT_MAX;
		for (int i = 0; i < population; i++)
		{
			if (pops[i]->fitnes < min)
			{
				p2 = p1;
				p1 = i;
				min = pops[i]->fitnes;
			}
		}
		if (min < result) result = min;
		temp = repopulate(pops[p1], pops[p2]);
		for (int i = 0; i < population; i++) delete pops[i];
		pops.clear();
		pops = temp;
	}
}

//Funkcja tworz¹ca nowe pokolenie
vector<Genes*> Solutions::repopulate(Genes *p1, Genes *p2)
{
	int dice, last, index, cost, counter;
	int *path = new int;
	vector<Genes*> offspring(population);
	vector<int> line;
	vector<bool> visited(ext);
	for (int i = 0; i < population; i++)
	{
		dice = (rand() % 99);
		if (dice != 1)
		{
			line.clear();
			cost = 0;
			for (int j = 0; j < ext; j++) visited[j] = false;
			dice = rand() % 2;
			if (dice == 0) last = p1->path[0];
			else last = p2->path[0];
			line.push_back(last);
			visited[last] = true;
			for (int j = 1; j < ext; j++)
			{
				dice = rand() % 2;
				if (dice == 0) index = p1->path[j];
				else index = p2->path[j];
				if (visited[index])
				{
					dice = (rand() % (ext - j)) + 1;
					for (int k = 0, counter = 0; k < ext; k++)
					{
						if (visited[k]) continue;
						index = k;
						counter++;
						if (counter == dice) break;
					}
				}
				visited[index] = true;
				line.push_back(index);
				cost = cost + tab[line[j - 1]][line[j]];
			}
			cost = cost + tab[line.size() - 1][last];
			line.push_back(last);
			offspring[i] = new Genes(line, cost);
			line.clear();
		}
		else offspring[i] = new Genes(random_route(path), *path);
	}

	/**/
	system("cls");
	for (int i = 0; i < population; i++)
	{
		cout << "\nRozmiar: " << offspring[i]->fitnes << "\nTrasa: ";
		for (int j = 0; j < offspring[i]->path.size(); j++)
		{
			cout << offspring[i]->path[j] << ", ";
		}
	}
	_getche();
	/**/

	return offspring;
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
		fate = rand() % rem + 1;
		rem--;
		for (int i = 0, counter = 0; i < ext; i++)
		{
			if (visited[i]) continue;
			counter++;
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