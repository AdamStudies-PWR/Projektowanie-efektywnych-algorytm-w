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
		cout << " [8] Testowanie" << endl;
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
		case '8':
		{
			if (!exists)
			{
				system("cls");
				cout << "Brak danych" << endl;
				_getche();
			}
			else test_menu();
		} break;
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
		cout << " Wyb�r: ";
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

void Interface::test_menu()
{
	char choice;
	string filename;
	do
	{
		system("cls");
		cout << "\t---Testowanie---" << endl;
		cout << " Obecne dane: " << nazwa << endl;
		cout << " Ilo�� pr�b: " << loops << endl;
		cout << " [1] Zmie� ilo�� pr�b" << endl;
		cout << " [2] Testowane algorytmy" << endl;
		cout << " [3] Uruchom" << endl;
		cout << " [4] Wy�wietl wynik pomiar�w [Tylko ostatni pomiar]" << endl;
		cout << " [5] Zapisz do pliku" << endl;
		cout << " [0] Cofnij" << endl;
		cout << " Wyb�r: ";
		choice = _getche();
		switch (choice)
		{
		case '1':
		{
			cout << "\n Podaj now� warto��: ";
			cin >> loops;
		}; break;
		case '2':
		{
			tested_alg();
		}; break;
		case '3':
		{
			voy.testing(loops, tested);
		}; break;
		case '4':
		{
			voy.dispaly_results(tested, loops);
		}; break;
		case '5':
		{
			system("cls");
			cout << "Wprowad� nazw� pliku: ";
			cin >> filename;
			voy.save(tested, loops, filename);
		}; break;
		case '0': {}break;
		default: cout << "\nB��d wprowadzenia, spr�buj ponownie" << endl, _getch();
		}
	} while (choice != '0');
}

void Interface::tested_alg()
{
	char choice;
	do
	{
		system("cls");
		cout << "\t---Testowane algorytmy---" << endl;
		cout << " [1] Bruteforce\t\t\t\t" << tested[0] <<endl;
		cout << " [2] Bruteforce z optymalizacj�\t\t" << tested[1] << endl;
		cout << " [3] Branch and Bound\t\t\t" << tested[2] << endl;
		cout << " [4] Held Karp\t\t\t\t" << tested[3] << endl;
		cout << " [0] Cofnij" << endl;
		cout << " Wyb�r: ";
		choice = _getche();
		switch (choice)
		{
		case '1':
		{
			tested[0] = !tested[0];
		}; break;
		case '2':
		{
			tested[1] = !tested[1];
		}; break;
		case '3':
		{
			tested[2] = !tested[2];
		}; break;
		case '4':
		{
			tested[3] = !tested[3];
		}; break;
		case '0': {}break;
		default: cout << "\nB��d wprowadzenia, spr�buj ponownie" << endl, _getch();
		}
	} while (choice != '0');
}