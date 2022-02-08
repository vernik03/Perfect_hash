#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include <filesystem>

using namespace std;

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
		cout << count_elems;
		ReadElem(elem, filename);
	}

	void ReadElem(string& elem, const string& filename) {
		ifstream in(filename);
		in >> elem;
		FirstLevelHash(elem);
	}

	void FirstLevelHash(string& elem) {
		int k;
	}

private:
	vector<vector<string>> hash_table;
	int file_size;
	int count_elems = 0;
	int A, B;
};

//В хэш - функции вида «(A * k + B) % P % N», с возможностью подбора двух коэффициентов A и В :
//k - хэшкод уникального ключа,
//P - заранее заданное простое число, большее любого возможного ключа k,+
//N - размер хеш - таблицы, то есть количество всех ключей.

int main()
{
	HashTable table;
}
