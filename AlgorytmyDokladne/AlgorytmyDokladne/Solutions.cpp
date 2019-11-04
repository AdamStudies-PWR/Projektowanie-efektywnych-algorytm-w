//Klasa obs³uguj¹ca obliczanie problemu komiwoja¿era za pomoc¹ brute-force
#include "pch.h"
#include "Solutions.h"
using namespace std;

//Destruktor
Solutions::~Solutions()
{
	if (exists)
	{
		for (int i = 0; i < ext; i++)
		{
			delete[] tab[i];
		}
		delete[] tab;
	}
}

//Rekurencyjne przeszukiwanie drzewa
void Solutions::rectree(int line, vector<bool> visited, int  distance, int layer)
{
	visited[line] = true;
	if (layer != (ext-1))
	{
		for (int i = 1; i < ext; i++)
		{
			if(!visited[i]) rectree(i, visited, (distance + tab[line][i]), (layer + 1));
		}
	}
	else if ((distance + tab[line][0]) < max || max == -1)
	{
		max = distance + tab[line][0];
	}
	return;
}

//Rekurencyjne przeszukiwanie drzewa z dodatkow¹ optymalizacj¹
void Solutions::rectree_opt(int line, vector<bool> visited, int  distance, int layer)
{
	visited[line] = true;
	if (distance > max && max != -1) return;
	if (layer != (ext - 1))
	{
		for (int i = 1; i < ext; i++)
		{
			if (!visited[i]) rectree_opt(i, visited, (distance + tab[line][i]), (layer + 1));
		}
	}
	else if ((distance + tab[line][0]) < max || max == -1)
	{
		max = distance + tab[line][0];
	}
	return;
}

//Funkcja przeszukuj¹ca drzewo w poszukiwaniu najlepszych rozwi¹zañ
void Solutions::searchtree()
{
	max = -1;
	vector<bool> visited(ext);
	visited[0] = true;
	for (int i = 1; i < ext; i++) visited[i] = false;
	for (int i = 0; i < (ext - 1); i++)
	{
		rectree((i + 1), visited, tab[0][i + 1], 1);
	}
}
void Solutions::seacrhtree_opt()
{
	max = -1;
	vector<bool> visited(ext);
	visited[0] = true;
	for (int i = 1; i < ext; i++) visited[i] = false;
	for (int i = 0; i < (ext - 1); i++)
	{
		rectree_opt((i + 1), visited, tab[0][i + 1], 1);
	}
}

//Pocz¹tek Branch & Bound
void Solutions::BiBbegin()
{
	max = -1;
	vector<bool> visited(ext);
	for (int i = 0; i < ext; i++)visited[i] = false;
	visited[0] = true;
	Node *first = new Node(tab, ext, (ext - 1), visited);
	nlist.push_back(first);
	first->weight = minimize(first->data);
	vector<Node*> nodes;
	for (int i = 0; i < (ext - 1); i++)
	{
		nodes.push_back(new Node(first->data, ext, (first->rem - 1), first->visited));
		nodes[i]->parent = first;
		nodes[i]->visited[i + 1] = true;
		nodes[i]->location = i + 1;
		nodes[i]->weight = calculatecost(nodes[i], 0, (i + 1));
		nlist.push_back(nodes[i]);
	}
	BiBcalc(nodes);
	for (int i = 0; i < nlist.size(); i++)
	{
		delete nlist[i];
	}
	nlist.clear();
}

//G³ówna pêtla dla Branch & Bound
void Solutions::BiBcalc(vector<Node*> nodes)
{
	int small, index;
	Node *current;
	while (nodes.size() != 0)
	{
		index = 0;
		small = nodes[index]->weight;
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i]->weight < small)
			{
				small = nodes[i]->weight;
				index = i;
			}
		}
		current = nodes[index];
		nodes.erase(nodes.begin() + index);
		if (max != -1)
		{
			if (current->weight > max) continue;
		}
		for (int i = 0; i < ext; i++)
		{
			if (!current->visited[i])
			{
				nodes.push_back(new Node(current->data, ext, (current->rem - 1), current->visited));
				nodes[nodes.size() - 1]->parent = current;
				nodes[nodes.size() - 1]->visited[i] = true;
				nodes[nodes.size() - 1]->location = i;
				nodes[nodes.size() - 1]->weight = calculatecost(nodes[nodes.size() - 1], current->location, i);
				nlist.push_back(nodes[nodes.size() - 1]);
			}
		}
		if (nodes[nodes.size() - 1]->rem == 0)
		{
			if (nodes[nodes.size() - 1]->weight < max || max == -1) max = nodes[nodes.size() - 1]->weight;
		}
	}
}

