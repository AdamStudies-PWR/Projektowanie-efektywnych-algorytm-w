#pragma once
#ifndef Sulutions_hpp
#define Solutions_hpp

#include "Data.h"

//Klasa obs�uguj�ce obliczenia dla realizowanych w tym programie problem�w
class Solutions : public Data
{
private:
	//Zmienne
	int result;
public:
	//Metody
	//Algorytm genetyczny
	void genetic_setup();
	//Gettery i settery
	int getResult();
private:
	//Algorytm genetyczny
	void genetic_algorithm();
};

#endif