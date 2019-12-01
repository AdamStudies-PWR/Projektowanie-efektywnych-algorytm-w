#pragma once
#ifndef Sulutions_hpp
#define Solutions_hpp

#include "Data.h"

//Klasa obsługujące obliczenia dla realizowanych w tym programie problemów
class Solutions : public Data
{
private:
	//Zmienne
	int result;
	//tabu search
	int **tabu;
	int current;
	static const int lock = 10;
	static const int iterations = 100000;
	vector<int> line;
public:
	//Metody
	void naive_search();
	void tabu_setup();
	void tabu_setup_naive();
	void annealing_setup();
	//Gettery i settery
	int get_result();
private:
	void tabu_search();
	void simulated_annealing();
	//void quick_sort(vector<Node*> &arr, int left, int right);
};

#endif