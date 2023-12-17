#include "Tree.h"

void Tree::SetNameChildren(int first, int second)
{
	string name = "(" + to_string(first) + ", " + to_string(second) + ")";

	left = new Tree("-" + name, this);
	right = new Tree(name, this, first, second);
}

void Tree::FindNewCur()
{
	if (left != NULL)
	{
		left->FindNewCur();
		right->FindNewCur();
	}
	else
	{
		if (current->left != NULL || current->cost > cost)
		{
			current = this;
		}
	}
}

void Tree::CurSetNameChildren(int first, int second)
{
	current->SetNameChildren(first, second);
}

void Tree::CurSetCost(int cost)
{
	current->SetCost(cost);
}

void Tree::CurSetLeftCost(int cost)
{
	current->left->cost = cost + current->cost;
}

void Tree::FindMinCost()
{
	FindNewCur();
}

void Tree::PrintCurrent()
{
	cout << current->number << ") " << current->name;
	if (current->cost >= 0) cout << " [" << current->cost << "]";
}

void Tree::SaveTable(int curtable[6][6], int curindex[2][6], int n)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			current->table[i][j] = curtable[i][j];
		}

		for (int j = 0; j < 2; j++)
		{
			current->index[j][i] = curindex[j][i];
		}
	}

	current->n = n;
}

void Tree::RightSaveTable(int curtable[6][6], int curindex[2][6], int n)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			current->right->table[i][j] = curtable[i][j];
		}

		for (int j = 0; j < 2; j++)
		{
			current->right->index[j][i] = curindex[j][i];
		}
	}

	current->right->n = n;
}

int Tree::FindWay(int* start, int* end)
{
	list<int> way = {*start, *end};
	int lastlen = 1;

	do
	{
		lastlen = way.size() / 2;
		way = current->MakeChain(way);
	} while (way.size() / 2 > lastlen);

	*start = way.front();
	*end = way.back();

	return way.size() / 2;
}

int Tree::FindWay()
{
	list<int> way = {current->first , current->last };
	int lastlen = 1;

	do
	{
		lastlen = way.size() / 2;
		way = current->MakeChain(way);
	} while (way.size() / 2 > lastlen);

	return way.size() / 2;
}

void Tree::RestoreTable(int* curtable, int* curindex, int* n)
{
	Tree* node = current->parent;

	if (current->node)
	{
		node = current;
	}
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			*(curtable + i * 6 + j) = node->table[i][j];
		}

		for (int j = 0; j < 2; j++)
		{
			*(curindex + j * 6 + i) = node->index[j][i];
		}
	}

	*n = node->n;

	if (!current->node)
	{
		int row = -1, col = -1;
		int x = current->parent->right->first;
		int y = current->parent->right->last;

		for (int i = 0; i < *n && (col < 0 || row < 0); i++)
		{
			if (node->index[1][i] == x)
			{
				row = i;
			}

			if (node->index[0][i] == y)
			{
				col = i;
			}
		}

		*(curtable + row * 6 + col) = -1;
	}
}

list<int> Tree::MakeChain(list<int> way)
{
	if (number != 0)
	{
		if (node)
		{
			bool added = false;

			if (first == way.back())
			{
				way.push_back(first);
				way.push_back(last);
				added = true;
			}

			if (last == way.front())
			{
				way.push_front(last);
				way.push_front(first);
				added = true;
			}

			if (added)
			{
				return way;
			}
		}

		return parent->MakeChain(way);
	}

	return way;
}

void Tree::CurSetRightCost(int cost)
{
	current->right->cost = cost + current->cost;
}

void Tree::PrintTree()
{
	cout << number << ") " << name;
	if (cost >= 0) cout << " [" << cost << "]";

	if (left != NULL && right != NULL)
	{
		cout << " ------ " << left->number << ") " << left->name;
		if (left->cost >= 0) cout << " [" << left->cost << "]";
		cout << endl;
		cout << "             |" << endl;
		cout << "             ------ " << right->number << ") " << right->name;
		if (right->cost >= 0) cout << " [" << right->cost << "]";
		cout << endl;

		left->PrintTree();
		right->PrintTree();
	}
	else
	{
		cout << endl;
	}
}

void Tree::SetCost(int cost)
{
	this->cost = cost;
}

