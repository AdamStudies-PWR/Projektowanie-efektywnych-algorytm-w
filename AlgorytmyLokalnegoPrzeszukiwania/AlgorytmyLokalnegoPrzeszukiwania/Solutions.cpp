//Implementacja funkcji z klasy Solutions
#include "pch.h"
#include "Solutions.h"

//Funkcja szukająca rozwiązania naiwnie - najmniejsza odległość od danego miasta
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

//Rekurencyjne rozwinięcie tabu searcha
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

//Rekurencyjne rozwinięcie tabu searcha
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

//Funkcja szukająca rozwiązania poprzez tabu search
void Solutions::tabu_search()
{
	//int x, y;
	int cost, temp;
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
			if (proxy[j] == 0)
			{
				if (current == 1)
				{
					temp = cost - tab[line[0]][line[1]] - tab[line[1]][line[2]] - tab[line[ext - 1]][line[ext]];
					temp = temp + tab[line[1]][line[0]] + tab[line[0]][line[2]] + tab[line[ext - 1]][line[1]];
				}
				else if (current == (ext - 1))
				{
					temp = cost - tab[line[0]][line[1]] - tab[line[ext - 2]][line[ext - 1]] - tab[line[ext - 1]][line[ext]];
					temp = temp + tab[line[ext - 1]][line[1]] + tab[line[ext - 2]][line[0]] + tab[line[0]][line[ext - 1]];
				}
				else
				{
					temp = cost - tab[line[0]][line[1]] - tab[line[ext - 1]][line[ext]] - tab[line[current - 1]][line[current]] - tab[line[current]][line[current + 1]];
					temp = temp + tab[line[current]][line[1]] + tab[line[ext - 1]][line[current]] + tab[line[current - 1]][line[0]] + tab[line[0]][line[current + 1]];
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


//Funkcja obsługująca Sumulowane wyzarzanie 
void Solutions::annealing_setup()
{
	TT = 10;
	line.clear();
	result = limits;
	current = ext / 2;
	for (int i = 0; i < ext; i++) line.push_back(i);
	line.push_back(0);
	simulated_annealing();
}

void Solutions::simulated_annealing()
{
	int cost, temp;
	int best, index, prev;
	double chance, prob;
	vector<int> proxy;
	while(TT > 0)
	{
		best = INT_MAX;
		cost = result;
		for (int j = 0; j < ext; j++) if (current != j && j != prev) proxy.push_back(j);
		for (int j = 0; j < proxy.size(); j++)
		{
			if (proxy[j] == 0)
			{
				if (current == 1)
				{
					temp = cost - tab[line[0]][line[1]] - tab[line[1]][line[2]] - tab[line[ext - 1]][line[ext]];
					temp = temp + tab[line[1]][line[0]] + tab[line[0]][line[2]] + tab[line[ext - 1]][line[1]];
				}
				else if (current == (ext - 1))
				{
					temp = cost - tab[line[0]][line[1]] - tab[line[ext - 2]][line[ext - 1]] - tab[line[ext - 1]][line[ext]];
					temp = temp + tab[line[ext - 1]][line[1]] + tab[line[ext - 2]][line[0]] + tab[line[0]][line[ext - 1]];
				}
				else
				{
					temp = cost - tab[line[0]][line[1]] - tab[line[ext - 1]][line[ext]] - tab[line[current - 1]][line[current]] - tab[line[current]][line[current + 1]];
					temp = temp + tab[line[current]][line[1]] + tab[line[ext - 1]][line[current]] + tab[line[current - 1]][line[0]] + tab[line[0]][line[current + 1]];
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
			}
			if (temp < best) best = temp, index = proxy[j];
		}
		if (best < result)
		{
			prev = current;
			result = best;
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
		}
		else
		{
			chance = (rand() % 99) / (double)100;
			//cout << "\nChance: " << chance;
			prob = pow(2.76, -double((best - result)/TT)) * 100;
			//cout << "\nProb1: " << result;
			prob = min(1, prob);
			//cout << "\nProb2: " << best;
			if (chance < prob)
			{
				//cout << "\nIT WORKS UWU OWO";
				result = best;
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
			}
			//else cout << "\nNOPE";
		}
		TT = TT - 0.1;
		proxy.clear();
	}
	while (true)
	{
		best = INT_MAX;
		cost = result;
		for (int j = 1; j < ext; j++) if (current != j) proxy.push_back(j);
		for (int j = 0; j < proxy.size(); j++)
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
		if (best < result)
		{
			result = best;
			temp = line[index];
			line[index] = line[current];
			line[current] = temp;
		}
		else return;
		proxy.clear();
	}
}

/*//Utility
void Solutions::quick_sort(vector<Node*> &array, int left, int right)
{
	if (left < right)
	{
		Node *temp;
		int index = left + (right - left)/2;
		int part = array[index]->cost;
		int i = left, j = right;
		while (i <= j)
		{
			while (array[i]->cost > part) i++;
			while (array[j]->cost < part) j--;
			if (i <= j)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
				i++;
				j--;
			}
		}
		part = i;
		quick_sort(array, left, part - 1);
		quick_sort(array, part, right);
	}
}*/

//Gettery i settery
int Solutions::get_result() { return result; }