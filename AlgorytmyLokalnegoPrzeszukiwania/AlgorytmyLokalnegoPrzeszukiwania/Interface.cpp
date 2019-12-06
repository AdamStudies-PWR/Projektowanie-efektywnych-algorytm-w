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
		cout << "\t---Algorytmy Lokalnego Przeszukiwania---" << endl;
		cout << " Obecne dane: " << nazwa << endl;
		cout << " [1] Wczytaj z pliku" << endl;
		cout << " [2] Generuj losowo" << endl;
		cout << " [3] WprowadŸ rêcznie" << endl;
		cout << " [4] Wyœwietl" << endl;
		cout << " [5] Algorytm naiwny" << endl;
		cout << " [6] Tabu Search" << endl;
		cout << " [7] Simulated Annealing" << endl;
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
				count.StartFileCounter();
				voy.naive_search();
				cout << "\nCzas: " << count.GetCounter() << "ms" << endl;
				cout << "Wynik: " << voy.get_result() << endl;
				_getche();
			}
		} break;
		case '6':
		{
			if (!exists)
			{
				system("cls");
				cout << "Brak danych" << endl;
				_getche();
			}
			else tabu();
		} break;
		case '7':
		{
			if (!exists)
			{
				system("cls");
				cout << "Brak danych" << endl;
				_getche();
			}
			else annealing();
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

//Menu dla tabu search
void Interface::tabu()
{
	char choice;
	do
	{
		system("cls");
		cout << "\t---Tabu Search---" << endl;
		cout << " Obecne dane: " << nazwa << endl;
		cout << " [1] Tabu Search [Funkcja celu]" << endl;
		cout << " [2] Tabu Search [Algorytm naiwny]" << endl;
		cout << " [0] Cofnij" << endl;
		cout << " Wybór: ";
		choice = _getche();
		switch (choice)
		{
		case '1':
		{
			count.StartFileCounter();
			voy.tabu_setup();
			cout << "\nCzas: " << count.GetCounter() << "ms" << endl;
			cout << "Wynik: " << voy.get_result() <<  endl;
			_getche();
		} break;
		case '2':
		{
			count.StartFileCounter();
			voy.tabu_setup_naive();
			cout << "\nCzas: " << count.GetCounter() << "ms" << endl;
			cout << "Wynik: " << voy.get_result() << endl;
			_getche();
		} break;
		case '0': {} break;
		default: cout << "\nB³¹d wprowadzenia, spróbuj ponownie" << endl, _getch();
		}
	} while (choice != '0');
}

//Menu dla Simulated Annealing
void Interface::annealing()
{
	char choice;
	do
	{
		system("cls");
		cout << "\t---Simulated Annealing---" << endl;
		cout << " Obecne dane: " << nazwa << endl;
		cout << " [1] Simulated Annealing [Funkcja celu]" << endl;
		cout << " [2] Simulated Annealing [Algorytm naiwny]" << endl;
		cout << " [3] SA - wersja 1 [Funkcja celu]" << endl;
		cout << " [4] SA - wersja 1 [Algorytm naiwny]" << endl;
		cout << " [0] Cofnij" << endl;
		cout << " Wybór: ";
		choice = _getche();
		switch (choice)
		{
		case '1':
		{
			count.StartFileCounter();
			voy.annealing_setup();
			cout << "\nCzas: " << count.GetCounter() << "ms" << endl;
			cout << "Wynik: " << voy.get_result() << endl;
			_getche();
		} break;
		case '2':
		{
			count.StartFileCounter();
			voy.annealing_setup_naive();
			cout << "\nCzas: " << count.GetCounter() << "ms" << endl;
			cout << "Wynik: " << voy.get_result() << endl;
			_getche();
		} break;
		case '3':
		{
			count.StartFileCounter();
			voy.sa_setup();
			cout << "\nCzas: " << count.GetCounter() << "ms" << endl;
			cout << "Wynik: " << voy.get_result() << endl;
			_getche();
		} break;
		case '4':
		{
			count.StartFileCounter();
			voy.sa_setup_naive();
			cout << "\nCzas: " << count.GetCounter() << "ms" << endl;
			cout << "Wynik: " << voy.get_result() << endl;
			_getche();
		} break;
		case '0': {} break;
		default: cout << "\nB³¹d wprowadzenia, spróbuj ponownie" << endl, _getch();
		}
	} while (choice != '0');
}