#pragma once
#ifndef BruteForce_hpp
#define BruteForce_hpp

#include "Data.h"

//Klasa obsługująca obliczanie problemu komiwojażera za pomocą brute-force
class BruteForce : public Data
{
private:
	//zmienne
	bool *visited;
public:
	//metody
	~BruteForce();
	void searchtree();
	int findshort(int line);
};

#endif
