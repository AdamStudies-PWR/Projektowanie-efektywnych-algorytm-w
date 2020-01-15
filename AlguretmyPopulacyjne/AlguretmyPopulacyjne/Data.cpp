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

void Data::dispaly_results(bool tab[], bool rounds[], int size)
{
	system("cls");
	if (results == nullptr) cout << "Brak pomiarów!" << endl;
	else
	{
		if (tab[0] && rounds[0]) cout << "Populacja 50, pêtla 100, brak rodziców    : " << results[0][size - 1] << ", wynik: " << results[1][size - 1] << endl;
		if (tab[0] && rounds[0]) cout << "Populacja 50, pêtla 100, 10% najlepszych  : " << results[2][size - 1] << ", wynik: " << results[3][size - 1] << endl;
		if (tab[0] && rounds[1]) cout << "Populacja 50, pêtla 1000, brak rodziców   : " << results[4][size - 1] << ", wynik: " << results[5][size - 1] << endl;
		if (tab[0] && rounds[1]) cout << "Populacja 50, pêtla 1000, 10% najlepszych : " << results[6][size - 1] << ", wynik: " << results[7][size - 1] << endl;
		if (tab[0] && rounds[2]) cout << "Populacja 50, pêtla 2000, brak rodziców   : " << results[8][size - 1] << ", wynik: " << results[9][size - 1] << endl;
		if (tab[0] && rounds[2]) cout << "Populacja 50, pêtla 2000, 10% najlepszych : " << results[10][size - 1] << ", wynik: " << results[11][size - 1] << endl;
		if (tab[0] && rounds[3]) cout << "Populacja 50, pêtla 5000, brak rodziców   : " << results[12][size - 1] << ", wynik: " << results[13][size - 1] << endl;
		if (tab[0] && rounds[3]) cout << "Populacja 50, pêtla 5000, 10% najlepszych : " << results[14][size - 1] << ", wynik: " << results[15][size - 1] << endl;
		if (tab[0] && rounds[4]) cout << "Populacja 50, pêtla 10000, brak rodziców  : " << results[16][size - 1] << ", wynik: " << results[17][size - 1] << endl;
		if (tab[0] && rounds[4]) cout << "Populacja 50, pêtla 10000, 10% najlepszych: " << results[18][size - 1] << ", wynik: " << results[19][size - 1] << endl;
		cout << endl;
		if (tab[1] && rounds[0]) cout << "Populacja 100, pêtla 100, brak rodziców    : " << results[20][size - 1] << ", wynik: " << results[21][size - 1] << endl;
		if (tab[1] && rounds[0]) cout << "Populacja 100, pêtla 100, 10% najlepszych  : " << results[22][size - 1] << ", wynik: " << results[23][size - 1] << endl;
		if (tab[1] && rounds[1]) cout << "Populacja 100, pêtla 1000, brak rodziców   : " << results[24][size - 1] << ", wynik: " << results[25][size - 1] << endl;
		if (tab[1] && rounds[1]) cout << "Populacja 100, pêtla 1000, 10% najlepszych : " << results[26][size - 1] << ", wynik: " << results[27][size - 1] << endl;
		if (tab[1] && rounds[2]) cout << "Populacja 100, pêtla 2000, brak rodziców   : " << results[28][size - 1] << ", wynik: " << results[29][size - 1] << endl;
		if (tab[1] && rounds[2]) cout << "Populacja 100, pêtla 2000, 10% najlepszych : " << results[30][size - 1] << ", wynik: " << results[31][size - 1] << endl;
		if (tab[1] && rounds[3]) cout << "Populacja 100, pêtla 5000, brak rodziców   : " << results[32][size - 1] << ", wynik: " << results[33][size - 1] << endl;
		if (tab[1] && rounds[3]) cout << "Populacja 100, pêtla 5000, 10% najlepszych : " << results[34][size - 1] << ", wynik: " << results[35][size - 1] << endl;
		if (tab[1] && rounds[4]) cout << "Populacja 100, pêtla 10000, brak rodziców  : " << results[36][size - 1] << ", wynik: " << results[37][size - 1] << endl;
		if (tab[1] && rounds[4]) cout << "Populacja 100, pêtla 10000, 10% najlepszych: " << results[38][size - 1] << ", wynik: " << results[39][size - 1] << endl;
		cout << endl;
		if (tab[2] && rounds[0]) cout << "Populacja 200, pêtla 100, brak rodziców    : " << results[40][size - 1] << ", wynik: " << results[51][size - 1] << endl;
		if (tab[2] && rounds[0]) cout << "Populacja 200, pêtla 100, 10% najlepszych  : " << results[42][size - 1] << ", wynik: " << results[53][size - 1] << endl;
		if (tab[2] && rounds[1]) cout << "Populacja 200, pêtla 1000, brak rodziców   : " << results[44][size - 1] << ", wynik: " << results[55][size - 1] << endl;
		if (tab[2] && rounds[1]) cout << "Populacja 200, pêtla 1000, 10% najlepszych : " << results[46][size - 1] << ", wynik: " << results[57][size - 1] << endl;
		if (tab[2] && rounds[2]) cout << "Populacja 200, pêtla 2000, brak rodziców   : " << results[48][size - 1] << ", wynik: " << results[59][size - 1] << endl;
		if (tab[2] && rounds[2]) cout << "Populacja 200, pêtla 2000, 10% najlepszych : " << results[50][size - 1] << ", wynik: " << results[51][size - 1] << endl;
		if (tab[2] && rounds[3]) cout << "Populacja 200, pêtla 5000, brak rodziców   : " << results[52][size - 1] << ", wynik: " << results[53][size - 1] << endl;
		if (tab[2] && rounds[3]) cout << "Populacja 200, pêtla 5000, 10% najlepszych : " << results[54][size - 1] << ", wynik: " << results[55][size - 1] << endl;
		if (tab[2] && rounds[4]) cout << "Populacja 200, pêtla 10000, brak rodziców  : " << results[56][size - 1] << ", wynik: " << results[57][size - 1] << endl;
		if (tab[2] && rounds[4]) cout << "Populacja 200, pêtla 10000, 10% najlepszych: " << results[58][size - 1] << ", wynik: " << results[59][size - 1] << endl;
		cout << endl;
		if (tab[3] && rounds[0]) cout << "Populacja 400, pêtla 100, brak rodziców    : " << results[60][size - 1] << ", wynik: " << results[61][size - 1] << endl;
		if (tab[3] && rounds[0]) cout << "Populacja 400, pêtla 100, 10% najlepszych  : " << results[62][size - 1] << ", wynik: " << results[63][size - 1] << endl;
		if (tab[3] && rounds[1]) cout << "Populacja 400, pêtla 1000, brak rodziców   : " << results[64][size - 1] << ", wynik: " << results[65][size - 1] << endl;
		if (tab[3] && rounds[1]) cout << "Populacja 400, pêtla 1000, 10% najlepszych : " << results[66][size - 1] << ", wynik: " << results[67][size - 1] << endl;
		if (tab[3] && rounds[2]) cout << "Populacja 400, pêtla 2000, brak rodziców   : " << results[68][size - 1] << ", wynik: " << results[69][size - 1] << endl;
		if (tab[3] && rounds[2]) cout << "Populacja 400, pêtla 2000, 10% najlepszych : " << results[70][size - 1] << ", wynik: " << results[71][size - 1] << endl;
		if (tab[3] && rounds[3]) cout << "Populacja 400, pêtla 5000, brak rodziców   : " << results[72][size - 1] << ", wynik: " << results[73][size - 1] << endl;
		if (tab[3] && rounds[3]) cout << "Populacja 400, pêtla 5000, 10% najlepszych : " << results[74][size - 1] << ", wynik: " << results[75][size - 1] << endl;
		if (tab[3] && rounds[4]) cout << "Populacja 400, pêtla 10000, brak rodziców  : " << results[76][size - 1] << ", wynik: " << results[77][size - 1] << endl;
		if (tab[3] && rounds[4]) cout << "Populacja 400, pêtla 10000, 10% najlepszych: " << results[78][size - 1] << ", wynik: " << results[79][size - 1] << endl;
		cout << endl;
		if (tab[4] && rounds[0]) cout << "Populacja 800, pêtla 100, brak rodziców    : " << results[80][size - 1] << ", wynik: " << results[81][size - 1] << endl;
		if (tab[4] && rounds[0]) cout << "Populacja 800, pêtla 100, 10% najlepszych  : " << results[82][size - 1] << ", wynik: " << results[83][size - 1] << endl;
		if (tab[4] && rounds[1]) cout << "Populacja 800, pêtla 1000, brak rodziców   : " << results[84][size - 1] << ", wynik: " << results[85][size - 1] << endl;
		if (tab[4] && rounds[1]) cout << "Populacja 800, pêtla 1000, 10% najlepszych : " << results[86][size - 1] << ", wynik: " << results[87][size - 1] << endl;
		if (tab[4] && rounds[2]) cout << "Populacja 800, pêtla 2000, brak rodziców   : " << results[88][size - 1] << ", wynik: " << results[89][size - 1] << endl;
		if (tab[4] && rounds[2]) cout << "Populacja 800, pêtla 2000, 10% najlepszych : " << results[90][size - 1] << ", wynik: " << results[91][size - 1] << endl;
		if (tab[4] && rounds[3]) cout << "Populacja 800, pêtla 5000, brak rodziców   : " << results[92][size - 1] << ", wynik: " << results[93][size - 1] << endl;
		if (tab[4] && rounds[3]) cout << "Populacja 800, pêtla 5000, 10% najlepszych : " << results[94][size - 1] << ", wynik: " << results[95][size - 1] << endl;
		if (tab[4] && rounds[4]) cout << "Populacja 800, pêtla 10000, brak rodziców  : " << results[96][size - 1] << ", wynik: " << results[97][size - 1] << endl;
		if (tab[4] && rounds[4]) cout << "Populacja 800, pêtla 10000, 10% najlepszych: " << results[98][size - 1] << ", wynik: " << results[99][size - 1] << endl;
		cout << endl;
		if (tab[5] && rounds[0]) cout << "Populacja 1000, pêtla 100, brak rodziców    : " << results[100][size - 1] << ", wynik: " << results[101][size - 1] << endl;
		if (tab[5] && rounds[0]) cout << "Populacja 1000, pêtla 100, 10% najlepszych  : " << results[102][size - 1] << ", wynik: " << results[103][size - 1] << endl;
		if (tab[5] && rounds[1]) cout << "Populacja 1000, pêtla 1000, brak rodziców   : " << results[104][size - 1] << ", wynik: " << results[105][size - 1] << endl;
		if (tab[5] && rounds[1]) cout << "Populacja 1000, pêtla 1000, 10% najlepszych : " << results[106][size - 1] << ", wynik: " << results[107][size - 1] << endl;
		if (tab[5] && rounds[2]) cout << "Populacja 1000, pêtla 2000, brak rodziców   : " << results[108][size - 1] << ", wynik: " << results[109][size - 1] << endl;
		if (tab[5] && rounds[2]) cout << "Populacja 1000, pêtla 2000, 10% najlepszych : " << results[110][size - 1] << ", wynik: " << results[111][size - 1] << endl;
		if (tab[5] && rounds[3]) cout << "Populacja 1000, pêtla 5000, brak rodziców   : " << results[112][size - 1] << ", wynik: " << results[113][size - 1] << endl;
		if (tab[5] && rounds[3]) cout << "Populacja 1000, pêtla 5000, 10% najlepszych : " << results[114][size - 1] << ", wynik: " << results[115][size - 1] << endl;
		if (tab[5] && rounds[4]) cout << "Populacja 1000, pêtla 10000, brak rodziców  : " << results[116][size - 1] << ", wynik: " << results[117][size - 1] << endl;
		if (tab[5] && rounds[4]) cout << "Populacja 1000, pêtla 10000, 10% najlepszych: " << results[118][size - 1] << ", wynik: " << results[119][size - 1] << endl;
	}
	_getche();
}

