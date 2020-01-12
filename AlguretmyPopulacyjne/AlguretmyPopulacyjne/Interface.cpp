//Interface.cpp - implemecntacja funkcji z klasy Interface
#include "pch.h"
#include "Interface.h"
using namespace std;

//G³ówne menu programu
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
		cout << " [3] WprowadŸ rêcznie" << endl;
		cout << " [4] Wyœwietl" << endl;
		cout << " [5] Algorytm genetyczny" << endl;
		cout << " [0] Zakoñcz program" << endl;
		cout << " Wybór: ";
		choice = _getche();
		switch (choice)
		{
		case '1':
		{
			system("cls");
			cout << "WprowadŸ nazwê pliku: ";
			cin >> input;
			nazwa = voy.load(input);
			if (nazwa == "error") exists = false;
			else exists = true;
		} break;
		case '2':
		{
			system("cls");
			cout << "WprowadŸ rozmiar problemu: ";
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
			cout << "WprowadŸ rozmiar problemu: ";
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
		default: cout << "\nB³¹d wprowadzenia, spróbuj ponownie" << endl, _getch();
		}
	} while (choice != '0');
}

//Funkcja obs³uguj¹ca interjfejs wyboru rozmiaru populacji  w algorytmie genetycznym
void Interface::genes_menu()
{
	char choice;
	do
	{
		system("cls");
		cout << "\t---Algorytm genetyczny---" << endl;
		cout << " Obecne dane: " << nazwa << endl;
		cout << " Tryb: " << modeS << endl;
		cout << " [1] Populacja 50" << endl;
		cout << " [2] Populacja 100" << endl;
		cout << " [3] Populacja 200" << endl;
		cout << " [4] Populacja 400" << endl;
		cout << " [5] Populacja 800" << endl;
		cout << " [6] Populacja 1000" << endl;
		cout << " [7] Zmieñ iloœæ iteracji" << endl;
		cout << " [8] Prze³¹cz tryb" << endl;
		cout << " [0] Cofnij" << endl;
		cout << " Wybór: ";
		choice = _getche();
		switch (choice)
		{
		case '1':
		{
			voy.genetic_setup(50, mode);
			cout << "\nWynik: " << voy.getResult() << endl;
			_getch();
		} break;
		case '2':
		{
			voy.genetic_setup(100, mode);
			cout << "\nWynik: " << voy.getResult() << endl;
			_getch();
		} break;
		case '3':
		{
			voy.genetic_setup(200, mode);
			cout << "\nWynik: " << voy.getResult() << endl;
			_getch();
		} break;
		case '4':
		{
			voy.genetic_setup(400, mode);
			cout << "\nWynik: " << voy.getResult() << endl;
			_getch();
		} break;
		case '5':
		{
			voy.genetic_setup(800, mode);
			cout << "\nWynik: " << voy.getResult() << endl;
			_getch();
		} break;
		case '6':
		{
			voy.genetic_setup(1000, mode);
			cout << "\nWynik: " << voy.getResult() << endl;
			_getch();
		} break;
		case '7': iterations();
			break;
		case '8':
		{
			mode = !mode;
			if(mode) modeS = "Brak rodziców";
			else modeS = "10% najlepszych";
		} break;
		case '0': break;
		default: cout << "\nB³¹d wprowadzenia, spróbuj ponownie" << endl, _getch();
		}
	} while (choice != '0');
}

//Program s³u¿¹cy do wyboru iloœci iteracji
void Interface::iterations()
{
	char t1 = 'O', t2 = 'O', t3 = 'O', t4 = 'O', t5 = 'O';
	int iter = voy.getSim();
	switch (iter)
	{
	case 100: t1 = 'X'; break;
	case 1000: t2 = 'X'; break;
	case 2000: t3 = 'X'; break;
	case 5000: t4 = 'X'; break;
	case 10000: t5 = 'X'; break;
	}
	char choice;
	do
	{
		system("cls");
		cout << "\t---Algorytm genetyczny---" << endl;
		cout << " Obecne dane: " << nazwa << endl;
		cout << " [1] 100    [" << t1 << "]" << endl;
		cout << " [2] 1000   [" << t2 << "]" << endl;
		cout << " [3] 2000   [" << t3 << "]" << endl;
		cout << " [4] 5000   [" << t4 << "]" << endl;
		cout << " [5] 10000  [" << t5 << "]" << endl;
		cout << " [0] Cofnij" << endl;
		cout << " Wybór: ";
		choice = _getche();
		switch (choice)
		{
		case '1':
		{
			t1 = 'X', t2 = 'O', t3 = 'O', t4 = 'O', t5 = 'O';
			voy.setSim(100);
		} break;
		case '2':
		{
			t1 = 'O', t2 = 'X', t3 = 'O', t4 = 'O', t5 = 'O';
			voy.setSim(1000);
		} break;
		case '3':
		{
			t1 = 'O', t2 = 'O', t3 = 'X', t4 = 'O', t5 = 'O';
			voy.setSim(2000);
		} break;
		case '4':
		{
			t1 = 'O', t2 = 'O', t3 = 'O', t4 = 'X', t5 = 'O';
			voy.setSim(5000);
		} break;
		case '5':
		{
			t1 = 'O', t2 = 'O', t3 = 'O', t4 = 'O', t5 = 'X';
			voy.setSim(10000);
		} break;
		case '0': break;
		default: cout << "\nB³¹d wprowadzenia, spróbuj ponownie" << endl, _getch();
		}
	} while (choice != '0');
}