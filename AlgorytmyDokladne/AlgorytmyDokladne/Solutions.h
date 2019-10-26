#pragma once
#ifndef Solutions_hpp
#define Solutions_hpp

#include "Data.h"

//Klasa obs³uguj¹ca obliczanie problemu komiwoja¿era za pomoc¹ brute-force
class Solutions : public Data
{
private:
	//zmienne
	int max;
public:
	//metody
	~Solutions();
	void searchtree();
	void seacrhtree_opt();
	//Gettery i settery
	int getDistance();
private:
	void rectree(int line, vector<bool> visted, int distance, int layer);
	void rectree_opt(int line, vector<bool> visted, int distance, int layer);
};

#endif
