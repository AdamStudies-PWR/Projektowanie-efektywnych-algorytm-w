// Klasa obsługująca funkcje mierzenia czasu
#include "pch.h"
#include "Counter.h"

//Funkcja uruchamiająca odliczanie
void Counter::StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li)) cout << "\n Błąd pomiaru czasu!" << endl;
	PCFreq = double(li.QuadPart) / 1000000.0;
	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
//Funkcja uruchamiająca odliczanie w decysekundach
void Counter::StartFileCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li)) cout << "\n Błąd pomiaru czasu!" << endl;
	PCFreq = double(li.QuadPart) / 1000.0;
	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
//Funkcja zwracjąca czas który upłynął
double Counter::GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}