#pragma once
#ifndef Interface_hpp
#define Interface_hpp

using namespace std;

#include "Solutions.h"

// Klasa obs³uguj¹ca interakcje z u¿ytkownikiem
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
private:
};
#endif