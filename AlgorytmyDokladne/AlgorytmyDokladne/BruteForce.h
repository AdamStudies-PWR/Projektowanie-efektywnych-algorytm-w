#pragma once
#ifndef BruteForce_hpp
#define BruteForce_hpp

#include "Data.h"

//Klasa obs³uguj¹ca obliczanie problemu komiwoja¿era za pomoc¹ brute-force
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
