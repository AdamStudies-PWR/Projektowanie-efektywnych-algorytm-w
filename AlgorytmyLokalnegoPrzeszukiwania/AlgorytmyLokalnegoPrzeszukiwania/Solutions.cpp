//Implementacja funkcji z klasy Solutions
#include "pch.h"
#include "Solutions.h"

//Rekurencyjne rozwiniêcie tabu searcha
void Solutions::tabu_setup()
{
	line.clear();
	result = limits;
	current = ext / 2;
	tabu = new int*[ext];
	for (int i = 0; i < ext; i++)
	{
		tabu[i] = new int[ext];
		for (int j = 0; j < ext; j++)tabu[i][j] = 0;
		line.push_back(i);
	}
	line.push_back(0);
	tabu_search();
	for (int i = 0; i < ext; i++)
	{
		delete[] tabu[i];
	}
	delete[] tabu;
}

//Ustawienia tabu searcha
void Solutions::tabu_setup_naive()
{
	line.clear();
	current = ext / 2;
	tabu = new int*[ext];
	for (int i = 0; i < ext; i++)
	{
		tabu[i] = new int[ext];
		for (int j = 0; j < ext; j++)tabu[i][j] = 0;
	}
	naive_search();
	tabu_search();
	for (int i = 0; i < ext; i++)
	{
		delete[] tabu[i];
	}
	delete[] tabu;
}

//Ustawianie parametrów próbnej wersji algorytmu SA
void Solutions::sa_setup()
{
	TT = 10000;
	line.clear();
	result = limits;
	current = ext / 2;
	for (int i = 0; i < ext; i++) line.push_back(i);
	line.push_back(0);
	sa_first();
}

//Ustawianie parametrów próbnej wersji algorytmu SA - algorytm zach³anny
void Solutions::sa_setup_naive()
{
	TT = 100000;
	line.clear();
	current = ext / 2;
	naive_search();
	sa_first();
}

//Ustawianie parametrów symulowanego wyrza¿ania - algorytm zach³anny
void Solutions::annealing_setup()
{
	TT = 1000000;
	line.clear();
	result = limits;
	current = ext / 2;
	for (int i = 0; i < ext; i++) line.push_back(i);
	line.push_back(0);
	simulated_annealing();
}

//Ustawianie parametrów symulowanego wyrza¿ania
void Solutions::annealing_setup_naive()
{
	TT = 1000000;
	line.clear();
	current = ext / 2;
	naive_search();
	simulated_annealing();
}

//Funkcja szukaj¹ca rozwi¹zania naiwnie - najmniejsza odleg³oœæ od danego miasta
void Solutions::naive_search()
{
	int res = 0, min, index = 0;
	int temp = 0;
	int rem = ext - 1;
	vector<bool> visited(ext);
	for (int i = 1; i < ext; i++) visited[i] = false;
	visited[0] = true;
	line.push_back(0);
	while (rem != 0)
	{
		min = INT_MAX;
		for (int i = 1; i < ext; i++)
		{
			if (!visited[i])
			{
				if (tab[temp][i] < min)
				{
					index = i;
					min = tab[temp][i];
				}
			}
		}
		temp = index;
		line.push_back(index);
		visited[index] = true;
		res = res + min;
		rem--;
	}
	line.push_back(0);
	result = res + tab[index][0];
}

//Funkcja szukaj¹ca rozwi¹zania poprzez tabu search
void Solutions::tabu_search()
{
	int temp;
	int best, index;
	vector<int> proxy;
	for (int i = 0; i < iterations; i++)
	{
		proxy.clear();
		best = INT_MAX;
		for (int j = 0; j < ext; j++) if (current != j) proxy.push_back(j);
		for (int j = 0; j < proxy.size(); j++)
		{
			temp = perform_move(proxy[j]);
			if (tabu[current][proxy[j]] != 0)
			{
				if (temp < result)
				{
					index = proxy[j];
					best = temp;
				}
			}
			else
			{
				if (temp < best)
				{
					index = proxy[j];
					best = temp;
				}
			}
		}
		if (best <= result)
		{
			result = best;
			tabu[line[current]][line[index]] = lock;
			tabu[line[index]][line[current]] = lock;
			if (current == 0)
			{
				temp = line[current];
				line[current] = line[index];
				line[ext] = line[index];
				line[index] = temp;
			}
			else if (index == 0)
			{
				temp = line[index];
				line[index] = line[current];
				line[ext] = line[current];
				line[current] = temp;
			}
			else
			{
				temp = line[index];
				line[index] = line[current];
				line[current] = temp;
			}
			//current = index;
			current = rand() % ext;
		}
		else current = rand() % ext;
		for (int i = 0; i < ext; i++)
		{
			for (int j = 0; j < ext; j++)
			{
				if (tabu[i][j] != 0) tabu[i][j]--;
			}
		}
	}
}

