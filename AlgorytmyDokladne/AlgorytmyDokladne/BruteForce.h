#pragma once
#ifndef BruteForce_hpp
#define BruteForce_hpp

#include "Data.h"

//Klasa obs³uguj¹ca obliczanie problemu komiwoja¿era za pomoc¹ brute-force
class BruteForce : public Data
{
private:
	//zmienne
	int max = -1;
public:
	//metody
	~BruteForce();
	void searchtree();
	void rectree(int line, vector<bool> visted, int distance, int layer);
	//Gettery i settery
	int getDistance();
};

#endif
