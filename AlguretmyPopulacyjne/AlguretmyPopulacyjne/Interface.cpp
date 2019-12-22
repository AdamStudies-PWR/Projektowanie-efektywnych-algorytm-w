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
			else
			{
				voy.genetic_setup();
				cout << "\nWynik: " << voy.getResult();
				_getche();
			}
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
