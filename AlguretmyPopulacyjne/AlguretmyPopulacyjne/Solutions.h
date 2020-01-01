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

//Klasa obs³uguj¹ce obliczenia dla realizowanych w tym programie problemów
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
	void genetic_setup(int mode);
	//Gettery i settery
	int getResult();
private:
	//Algorytm genetyczny
	void genetic_algorithm(vector<Genes*> pops);
	void genetic_new_blood(vector<Genes*> pops);
	vector<Genes*> repopulate(Genes *p1, Genes *p2);
	//Generowanie tras pocz¹tkowych
	vector<int> natural_route(int *path);
	vector<int> naive_route(int *path);
	vector<int> random_route(int *path);
};

#endif