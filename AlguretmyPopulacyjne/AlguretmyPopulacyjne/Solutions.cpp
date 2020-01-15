//Implementacja funkcji z klasy Solutions
#include "pch.h"
#include "Solutions.h"

//Funkcja inicuj¹j¹ca dzia³anie algorytmu genetycznego
void Solutions::genetic_setup(int psize, bool mode)
{
	population = psize;
	result = INT_MAX;
	int *path = new int;
	vector<Genes*> pops(population);
	pops[0] = new Genes(natural_route(path), *path);
	pops[1] = new Genes(naive_route(path), *path);
	for (int i = 2; i < population; i++)
	{
		pops[i] = new Genes(random_route(path), *path);
	}
	if(mode) genetic_algorithm(pops);
	else genetic_algorithm_10(pops);
	delete path;
}

//G³ówna pêtla algorytmu genetycznego
void Solutions::genetic_algorithm(vector<Genes*> pops)
{
	vector<Genes*> temp;
	vector<Genes*> newpop;
	int p1, p2;
	for (int i = 0; i < sim; i++)
	{
		quicksort(pops, 0, (population - 1));
		newpop.clear();
		/**
		system("cls");
		cout << "Iteracja: " << i << " z: " << sim << endl;
		for (int i = 0; i < population; i++)
		{
			cout << "\nRozmiar: " << pops[i]->fitnes << "\nTrasa: ";
			for (int j = 0; j < pops[i]->path.size(); j++)
			{
				cout << pops[i]->path[j] << ", ";
			}
		}
		_getche();
		/**/
		if (pops[0]->fitnes < result) result = pops[0]->fitnes;
		for (int j = 0; j < (population / 2); j++)
		{
			temp.clear();
			p1 = rand() % (population / 2);
			do
			{
				p2 = rand() % (population / 2);
			} while (p1 == p2);
			temp = repopulate(pops[p1], pops[p2]);
			newpop.push_back(temp[0]);
			newpop.push_back(temp[1]);
		}
		for (int j = 0; j < population; j++) delete pops[j];
		pops.clear();
		pops = newpop;
	}
	for (int j = 0; j < population; j++) delete pops[j];
	pops.clear();
}

//G³ówna pêtla algorytmu genetycznego wersja 2
void Solutions::genetic_algorithm_10(vector<Genes*> pops)
{
	vector<Genes*> temp;
	vector<Genes*> newpop;
	int p1, p2;
	int elyta = 0.1 * population;
	if ((elyta % 2) != 0) elyta++;
	for (int i = 0; i < sim; i++)
	{
		quicksort(pops, 0, (population - 1));
		newpop.clear();
		/**
		system("cls");
		cout << "Iteracja: " << i << " z: " << sim << endl;
		for (int i = 0; i < population; i++)
		{
			cout << "\nRozmiar: " << pops[i]->fitnes << "\nTrasa: ";
			for (int j = 0; j < pops[i]->path.size(); j++)
			{
				cout << pops[i]->path[j] << ", ";
			}
		}
		_getche();
		/**/
		if (pops[0]->fitnes < result) result = pops[0]->fitnes;
		for (int j = 0; j < elyta; j++) newpop.push_back(pops[j]);
		for (int j = 0; j < ((population - elyta) / 2); j++)
		{
			temp.clear();
			p1 = rand() % (population / 2);
			do
			{
				p2 = rand() % (population / 2);
			} while (p1 == p2);
			temp = repopulate(pops[p1], pops[p2]);
			newpop.push_back(temp[0]);
			newpop.push_back(temp[1]);
		}
		for (int j = (elyta); j < population; j++) delete pops[j];
		pops.clear();
		pops = newpop;
	}
	for (int j = 0; j < population; j++) delete pops[j];
	pops.clear();
}

