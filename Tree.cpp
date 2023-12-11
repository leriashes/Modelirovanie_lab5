#include "Tree.h"

void Tree::SetNameChildren(int first, int second)
{
	string name = "(" + to_string(first) + ", " + to_string(second) + ")";

	left = new Tree("-" + name, this);
	right = new Tree(name, this);
}

void Tree::FindNewCur(Tree* root)
{
	if (left != NULL)
	{
		left->FindNewCur(root);
		right->FindNewCur(root);
	}
	else
	{
		if (root->current->left != NULL || root->current->cost > cost)
		{
			root->current = this;
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
	current->left->cost = cost;
}

void Tree::FindMinCost()
{
	FindNewCur(this);
}

void Tree::PrintCurrent()
{
	cout << current->number << ") " << current->name;
	if (current->cost >= 0) cout << " [" << current->cost << "]";
}

void Tree::CurSetRightCost(int cost)
{
	current->right->cost = cost;
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

