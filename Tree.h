#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;

class Tree
{
	static int counter;

private:
	string name;
	int first;
	int last;
	int length = 0;
	int number;
	int cost = -1;
	bool node = true;
	int table[6][6];
	int index[2][6];
	int n;

	Tree* parent = NULL;
	Tree* left = NULL;
	Tree* right = NULL;

	static Tree* current;

	void SetCost(int cost);
	void SetNameChildren(int first, int second);
	void FindNewCur();

public:
	Tree(string name, Tree* parent, int first, int last) { this->name = name; this->parent = parent; number = counter++; this->first = first; this->last = last; }
	Tree(string name, Tree* parent) { this->name = name; this->parent = parent; number = counter++; node = false; }
	Tree(string name) { this->name = name; current = this; number = 0; counter = 1; }
	void CurSetNameChildren(int first, int second);
	void CurSetCost(int cost);
	void CurSetLeftCost(int cost);
	void CurSetRightCost(int cost);
	void PrintTree();
	void PrintCurrent();
	int GetCurCost();
	void FindMinCost();
	void SaveTable(int curtable[6][6], int curindex[2][6], int n);
	void RightSaveTable(int curtable[6][6], int curindex[2][6], int n);
	void RestoreTable(int* curtable, int* curindex, int* n);
	int FindWay(int* first, int* last);
	int FindWay();
	void PrintWay();
	bool CheckVariants();
	list<int> MakeChain(list<int> way);
};

