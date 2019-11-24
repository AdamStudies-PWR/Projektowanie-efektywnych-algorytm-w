#pragma once
#ifndef Sulutions_hpp
#define Solutions_hpp

#include "Data.h"

//Struktura reprezentująca węzeł
struct Node
{
	int index;
	int cost;
	Node(int ii, int cc)
	{
		index = ii;
		cost = cc;
	}
};

//Klasa obsługujące obliczenia dla realizowanych w tym programie problemów
class Solutions : public Data
{
private:
	//Zmienne
	int result;
	//tabu search
	vector<int> tabu_list;
	int max_tabu = 20;
public:
	//Metody
	void naive_search();
	void tabu_search();
	void simulated_annealing();
	//Gettery i settery
	int get_result();
private:
	bool contains(int index);
	void tabu_rec(int line, vector<bool> visited, int distance, int layer);
	void quick_sort(vector<Node*> &arr, int left, int right);
};

#endif