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
	bool *visited;
	Node *parent = nullptr;
	Node(int **src, int ext, int remaining)
	{
		rem = remaining;
		visited = new bool[ext];
		data = new int*[ext];
		for (int i = 0; i < ext; i++)
		{
			visited[i] = false;
			data[i] = new int[ext];
			for (int j = 0; j < ext; j++)
			{
				data[i][j] = src[i][j];
			}
		}
		visited[0] = true;
	}
	~Node()
	{
		//delete[] data;
		//delete[] visited;
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
};

#endif
