#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include <filesystem>

using namespace std;

class SecondLevel {
public:
	SecondLevel(){}
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
				h += ((A * temp[i] + B) % P) % count_elems;
			}
			if (h > elems.size())
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
		in.close();
		hash_table.resize(count_elems);
		A = rand();
		B = rand();
		for (int i = 0; i < count_elems; i++)
		{
			SecondLevel temp = (P);
			hash_table[i] = temp;
		}
		ReadElem(elem, filename);
	}

	void PrintTable() {
		for (int i = 0; i < hash_table.size(); i++)
		{
			cout << i << ": ";
			hash_table[i].PrintTable();
			cout << endl;
		}
	}

private:
	vector<SecondLevel> hash_table;
	int file_size;
	int count_elems = 0; //N
	int A, B, P = 999;

	void ReadElem(string& elem, const string& filename) {
		ifstream in(filename);
		while (!in.eof())
		{
			in >> elem;
			FirstLevelHash(elem);
		}
	}
	
	void FirstLevelHash(string& elem) {
		int h=1;
		for (int i = 0; i < elem.size(); i++)
		{
			h += (((A * elem[i] + B) % P) % count_elems)/10;
		}
		if (h > hash_table.size())
		{
			hash_table.resize(h + 1);
		}
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
