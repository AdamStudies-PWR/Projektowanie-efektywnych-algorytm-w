//Interface.cpp - implemecntacja funkcji z klasy Interface
#include "pch.h"
#include "Interface.h"
using namespace std;

//G³ówne menu programu
void Interface::main_menu()
{
	char choice;
	do
	{
		system("cls");
		cout << "\t---Algorytmy Dok³adne---" << endl;
		cout << " [0] Zakoñcz program" << endl;
		cout << " Wybór: ";
		choice = _getche();
		switch (choice)
		{
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