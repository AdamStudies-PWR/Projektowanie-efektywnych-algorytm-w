#pragma once
#ifndef Interface_hpp
#define Interface_hpp

#include "Solutions.h"
#include "Counter.h"

using namespace std;

// Klasa obs³uguj¹ca interakcje z u¿ytkownikiem
class Interface
{
private:
	//Atrybuty
	string nazwa = "brak";
	Solutions voy;
	Counter count;
	bool exists = false;
public:
	//Metody
	void main_menu();
private:
	void annealing();
	void tabu();
};
#endif