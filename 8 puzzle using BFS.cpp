#include<iostream>
#include<vector>
#include<math.h>
#include <windows.h>
using namespace std;
HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
static int cost = 0;
int H = 0;
struct myArray {
	int par[3][3];
	int arr[3][3];
	int h_value, actual_cost;
};
int Euclidean_Distance(myArray &state, int A[3][3], int val) {
	int x1, y1, x2, y2;
	int Goal[3][3] = { { 1,8,7 },{ 2,0,6 },{ 3,4,5 } };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (state.arr[i][j] == val) {
				x1 = i;
				y1 = j;
			}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (A[i][j] == val) {
				x2 = i;
				y2 = j;
			}
	int dis = (int)sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	return dis;
}
void Heuristic_01(myArray &m1) {
	int sum = 0;
	int Goal[3][3] = { { 1,8,7 },{ 2,0,6 },{ 3,4,5 } };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (m1.arr[i][j] != Goal[i][j])
				sum = sum + Euclidean_Distance(m1, Goal, m1.arr[i][j]);
	m1.h_value = sum;
}
void Heuristic_02(myArray &m1) {
	int x_g, y_g,x_s,y_s;
	int c = 0;
	int Goal[3][3] = { { 1,8,7 },{ 2,0,6 },{ 3,4,5 } };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (m1.arr[i][j] != Goal[i][j]) {
				//is mismatched
				x_s = i;
				y_s = j;
				for (int k = 0; k < 3; k++) {
					for (int l = 0; l < 3; l++) {
						//find where val is in goal state
						if (Goal[k][l] == m1.arr[k][l]) {
							x_g = k;
							y_g = l;
						}
					}
				}
				if (x_g != x_s)
					c++;
				if (y_g != y_s)
					c++;
			}
	m1.h_value = c;
}
void set_Heuristic() {
	int choice;
	cout << "Which heuristic do you want to use while solving?\n\t1. Sum Of Euclidean distances of the tiles from their goal position.\n\t2. Number of tiles out of row + Number of tiles out of column.\n\nEnter your choice:";
	do {
		cin >> choice;
		if (choice <= 0 || choice > 2) {
			cin.clear();
			cin.ignore();
			SetConsoleTextAttribute(hConsole, 12);
			cout << "Please enter a valid choice.\n";
			SetConsoleTextAttribute(hConsole, 15);
			cout << "Enter your choice :";
		}
	} while ((choice <= 0 || choice > 2));
	system("cls");
	H = choice;
	cout << endl;
}
void Heuristic(myArray &state) {
	if (H == 1)
		Heuristic_01(state);
	else if (H == 2)
		Heuristic_02(state);
}
void copyArray(int A[3][3], int B[3][3]) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			A[i][j] = B[i][j];
}
void copystruct(myArray &m1, myArray &m2) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			m1.par[i][j] = m2.par[i][j];
			m1.arr[i][j] = m2.arr[i][j];
		}
	m1.actual_cost = m2.actual_cost;
	m1.h_value = m2.h_value;
}
bool isEmpty(myArray &state) {
	if (state.h_value == 0 && state.actual_cost == 0) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (state.arr[i][j] != 0 || state.par[i][j] != 0)
					return false;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (state.par[i][j] != 0)
					return false;
		return true;
	}
	else
		return false;
}
void clearStruct(myArray &new1) {
	int Z[3][3] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 } };
	copyArray(new1.par, Z);
	copyArray(new1.arr, Z);
	new1.actual_cost = new1.h_value = 0;
}
myArray make_move(myArray &state, char c) {
	myArray new1;
	clearStruct(new1);
	int x, y;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (state.arr[i][j] == 0) {
				x = i;
				y = j;
			}
	int n;
	bool u_exist = false, d_exist = false, r_exist = false, l_exist = false;
	if (c == 'u') {
		n = x - 1;
		if (n >= 0)
			u_exist = true;
	}
	else if (c == 'd') {
		n = x + 1;
		if (n < 3)
			d_exist = true;
	}
	else if (c == 'r') {
		n = y + 1;
		if (n < 3)
			r_exist = true;
	}
	else if (c == 'l') {
		n = y - 1;
		if (n >= 0)
			l_exist = true;
	}
	if (!u_exist && !d_exist && !r_exist && !l_exist)
		return new1;
	copystruct(new1, state);
	copyArray(new1.par, new1.arr);
	if (u_exist || d_exist) {
		int temp = new1.arr[n][y];
		new1.arr[n][y] = new1.arr[x][y];
		new1.arr[x][y] = temp;
	}
	else if (r_exist || l_exist) {
		int temp = new1.arr[x][n];
		new1.arr[x][n] = new1.arr[x][y];
		new1.arr[x][y] = temp;
	}
	Heuristic(new1);
	new1.actual_cost = state.actual_cost + 1;
	return new1;
}
void sort_queue(vector<myArray>& myVector) {
	for (unsigned int i = 0; i < myVector.size() - 1; i++)
		for (unsigned int j = i; j < myVector.size(); j++) {
			if (myVector[i].h_value + myVector[i].actual_cost > myVector[j].h_value + myVector[j].actual_cost) {
				myArray temp;
				copystruct(temp, myVector[i]);
				copystruct(myVector[i], myVector[j]);
				copystruct(myVector[j], temp);
			}
		}
}
bool isEqual(int A[3][3], int B[3][3]) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (A[i][j] != B[i][j])
				return false;
	return true;
}
void show_Initial(int A[3][3], int B[3][3]) {
	SetConsoleTextAttribute(hConsole, 14);
	cout << "Initial State:      Goal State:\n";
	SetConsoleTextAttribute(hConsole, 15);
	for (int i = 0; i < 3; i++) {
		cout << "    ";
		for (int j = 0; j < 3; j++) {
			if (A[i][j] == 0)
				SetConsoleTextAttribute(hConsole, 12);
			cout << A[i][j] << "  ";
			if (A[i][j] == 0)
				SetConsoleTextAttribute(hConsole, 15);
		}
		if (i == 1)
			cout << "  -->   ";
		else
			cout << "\t     ";
		for (int j = 0; j < 3; j++) {
			if (B[i][j] == 0)
				SetConsoleTextAttribute(hConsole, 12);
			cout << B[i][j] << "  ";
			if (B[i][j] == 0)
				SetConsoleTextAttribute(hConsole, 15);
		}
		cout << endl;
	}
	cout << endl;
}
void insertInQueue(vector<myArray> &myVector, char c, myArray &state) {
	myArray move = make_move(state, c);
	if (!isEmpty(move))
		myVector.push_back(move);
}
int BestFirstSearch(myArray &state) {
	int Goal[3][3] = { { 1,8,7 },{ 2,0,6 },{ 3,4,5 } };
	show_Initial(state.arr, Goal);
	vector<myArray> Queue;
	while (true) {
		if (isEqual(state.arr, Goal))
			return state.actual_cost;
		else {
			insertInQueue(Queue, 'u', state);
			insertInQueue(Queue, 'd', state);
			insertInQueue(Queue, 'r', state);
			insertInQueue(Queue, 'l', state);
			sort_queue(Queue);
		}
		if (isEqual(Queue[0].arr, state.arr))
			return -1;
		if (Queue.empty())
			return -1;
		copystruct(state, Queue[0]);
		Queue.erase(Queue.begin());
	}
}
void which_Heuristic() {
	SetConsoleTextAttribute(hConsole, 7);
	if (H == 1)
		cout << "Heuristic 1 used: Sum Of Euclidean distances of the tiles from their goal position.";
	else
		cout << "Heuristic 2 used: Number of tiles out of row + Number of tiles out of column.";
	cout << endl << endl;
	SetConsoleTextAttribute(hConsole, 15);
}
int main() {

	int A[3][3] = { { 1,7,0 },
					{ 2,8,6 },
					{ 3,4,5 } };
	myArray state;
	clearStruct(state);
	copyArray(state.arr, A);
	state.actual_cost = cost++;
	set_Heuristic();
	Heuristic(state);
	int found = BestFirstSearch(state);
	which_Heuristic();
	cout << "Goal ";
	SetConsoleTextAttribute(hConsole, 12);
	if (found >= 0) {
		cout << "FOUND";
		SetConsoleTextAttribute(hConsole, 15);
		cout << " at depth " << found << ".\n";
	}
	else {
		cout << "NOT FOUND.\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	return 0;
}


