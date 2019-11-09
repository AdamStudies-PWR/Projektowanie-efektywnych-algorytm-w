#pragma once
#ifndef Interface_hpp
#define Interface_hpp

#include "Solutions.h"

using namespace std;

// Klasa obs³uguj¹ca interakcje z u¿ytkownikiem
class Interface
{
private:
	//Atrybuty
	string nazwa = "brak";
	Solutions voy;
	bool exists = false;
	int loops = 100;
	bool tested[4] = { true, true, true, true };
public:
	//Metody
	void main_menu();
private:
	void brute_force();
	void test_menu();
	void tested_alg();
};
#endif