void Data::save(bool pop[], bool rounds[], int size, string filename)
{
	system("cls");
	if (results == nullptr) cout << "Brak pomiarów!" << endl, _getche;
	else
	{
		ofstream plik(filename + ".txt");
		if (plik.good() == true)
		{
			if (tab[0] && rounds[0]) plik << "p50r100w1;";
			if (tab[0] && rounds[0]) plik << "p50r100w2;";
			if (tab[0] && rounds[1]) plik << "p50r1000w1;";
			if (tab[0] && rounds[1]) plik << "p50r1000w2;";
			if (tab[0] && rounds[2]) plik << "p50r2000w1;";
			if (tab[0] && rounds[2]) plik << "p50r2000w2;";
			if (tab[0] && rounds[3]) plik << "p50r5000w1;";
			if (tab[0] && rounds[3]) plik << "p50r5000w2;";
			if (tab[0] && rounds[4]) plik << "p50r10000w1;";
			if (tab[0] && rounds[4]) plik << "p50r10000w2;";
			if (tab[1] && rounds[0]) plik << "p100r100w1;";
			if (tab[1] && rounds[0]) plik << "p100r100w2;";
			if (tab[1] && rounds[1]) plik << "p100r1000w1;";
			if (tab[1] && rounds[1]) plik << "p100r1000w2;";
			if (tab[1] && rounds[2]) plik << "p100r2000w1;";
			if (tab[1] && rounds[2]) plik << "p100r2000w2;";
			if (tab[1] && rounds[3]) plik << "p100r5000w1;";
			if (tab[1] && rounds[3]) plik << "p100r5000w2;";
			if (tab[1] && rounds[4]) plik << "p100r10000w1;";
			if (tab[1] && rounds[4]) plik << "p100r10000w2;";
			if (tab[2] && rounds[0]) plik << "p200r100w1;";
			if (tab[2] && rounds[0]) plik << "p200r100w2;";
			if (tab[2] && rounds[1]) plik << "p200r1000w1;";
			if (tab[2] && rounds[1]) plik << "p200r1000w2;";
			if (tab[2] && rounds[2]) plik << "p200r2000w1;";
			if (tab[2] && rounds[2]) plik << "p200r2000w2;";
			if (tab[2] && rounds[3]) plik << "p200r5000w1;";
			if (tab[2] && rounds[3]) plik << "p200r5000w2;";
			if (tab[2] && rounds[4]) plik << "p200r10000w1;";
			if (tab[2] && rounds[4]) plik << "p200r10000w2;";
			if (tab[3] && rounds[0]) plik << "p400r100w1;";
			if (tab[3] && rounds[0]) plik << "p400r100w2;";
			if (tab[3] && rounds[1]) plik << "p400r1000w1;";
			if (tab[3] && rounds[1]) plik << "p400r1000w2;";
			if (tab[3] && rounds[2]) plik << "p400r2000w1;";
			if (tab[3] && rounds[2]) plik << "p400r2000w2;";
			if (tab[3] && rounds[3]) plik << "p400r5000w1;";
			if (tab[3] && rounds[3]) plik << "p400r5000w2;";
			if (tab[3] && rounds[4]) plik << "p400r10000w1;";
			if (tab[3] && rounds[4]) plik << "p400r10000w2;";
			if (tab[4] && rounds[0]) plik << "p800r100w1;";
			if (tab[4] && rounds[0]) plik << "p800r100w2;";
			if (tab[4] && rounds[1]) plik << "p800r1000w1;";
			if (tab[4] && rounds[1]) plik << "p800r1000w2;";
			if (tab[4] && rounds[2]) plik << "p800r2000w1;";
			if (tab[4] && rounds[2]) plik << "p800r2000w2;";
			if (tab[4] && rounds[3]) plik << "p800r5000w1;";
			if (tab[4] && rounds[3]) plik << "p800r5000w2;";
			if (tab[4] && rounds[4]) plik << "p800r10000w1;";
			if (tab[4] && rounds[4]) plik << "p800r10000w2;";
			if (tab[5] && rounds[0]) plik << "p1000r100w1;";
			if (tab[5] && rounds[0]) plik << "p1000r100w2;";
			if (tab[5] && rounds[1]) plik << "p1000r1000w1;";
			if (tab[5] && rounds[1]) plik << "p1000r1000w2;";
			if (tab[5] && rounds[2]) plik << "p1000r2000w1;";
			if (tab[5] && rounds[2]) plik << "p1000r2000w2;";
			if (tab[5] && rounds[3]) plik << "p1000r5000w1;";
			if (tab[5] && rounds[3]) plik << "p1000r5000w2;";
			if (tab[5] && rounds[4]) plik << "p1000r10000w1;";
			if (tab[5] && rounds[4]) plik << "p1000r10000w2;";
			if (tab[0] && rounds[0]) plik << "resultp50r100w1;";
			if (tab[0] && rounds[0]) plik << "resultp50r100w2;";
			if (tab[0] && rounds[1]) plik << "resultp50r1000w1;";
			if (tab[0] && rounds[1]) plik << "resultp50r1000w2;";
			if (tab[0] && rounds[2]) plik << "resultp50r2000w1;";
			if (tab[0] && rounds[2]) plik << "resultp50r2000w2;";
			if (tab[0] && rounds[3]) plik << "resultp50r5000w1;";
			if (tab[0] && rounds[3]) plik << "resultp50r5000w2;";
			if (tab[0] && rounds[4]) plik << "resultp50r10000w1;";
			if (tab[0] && rounds[4]) plik << "resultp50r10000w2;";
			if (tab[1] && rounds[0]) plik << "resultp100r100w1;";
			if (tab[1] && rounds[0]) plik << "resultp100r100w2;";
			if (tab[1] && rounds[1]) plik << "resultp100r1000w1;";
			if (tab[1] && rounds[1]) plik << "resultp100r1000w2;";
			if (tab[1] && rounds[2]) plik << "resultp100r2000w1;";
			if (tab[1] && rounds[2]) plik << "resultp100r2000w2;";
			if (tab[1] && rounds[3]) plik << "resultp100r5000w1;";
			if (tab[1] && rounds[3]) plik << "resultp100r5000w2;";
			if (tab[1] && rounds[4]) plik << "resultp100r10000w1;";
			if (tab[1] && rounds[4]) plik << "resultp100r10000w2;";
			if (tab[2] && rounds[0]) plik << "resultp200r100w1;";
			if (tab[2] && rounds[0]) plik << "resultp200r100w2;";
			if (tab[2] && rounds[1]) plik << "resultp200r1000w1;";
			if (tab[2] && rounds[1]) plik << "resultp200r1000w2;";
			if (tab[2] && rounds[2]) plik << "resultp200r2000w1;";
			if (tab[2] && rounds[2]) plik << "resultp200r2000w2;";
			if (tab[2] && rounds[3]) plik << "resultp200r5000w1;";
			if (tab[2] && rounds[3]) plik << "resultp200r5000w2;";
			if (tab[2] && rounds[4]) plik << "resultp200r10000w1;";
			if (tab[2] && rounds[4]) plik << "resultp200r10000w2;";
			if (tab[3] && rounds[0]) plik << "resultp400r100w1;";
			if (tab[3] && rounds[0]) plik << "resultp400r100w2;";
			if (tab[3] && rounds[1]) plik << "resultp400r1000w1;";
			if (tab[3] && rounds[1]) plik << "resultp400r1000w2;";
			if (tab[3] && rounds[2]) plik << "resultp400r2000w1;";
			if (tab[3] && rounds[2]) plik << "resultp400r2000w2;";
			if (tab[3] && rounds[3]) plik << "resultp400r5000w1;";
			if (tab[3] && rounds[3]) plik << "resultp400r5000w2;";
			if (tab[3] && rounds[4]) plik << "resultp400r10000w1;";
			if (tab[3] && rounds[4]) plik << "resultp400r10000w2;";
			if (tab[4] && rounds[0]) plik << "resultp800r100w1;";
			if (tab[4] && rounds[0]) plik << "resultp800r100w2;";
			if (tab[4] && rounds[1]) plik << "resultp800r1000w1;";
			if (tab[4] && rounds[1]) plik << "resultp800r1000w2;";
			if (tab[4] && rounds[2]) plik << "resultp800r2000w1;";
			if (tab[4] && rounds[2]) plik << "resultp800r2000w2;";
			if (tab[4] && rounds[3]) plik << "resultp800r5000w1;";
			if (tab[4] && rounds[3]) plik << "resultp800r5000w2;";
			if (tab[4] && rounds[4]) plik << "resultp800r10000w1;";
			if (tab[4] && rounds[4]) plik << "resultp800r10000w2;";
			if (tab[5] && rounds[0]) plik << "resultp1000r100w1;";
			if (tab[5] && rounds[0]) plik << "resultp1000r100w2;";
			if (tab[5] && rounds[1]) plik << "resultp1000r1000w1;";
			if (tab[5] && rounds[1]) plik << "resultp1000r1000w2;";
			if (tab[5] && rounds[2]) plik << "resultp1000r2000w1;";
			if (tab[5] && rounds[2]) plik << "resultp1000r2000w2;";
			if (tab[5] && rounds[3]) plik << "resultp1000r5000w1;";
			if (tab[5] && rounds[3]) plik << "resultp1000r5000w2;";
			if (tab[5] && rounds[4]) plik << "resultp1000r10000w1;";
			if (tab[5] && rounds[4]) plik << "resultp1000r10000w2;";
			plik << endl;
			for (int i = 0; i < size; i++)
			{
				if (tab[0] && rounds[0]) cout << results[0][i] << ";";
				if (tab[0] && rounds[0]) cout << results[2][i] << ";";
				if (tab[0] && rounds[1]) cout << results[4][i] << ";";
				if (tab[0] && rounds[1]) cout << results[6][i] << ";";
				if (tab[0] && rounds[2]) cout << results[8][i] << ";";
				if (tab[0] && rounds[2]) cout << results[10][i] << ";";
				if (tab[0] && rounds[3]) cout << results[12][i] << ";";
				if (tab[0] && rounds[3]) cout << results[14][i] << ";";
				if (tab[0] && rounds[4]) cout << results[16][i] << ";";
				if (tab[0] && rounds[4]) cout << results[18][i] << ";";
				if (tab[1] && rounds[0]) cout << results[20][i] << ";";
				if (tab[1] && rounds[0]) cout << results[22][i] << ";";
				if (tab[1] && rounds[1]) cout << results[24][i] << ";";
				if (tab[1] && rounds[1]) cout << results[26][i] << ";";
				if (tab[1] && rounds[2]) cout << results[28][i] << ";";
				if (tab[1] && rounds[2]) cout << results[30][i] << ";";
				if (tab[1] && rounds[3]) cout << results[32][i] << ";";
				if (tab[1] && rounds[3]) cout << results[34][i] << ";";
				if (tab[1] && rounds[4]) cout << results[36][i] << ";";
				if (tab[1] && rounds[4]) cout << results[38][i] << ";";
				if (tab[2] && rounds[0]) cout << results[40][i] << ";";
				if (tab[2] && rounds[0]) cout << results[42][i] << ";";
				if (tab[2] && rounds[1]) cout << results[44][i] << ";";
				if (tab[2] && rounds[1]) cout << results[46][i] << ";";
				if (tab[2] && rounds[2]) cout << results[48][i] << ";";
				if (tab[2] && rounds[2]) cout << results[50][i] << ";";
				if (tab[2] && rounds[3]) cout << results[52][i] << ";";
				if (tab[2] && rounds[3]) cout << results[54][i] << ";";
				if (tab[2] && rounds[4]) cout << results[56][i] << ";";
				if (tab[2] && rounds[4]) cout << results[58][i] << ";";
				if (tab[3] && rounds[0]) cout << results[60][i] << ";";
				if (tab[3] && rounds[0]) cout << results[62][i] << ";";
				if (tab[3] && rounds[1]) cout << results[64][i] << ";";
				if (tab[3] && rounds[1]) cout << results[66][i] << ";";
				if (tab[3] && rounds[2]) cout << results[68][i] << ";";
				if (tab[3] && rounds[2]) cout << results[70][i] << ";";
				if (tab[3] && rounds[3]) cout << results[72][i] << ";";
				if (tab[3] && rounds[3]) cout << results[74][i] << ";";
				if (tab[3] && rounds[4]) cout << results[76][i] << ";";
				if (tab[3] && rounds[4]) cout << results[78][i] << ";";
				if (tab[4] && rounds[0]) cout << results[80][i] << ";";
				if (tab[4] && rounds[0]) cout << results[82][i] << ";";
				if (tab[4] && rounds[1]) cout << results[84][i] << ";";
				if (tab[4] && rounds[1]) cout << results[86][i] << ";";
				if (tab[4] && rounds[2]) cout << results[88][i] << ";";
				if (tab[4] && rounds[2]) cout << results[90][i] << ";";
				if (tab[4] && rounds[3]) cout << results[92][i] << ";";
				if (tab[4] && rounds[3]) cout << results[94][i] << ";";
				if (tab[4] && rounds[4]) cout << results[96][i] << ";";
				if (tab[4] && rounds[4]) cout << results[98][i] << ";";
				if (tab[1] && rounds[0]) cout << results[100][i] << ";";
				if (tab[1] && rounds[0]) cout << results[102][i] << ";";
				if (tab[1] && rounds[1]) cout << results[104][i] << ";";
				if (tab[1] && rounds[1]) cout << results[106][i] << ";";
				if (tab[1] && rounds[2]) cout << results[108][i] << ";";
				if (tab[1] && rounds[2]) cout << results[110][i] << ";";
				if (tab[1] && rounds[3]) cout << results[112][i] << ";";
				if (tab[1] && rounds[3]) cout << results[114][i] << ";";
				if (tab[1] && rounds[4]) cout << results[116][i] << ";";
				if (tab[1] && rounds[4]) cout << results[118][i] << ";";
				if (tab[0] && rounds[0]) cout << results[1][i] << ";";
				if (tab[0] && rounds[0]) cout << results[3][i] << ";";
				if (tab[0] && rounds[1]) cout << results[5][i] << ";";
				if (tab[0] && rounds[1]) cout << results[7][i] << ";";
				if (tab[0] && rounds[2]) cout << results[9][i] << ";";
				if (tab[0] && rounds[2]) cout << results[11][i] << ";";
				if (tab[0] && rounds[3]) cout << results[13][i] << ";";
				if (tab[0] && rounds[3]) cout << results[15][i] << ";";
				if (tab[0] && rounds[4]) cout << results[17][i] << ";";
				if (tab[0] && rounds[4]) cout << results[19][i] << ";";
				if (tab[1] && rounds[0]) cout << results[21][i] << ";";
				if (tab[1] && rounds[0]) cout << results[23][i] << ";";
				if (tab[1] && rounds[1]) cout << results[25][i] << ";";
				if (tab[1] && rounds[1]) cout << results[27][i] << ";";
				if (tab[1] && rounds[2]) cout << results[29][i] << ";";
				if (tab[1] && rounds[2]) cout << results[31][i] << ";";
				if (tab[1] && rounds[3]) cout << results[33][i] << ";";
				if (tab[1] && rounds[3]) cout << results[35][i] << ";";
				if (tab[1] && rounds[4]) cout << results[37][i] << ";";
				if (tab[1] && rounds[4]) cout << results[39][i] << ";";
				if (tab[2] && rounds[0]) cout << results[41][i] << ";";
				if (tab[2] && rounds[0]) cout << results[43][i] << ";";
				if (tab[2] && rounds[1]) cout << results[45][i] << ";";
				if (tab[2] && rounds[1]) cout << results[47][i] << ";";
				if (tab[2] && rounds[2]) cout << results[49][i] << ";";
				if (tab[2] && rounds[2]) cout << results[51][i] << ";";
				if (tab[2] && rounds[3]) cout << results[53][i] << ";";
				if (tab[2] && rounds[3]) cout << results[55][i] << ";";
				if (tab[2] && rounds[4]) cout << results[57][i] << ";";
				if (tab[2] && rounds[4]) cout << results[59][i] << ";";
				if (tab[3] && rounds[0]) cout << results[61][i] << ";";
				if (tab[3] && rounds[0]) cout << results[63][i] << ";";
				if (tab[3] && rounds[1]) cout << results[65][i] << ";";
				if (tab[3] && rounds[1]) cout << results[67][i] << ";";
				if (tab[3] && rounds[2]) cout << results[69][i] << ";";
				if (tab[3] && rounds[2]) cout << results[71][i] << ";";
				if (tab[3] && rounds[3]) cout << results[73][i] << ";";
				if (tab[3] && rounds[3]) cout << results[75][i] << ";";
				if (tab[3] && rounds[4]) cout << results[77][i] << ";";
				if (tab[3] && rounds[4]) cout << results[79][i] << ";";
				if (tab[4] && rounds[0]) cout << results[81][i] << ";";
				if (tab[4] && rounds[0]) cout << results[83][i] << ";";
				if (tab[4] && rounds[1]) cout << results[85][i] << ";";
				if (tab[4] && rounds[1]) cout << results[87][i] << ";";
				if (tab[4] && rounds[2]) cout << results[89][i] << ";";
				if (tab[4] && rounds[2]) cout << results[91][i] << ";";
				if (tab[4] && rounds[3]) cout << results[93][i] << ";";
				if (tab[4] && rounds[3]) cout << results[95][i] << ";";
				if (tab[4] && rounds[4]) cout << results[97][i] << ";";
				if (tab[4] && rounds[4]) cout << results[99][i] << ";";
				if (tab[1] && rounds[0]) cout << results[101][i] << ";";
				if (tab[1] && rounds[0]) cout << results[103][i] << ";";
				if (tab[1] && rounds[1]) cout << results[105][i] << ";";
				if (tab[1] && rounds[1]) cout << results[107][i] << ";";
				if (tab[1] && rounds[2]) cout << results[109][i] << ";";
				if (tab[1] && rounds[2]) cout << results[111][i] << ";";
				if (tab[1] && rounds[3]) cout << results[113][i] << ";";
				if (tab[1] && rounds[3]) cout << results[115][i] << ";";
				if (tab[1] && rounds[4]) cout << results[117][i] << ";";
				if (tab[1] && rounds[4]) cout << results[119][i] << ";";
				plik << endl;
			}
			plik.close();
		}
		else cout << "B³¹d zapisu" << endl, _getche();
	}
}