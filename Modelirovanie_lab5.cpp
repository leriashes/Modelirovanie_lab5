#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


int main()
{
    ifstream f("input.txt");

	int table[6][6];
	int index[2][6];
	int n = 6;

	for (int i = 0; i < n; i++)
	{
		index[0][i] = i + 1;
		index[1][i] = i + 1;
	}

	//Файл для чтения не открылся
	if (!f)
	{
		cout << "Не удалось открыть файл 'input.txt'";
		return -1;
	}

	int i = 0, j = 0;

	//Заполнение таблицы
	while (!f.eof())
	{
		f >> table[i][j];
		j++;

		if (j == n)
		{
			j = 0;
			i += 1;
		}

		if (i == n)
		{
			break;
		}
	}

	f.close();


	return 0;

}
