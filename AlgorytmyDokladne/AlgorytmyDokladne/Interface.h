#pragma once
#ifndef Interface_hpp
#define Interface_hpp

#include "BruteForce.h"

using namespace std;

// Klasa obs�uguj�ca interakcje z u�ytkownikiem
class Interface
{
private:
	//Atrybuty
	string nazwa = "brak";
	BruteForce voy;
	bool exists = false;
public:
	//Metidy
	void main_menu();
	void brute_force();
private:

};
#endif