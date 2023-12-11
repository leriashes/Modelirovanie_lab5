#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <format>
using namespace std;

int table[6][6];
int index[2][6];
int fine[6][6];
int n = 6;

void printTable()
{
	cout << "     ";

	for (int i = 0; i < n; i++)
	{
		cout << "|   "  << index[0][i] << "  ";
	}

	for (int i = 0; i < n; i++)
	{
		cout << "\n-----";

		for (int j = 0; j < n; j++)
		{
			cout << "-------";
		}

		cout << "\n  " << index[1][i] << "  ";

		for (int j = 0; j < n; j++)
		{
			if (table[i][j] >= 0)
				cout << std::format("|  {:2}  ", table[i][j]);
			else
				cout << "|  inf ";
		}
	}

	cout << endl << endl << endl;
}

void printFineTable()
{
	cout << "     ";

	for (int i = 0; i < n; i++)
	{
		cout << "|   " << index[0][i] << "  ";
	}

	for (int i = 0; i < n; i++)
	{
		cout << "\n-----";

		for (int j = 0; j < n; j++)
		{
			cout << "-------";
		}

		cout << "\n     ";

		for (int j = 0; j < n; j++)
		{
			if (table[i][j] == 0)
				cout << std::format("| {:<3}  ", fine[i][j]);
			else
				cout << "|      ";
		}

		cout << "\n  " << index[1][i] << "  ";

		for (int j = 0; j < n; j++)
		{
			if (table[i][j] >= 0)
				cout << std::format("|  {:2}  ", table[i][j]);
			else
				cout << "|  inf ";
		}
	}

	cout << endl << endl << endl;
}

int main()
{
	setlocale(LC_ALL, "Rus");

    ifstream f("input.txt");

	for (int i = 0; i < n; i++)
	{
		index[0][i] = i + 1;
		index[1][i] = i + 1;

		for (int j = 0; j < n; j++)
		{
			fine[i][j] = 0;
		}
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
		f >> table[i][j++];

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


	cout << "Исходная матрица затрат" << endl << endl;
	printTable();

	int k = 1;


	//шаг 1 - приведение матрицы затрат
	int r = 0;

	//приведение по строкам
	for (int i = 0; i < n; i++)
	{
		int m = 0;

		for (int j = 0; j < n; j++)
		{
			if (table[i][j] >= 0)
			{
				m = table[i][j];
				break;
			}
		}

		for (int j = 0; j < n; j++)
		{
			if (table[i][j] < m && table[i][j] >= 0)
			{
				m = table[i][j];
			}
		}

		r += m;

		for (int j = 0; j < n; j++)
		{
			table[i][j] -= m;
		}
	}

	//приведение по столбцам
	for (int j = 0; j < n; j++)
	{
		int m = 0;

		for (int i = 0; i < n; i++)
		{
			if (table[i][j] >= 0)
			{
				m = table[i][j];
				break;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (table[i][j] < m && table[i][j] >= 0)
			{
				m = table[i][j];
			}
		}

		r += m;

		for (int i = 0; i < n; i++)
		{
			table[i][j] -= m;
		}
	}

	cout << k << ".1 Приведение матрицы затрат: r = " << r << endl << endl;
	printTable();


	//шаг 2 - вычисление штрафов за неиспользование
	int maxFine = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (table[i][j] == 0)
			{
				int m1 = -1, m2 = -1;

				for (int h = 0; h < n && (m1 < 0 || m2 < 0); h++)
				{
					if (table[i][h] >= 0 && h != j)
					{
						m1 = table[i][h];
					}

					if (table[h][j] >= 0 && h != i)
					{
						m2 = table[h][j];
					}
				}

				for (int h = 0; h < n; h++)
				{
					if (table[i][h] < m1 && table[i][h] >= 0 && h != j)
					{
						m1 = table[i][h];
					}

					if (table[h][j] < m2 && table[h][j] >= 0 && h != i)
					{
						m2 = table[h][j];
					}
				}

				fine[i][j] = m1 + m2;

				if (fine[i][j] > maxFine)
					maxFine = fine[i][j];
			}
		}
	}
	
	cout << k << ".2 Вычисление штрафов: max = " << maxFine << endl << endl;
	printFineTable();

	return 0;
}
