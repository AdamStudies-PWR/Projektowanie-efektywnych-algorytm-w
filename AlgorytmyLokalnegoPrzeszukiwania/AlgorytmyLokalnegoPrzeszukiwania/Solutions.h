#pragma once
#ifndef Sulutions_hpp
#define Solutions_hpp

#include "Data.h"

//Struktura reprezentuj¹ca miasto
struct Node
{
	int current;
	int cost;
	vector<bool> visited;
	Node(int index, vector<bool> visited, int cost)
	{
		this->cost = cost;
		current = index;
		this->visited = visited;
		this->visited[index] = true;
	}
};

//Klasa obs³uguj¹ce obliczenia dla realizowanych w tym programie problemów
class Solutions : public Data
{
public:
	//Zmienne
	int result;
	//tabu search
	vector<Node*> tabu_list;
	int max_tabu = 3;
	//Metody
	void naive_search();
	void tabu_search();
	bool contains(int index);
	Node* find_candidate(Node* best);
};

#endif