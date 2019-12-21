//Data.cpp - implemecntacja funkcji z klasy Data
#include "pch.h"
#include "Data.h"


//Metoda wczytuj¹ca dane z pliku
string Data::load(string filename)
{
	string name;
	system("cls");
	if (exists)
	{
		for (int i = 0; i < ext; i++)
		{
			delete[] tab[i];
		}
		delete[] tab;
	}
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
		limits = counttarget();
		return "wczytane z " + name + ".txt";
	}
	else
	{
		cout << "B³¹d odczytu" << endl;
		_getch();
		return "error";
	}
}

//Metoda wyœwietlaj¹ca tabele wizualizujac¹ problem komiwoja¿era w celu kontrolnym
void Data::display()
{
	system("cls");
	cout << "\n Rozmiar: " << ext;
	cout << "\n D³ugoœæ œcie¿ki: " << limits << endl;
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

//Metoda losowo wype³nij¹ca macierz
void Data::randomify(int size, bool mirror)
{
	int k = 0;
	ext = size;
	if (exists)
	{
		for (int i = 0; i < ext; i++)
		{
			delete[] tab[i];
		}
		delete[] tab;
	}
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
	limits = counttarget();
}

//Rêczne uzupe³nianie danych
void Data::manual(int size, bool mirror)
{
	int k = 0, num;
	ext = size;
	if (exists)
	{
		for (int i = 0; i < ext; i++)
		{
			delete[] tab[i];
		}
		delete[] tab;
	}
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
					cout << "Podaj odleg³oœæ pomiedzy [" << i << "], a [" << j << "]: ";
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
					cout << "Podaj odleg³oœæ pomiedzy [" << i << "], a [" << j << "]: ";
					cin >> num;
					tab[i][j] = num;
				}
			}
		}
	}
	limits = counttarget();
}

//Metoda licz¹ca d³ugoœæ œciezki komiwoja¿era
int Data::counttarget()
{
	int value = 0;
	for (int i = 1; i < ext; i++) value = value + tab[i - 1][i];
	value = value + tab[ext - 1][0];
	return value;
}

//Funkca wyœwietlaj¹ca wyniki testowania
void Data::dispaly_results(bool tab[], int size)
{
	system("cls");
	if (results == nullptr) cout << "Brak pomiarów!" << endl;
	else
	{
		if (tab[0]) cout << "Algorytm naiwny: " << results[0][size - 1] << ", wynik: " << results[1][size - 1] << endl;
		if (tab[1]) cout << "Tabu search: " << results[2][size - 1] << ", wynik: " << results[3][size - 1] << endl;
		if (tab[2]) cout << "Tabu search - AN: " << results[4][size - 1] << ", wynik: " << results[5][size - 1] << endl;
		if (tab[3]) cout << "Symulowane wyrza¿anie: " << results[6][size - 1] << ", wynik: " << results[7][size - 1] << endl;
		if (tab[4]) cout << "Symulowane wyrza¿anie - AN: " << results[8][size - 1] << ", wynik: " << results[9][size - 1] << endl;
		if (tab[5]) cout << "Mój algorytm: " << results[10][size - 1] << ", wynik: " << results[11][size - 1] << endl;
		if (tab[6]) cout << "Mój algorytm - AN: " << results[12][size - 1] << ", wynik: " << results[13][size - 1] << endl;
	}
	_getche();
}

//Funckja zapisuj¹ca wyniki do pliku
void Data::save(bool tab[], int size, string filename)
{
	system("cls");
	if (results == nullptr) cout << "Brak pomiarów!" << endl, _getche;
	else
	{
		ofstream plik(filename + ".txt");
		if (plik.good() == true)
		{
			if (tab[0]) plik << "NS;";
			if (tab[1]) plik << "Tabu;";
			if (tab[2]) plik << "TabuNS;";
			if (tab[3]) plik << "ANN";
			if (tab[4]) plik << "ANNNS;";
			if (tab[5]) plik << "SA;";
			if (tab[6]) plik << "SANS;";
			if (tab[0]) plik << "Wynik_NS;";
			if (tab[1]) plik << "Wynik_Tabu;";
			if (tab[2]) plik << "Wynik_TabuNS;";
			if (tab[3]) plik << "Wynik_ANN;";
			if (tab[4]) plik << "Wynik_ANNNS;";
			if (tab[5]) plik << "Wynik_SA;";
			if (tab[6]) plik << "Wynik_SANS;";
			plik << endl;
			for (int i = 0; i < size; i++)
			{
				if (tab[0]) plik << results[0][i] << ";";
				if (tab[1]) plik << results[2][i] << ";";
				if (tab[2]) plik << results[4][i] << ";";
				if (tab[3]) plik << results[6][i] << ";";
				if (tab[4]) plik << results[8][i] << ";";
				if (tab[5]) plik << results[10][i] << ";";
				if (tab[6]) plik << results[12][i] << ";";
				if (tab[0]) plik << results[1][i] << ";";
				if (tab[1]) plik << results[3][i] << ";";
				if (tab[2]) plik << results[5][i] << ";";
				if (tab[3]) plik << results[7][i] << ";";
				if (tab[4]) plik << results[9][i] << ";";
				if (tab[5]) plik << results[11][i] << ";";
				if (tab[6]) plik << results[13][i];
				plik << endl;
			}
			plik.close();
		}
		else cout << "B³¹d zapisu" << endl, _getche();
	}
}