//Próbana wersja algorytmu SA
void Solutions::sa_first()
{
	int temp;
	int best, index;
	double chance, prob;
	vector<int> proxy;
	while (TT > 0)
	{
		proxy.clear();
		best = INT_MAX;
		for (int i = 0; i < ext; i++) if (current != i) proxy.push_back(i);
		for (int i = 0; i < proxy.size(); i++)
		{
			temp = perform_move(proxy[i]);
			if (temp < best)
			{
				best = temp;
				index = proxy[i];
			}
		}
		if (best >= result)
		{
			chance = (rand() % 99) / (double)100;
			prob = pow(2.76, -double((best - result) / TT));
			prob = min(1, prob);
			if (chance <= prob)
			{
				TT = TT - 1;
				current = rand() % ext;
				continue;
			}
		}
		if (current == 0)
		{
			temp = line[current];
			line[current] = line[index];
			line[ext] = line[index];
			line[index] = temp;
		}
		else if (index == 0)
		{
			temp = line[index];
			line[index] = line[current];
			line[ext] = line[current];
			line[current] = temp;
		}
		else
		{
			temp = line[index];
			line[index] = line[current];
			line[current] = temp;
		}
		result = best;
		TT = TT - 1;
	}
	while (true)
	{
		proxy.clear();
		best = INT_MAX;
		for (int i = 0; i < ext; i++) if (current != i) proxy.push_back(i);
		for (int i = 0; i < proxy.size(); i++)
		{
			temp = perform_move(proxy[i]);
			if (temp < best)
			{
				best = temp;
				index = proxy[i];
			}
		}
		if (best < result)
		{
			if (index == 0)
			{
				temp = line[current];
				line[current] = line[index];
				line[ext] = temp;
				line[index] = temp;
			}
			else if (current == 0)
			{
				temp = line[index];
				line[index] = line[current];
				line[current] = temp;
				line[ext] = temp;
			}
			else
			{
				temp = line[index];
				line[index] = line[current];
				line[current] = temp;
			}
			current = index;
			result = best;
		}
		else return;
	}
}

//Simulated anneling  -obliczenia
void Solutions::simulated_annealing()
{
	int temp;
	int best;
	int next;
	double chance, prob;
	float gem = 0.9;
	vector<int> proxy;
	while (TT > 0.0001)
	{
		for (int i = 0; i < (ext / 3); i++)
		{
			//current = rand() % ext;
			proxy.clear();
			for (int i = 0; i < ext; i++) if (current != i) proxy.push_back(i);
			next = rand() % (ext - 1);
			best = perform_move(proxy[next]);
			if (best >= result)
			{
				chance = (rand() % 99) / (double)100;
				prob = pow(2.76, -double((best - result) / TT));
				prob = min(1, prob);
				if (chance >= prob)
				{
					current = rand() % ext;
					continue;
				}
			}
			if (current == 0)
			{
				temp = line[current];
				line[current] = line[proxy[next]];
				line[ext] = line[proxy[next]];
				line[proxy[next]] = temp;
			}
			else if (proxy[next] == 0)
			{
				temp = line[proxy[next]];
				line[proxy[next]] = line[current];
				line[ext] = line[current];
				line[current] = temp;
			}
			else
			{
				temp = line[proxy[next]];
				line[proxy[next]] = line[current];
				line[current] = temp;
			}
			result = best;
			current = proxy[next];
		}
		TT = TT * gem;
		if (TT < 10000) gem = 0.999;
		else if (TT < 1000000) gem = 0.99;
	}
	int index;
	while (true)
	{
		proxy.clear();
		best = INT_MAX;
		for (int i = 0; i < ext; i++) if (current != i) proxy.push_back(i);
		for (int i = 0; i < proxy.size(); i++)
		{
			temp = perform_move(proxy[i]);
			if (temp < best)
			{
				best = temp;
				index = proxy[i];
			}
		}
		if (best < result)
		{
			if (index == 0)
			{
				temp = line[current];
				line[current] = line[index];
				line[ext] = temp;
				line[index] = temp;
			}
			else if (current == 0)
			{
				temp = line[index];
				line[index] = line[current];
				line[current] = temp;
				line[ext] = temp;
			}
			else
			{
				temp = line[index];
				line[index] = line[current];
				line[current] = temp;
			}
			//current = rand() % ext;
			current = index;
			result = best;
		}
		else return;
	}
}

