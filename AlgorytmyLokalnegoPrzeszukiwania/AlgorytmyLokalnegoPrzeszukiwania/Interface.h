#pragma once
#ifndef Interface_hpp
#define Interface_hpp

#include "Data.h"

using namespace std;

// Klasa obsługująca interakcje z użytkownikiem
class Interface
{
private:
	//Atrybuty
	string nazwa = "brak";
	Data voy;
	bool exists = false;
public:
	//Metody
	void main_menu();
private:
};
#endif