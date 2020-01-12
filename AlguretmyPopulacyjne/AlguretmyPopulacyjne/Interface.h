#pragma once
#ifndef Interface_hpp
#define Interface_hpp

using namespace std;

#include "Solutions.h"

// Klasa obs�uguj�ca interakcje z u�ytkownikiem
class Interface
{
private:
	//Atrybuty
	string nazwa = "brak";
	Solutions voy;
	bool exists = false;
	bool mode = true;
	string modeS = "Brak rodzic�w";
public:
	//Metody
	void main_menu();
	void genes_menu();
	void iterations();
private:
};
#endif