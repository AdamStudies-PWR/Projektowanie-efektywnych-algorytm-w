#pragma once
#ifndef Data_hpp
#define Data_hpp

using namespace std;

//Klasa przechowuj¹ca i ob³uguj¹ca wygenerowane dane
class Data
{
private:
	//Atrybuty
	bool exists = false;
	int **tab;
	int ext;
	const static int limit = 1000;
public:
	//Metody
	~Data();
	string load(string filename);
	void randomify(int size, bool mirror);
	void manual(int size, bool mirror);
	void display();
	int counttarget();
};
#endif