//Funkcja tworz¹ca nowe pokolenie
vector<Genes*> Solutions::repopulate(Genes *p1, Genes *p2)
{
	vector<Genes*> result;
	int mutation = rand() % 100;
	if (mutation != 1)
	{
		int e1;
		int div1 = rand() % ext;
		if ((div1 + 2) >= ext) e1 = div1 - 2;
		else if ((div1 - 2) < 0) e1 = div1 + 2;
		else
		{
			e1 = rand() % 2;
			if (e1 == 0) e1 = div1 + 2;
			else e1 = div1 - 2;
		}

		Genes *t1;
		Genes *t2;
		int cost1 = 0;
		int cost2 = 0;
		vector<bool> visited1(ext);
		vector<bool> visited2(ext);
		vector<int> path1(ext + 1);
		vector<int> path2(ext + 1);
		for (int i = 0; i < ext; i++)
		{
			visited1[i] = false;
			visited2[i] = false;
		}
		if (e1 < div1)
		{
			path1[0] = p2->path[e1];
			path1[1] = p2->path[e1 + 1];
			path1[2] = p2->path[e1 + 2];

			path2[0] = p1->path[e1];
			path2[1] = p1->path[e1 + 1];
			path2[2] = p1->path[e1 + 2];
		}
		else
		{
			path1[0] = p2->path[div1];
			path1[1] = p2->path[div1 + 1];
			path1[2] = p2->path[div1 + 2];

			path2[0] = p1->path[div1];
			path2[1] = p1->path[div1 + 1];
			path2[2] = p1->path[div1 + 2];
		}
		visited1[path1[0]] = true;
		visited1[path1[1]] = true;
		visited1[path1[2]] = true;
		visited2[path2[0]] = true;
		visited2[path2[1]] = true;
		visited2[path2[2]] = true;
		cost1 = cost1 + tab[path1[0]][path1[1]] + tab[path1[1]][path1[2]];
		cost2 = cost2 + tab[path2[0]][path2[1]] + tab[path2[1]][path2[2]];

		int i1, i2;
		if (e1 < div1) i1 = div1 + 1, i2 = i1;
		else i1 = e1 + 1, i2 = i1;
		for (int i = 3; i < ext; i++)
		{
			if (i2 >= ext) i2 = 0;
			if (i1 >= ext) i1 = 0;
			while (visited1[p1->path[i1]])
			{
				i1++;
				if (i1 >= ext) i1 = 0;
			};
			path1[i] = p1->path[i1];
			cost1 = cost1 + tab[path1[i - 1]][path1[i]];
			visited1[path1[i]] = true;

			while (visited2[p2->path[i2]])
			{
				i2++;
				if (i2 >= ext) i2 = 0;
			};
			path2[i] = p2->path[i2];
			cost2 = cost2 + tab[path2[i - 1]][path2[i]];
			visited2[path2[i]] = true;
			i1++;
			i2++;
		}
		path1[ext] = path1[0];
		cost1 = cost1 + tab[path1[ext - 1]][path1[ext]];
		path2[ext] = path2[0];
		cost2 = cost2 + tab[path2[ext - 1]][path2[ext]];
		result.push_back(new Genes(path1, cost1));
		result.push_back(new Genes(path2, cost2));
	}
	else
	{
		int *path = new int;
		result.push_back(new Genes(random_route(path), *path));
		result.push_back(new Genes(random_route(path), *path));
		delete path;
	}
	return result;
}

//Gettery i settery

//Funkcja zwracaj¹ca wartoœæ koñcow¹ algorytmu
int Solutions::getResult() { return result; }

int Solutions::getSim() { return sim; }

void Solutions::setSim(int iter) { sim = iter; }

//Generowanie pocz¹tkowej trasy

//Trasa naturalna
vector<int> Solutions::natural_route(int *path)
{
	vector<int> line;
	*path = limits;
	for (int i = 0; i < ext; i++) line.push_back(i);
	line.push_back(0);
	return line;
}

//Trasa naturalna
vector<int> Solutions::naive_route(int *path)
{
	vector<int> line;
	*path = 0;
	int min, index = 0;
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
		*path = *path + min;
		rem--;
	}
	line.push_back(0);
	*path = *path + tab[index][0];
	return line;
}

