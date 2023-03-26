
#include <iostream>

using namespace std;

struct node {
	int arr[4][4];
	node* parent;
};

struct que {
	node arr;
	que* next;
};

void pushNode(int[4][4], int[4][4]);
void popQue(que*, node);
bool isEqual(node, node);
bool queExists(que*, node);
void addQue(que*, node);
void printQue(que*);
void printArr(int[4][4]);
bool check(int[4][4]);

void addQue(que* qname, node data)
{

	if (qname == NULL)
	{
		que* start = new que;
		start->arr = data;
		start->next = NULL;
		qname = start;
	}
	else
	{
		que* tempAdd = new que;
		tempAdd = qname;
		for (; qname->next != NULL; qname = qname->next);
		que* newPart = new que;
		pushNode(newPart->arr.arr, data.arr);
		newPart->next = NULL;
		newPart->arr.parent = data.parent;
		qname->next = newPart;
		qname = tempAdd;
	}
}

void popQue(que* qname, node data)
{
	que* tempAdd = new que;
	tempAdd = qname;
	tempAdd->next = qname->next;
	node* dataAddress = &data;
	dataAddress->parent = data.parent;
	if (qname->next == NULL && isEqual(qname->arr, data))
	{
		que* temp = qname;
		qname = qname->next;
		delete temp;
	}
	else
	{
		for (; qname->next != NULL; qname = qname->next)
		{
			if (isEqual(qname->arr, data) == true)
			{
				qname->next = qname->next->next;
				qname = tempAdd;
				break;
			}
		}
	}
}

bool queExists(que* qname, node data)
{
	if (qname == NULL)
		cout << "This queue is empty!";
	else
	{
		bool flag = false;
		que* temp = qname;

		for (; qname != NULL; qname = qname->next)
			if (isEqual(qname->arr, data) == true)
				flag = true;

		qname = temp;
		return flag;
	}
}

void pushNode(int a[4][4], int b[4][4])
{
	for (int i = 0; i <= 3; i++)
		for (int j = 0; j <= 3; j++)
		{
			a[i][j] = b[i][j];
		}
}

void printQue(que* qname)
{
	que* temp = qname;
	for (; qname != NULL; qname = qname->next)
	{
		printArr(qname->arr.arr);
	}
	qname = temp;
}

bool check(int arr[4][4])
{
	// 1 2 3 4
	// 5 6 7 8
	//9 10 11 12
	// 13 14 0 0
	// must be the final status.
	int result[4][4];
	result[0][0] = 1; result[0][1] = 2; result[0][2] = 3; result[0][3] = 4;
	result[1][0] = 5; result[1][1] = 6; result[1][2] = 7; result[1][3] = 8;
	result[2][0] = 9; result[2][1] = 10; result[2][2] = 11; result[2][3] = 12;
	result[3][0] = 13; result[3][1] = 14; result[3][2] = 0; result[3][3] = 0;
	bool flag = true;
	for (int i = 0; i <= 3; i++)
		for (int j = 0; j <= 3; j++)
		{
			if (arr[i][j] == result[i][j]) continue;
			else
				flag = false;
		}
	if (flag != false)
		return true;
	else return false;
}

bool isEqual(node a, node b)
{
	bool flag = true;
	for (int i = 0; i <= 3; i++)
		for (int j = 0; j <= 3; j++)
		{
			if (a.arr[i][j] != b.arr[i][j])
			{
				flag = false;
				break;
			}
		}

	return flag;
}

void printArr(int arr[4][4])
{
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	bool finished = false;
	int arr[4][4];

	arr[0][0] = 1; arr[0][1] = 2; arr[0][2] = 0; arr[0][3] = 0;
	arr[1][0] = 5; arr[1][1] = 6; arr[1][2] = 3; arr[1][3] = 4;
	arr[2][0] = 9; arr[2][1] = 10; arr[2][2] = 7; arr[2][3] = 8;
	arr[3][0] = 13; arr[3][1] = 14; arr[3][2] = 11; arr[3][3] = 12;

	node firstState;
	pushNode(firstState.arr, arr);
	firstState.parent = NULL;

	node* currentState = new node;
	currentState->parent = NULL;
	pushNode(currentState->arr, arr);

	que* checked = new que;
	checked->arr = firstState;
	checked->next = NULL;

	que* unchecked = new que;
	unchecked->arr = firstState;
	unchecked->next = NULL;

	que* tempParent;

	int nodesCreated = 1;

	while (finished == false)
	{
		if (check(currentState->arr))
		{
			int moves = -1;
			cout << "Solved!" << endl;
			finished = true;
			while (currentState != NULL)
			{
				printArr(currentState->arr);
				moves++;
				currentState = currentState->parent;
			}
			cout << endl;
			cout << "Solved in " << moves << " moves!";
			cout << endl;
			cout << nodesCreated << " nodes were created.";
		}
		else
		{
			if (queExists(unchecked, *currentState) == true)
			{
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
					{
						if (currentState->arr[i][j] == 0)
						{
							if (i - 1 >= 0 && currentState->arr[i - 1][j] != 0) //to check if the higher row is within array range.
							{
								node* newNode1 = new node;
								newNode1->parent = currentState;
								pushNode(newNode1->arr, currentState->arr);
								int temp1;
								temp1 = newNode1->arr[i - 1][j];
								newNode1->arr[i - 1][j] = 0;
								newNode1->arr[i][j] = temp1;
								if (queExists(checked, *newNode1) == false)
								{
									addQue(unchecked, *newNode1);
									nodesCreated++;
								}
								else delete newNode1;
							}
							if (i + 1 <= 3 && currentState->arr[i + 1][j] != 0)
							{
								node* newNode2 = new node;
								newNode2->parent = currentState;
								pushNode(newNode2->arr, currentState->arr);
								int temp2;
								temp2 = newNode2->arr[i + 1][j];
								newNode2->arr[i + 1][j] = 0;
								newNode2->arr[i][j] = temp2;
								if (queExists(checked, *newNode2) == false)
								{
									addQue(unchecked, *newNode2);
									nodesCreated++;
								}
								else delete newNode2;
							}
							if (j - 1 >= 0 && currentState->arr[i][j - 1] != 0)
							{
								node* newNode3 = new node;
								newNode3->parent = currentState;
								pushNode(newNode3->arr, currentState->arr);
								int temp3;
								temp3 = newNode3->arr[i][j - 1];
								newNode3->arr[i][j - 1] = 0;
								newNode3->arr[i][j] = temp3;
								if (queExists(checked, *newNode3) == false)
								{
									addQue(unchecked, *newNode3);
									nodesCreated++;
								}
								else delete newNode3;
							}
							if (j + 1 <= 3 && currentState->arr[i][j + 1] != 0)
							{
								node* newNode4 = new node;
								newNode4->parent = currentState;
								pushNode(newNode4->arr, currentState->arr);
								int temp4;
								temp4 = newNode4->arr[i][j + 1];
								newNode4->arr[i][j + 1] = 0;
								newNode4->arr[i][j] = temp4;
								if (queExists(checked, *newNode4) == false)
								{
									addQue(unchecked, *newNode4);
									nodesCreated++;
								}
								else delete newNode4;
							}
						}
					}
				if (queExists(checked, *currentState) == false)
				{
					currentState = &unchecked->next->arr;
					addQue(checked, *currentState);
					unchecked = unchecked->next;
				}
				else
				{
					currentState = &unchecked->next->arr;
					unchecked = unchecked->next;
				}
			}
		}
	}

}

