#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include <filesystem>

using namespace std;

int x=0;

int PrimeNum(const int& count_elems){
	int prime = 997;/*
	while ((prime * prime) % 24 != 1)
	{
		for (i = 2; i < sqrt(n); i++) {
			if (n % i == 0) {
				
				return 0;
			}
		}
	}*/
	
	return prime;
	
}

class SecondLevel {
public:
	SecondLevel(){
		P = 997;
	}
	SecondLevel(int p) {
		P = p;
	}
	void AddElem(string temp) {
		if (elems.size() > 1)
		{
			count_elems = elems.size()* elems.size();
			A = rand();
			B = rand();
			int h=1;
			for (int i = 0; i < temp.size(); i++)
			{
				h += A * temp[i] + B;
			}
			h = (h % P) % count_elems;
			if (h >= elems.size())
			{
				elems.resize(h+1);				
			}
			elems[h] = temp;
		}
		else
		{
			elems.push_back(temp);
		}		
	}
	void PrintTable() {
		for (int i = 0; i < elems.size(); i++)
		{
			if (elems[i].size()>0)
			{
				cout << i << "|" << elems[i] << " ";
			}
			
		}
	}
private:
	int A, B, count_elems, P;
	vector<string> elems;

};

class HashTable
{
public:
	HashTable(string filename = "text.txt") {
		string elem;
		file_size = filesystem::file_size(filename);
		ifstream in(filename);
		while (!in.eof())
		{
			in >> elem;
			count_elems++;
		}
		cout << count_elems<<endl;
		in.close();
		hash_table.resize(count_elems);
		A = rand();
		B = rand();
		P = PrimeNum(count_elems);
		for (int i = 0; i < count_elems; i++)
		{
			SecondLevel temp(P);
			hash_table[i] = temp;
		}		
		ReadElem(elem, filename);
	}

	void PrintTable() {
		//cout << hash_table.size();
		
		for (int i = 0; i < hash_table.size(); i++)
		{
			cout << i+1 << ": ";
			hash_table[i].PrintTable();
			cout << endl;
		}
	}

private:
	vector<SecondLevel> hash_table;
	int file_size;
	int count_elems = 0; //N
	int A, B, P;

	void ReadElem(string& elem, const string& filename) {
		ifstream in(filename);
		while (!in.eof())
		{
			in >> elem;
			FirstLevelHash(elem);
			
		}
	}
	
	void FirstLevelHash(string& elem) {
		if (x==74)
		{
			cout << "!";
		}
		int h=1;
		for (int i = 0; i < elem.size(); i++)
		{
			h += A * elem[i] + B;
		}
		h = (h % P) % count_elems;
		x++;
		//cout << h << " ";
		cout << x <<" ";
		hash_table[h].AddElem(elem);		
	}

};

//В хэш - функции вида «(A * k + B) % P % N», с возможностью подбора двух коэффициентов A и В :
//k - хэшкод уникального ключа,
//P - заранее заданное простое число, большее любого возможного ключа k,+
//N - размер хеш - таблицы, то есть количество всех ключей.

int main()
{
	HashTable table;
	table.PrintTable();
}