//Trasa losowa
vector<int> Solutions::random_route(int *path)
{
	vector<int> line;
	*path = 0;
	int index;
	int fate, counter;
	int rem = ext;
	int temp = rand() % rem;
	int last = temp;
	rem--;
	vector<bool> visited(ext);
	for (int i = 0; i < ext; i++) visited[i] = false;
	visited[temp] = true;
	line.push_back(temp);
	while (rem != 0)
	{
		fate = rand() % rem + 1;
		rem--;
		for (int i = 0, counter = 0; i < ext; i++)
		{
			if (visited[i]) continue;
			counter++;
			index = i;
			if (counter == fate) break;
		}
		line.push_back(index);
		visited[index] = true;
		*path = *path + tab[temp][index];
		temp = index;
	}
	line.push_back(last);
	*path = *path + tab[index][last];
	return line;
}

//Sortowanie populacji
void Solutions::quicksort(vector<Genes*> &pops, int low, int high)
{
	Genes* temp;
	if (low < high)
	{
		int pivot = pops[high]->fitnes;
		int smol = low;
		for (int i = low; i <= (high - 1); i++)
		{
			if (pops[i]->fitnes <= pivot)
			{	
				temp = pops[i];
				pops[i] = pops[smol];
				pops[smol] = temp;
				smol++;
			}
		}
		temp = pops[smol];
		pops[smol] = pops[high];
		pops[high] = temp;
		quicksort(pops, low, smol - 1);
		quicksort(pops, smol + 1, high);
	}
}

