//Implementacja funkcji z klasy Solutions
#include "pch.h"
#include "Solutions.h"

//Funkcja inicuj¹j¹ca dzia³anie algorytmu genetycznego
void Solutions::genetic_setup(int psize)
{
	population = psize;
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
}

//G³ówna pêtla algorytmu genetycznego
void Solutions::genetic_algorithm(vector<Genes*> pops)
{
	vector<Genes*> temp;
	vector<Genes*> build;
	int steps;
	int p1 = -1, p2, min;
	for (int i = 0; i < sim; i++)
	{
		steps = 0;
		for (int j = 0; j < (population / 2); j++)
		{
			min = INT_MAX;
			for (int k = 0; k < (population - steps); k++)
			{
				if (pops[k]->fitnes < min)
				{
					p2 = p1;
					p1 = k;
					min = pops[k]->fitnes;
				}
			}
			if (min < result) result = min;
			temp = repopulate(pops[p1], pops[p2]);
		}
		for (int k = 0; k < population; k++) delete pops[i];
		pops.clear();
		pops = temp;
	}
}

//Funkcja tworz¹ca nowe pokolenie
vector<Genes*> Solutions::repopulate(Genes *p1, Genes *p2)
{
	int e1;
	int div1 = rand() % ext;
	if ((div1 + 2) >= ext) e1 = div1 - 2;
	else if ((div1 - 2) < 0) e1 = div1 + 2;
	else
	{
		e1 = rand() % 2;
		if (e1 == 0) e1 = div1 + 2;
		else e1 = div1 - 2;
	}

	Genes *t1;
	Genes *t2;
	int cost1 = 0;
	int cost2 = 0;
	vector<bool> visited1(ext);
	vector<bool> visited2(ext);
	vector<int> path1(ext + 1);
	vector<int> path2(ext + 1);
	for (int i = 0; i < ext; i++)
	{
		visited1[i] = false;
		visited2[i] = false;
	}
	if (e1 < div1) 
	{
		path1[0] = p2->path[e1];
		path1[1] = p2->path[e1 + 1];
		path1[2] = p2->path[e1 + 2];		

		path2[0] = p1->path[e1];
		path2[1] = p1->path[e1 + 1];
		path2[2] = p1->path[e1 + 2];
	}
	else
	{
		path1[0] = p2->path[div1];
		path1[1] = p2->path[div1 + 1];
		path1[2] = p2->path[div1 + 2];

		path2[0] = p1->path[div1];
		path2[1] = p1->path[div1 + 1];
		path2[2] = p1->path[div1 + 2];
	}
	visited1[path1[0]] = true;
	visited1[path1[1]] = true;
	visited1[path1[2]] = true;
	visited2[path2[0]] = true;
	visited2[path2[1]] = true;
	visited2[path2[2]] = true;
	cost1 = cost1 + tab[path1[0]][path1[1]] + tab[path1[1]][path1[2]];
	cost2 = cost2 + tab[path2[0]][path2[1]] + tab[path2[1]][path2[2]];

	int i1, i2;
	if (e1 < div1) i1 = div1 + 1, i2 = i1;
	else i1 = e1 + 1, i2 = i1;
	for (int i = 3; i < ext; i++)
	{
		if (i2 >= ext) i2 = 0;
		if (i1 >= ext) i1 = 0;
		while (visited1[p1->path[i1]])
		{
			i1++;
			if (i1 >= ext) i1 = 0;
		};
		path1[i] = p1->path[i1];
		cost1 = cost1 + tab[path1[i - 1]][path1[i]];
		visited1[path1[i]] = true;

		while (visited2[p2->path[i2]])
		{
			i2++;
			if (i2 >= ext) i2 = 0;
		};
		path2[i] = p2->path[i2];
		cost2 = cost2 + tab[path2[i - 1]][path2[i]];
		visited2[path2[i]] = true;
		i1++;
		i2++;
	}
	path1[ext] = path1[0];
	cost1 = cost1 + tab[path1[ext - 1]][path1[ext]];
	path2[ext] = path2[0];
	cost2 = cost2 + tab[path2[ext - 1]][path2[ext]];

	vector<Genes*> result;
	result.push_back(new Genes(path1, cost1));
	result.push_back(new Genes(path2, cost2));
	return result;
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