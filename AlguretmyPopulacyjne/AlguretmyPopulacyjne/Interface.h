#pragma once
#ifndef Interface_hpp
#define Interface_hpp

using namespace std;

// Klasa obs�uguj�ca interakcje z u�ytkownikiem
class Interface
{
private:
	//Atrybuty
	string nazwa = "brak";
	//Solutions voy;
	bool exists = false;
public:
	//Metody
	void main_menu();
private:
	void annealing();
	void tabu();
	void test_menu();
	void tested_alg();
};
#endif