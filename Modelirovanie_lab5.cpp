#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <format>
#include "Tree.h"
#include <conio.h>
using namespace std;

int table[6][6];
int index[2][6];
int fine[6][6];
int n = 6;
int Tree::counter = 0;
Tree* Tree::current = (Tree*)NULL;
 
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
			{
				if (fine[i][j] == -2)
				{
					cout << std::format("| inf  ");
				}
				else
				{
					cout << std::format("| {:<3}  ", fine[i][j]);
				}
			}
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

int privedenie()
{
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

	return r;
}

int main()
{
	setlocale(LC_ALL, "Rus");

    ifstream f("input1.txt");

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
	Tree* root = new Tree("S(0)");

	//шаг 1 - приведение матрицы затрат
	int r = 0;
	int first = 0;
	int last = 0;

	r = privedenie();

	root->CurSetCost(r);

	/*cout << k << ".1 Приведение матрицы затрат: r = " << r << endl << endl;
	if (r > 0) printTable();

	root->SaveTable(table, index, n);*/


	while (k < 16)
	{
		if (k > 1)
			r = privedenie();

		cout << k << ".1 Приведение матрицы затрат: r = " << r << endl << endl;
		if (r > 0) printTable();

		root->SaveTable(table, index, n);

		//шаг 2 - вычисление штрафов за неиспользование
		int maxFine = -1;
		int x, y;
		bool infi = false;

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

					if (fine[i][j] > maxFine && !infi)
					{
						maxFine = fine[i][j];
						x = index[1][i];
						y = index[0][j];
					}

					if (fine[i][j] < 0)
					{
						x = index[1][i];
						y = index[0][j];
						maxFine = -2;
						infi = true;
					}
				}
			}
		}


		if (first == 0)
			first = x;

		last = y;

		if (infi)
		{
			cout << k << ".2 Вычисление штрафов: max = inf"  << endl << endl;
		}
		else
		{
			cout << k << ".2 Вычисление штрафов: max = " << maxFine << endl << endl;
		}
		
		printFineTable();


		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				fine[i][j] = 0;
			}
		}


		//шаг 3 - добавление потомков
		root->CurSetNameChildren(x, y);
		cout << k << ".3 Добавление потомков: маршруты (" << x << ", " << y << ")" << ", -(" << x << ", " << y << ")" << endl << endl;
		root->PrintTree();
		cout << endl << endl;


		//шаг 4 - вычисление оценок затрат
		root->CurSetLeftCost(maxFine);


		int row = -1, col = -1;
		int xw, yw;
		xw = x;
		yw = y;

		int len = root->FindWay(&xw, &yw);


		//вычеркивание строки и столбца
		for (int i = 0; i < n && (row < 0 || col < 0); i++)
		{
			if (index[1][i] == x)
			{
				row = i;
				index[1][i] = 0;
			}

			if (index[0][i] == y)
			{
				col = i;
				index[0][i] = 0;
			}
		}

		for (int i = row; i < n - 1; i++)
		{
			if (index[1][i] < index[1][i + 1])
			{
				index[1][i] = index[1][i + 1];
				index[1][i + 1] = 0;

				for (int j = 0; j < n; j++)
				{
					table[i][j] = table[i + 1][j];
				}
			}
		}

		for (int i = col; i < n - 1; i++)
		{
			if (index[0][i] < index[0][i + 1])
			{
				index[0][i] = index[0][i + 1];
				index[0][i + 1] = 0;

				for (int j = 0; j < n; j++)
				{
					table[j][i] = table[j][i + 1];
				}
			}
		}

		row = col = -1;

		for (int i = 0; i < n && (col < 0 || row < 0); i++)
		{
			if (index[0][i] == xw)
			{
				col = i;
			}

			if (index[1][i] == yw)
			{
				row = i;
			}
		}

		if (len < 5)
			table[row][col] = -1;
		else
			table[row][col] = 0;

		n--;



		int r1 = privedenie();

		cout << k << ".4 Вычисление оценок затрат: r = " << r1 << endl << endl;
		printTable();

		root->CurSetRightCost(r1);
		root->PrintTree();
		cout << endl << endl;

		root->RightSaveTable(table, index, n);

		//шаг 5 - выбор нового подмножества с минимальной оценкой
		root->FindMinCost();
		cout << k << ".5 Выбор нового подмножества: ";
		root->PrintCurrent();
		root->RestoreTable(&table[0][0], &index[0][0], &n);
		cout << endl << endl;
		cout << endl << endl;

		if (root->FindWay() >= 5 || n == 0)
			break;

		k++;
	}


	cout << "\nНайден оптимальный маршрут: ";
	root->PrintWay();

	_getch();

	root->CurSetCost(-2);

	while (k < 16)
	{
		if (k > 1)
			r = privedenie();

		cout << k << ".1 Приведение матрицы затрат: r = " << r << endl << endl;
		if (r > 0) printTable();

		root->SaveTable(table, index, n);

		//шаг 2 - вычисление штрафов за неиспользование
		int maxFine = 0;
		int x, y;
		bool infi = false;

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

					if (fine[i][j] > maxFine && !infi)
					{
						maxFine = fine[i][j];
						x = index[1][i];
						y = index[0][j];
					}

					if (fine[i][j] == -2)
					{
						x = index[1][i];
						y = index[0][j];
						maxFine = -2;
						infi = true;
					}
				}
			}
		}


		if (first == 0)
			first = x;

		last = y;

		if (infi)
		{
			cout << k << ".2 Вычисление штрафов: max = inf" << endl << endl;
		}
		else
		{
			cout << k << ".2 Вычисление штрафов: max = " << maxFine << endl << endl;
		}

		printFineTable();


		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				fine[i][j] = 0;
			}
		}


		//шаг 3 - добавление потомков
		root->CurSetNameChildren(x, y);
		cout << k << ".3 Добавление потомков: маршруты (" << x << ", " << y << ")" << ", -(" << x << ", " << y << ")" << endl << endl;
		root->PrintTree();
		cout << endl << endl;


		//шаг 4 - вычисление оценок затрат
		root->CurSetLeftCost(maxFine);


		int row = -1, col = -1;
		int xw, yw;
		xw = x;
		yw = y;

		int len = root->FindWay(&xw, &yw);


		//вычеркивание строки и столбца
		for (int i = 0; i < n && (row < 0 || col < 0); i++)
		{
			if (index[1][i] == x)
			{
				row = i;
				index[1][i] = 0;
			}

			if (index[0][i] == y)
			{
				col = i;
				index[0][i] = 0;
			}
		}

		for (int i = row; i < n - 1; i++)
		{
			if (index[1][i] < index[1][i + 1])
			{
				index[1][i] = index[1][i + 1];
				index[1][i + 1] = 0;

				for (int j = 0; j < n; j++)
				{
					table[i][j] = table[i + 1][j];
				}
			}
		}

		for (int i = col; i < n - 1; i++)
		{
			if (index[0][i] < index[0][i + 1])
			{
				index[0][i] = index[0][i + 1];
				index[0][i + 1] = 0;

				for (int j = 0; j < n; j++)
				{
					table[j][i] = table[j][i + 1];
				}
			}
		}

		row = col = -1;

		for (int i = 0; i < n && (col < 0 || row < 0); i++)
		{
			if (index[0][i] == xw)
			{
				col = i;
			}

			if (index[1][i] == yw)
			{
				row = i;
			}
		}

		if (len < 5)
			table[row][col] = -1;
		else
			table[row][col] = 0;

		n--;



		int r1 = privedenie();

		cout << k << ".4 Вычисление оценок затрат: r = " << r1 << endl << endl;
		printTable();

		root->CurSetRightCost(r1);
		root->PrintTree();
		cout << endl << endl;

		root->RightSaveTable(table, index, n);

		//шаг 5 - выбор нового подмножества с минимальной оценкой
		root->FindMinCost();
		cout << k << ".5 Выбор нового подмножества: ";
		root->PrintCurrent();
		root->RestoreTable(&table[0][0], &index[0][0], &n);
		cout << endl << endl;
		cout << endl << endl;

		if (root->FindWay() >= 5 || n == 0)
			break;

		k++;
	}

	return 0;
}
