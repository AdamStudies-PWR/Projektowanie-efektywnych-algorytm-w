#pragma once
#ifndef Interface_hpp
#define Interface_hpp

using namespace std;

#include "Solutions.h"
#include "Counter.h"

// Klasa obs³uguj¹ca interakcje z u¿ytkownikiem
class Interface
{
private:
	//Atrybuty
	string nazwa = "brak";
	Solutions voy;
	bool exists = false;
	bool mode = true;
	string modeS = "Brak rodziców";
	int loops = 100;
	bool pop[6] = { true, true, true, true, true, true };
	bool sizes[5] = { true, true, true, true, true };
public:
	//Metody
	void main_menu();	
private:
	void genes_menu();
	void iterations();
	void test_menu();
	void tested_pop();
	void tested_size();
};
#endif