#pragma once
#ifndef Solutions_hpp
#define Solutions_hpp

#include "Data.h"

//Struktura tworz¹ca poszczególne wêz³y w trakcie przeszukiwania Branch & Bound
struct Node
{
	int **data;
	int rem;
	int weight;
	int size;
	vector<bool> visited;
	int location;
	Node *parent = nullptr;
	Node(int **src, int ext, int remaining, vector<bool> visits)
	{
		size = ext;
		rem = remaining;
		visited = visits;
		data = new int*[ext];
		for (int i = 0; i < ext; i++)
		{
			data[i] = new int[ext];
			for (int j = 0; j < ext; j++)
			{
				data[i][j] = src[i][j];
			}
		}
	}
	~Node()
	{
		for (int i = 0; i < size; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}
};

struct Set
{
	int current;
	int weight;
	vector<bool> visited;
	Set(vector<bool> visits)
	{
		visited = visits;
	}
};

//Klasa obs³uguj¹ca obliczanie problemu komiwoja¿era za pomoc¹ brute-force
class Solutions : public Data
{
private:
	//zmienne
	int max;
	vector<Node*> nlist;
public:
	//metody
	~Solutions();
	//Brute force
	void searchtree();
	void seacrhtree_opt();
	//Branch&Bound
	void BiBbegin();
	//Held-Karp
	void HPbegin();
	//Gettery i settery
	int getDistance();
private:
	//Brute force
	void rectree(int line, vector<bool> visted, int distance, int layer);
	void rectree_opt(int line, vector<bool> visted, int distance, int layer);
	//Branch&Bound
	int minimize(int **node);
	int calculatecost(Node *node, int from, int to);
	void BiBcalc(vector<Node*> nodes);
	//Held-Karp
	vector<Set*> addlayer(vector<Set*> data);
	//Funkcje pomocnicze
	void quickSort(vector<Node*> &data, int start, int end);
};

#endif
