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
		cout << "\t---Algorytmy Dok�adne---" << endl;
		cout << " Obecne dane: " << nazwa << endl;
		cout << " [1] Wczytaj z pliku" << endl;
		cout << " [2] Generuj losowo" << endl;
		cout << " [3] Wprowad� r�cznie" << endl;
		cout << " [4] Wy�wietl" << endl;
		cout << " [5] Brute Force" << endl;
		cout << " [6] Branch & Bound" << endl;
		cout << " [7] Held-Karp" << endl;
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
			else brute_force();
		} break;
		case '6':
		{
			if (!exists)
			{
				system("cls");
				cout << "Brak danych" << endl;
				_getche();
			}
			else
			{
				voy.BiBbegin();
				cout << "\n Rozwi�zanie: " << voy.getDistance() << endl;
				_getch();
			}
		}break;
		case '7':
		{
			if (!exists)
			{
				system("cls");
				cout << "Brak danych" << endl;
				_getche();
			}
			else
			{
				voy.HPbegin();
				cout << "\n Rozwi�zanie: " << voy.getDistance() << endl;
				_getch();
			}
		}break;
		case '0':
		{
			system("cls");
			voy.~Solutions();
			cout << "Koniec" << endl;
			_getch();
		} break;
		default: cout << "\nB��d wprowadzenia, spr�buj ponownie" << endl, _getch();
		}
	} while (choice != '0');
}

//Menu brute-force
void Interface::brute_force()
{
	char choice;
	do
	{
		system("cls");
		cout << "\t---Brute Force---" << endl;
		cout << " Obecne dane: " << nazwa << endl;
		cout << " [1] Zwyk�y" << endl;
		cout << " [2] Zoptymalizowany" << endl;
		cout << " [0] Cofnij" << endl;
		choice = _getche();
		switch (choice)
		{
		case '1':
		{
			voy.searchtree();
			cout << "\n Rozwi�zanie: " << voy.getDistance() << endl;
			_getch();
		}; break;
		case '2':
		{
			voy.seacrhtree_opt();
			cout << "\n Rozwi�zanie: " << voy.getDistance() << endl;
			_getch();
		}; break;
		case '0': {}break;
		default: cout << "\nB��d wprowadzenia, spr�buj ponownie" << endl, _getch();
		}
	} while (choice != '0');
}