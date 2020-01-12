#pragma once
#ifndef Interface_hpp
#define Interface_hpp

using namespace std;

#include "Solutions.h"

// Klasa obsługująca interakcje z użytkownikiem
class Interface
{
private:
	//Atrybuty
	string nazwa = "brak";
	Solutions voy;
	bool exists = false;
public:
	//Metody
	void main_menu();
	void genes_menu();
	void iterations();
private:
};
#endif