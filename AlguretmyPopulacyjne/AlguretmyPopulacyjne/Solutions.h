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

//Klasa obs�uguj�ce obliczenia dla realizowanych w tym programie problem�w
class Solutions : public Data
{
private:
	//Zmienne
	int result;
	int population;
	int sim = 1000;
public:
	//Metody
	//Algorytm genetyczny
	void genetic_setup(int psize);
	//Gettery i settery
	int getResult();
	void setSim(int iter);
	int getSim();
private:
	//Algorytm genetyczny
	void genetic_algorithm(vector<Genes*> pops);
	vector<Genes*> repopulate(Genes *p1, Genes *p2);
	//Generowanie tras pocz�tkowych
	vector<int> natural_route(int *path);
	vector<int> naive_route(int *path);
	vector<int> random_route(int *path);
	//Sortowanie 
	void quicksort(vector<Genes*> &pops, int low, int high);
};

#endif