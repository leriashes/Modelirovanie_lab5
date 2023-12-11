#pragma once
#include <iostream>
#include <string>
using namespace std;

class Tree
{
	static int counter;

private:
	string name;
	int number;
	int cost = -1;

	Tree* parent = NULL;
	Tree* left = NULL;
	Tree* right = NULL;

	Tree* current;

	void SetCost(int cost);
	void SetNameChildren(int first, int second);
	void FindNewCur(Tree* root);

public:
	Tree(string name, Tree* parent) { this->name = name; this->parent = parent; number = counter++; }
	Tree(string name) { this->name = name; current = this; number = 0; counter = 1; }
	void CurSetNameChildren(int first, int second);
	void CurSetCost(int cost);
	void CurSetLeftCost(int cost);
	void CurSetRightCost(int cost);
	void PrintTree();
	void PrintCurrent();
	void FindMinCost();
};

