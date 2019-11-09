//Data.cpp - implemecntacja funkcji z klasy Data
#include "pch.h"
#include "Data.h"


//Metoda wczytuj�ca dane z pliku
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
	cout << "\n D�ugo�� �cie�ki: " << limits << endl;
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

//R�czne uzupe�nianie danych
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
	limits = counttarget();
}

//Metoda licz�ca d�ugo�� �ciezki komiwoja�era
int Data::counttarget()
{
	int value = 0;
	for (int i = 1; i < ext; i++) value = value + tab[i - 1][i];
	value = value + tab[ext - 1][0];
	return value;
}

//Wy�wietlanie wynik�w pomiaru (ostatniego pomiaru)
void Data::dispaly_results(bool tab[], int size)
{
	system("cls");
	if (results == nullptr) cout << "Brak pomiar�w!" << endl;
	else
	{
		if (tab[0]) cout << "Brute force: " << results[0][size - 1] << endl;
		if (tab[1]) cout << "Brute force z optymalizacj�: " << results[1][size - 1] << endl;
		if (tab[2]) cout << "Branch and Bound: " << results[2][size - 1] << endl;
		if (tab[3]) cout << "Held-Karp: " << results[3][size - 1] << endl;
	}
	_getche();
}

//Funkcja zapisuj�ca wyniki pomiar�w do pliku
void Data::save(bool tab[], int size, string filename)
{
	system("cls");
	if (results == nullptr) cout << "Brak pomiar�w!" << endl, _getche;
	else
	{
		ofstream plik(filename + ".txt");
		if (plik.good() == true)
		{
			if (tab[0]) plik << "BRT;";
			if (tab[1]) plik << "BRTopt;";
			if (tab[2]) plik << "BnB;";
			if (tab[3]) plik << "HP" << endl;
			for (int i = 0; i < size; i++)
			{
				if (tab[0]) plik << results[0][i] << ";";
				if (tab[1]) plik << results[1][i] << ";";
				if (tab[2]) plik << results[2][i] << ";";
				if (tab[3]) plik << results[3][i] << endl;
			}
			plik.close();
		}
		else cout << "B��d zapisu" << endl, _getche();
	}
}