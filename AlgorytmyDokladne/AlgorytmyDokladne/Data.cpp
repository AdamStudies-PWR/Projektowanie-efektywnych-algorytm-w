//Data.cpp - implemecntacja funkcji z klasy Data
#include "pch.h"
#include "Data.h"


//Metoda wczytuj�ca dane z pliku
string Data::load(string filename)
{
	string name;
	system("cls");
	if (exists) delete[] tab;
	ifstream plik(filename + ".txt");
	if (plik.good() == true)
	{
		plik >> name;
		plik >> ext;
		tab = new int*[ext];
		for (int i = 0; i < ext; i++) tab[i] = new int[ext];
		for (int i = 0; i < ext; i++) 
		{
			for (int j = 0; j < ext; j++)
			{
				plik >> tab[i][j];
			}
		}
		return "wczytane z " + name + ".txt";
	}
	else
	{
		cout << "B��d odczytu" << endl;
		_getch();
		return "error";
	}
}

//Metoda wy�wietlaj�ca tabele wizualizujac� problem komiwoja�era w celu kontrolnym
void Data::display()
{
	system("cls");
	cout << "\n Rozmiar: " << ext;
	cout << "\n D�ugo�� �cie�ki: " << counttarget() << endl;
	for (int i = 0; i < ext; i++)
	{
		cout << " ";
		for (int j = 0; j < ext; j++)
		{
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}
	_getche();
}

//Metoda losowo wype�nij�ca macierz
void Data::randomify(int size, bool mirror)
{
	int k = 0;
	ext = size;
	if (exists) delete[] tab;
	tab = new int*[ext];
	for (int i = 0; i < ext; i++) tab[i] = new int[ext];
	if (mirror)
	{
		for (int i = 0; i < ext; i++)
		{
			for (int j = k; j < ext; j++)
			{
				if (i == j) tab[i][j] = -1;
				else
				{
					tab[i][j] = rand() % limit + 1;
					tab[j][i] = tab[i][j];
				}
			}
			k++;
		}
	}
	else
	{
		for (int i = 0; i < ext; i++)
		{
			for (int j = 0; j < ext; j++)
			{
				if (i == j) tab[i][j] = -1;
				else tab[i][j] = rand() % limit + 1;
			}
		}
	}
}

//R�czne uzupe�nianie danych
void Data::manual(int size, bool mirror)
{
	int k = 0, num;
	ext = size;
	if (exists) delete[] tab;
	tab = new int*[ext];
	for (int i = 0; i < ext; i++) tab[i] = new int[ext];
	if (mirror)
	{
		for (int i = 0; i < ext; i++)
		{
			for (int j = k; j < ext; j++)
			{
				if (i == j) tab[i][j] = -1;
				else
				{
					system("cls");
					cout << "Podaj odleg�o�� pomiedzy [" << i << "], a [" << j << "]: ";
					cin >> num;
					tab[j][i] = tab[i][j] = num;
				}
			}
			k++;
		}
	}
	else
	{
		for (int i = 0; i < ext; i++)
		{
			for (int j = 0; j < ext; j++)
			{
				if (i == j) tab[i][j] = -1;
				else
				{
					system("cls");
					cout << "Podaj odleg�o�� pomiedzy [" << i << "], a [" << j << "]: ";
					cin >> num;
					tab[i][j] = num;
				}
			}
		}
	}
}

//Metoda licz�ca d�ugo�� �ciezki komiwoja�era
int Data::counttarget()
{
	int value = 0;
	for (int i = 1; i < ext; i++) value = value + tab[i - 1][i];
	value = value + tab[ext - 1][0];
	return value;
}

//Gettery i Settery
int Data::getDistance() { return distance; }