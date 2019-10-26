//Klasa obs³uguj¹ca obliczanie problemu komiwoja¿era za pomoc¹ brute-force
#include "pch.h"
#include "Solutions.h"
using namespace std;

//Destruktor
Solutions::~Solutions()
{
	if (exists) delete[] tab;
}

//Rekurencyjne przeszukiwanie drzewa
void Solutions::rectree(int line, vector<bool> visited, int  distance, int layer)
{
	visited[line] = true;
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

//Rekurencyjne przeszukiwanie drzewa z dodatkow¹ optymalizacj¹
void Solutions::rectree_opt(int line, vector<bool> visited, int  distance, int layer)
{
	visited[line] = true;
	if (distance > max && max != -1) return;
	if (layer != (ext - 1))
	{
		for (int i = 1; i < ext; i++)
		{
			if (!visited[i]) rectree_opt(i, visited, (distance + tab[line][i]), (layer + 1));
		}
	}
	else if ((distance + tab[line][0]) < max || max == -1)
	{
		max = distance + tab[line][0];
	}
	return;
}

//Funkcja przeszukuj¹ca drzewo w poszukiwaniu najlepszych rozwi¹zañ
void Solutions::searchtree()
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
void Solutions::seacrhtree_opt()
{
	max = -1;
	vector<bool> visited(ext);
	visited[0] = true;
	for (int i = 1; i < ext; i++) visited[i] = false;
	for (int i = 0; i < (ext - 1); i++)
	{
		rectree_opt((i + 1), visited, tab[0][i + 1], 1);
	}
}

//Pocz¹tek Branch & Bound
void Solutions::BiBbeging()
{
	Node first;
	coppyarray(first.data, tab);
	system("cls");
	cout<<minimize(first.data)<<endl;
	for (int i = 0; i < ext; i++)
	{
		cout << " ";
		for (int j = 0; j < ext; j++)
		{
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n" << endl;
	for (int i = 0; i < ext; i++)
	{
		cout << " ";
		for (int j = 0; j < ext; j++)
		{
			cout << first.data[i][j] << " ";
		}
		cout << endl;
	}
}

//Funkcja minimalizuj¹ca macierz
int Solutions::minimize(int **data)
{
	int result = 0;
	for (int i = 0; i < ext; i++)
	{
		int small = data[i][0];
		{
			for (int j = 0; j < ext; j++)
			{
				if (data[i][j] < small && data[i][j] != -1) small = data[i][j];
			}
			if (small != 0)
			{
				for (int j = 0; j < ext; j++)
				{
					if (data[i][j] != -1)data[i][j] = data[i][j] - small;
				}
				result = result + small;
			}
		}
	}
	for (int i = 0; i < ext; i++)
	{
		int small = data[0][i];
		{
			for (int j = 0; j < ext; j++)
			{
				if (data[j][i] < small && data[j][i] != -1) small = data[j][i];
			}
			if (small != 0)
			{
				for (int j = 0; j < ext; j++)
				{
					if (data[j][i] != -1)data[j][i] = data[j][i] - small;
				}
				result = result + small;
			}
		}
	}
	return result;
}

//Funkcja tworz¹ca kopie tablicy
void Solutions::coppyarray(int **arr, int **src)
{
	arr = new int*[ext];
	for (int i = 0; i < ext; i++)
	{
		arr[i] = new int[ext];
		for (int j = 0; j < ext; j++)
		{
			arr[i][j] = src[i][j];
		}
	}
}

//Gettery i Settery
int Solutions::getDistance() { return max; }