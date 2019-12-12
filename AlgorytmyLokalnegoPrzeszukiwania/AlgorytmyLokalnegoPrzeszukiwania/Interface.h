#pragma once
#ifndef Interface_hpp
#define Interface_hpp

#include "Solutions.h"
#include "Counter.h"

using namespace std;

// Klasa obs�uguj�ca interakcje z u�ytkownikiem
class Interface
{
private:
	//Atrybuty
	string nazwa = "brak";
	Solutions voy;
	Counter count;
	bool exists = false;
	int loops = 100;
	bool tested[7] = { true, true, true, true, true, true, true };
public:
	//Metody
	void main_menu();
private:
	void annealing();
	void tabu();
	void test_menu();
	void tested_alg();
};
#endif