//Pocz¹tek algorytmu Helda Karpa (Held-Karpa?)
void Solutions::HPbegin()
{
	int kk ,it = 0;
	vector<bool> visited(ext);
	for (int i = 0; i < ext; i++)visited[i] = false;
	visited[0] = true;
	vector<Set*> list;
	for (int i = 1; i < ext; i++)
	{
		list.push_back(new Set(visited));
		list[i - 1]->weight = tab[0][i];
		list[i - 1]->visited[i] = true;
		list[i - 1]->current = i;
	}
	for (int i = 0; i < (ext - 2); i++)
	{
		list = addlayer(list);
	}
	int min = list[0]->weight + tab[list[0]->current][0];
	for (int i = 1; i < list.size(); i++)
	{
		if ((list[i]->weight + tab[list[i]->current][0]) < min)
		{
			min = list[i]->weight + tab[list[i]->current][0];
		}
		delete list[i];
	}
	max = min;
}

//Metoda dodaj¹ca kolejne "warstwy" do rozwi¹zania
vector<Set*> Solutions::addlayer(vector<Set*> list)
{
	int dist;
	int it = 0;
	vector<bool> visited;
	vector<Set*> newlist;
	vector<Set*> temp;
	for (int i = 1; i < ext; i++)
	{
		temp = list;
		for (int j = 0; j < temp.size(); j++)
		{
			if (temp[j]->visited[i])
			{
				temp.erase(temp.begin() + j);
				j--;
			}
		}
		while (temp.size() > 0)
		{
			dist = temp[0]->weight + tab[temp[0]->current][i];
			visited = temp[0]->visited;
			for (int j = 0; j < temp.size(); j++)
			{
				if (visited == temp[j]->visited)
				{
					if (dist > temp[j]->weight + tab[temp[j]->current][i]) dist = temp[j]->weight + tab[temp[j]->current][i];
					temp.erase(temp.begin() + j);
					j--;
				}
			}
			newlist.push_back(new Set(visited));
			newlist[it]->current = i;
			newlist[it]->weight = dist;
			newlist[it]->visited[i] = true;
			it++;
		}
	}
	for (int i = 0; i < list.size(); i++) delete list[i];
	return newlist;
}

//Funkcja obliczaj¹ca kost nastêpnego poziomu
int Solutions::calculatecost(Node *node, int from, int to)
{
	int result = node->parent->data[from][to] + node->parent->weight;
	for (int i = 0; i < ext; i++)
	{
		node->data[from][i] = -1;
		node->data[i][to] = -1;
	}
	node->data[to][from] = -1;
	result = result + minimize(node->data);
	return result;
}

//Funkcja minimalizuj¹ca macierz
int Solutions::minimize(int **data)
{
	int result = 0;
	int small;
	for (int i = 0; i < ext; i++)
	{
		small = data[i][0];
		for (int j = 0; j < ext; j++)
		{
			if ((data[i][j] < small && data[i][j] != -1) || small == -1) small = data[i][j];
		}
		if (small != 0)
		{
			for (int j = 0; j < ext; j++)
			{
				if (data[i][j] != -1) data[i][j] = data[i][j] - small;
			}
			if(small > 0) result = result + small;
		}
	}
	for (int i = 0; i < ext; i++)
	{
		int small = data[0][i];
		for (int j = 0; j < ext; j++)
		{
			if ((data[j][i] < small && data[j][i] != -1) || small == -1) small = data[j][i];
		}
		if (small != 0)
		{
			for (int j = 0; j < ext; j++)
			{
				if (data[j][i] != -1)data[j][i] = data[j][i] - small;
			}
			if (small > 0) result = result + small;
		}
	}
	return result;
}

//Gettery i Settery
int Solutions::getDistance() { return max; }