//Funkcja testuj¹ca
void Solutions::testing(int size, bool pop[], bool sizes[])
{
	system("cls");
	if (results != nullptr)
	{
		for (int i = 0; i < 120; i++)
		{
			delete[] results[i];
		}
		delete[] results;
	}
	results = new double*[120];
	for (int i = 0; i < 120; i++)
	{
		results[i] = new double[size];
	}
	for (int i = 0; i < size; i++)
	{
		cout << i << endl;
		if (pop[0])
		{
			if (sizes[0])
			{
				this->setSim(100);
				count.StartFileCounter();
				this->genetic_setup(50, true);
				results[0][i] = count.GetCounter();
				results[1][i] = result;
				count.StartFileCounter();
				this->genetic_setup(50, false);
				results[2][i] = count.GetCounter();
				results[3][i] = result;
			}
			if (sizes[1])
			{
				this->setSim(1000);
				count.StartFileCounter();
				this->genetic_setup(50, true);
				results[4][i] = count.GetCounter();
				results[5][i] = result;
				count.StartFileCounter();
				this->genetic_setup(50, false);
				results[6][i] = count.GetCounter();
				results[7][i] = result;
			}
			if (sizes[2])
			{
				this->setSim(2000);
				count.StartFileCounter();
				this->genetic_setup(50, true);
				results[8][i] = count.GetCounter();
				results[9][i] = result;
				count.StartFileCounter();
				this->genetic_setup(50, false);
				results[10][i] = count.GetCounter();
				results[11][i] = result;
			}
			if (sizes[3])
			{
				this->setSim(5000);
				count.StartFileCounter();
				this->genetic_setup(50, true);
				results[12][i] = count.GetCounter();
				results[13][i] = result;
				count.StartFileCounter();
				this->genetic_setup(50, false);
				results[14][i] = count.GetCounter();
				results[15][i] = result;
			}
			if (sizes[4])
			{
				this->setSim(10000);
				count.StartFileCounter();
				this->genetic_setup(50, true);
				results[16][i] = count.GetCounter();
				results[17][i] = result;
				count.StartFileCounter();
				this->genetic_setup(50, false);
				results[18][i] = count.GetCounter();
				results[19][i] = result;
			}
		}
		if (pop[1])
		{
			if (sizes[0])
			{
				this->setSim(100);
				count.StartFileCounter();
				this->genetic_setup(100, true);
				results[20][i] = count.GetCounter();
				results[21][i] = result;
				count.StartFileCounter();
				this->genetic_setup(100, false);
				results[22][i] = count.GetCounter();
				results[23][i] = result;
			}
			if (sizes[1])
			{
				this->setSim(1000);
				count.StartFileCounter();
				this->genetic_setup(100, true);
				results[24][i] = count.GetCounter();
				results[25][i] = result;
				count.StartFileCounter();
				this->genetic_setup(100, false);
				results[26][i] = count.GetCounter();
				results[27][i] = result;
			}
			if (sizes[2])
			{
				this->setSim(2000);
				count.StartFileCounter();
				this->genetic_setup(100, true);
				results[28][i] = count.GetCounter();
				results[29][i] = result;
				count.StartFileCounter();
				this->genetic_setup(100, false);
				results[30][i] = count.GetCounter();
				results[31][i] = result;
			}
			if (sizes[3])
			{
				this->setSim(5000);
				count.StartFileCounter();
				this->genetic_setup(100, true);
				results[32][i] = count.GetCounter();
				results[33][i] = result;
				count.StartFileCounter();
				this->genetic_setup(100, false);
				results[34][i] = count.GetCounter();
				results[35][i] = result;
			}
			if (sizes[4])
			{
				this->setSim(10000);
				count.StartFileCounter();
				this->genetic_setup(100, true);
				results[36][i] = count.GetCounter();
				results[37][i] = result;
				count.StartFileCounter();
				this->genetic_setup(100, false);
				results[38][i] = count.GetCounter();
				results[39][i] = result;
			}
		}
		if (pop[2])
		{
			if (sizes[0])
			{
				this->setSim(100);
				count.StartFileCounter();
				this->genetic_setup(200, true);
				results[40][i] = count.GetCounter();
				results[41][i] = result;
				count.StartFileCounter();
				this->genetic_setup(200, false);
				results[42][i] = count.GetCounter();
				results[43][i] = result;
			}
			if (sizes[1])
			{
				this->setSim(1000);
				count.StartFileCounter();
				this->genetic_setup(200, true);
				results[44][i] = count.GetCounter();
				results[45][i] = result;
				count.StartFileCounter();
				this->genetic_setup(200, false);
				results[46][i] = count.GetCounter();
				results[47][i] = result;
			}
			if (sizes[2])
			{
				this->setSim(2000);
				count.StartFileCounter();
				this->genetic_setup(200, true);
				results[48][i] = count.GetCounter();
				results[49][i] = result;
				count.StartFileCounter();
				this->genetic_setup(200, false);
				results[50][i] = count.GetCounter();
				results[51][i] = result;
			}
			if (sizes[3])
			{
				this->setSim(5000);
				count.StartFileCounter();
				this->genetic_setup(200, true);
				results[52][i] = count.GetCounter();
				results[53][i] = result;
				count.StartFileCounter();
				this->genetic_setup(200, false);
				results[54][i] = count.GetCounter();
				results[55][i] = result;
			}
			if (sizes[4])
			{
				this->setSim(10000);
				count.StartFileCounter();
				this->genetic_setup(200, true);
				results[56][i] = count.GetCounter();
				results[57][i] = result;
				count.StartFileCounter();
				this->genetic_setup(200, false);
				results[58][i] = count.GetCounter();
				results[59][i] = result;
			}
		}
		if (pop[3])
		{
			if (sizes[0])
			{
				this->setSim(100);
				count.StartFileCounter();
				this->genetic_setup(400, true);
				results[60][i] = count.GetCounter();
				results[61][i] = result;
				count.StartFileCounter();
				this->genetic_setup(400, false);
				results[62][i] = count.GetCounter();
				results[63][i] = result;
			}
			if (sizes[1])
			{
				this->setSim(1000);
				count.StartFileCounter();
				this->genetic_setup(400, true);
				results[64][i] = count.GetCounter();
				results[65][i] = result;
				count.StartFileCounter();
				this->genetic_setup(400, false);
				results[66][i] = count.GetCounter();
				results[67][i] = result;
			}
			if (sizes[2])
			{
				this->setSim(2000);
				count.StartFileCounter();
				this->genetic_setup(400, true);
				results[68][i] = count.GetCounter();
				results[69][i] = result;
				count.StartFileCounter();
				this->genetic_setup(400, false);
				results[70][i] = count.GetCounter();
				results[71][i] = result;
			}
			if (sizes[3])
			{
				this->setSim(5000);
				count.StartFileCounter();
				this->genetic_setup(400, true);
				results[72][i] = count.GetCounter();
				results[73][i] = result;
				count.StartFileCounter();
				this->genetic_setup(400, false);
				results[74][i] = count.GetCounter();
				results[75][i] = result;
			}
			if (sizes[4])
			{
				this->setSim(10000);
				count.StartFileCounter();
				this->genetic_setup(400, true);
				results[76][i] = count.GetCounter();
				results[77][i] = result;
				count.StartFileCounter();
				this->genetic_setup(400, false);
				results[78][i] = count.GetCounter();
				results[79][i] = result;
			}
		}
		if (pop[4])
		{
			if (sizes[0])
			{
				this->setSim(100);
				count.StartFileCounter();
				this->genetic_setup(800, true);
				results[80][i] = count.GetCounter();
				results[81][i] = result;
				count.StartFileCounter();
				this->genetic_setup(800, false);
				results[82][i] = count.GetCounter();
				results[83][i] = result;
			}
			if (sizes[1])
			{
				this->setSim(1000);
				count.StartFileCounter();
				this->genetic_setup(800, true);
				results[84][i] = count.GetCounter();
				results[85][i] = result;
				count.StartFileCounter();
				this->genetic_setup(800, false);
				results[86][i] = count.GetCounter();
				results[87][i] = result;
			}
			if (sizes[2])
			{
				this->setSim(2000);
				count.StartFileCounter();
				this->genetic_setup(800, true);
				results[88][i] = count.GetCounter();
				results[89][i] = result;
				count.StartFileCounter();
				this->genetic_setup(800, false);
				results[90][i] = count.GetCounter();
				results[91][i] = result;
			}
			if (sizes[3])
			{
				this->setSim(5000);
				count.StartFileCounter();
				this->genetic_setup(800, true);
				results[92][i] = count.GetCounter();
				results[93][i] = result;
				count.StartFileCounter();
				this->genetic_setup(800, false);
				results[94][i] = count.GetCounter();
				results[95][i] = result;
			}
			if (sizes[4])
			{
				this->setSim(10000);
				count.StartFileCounter();
				this->genetic_setup(800, true);
				results[96][i] = count.GetCounter();
				results[97][i] = result;
				count.StartFileCounter();
				this->genetic_setup(800, false);
				results[98][i] = count.GetCounter();
				results[99][i] = result;
			}
		}
		if (pop[5])
		{
			if (sizes[0])
			{
				this->setSim(100);
				count.StartFileCounter();
				this->genetic_setup(1000, true);
				results[100][i] = count.GetCounter();
				results[101][i] = result;
				count.StartFileCounter();
				this->genetic_setup(1000, false);
				results[102][i] = count.GetCounter();
				results[103][i] = result;
			}
			if (sizes[1])
			{
				this->setSim(1000);
				count.StartFileCounter();
				this->genetic_setup(1000, true);
				results[104][i] = count.GetCounter();
				results[105][i] = result;
				count.StartFileCounter();
				this->genetic_setup(1000, false);
				results[106][i] = count.GetCounter();
				results[107][i] = result;
			}
			if (sizes[2])
			{
				this->setSim(2000);
				count.StartFileCounter();
				this->genetic_setup(1000, true);
				results[108][i] = count.GetCounter();
				results[109][i] = result;
				count.StartFileCounter();
				this->genetic_setup(1000, false);
				results[110][i] = count.GetCounter();
				results[111][i] = result;
			}
			if (sizes[3])
			{
				this->setSim(5000);
				count.StartFileCounter();
				this->genetic_setup(1000, true);
				results[112][i] = count.GetCounter();
				results[113][i] = result;
				count.StartFileCounter();
				this->genetic_setup(1000, false);
				results[114][i] = count.GetCounter();
				results[115][i] = result;
			}
			if (sizes[4])
			{
				this->setSim(10000);
				count.StartFileCounter();
				this->genetic_setup(1000, true);
				results[116][i] = count.GetCounter();
				results[117][i] = result;
				count.StartFileCounter();
				this->genetic_setup(1000, false);
				results[118][i] = count.GetCounter();
				results[119][i] = result;
			}
		}
	}
}