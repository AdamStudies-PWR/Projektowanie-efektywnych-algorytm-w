//Interface.cpp - implemecntacja funkcji z klasy Interface
#include "pch.h"
#include "Interface.h"
using namespace std;

//G��wne menu programu
void Interface::main_menu()
{
	char choice;
	string input;
	int num;
	do
	{
		system("cls");
		cout << "\t---Algorytmy populacyjne---" << endl;
		cout << " Obecne dane: " << nazwa << endl;
		cout << " [1] Wczytaj z pliku" << endl;
		cout << " [2] Generuj losowo" << endl;
		cout << " [3] Wprowad� r�cznie" << endl;
		cout << " [4] Wy�wietl" << endl;
		cout << " [5] Algorytm genetyczny" << endl;
		cout << " [0] Zako�cz program" << endl;
		cout << " Wyb�r: ";
		choice = _getche();
		switch (choice)
		{
		case '1':
		{
			system("cls");
			cout << "Wprowad� nazw� pliku: ";
			cin >> input;
			nazwa = voy.load(input);
			if (nazwa == "error") exists = false;
			else exists = true;
		} break;
		case '2':
		{
			system("cls");
			cout << "Wprowad� rozmiar problemu: ";
			cin >> num;
			system("cls");
			cout << "Czy macierz parzysta [T]/[N]\n";
			choice = _getche();
			if(choice == 't' || choice == 'T') voy.randomify(num, true);
			else voy.randomify(num, false);
			exists = true;
			nazwa = "wygenerowane losowo";
		} break;
		case '3':
		{
			system("cls");
			cout << "Wprowad� rozmiar problemu: ";
			cin >> num;
			system("cls");
			cout << "Czy macierz parzysta [T]/[N]\n";
			choice = _getche();
			if (choice == 't' || choice == 'T') voy.manual(num, true);
			else voy.manual(num, false);
			exists = true;
			nazwa = "wygenerowane losowo";
		} break;
		case '4':
		{
			if (!exists)
			{
				system("cls");
				cout << "Brak danych" << endl;
				_getche();
			}
			else voy.display();
		} break;
		case '5':
		{
			if (!exists)
			{
				system("cls");
				cout << "Brak danych" << endl;
				_getche();
			}
			else genes_menu();
		} break;
		case '0':
		{
			system("cls");
			cout << "Koniec" << endl;
			_getch();
		} break;
		default: cout << "\nB��d wprowadzenia, spr�buj ponownie" << endl, _getch();
		}
	} while (choice != '0');
}

//Funkcja obs�uguj�ca interjfejs wyboru rozmiaru populacji  w algorytmie genetycznym
void Interface::genes_menu()
{
	char choice;
	do
	{
		system("cls");
		cout << "\t---Algorytm genetyczny---" << endl;
		cout << " Obecne dane: " << nazwa << endl;
		cout << " [1] Populacja 50" << endl;
		cout << " [2] Populacja 100" << endl;
		cout << " [3] Populacja 200" << endl;
		cout << " [4] Populacja 400" << endl;
		cout << " [5] Populacja 800" << endl;
		cout << " [6] Populacja 1000" << endl;
		cout << " [0] Cofnij" << endl;
		cout << " Wyb�r: ";
		choice = _getche();
		switch (choice)
		{
		case '1':
		{
			voy.genetic_setup(50);
			cout << "\nWynik: " << voy.getResult() << endl;
			_getch();
		} break;
		case '2':
		{
			voy.genetic_setup(100);
			cout << "\nWynik: " << voy.getResult() << endl;
			_getch();
		} break;
		case '3':
		{
			voy.genetic_setup(200);
			cout << "\nWynik: " << voy.getResult() << endl;
			_getch();
		} break;
		case '4':
		{
			voy.genetic_setup(400);
			cout << "\nWynik: " << voy.getResult() << endl;
			_getch();
		} break;
		case '5':
		{
			voy.genetic_setup(800);
			cout << "\nWynik: " << voy.getResult() << endl;
			_getch();
		} break;
		case '6':
		{
			voy.genetic_setup(1000);
			cout << "\nWynik: " << voy.getResult() << endl;
			_getch();
		} break;
		case '0': break;
		default: cout << "\nB��d wprowadzenia, spr�buj ponownie" << endl, _getch();
		}
	} while (choice != '0');
}

//Program s�u��cy do wyboru ilo�ci iteracji