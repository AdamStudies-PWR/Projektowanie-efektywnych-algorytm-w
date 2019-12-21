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
	static const int lock = 7;
	static const int iterations = 100000;
	vector<int> line;
	//Simulated Annealing
	float TT;
public:
	//Metody
	void naive_search();
	void tabu_setup();
	void tabu_setup_naive();
	void sa_setup();
	void sa_setup_naive();
	void annealing_setup();
	void annealing_setup_naive();
	//Testowanie
	void testing(int number, bool tab[]);
	//Gettery i settery
	int get_result();
private:
	void tabu_search();
	void simulated_annealing();
	void sa_first();
	int perform_move(int next);
};

#endif