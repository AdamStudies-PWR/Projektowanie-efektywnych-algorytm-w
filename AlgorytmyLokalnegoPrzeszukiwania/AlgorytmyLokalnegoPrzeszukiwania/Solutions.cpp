//Implementacja funkcji z klasy Solutions
#include "pch.h"
#include "Solutions.h"

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
		line.push_back(index);
		visited[index] = true;
		res = res + min;
		rem--;
	}
	line.push_back(0);
	result = res + tab[index][0];
}

//Rekurencyjne rozwiniêcie tabu searcha
void Solutions::tabu_setup()
{
	line.clear();
	result = limits;
	current = ext/2;
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

//Funkcja szukaj¹ca rozwi¹zania poprzez tabu search
void Solutions::tabu_search()
{
	//int x, y;
	int cost, temp;
	int safety;
	int best, index;
	vector<int> proxy;
	for (int i = 0; i < iterations; i++)
	{
		/*cout << "\nCurrent: " << current << ", wskzaujena: " << line[current] << ", Result: " << result <<"\nOrder: ";
		for (int j = 0; j < line.size(); j++) cout << line[j] << ", ";
		_getche();*/
		best = INT_MAX;
		cost = result;
		/*for (x = (current - 1), y = (current + 1); x > (current - 4); x--, y++)
		{
			if (x > 0) proxy.push_back(x);
			if (y < (line.size() - 1)) proxy.push_back(y);
		}*/
		for (int j = 0; j < ext; j++) if (tabu[current][j] == 0 && current != j && tabu[j][current] == 0) proxy.push_back(j);
		for (int j = 0; j < proxy.size(); j++)
		{
			if (proxy[j] == 0 || current == 0)
			{
				if (current == 0) safety = proxy[j], proxy[j] = 0;
				else safety = current;
				if (safety == 1)
				{
					temp = cost - tab[line[0]][line[1]] - tab[line[1]][line[2]] - tab[line[ext - 1]][line[ext]];
					temp = temp + tab[line[1]][line[0]] + tab[line[0]][line[2]] + tab[line[ext - 1]][line[1]];
				}
				else if (safety == (ext - 1))
				{
					temp = cost - tab[line[0]][line[1]] - tab[line[ext - 2]][line[ext - 1]] - tab[line[ext - 1]][line[ext]];
					temp = temp + tab[line[ext - 1]][line[1]] + tab[line[ext - 2]][line[0]] + tab[line[0]][line[ext - 1]];
				}
				else
				{
					temp = cost - tab[line[0]][line[1]] - tab[line[ext - 1]][line[ext]] - tab[line[safety - 1]][line[safety]] - tab[line[safety]][line[safety + 1]];
					temp = temp + tab[line[safety]][line[1]] + tab[line[ext - 1]][line[safety]] + tab[line[safety - 1]][line[0]] + tab[line[0]][line[safety + 1]];
				}
			}
			else
			{
				if ((proxy[j] + 1) == current)
				{
					temp = cost - tab[line[proxy[j] - 1]][line[proxy[j]]] - tab[line[proxy[j]]][line[current]] - tab[line[current]][line[current + 1]];
					temp = temp + tab[line[proxy[j] - 1]][line[current]] + tab[line[current]][line[proxy[j]]] + tab[line[proxy[j]]][line[current + 1]];
				}
				else if ((proxy[j] - 1) == current)
				{
					temp = cost - tab[line[current - 1]][line[current]] - tab[line[current]][line[proxy[j]]] - tab[line[proxy[j]]][line[proxy[j] + 1]];
					temp = temp + tab[line[current - 1]][line[proxy[j]]] + tab[line[proxy[j]]][line[current]] + tab[line[current]][line[proxy[j] + 1]];
				}
				else
				{
					temp = cost - tab[line[proxy[j] - 1]][line[proxy[j]]] - tab[line[proxy[j]]][line[proxy[j] + 1]] - tab[line[current - 1]][line[current]] - tab[line[current]][line[current + 1]];
					temp = temp + tab[line[proxy[j] - 1]][line[current]] + tab[line[current]][line[proxy[j] + 1]] + tab[line[current - 1]][line[proxy[j]]] + tab[line[proxy[j]]][line[current + 1]];
				}
				if (temp < best) best = temp, index = proxy[j];
			}
		}
		if (best < result)
		{
			/////////
			//cout << "\nCurrent: " << current << ", wskzaujena: " << line[current] << ", Result: " << result << "\nOrder: ";
			//for (int j = 0; j < line.size(); j++) cout << line[j] << ", ";
			//////////
			result = best;
			tabu[line[current]][line[index]] = lock;
			tabu[line[index]][line[current]] = lock;
			temp = line[index];
			if (index != 0)
			{
				line[index] = line[current];
				line[current] = temp;
			}
			else
			{
				line[index] = line[current];
				line[ext] = line[current];
				line[current] = temp;
			}
			current = index;
			//current = index;
			/////////
			//cout << "\nCurrent: " << current << ", wskzaujena: " << line[current] << ", Result: " << result << "\nOrder: ";
			//for (int j = 0; j < line.size(); j++) cout << line[j] << ", ";
			//////////
		}
		else current = (rand() % (ext - 1)) + 1;
		proxy.clear();
		for (int i = 0; i < ext; i++)
		{
			for (int j = 0; j < ext; j++)
			{
				if (tabu[i][j] != 0) tabu[i][j]--;
			}
		}
	}
}

//Ustawianie parametrów symulowanego wyrza¿ania
void Solutions::annealing_setup()
{
	TT = 1000;
	line.clear();
	result = limits;
	current = ext / 2;
	for (int i = 0; i < ext; i++) line.push_back(i);
	line.push_back(0);
	simulated_annealing();
}

//Symulowane wyrza¿anie obliczenia
void Solutions::simulated_annealing()
{
    int temp;
	int best, index, prev = -1;
	double chance, prob;
	vector<int> proxy;
	while (TT > 0)
	{
		proxy.clear();
		best = INT_MAX;
		for (int i = 0; i < ext; i++) if (current != i && i != prev) proxy.push_back(i);
		//cout << "\nSize: " << proxy.size() << ", Result: " << result;
		for (int i = 0; i < proxy.size(); i++)
		{
			temp = perform_move(proxy[i]);
			if (temp < best)
			{
				best = temp;
				index = i;
			}
		}
		if (best > result)
		{
			chance = (rand() % 99) / (double)100;
			prob = pow(2.76, -double((best - result) / TT));
			prob = min(1, prob);
			//cout << "\nCH: " << chance << " PR: " << prob;
			//if(TT < 10000) continue;
			if (chance >= prob)
			{
				current = index;
				TT = TT - 1;
				continue;
			}
		}
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
		prev = index;
		result = best;
		TT = TT - 1;
		//cout << endl;
		//for (int j = 0; j < line.size(); j++) cout << line[j] << ", ";
	}
	while (true)
	{
		best = INT_MAX;
		for (int i = 0; i < ext; i++) if (current != i && i != prev) proxy.push_back(i);
		for (int i = 0; i < proxy.size(); i++)
		{
			temp = perform_move(proxy[i]);
			if (temp < best)
			{
				best = temp;
				index = i;
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
		proxy.clear();
	}
}

/*void Solutions::simulated_annealing()
{
	int next;
	int best;
	int temp;
	///
	double chance;
	double prob;
	///
	while (TT > 0)
	{
		do
		{
			next = (rand() % (ext - 1));
		} while (next == current);
		best = perform_move(next);
		if (best > result)
		{
			TT = TT - 1;
			chance = (rand() % 99) / (double)100;
			prob = pow(2.76, -double((best - result) / TT));
			prob = min(1, prob);
			//cout << "\nCH: " << chance << " PR: " << prob;
			//if(TT < 10000) continue;
			if (chance >= prob) continue;
		}
		if (next == 0)
		{
			temp = line[current];
			line[current] = line[next];
			line[ext] = temp;
			line[next] = temp;
		}
		else if (current == 0)
		{
			temp = line[next];
			line[next] = line[current];
			line[current] = temp;
			line[ext] = temp;
		}
		else
		{
			temp = line[next];
			line[next] = line[current];
			line[current] = temp;
		}
		result = best;
		TT = TT - 1;
	}
}*/

//Wykonanie ruchu zamiany miast
int Solutions::perform_move(int next)
{
	int finall;
	if (next == 0)
	{
		if (current == 1)
		{
			finall = result - tab[line[next]][line[current]] - tab[line[current]][line[current + 1]] - tab[line[ext - 1]][line[next]];
			finall = finall + tab[line[current]][line[next]] + tab[line[next]][line[current + 1]] + tab[line[ext - 1]][line[current]];
		}
		else if (current == (ext - 1))
		{
			finall = result - tab[line[next]][line[next + 1]] - tab[line[current - 1]][line[current]] - tab[line[current]][line[next]];
			finall = finall + tab[line[current]][line[next + 1]] + tab[line[current - 1]][line[next]] + tab[line[next]][line[current]];
		}
		else
		{
			finall = result - tab[line[next]][line[next + 1]] - tab[line[current - 1]][line[current]] - tab[line[current]][line[current + 1]] - tab[line[ext - 1]][line[next]];
			finall = finall + tab[line[current]][line[next + 1]] + tab[line[current - 1]][line[next]] + tab[line[next]][line[current + 1]] + tab[line[ext - 1]][line[current]];
		}
	}
	else if (current == 0)
	{
		if (next == 1)
		{
			finall = result - tab[line[current]][line[next]] - tab[line[next]][line[next + 1]] - tab[line[ext - 1]][line[current]];
			finall = finall + tab[line[next]][line[current]] + tab[line[current]][line[next + 1]] + tab[line[ext - 1]][line[next]];
		}
		else if (next == (ext - 1))
		{
			finall = result - tab[line[current]][line[current + 1]] - tab[line[next - 1]][line[next]] - tab[line[next]][line[current]];
			finall = finall + tab[line[next]][line[current + 1]] + tab[line[next - 1]][line[current]] + tab[line[current]][line[next]];
		}
		else
		{
			finall = result - tab[line[current]][line[current + 1]] - tab[line[next - 1]][line[next]] - tab[line[next]][line[next + 1]] - tab[line[ext - 1]][line[current]];
			finall = finall + tab[line[next]][line[current + 1]] + tab[line[next - 1]][line[current]] + tab[line[current]][line[next + 1]] + tab[line[ext - 1]][line[next]];
		}
	}
	else
	{
		if (next == (current - 1))
		{
			finall = result - tab[line[next - 1]][line[next]] - tab[line[next]][line[current]] - tab[line[current]][line[current + 1]];
			finall = finall + tab[line[next - 1]][line[current]] + tab[line[current]][line[next]] + tab[line[next]][line[current + 1]];
		}
		else if (next == (current + 1))
		{
			finall = result - tab[line[current - 1]][line[current]] - tab[line[current]][line[next]] - tab[line[next]][line[next + 1]];
			finall = finall + tab[line[current - 1]][line[next]] + tab[line[next]][line[current]] + tab[line[current]][line[next + 1]];
		}
		else
		{
			finall = result - tab[line[next - 1]][line[next]] - tab[line[next]][line[next + 1]] - tab[line[current - 1]][line[current]] - tab[line[current]][line[current + 1]];
			finall = finall + tab[line[next - 1]][line[current]] + tab[line[current]][line[next + 1]] + tab[line[current - 1]][line[next]] + tab[line[next]][line[current + 1]];
		}
	}
	return finall;
}

//Gettery i settery
int Solutions::get_result() { return result; }