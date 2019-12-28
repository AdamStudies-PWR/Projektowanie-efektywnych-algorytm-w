#pragma once
#ifndef Sulutions_hpp
#define Solutions_hpp

#include "Data.h"

struct Genes
{
	vector<int> path;
	int fitnes;
	Genes(vector<int> path, int fitnes)
	{
		this->path = path;
		this->fitnes = fitnes;
	}
};

//Klasa obsługujące obliczenia dla realizowanych w tym programie problemów
class Solutions : public Data
{
private:
	//Zmienne
	int result;
	int population = 10;
	int sim = 10000;
public:
	//Metody
	//Algorytm genetyczny
	void genetic_setup();
	//Gettery i settery
	int getResult();
private:
	//Algorytm genetyczny
	void genetic_algorithm(vector<Genes*> pops);
	vector<Genes*> repopulate(Genes *p1, Genes *p2);
	//Generowanie tras początkowych
	vector<int> natural_route(int *path);
	vector<int> naive_route(int *path);
	vector<int> random_route(int *path);
};

#endif