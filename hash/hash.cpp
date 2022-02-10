#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include <map>
#include <string>
#include <filesystem>

using namespace std;

bool PrimeCheck(int primeCandidate) {
	int maxNum = sqrt(primeCandidate);
	for (int i = 2; i <= maxNum; i++) {
		if (primeCandidate % i == 0) {
			return false;
		}
	}
	return true;
}
int PrimeNum(int biggerThan) {
	int candidate = biggerThan + 1;
	while (!PrimeCheck(candidate)) {
		candidate += 1;
	}
	return candidate;
}

class SecondLevel {
public:
	SecondLevel(){}
	SecondLevel(int p) {
		P = p;
		A = rand();
		B = rand();
	}
	void AddElem(string temp) {		
			elems.push_back(temp);
	}
	void HashElems() {
		if (elems.size() > 0)
		{
			vector<string> old_elems;
			old_elems = elems;
			count_elems = elems.size() * elems.size();
			bool ready = false;
			while (!ready) {
				elems.clear();
				elems.resize(count_elems);
				A = rand();
				B = rand();
				int h = 1;
				for (int j = 0; j < old_elems.size(); j++) {
					for (int i = 0; i < old_elems[j].size(); i++)
					{
						h += A * old_elems[j][i] + B;
					}
					h = (h % P) % count_elems;			
					if ((elems[h] == "") || (elems[h] == old_elems[j])) {
						elems[h] = old_elems[j];
						if (j == old_elems.size() - 1) {
							ready = true;
						}
					}
					else {
						break;
					}
				}
			}
		}
	}
	void PrintTable() {
		for (int i = 0; i < elems.size(); i++)
		{
			if (elems[i].size()>0)
			{
				cout << i+1 << "|" << elems[i] << " ";
			}
			
		}
	}

	int GetCountElems() {
		return elems.size();
	}

	vector<string> GetElems() {
		return elems;
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
		P = PrimeNum(count_elems);
		for (int i = 0; i < count_elems; i++)
		{
			SecondLevel temp(P);
			hash_table[i] = temp;
		}		
		TheBestAB(elem, filename);
		ReadElem(elem, filename);
		for (int i = 0; i < count_elems; i++)
		{
			hash_table[i].HashElems();
		}		
	}

	void PrintTable() {
		for (int i = 0; i < hash_table.size(); i++)
		{
			cout << i+1 << ": ";
			hash_table[i].PrintTable();
			cout << endl;
		}
	}

	string Find(const string& key) {
		for (int i = 0; i < count_elems - 1; i++)
		{
			for (int j = 0; j < hash_table[i].GetCountElems() - 1; j++)
			{
				if (hash_table[i].GetElems()[j] == key)
				{
					return "on " + to_string(i+1) + "-" + to_string(j+1);
				}
			}
		}
		return "not found";
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
		int h=1;
		for (int i = 0; i < elem.size(); i++)
		{
			h += A * elem[i] + B;
		}
		h = (h % P) % count_elems;
		hash_table[h].AddElem(elem);		
	}

	void TheBestAB(string& elem, const string& filename) {
		map<int, pair<int, int>> list;
		int cycles = 200;
		for (int i = 0; i < cycles; i++)
		{
			int x=0;
			hash_table.clear();
			hash_table.resize(count_elems);
			A = rand();
			B = rand();
			ReadElem(elem, filename);
			for (int j = 0; j < count_elems; j++)
			{
				if (hash_table[j].GetElems().size() == 0)
				{
					x++;
				}
			}
			cout << i/(cycles/100) << "%\r";
			//cerr << x << " ";
			list[x] = make_pair(A, B);
		}
		//cerr << endl;
		map<int, pair<int, int>> ::iterator it = list.begin();
		//cerr << it->first << endl;
		A = it->second.first;
		B = it->second.second;
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
	cout << endl;
	cout << "Whant to find element?" << endl;
	cout << "Y or N: ";
	char ans;
	cin >> ans;
	while (ans == 'Y' || ans == 'y')
	{
		string elem;
		cout << "Enter element: ";
		cin >> elem;
		cout << "Your elem " << table.Find(elem) << endl;
		cout << endl;
		cout << "Whant to find another element?" << endl;
		cout << "Y or N: ";
		cin >> ans;
	}
	
}

