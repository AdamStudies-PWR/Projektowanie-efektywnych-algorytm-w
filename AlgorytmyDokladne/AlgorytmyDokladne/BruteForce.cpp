//Klasa obs³uguj¹ca obliczanie problemu komiwoja¿era za pomoc¹ brute-force
#include "pch.h"
#include "Bruteforce.h"
using namespace std;

//Destruktor
BruteForce::~BruteForce()
{
	if (exists) delete[] tab;
}

//Rekurencyjne przeszukiwanie drzewa
void BruteForce::rectree(int line, vector<bool> visited, int  distance, int layer)
{
	visited[line] = true;
	if (distance > max && max != -1) return;
	if (layer != (ext-1))
	{
		for (int i = 1; i < ext; i++)
		{
			if(!visited[i]) rectree(i, visited, (distance + tab[line][i]), (layer + 1));
		}
	}
	else if ((distance + tab[line][0]) < max || max == -1)
	{
		max = distance + tab[line][0];
	}
	return;
}

//Funkcja przeszukuj¹ca drzewo w poszukiwaniu najlepszych rozwi¹zañ
void BruteForce::searchtree()
{
	max = -1;
	vector<bool> visited(ext);
	visited[0] = true;
	for (int i = 1; i < ext; i++) visited[i] = false;
	for (int i = 0; i < (ext - 1); i++)
	{
		rectree((i + 1), visited, tab[0][i + 1], 1);
	}
}

//Gettery i Settery
int BruteForce::getDistance() { return max; }