#pragma once
#ifndef BruteForce_hpp
#define BruteForce_hpp

#include "Data.h"

//Klasa obs�uguj�ca obliczanie problemu komiwoja�era za pomoc� brute-force
class BruteForce : public Data
{
private:
	//zmienne
	int max;
public:
	//metody
	~BruteForce();
	void searchtree();
	void seacrhtree_opt();
	//Gettery i settery
	int getDistance();
private:
	void rectree(int line, vector<bool> visted, int distance, int layer);
	void rectree_opt(int line, vector<bool> visted, int distance, int layer);
};

#endif
