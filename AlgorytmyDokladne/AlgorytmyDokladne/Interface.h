#pragma once
#ifndef Interface_hpp
#define Interface_hpp

#include "Solutions.h"

using namespace std;

// Klasa obs�uguj�ca interakcje z u�ytkownikiem
class Interface
{
private:
	//Atrybuty
	string nazwa = "brak";
	Solutions voy;
	bool exists = false;
public:
	//Metidy
	void main_menu();
	void brute_force();
private:

};
#endif