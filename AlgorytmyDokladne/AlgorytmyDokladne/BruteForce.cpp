//Klasa obs³uguj¹ca obliczanie problemu komiwoja¿era za pomoc¹ brute-force
#include "pch.h"
#include "Bruteforce.h"
using namespace std;

//Destruktor
BruteForce::~BruteForce()
{
	if (exists) delete[] tab;
}

int BruteForce::findshort(int line)
{
	int searched = 0;
	int value;
	for (int i = 1; i < ext; i++)
	{
		if (!visited[i])
		{
			value = tab[line][i];
			searched = i;
			break;
		}
	}
	for (int i = 1; i < ext; i++)
	{
		if (tab[line][i] < value)
		{
			if (!visited[i] && tab[line][i] != -1)
			{
				value = tab[line][i];
				searched = i;
			}
		}
	}
	visited[searched] = true;
	return searched;
}

void BruteForce::searchtree()
{
	int next = 0, prev;
	visited = new bool[ext];
	visited[0] = true;
	for (int i = 1; i < ext; i++) visited[i] = false;
	distance = 0;
	for (int i = 0; i < (ext - 1); i++)
	{
		prev = next;
		next = findshort(next);
		distance = distance + tab[prev][next];

		cout << "elo";
	}
	distance = distance + tab[next][0];
}