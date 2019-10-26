#pragma once
#ifndef Solutions_hpp
#define Solutions_hpp

#include "Data.h"

//Struktura tworz¹ca poszczególne wêz³y w trakcie przeszukiwania Branch & Bound
struct Node
{
	int **data;
	int remaining;
	vector<bool> visisted;
	Node(int **src, int ext)
	{
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
};

//Klasa obs³uguj¹ca obliczanie problemu komiwoja¿era za pomoc¹ brute-force
class Solutions : public Data
{
private:
	//zmienne
	int max;
	vector<Node> nlist;
public:
	//metody
	~Solutions();
	//Brute force
	void searchtree();
	void seacrhtree_opt();
	//Branch&Bound
	void BiBbeging();
	//Gettery i settery
	int getDistance();
private:
	//Brute force
	void rectree(int line, vector<bool> visted, int distance, int layer);
	void rectree_opt(int line, vector<bool> visted, int distance, int layer);
	//Branch&Bound
	int minimize(int **node);
};

#endif