//Wykonanie ruchu zamiany miast
int Solutions::perform_move(int next)
{
	int finall;
	int tecost = result;
	if (next == 0)
	{
		if (current == 1)
		{
			finall = tecost - tab[line[next]][line[current]] - tab[line[current]][line[current + 1]] - tab[line[ext - 1]][line[next]];
			finall = finall + tab[line[current]][line[next]] + tab[line[next]][line[current + 1]] + tab[line[ext - 1]][line[current]];
		}
		else if (current == (ext - 1))
		{
			finall = tecost - tab[line[next]][line[next + 1]] - tab[line[current - 1]][line[current]] - tab[line[current]][line[next]];
			finall = finall + tab[line[current]][line[next + 1]] + tab[line[current - 1]][line[next]] + tab[line[next]][line[current]];
		}
		else
		{
			finall = tecost - tab[line[next]][line[next + 1]] - tab[line[current - 1]][line[current]] - tab[line[current]][line[current + 1]] - tab[line[ext - 1]][line[next]];
			finall = finall + tab[line[current]][line[next + 1]] + tab[line[current - 1]][line[next]] + tab[line[next]][line[current + 1]] + tab[line[ext - 1]][line[current]];
		}
	}
	else if (current == 0)
	{
		if (next == 1)
		{
			finall = tecost - tab[line[current]][line[next]] - tab[line[next]][line[next + 1]] - tab[line[ext - 1]][line[current]];
			finall = finall + tab[line[next]][line[current]] + tab[line[current]][line[next + 1]] + tab[line[ext - 1]][line[next]];
		}
		else if (next == (ext - 1))
		{
			finall = tecost - tab[line[current]][line[current + 1]] - tab[line[next - 1]][line[next]] - tab[line[next]][line[current]];
			finall = finall + tab[line[next]][line[current + 1]] + tab[line[next - 1]][line[current]] + tab[line[current]][line[next]];
		}
		else
		{
			finall = tecost - tab[line[current]][line[current + 1]] - tab[line[next - 1]][line[next]] - tab[line[next]][line[next + 1]] - tab[line[ext - 1]][line[current]];
			finall = finall + tab[line[next]][line[current + 1]] + tab[line[next - 1]][line[current]] + tab[line[current]][line[next + 1]] + tab[line[ext - 1]][line[next]];
		}
	}
	else
	{
		if ((next + 1) == current)
		{
			finall = tecost - tab[line[next - 1]][line[next]] - tab[line[next]][line[current]] - tab[line[current]][line[current + 1]];
			finall = finall + tab[line[next - 1]][line[current]] + tab[line[current]][line[next]] + tab[line[next]][line[current + 1]];
		}
		else if ((next - 1) == current)
		{
			finall = tecost - tab[line[current - 1]][line[current]] - tab[line[current]][line[next]] - tab[line[next]][line[next + 1]];
			finall = finall + tab[line[current - 1]][line[next]] + tab[line[next]][line[current]] + tab[line[current]][line[next + 1]];
		}
		else
		{
			finall = tecost - tab[line[current - 1]][line[current]] - tab[line[current]][line[current + 1]] - tab[line[next - 1]][line[next]] - tab[line[next]][line[next + 1]];
			finall = finall + tab[line[current - 1]][line[next]] + tab[line[next]][line[current + 1]] + tab[line[next - 1]][line[current]] + tab[line[current]][line[next + 1]];
		}
	}
	return finall;
}

//Gettery i settery
int Solutions::get_result() { return result; }