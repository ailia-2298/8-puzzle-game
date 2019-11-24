#include<iostream>
#include <windows.h>
#include<stack>
using namespace std;
HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
int Goal[3][3] = { { 1,8,7 },{ 2,0,6 },{ 3,4,5 } };
struct myArray {
char c; 	
int A[3][3];
};
stack<myArray> mystack;
void copyArray (int A [3] [3], int B [3] [3]) {
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++) 
			A [i] [j] = B [i] [j];
}
void initializeArray (int A [3] [3]) {
	A [0] [0] = 1;
	A [0] [1] = 7;
	A [0] [2] = 6;
	A [1] [0] = 0;
	A [1] [1] = 2;
	A [1] [2] = 5;
	A [2] [0] = 3;
	A [2] [1] = 8;
	A [2] [2] = 4;
}
void printArray (int A[3][3], int B[3][3]) {
	for (int i = 0; i < 3; i++) {
		cout << "    ";
		for (int j = 0; j < 3; j++) {
			if (A[i][j] == 0)
				SetConsoleTextAttribute (hConsole, 12);
			cout << A[i][j] << "  ";
			if (A[i][j] == 0)
				SetConsoleTextAttribute (hConsole, 15);
		}
		if (i == 1)
			cout << "  -->   ";
		else
			cout << "\t     ";
		for (int j = 0; j < 3; j++) {
			if (B[i][j] == 0)
				SetConsoleTextAttribute (hConsole, 12);
			cout << B[i][j] << "  ";
			if (B[i][j] == 0)
				SetConsoleTextAttribute (hConsole, 15);
		}
		cout << endl;
	}
	cout << endl;
}
void show_move (int i, char c) {
	SetConsoleTextAttribute (hConsole, 14);
	if (c == 'u')
		cout << i << ") MOVE \'0\' UP\n\n";
	else if (c =='d')
		cout << i << ") MOVE \'0\' DOWN\n\n";
	else if (c == 'l')
		cout << i << ") MOVE \'0\' LEFT\n\n";
	else if (c == 'r')
		cout << i << ") MOVE \'0\' RIGHT\n\n";
	SetConsoleTextAttribute (hConsole, 15);
}
void store_in_stack (stack<myArray> &mystack, int Arr [3][3], char c) {
	myArray t;
	t.c = c;
	copyArray (t.A, Arr);
	mystack.push(t);
}
void show_stack (int A[3][3], stack<myArray> &mystack) {
	int i = 0;
	int B[3][3];
	copyArray (B, A);
	while (! mystack.empty ()) {
		myArray f = mystack.top ();
		show_move (++i, f.c);
		mystack.pop ();
		printArray (B, f.A);
		copyArray (B, f.A);
	}
}
bool isEqual (int A[3][3]) {
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++)
			if (A[i][j] != Goal[i][j]) 
				return false;
	return true;
}
void up (int A[3][3]) {
	int x, y;
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++)
			if (A[i][j] == 0) {
				x = i;
				y = j;
			}
	int n = x - 1;
	if (n >= 0) {
		int temp = A[n][y];
		A[n][y] = A[x][y];
		A[x][y] = temp;
	}
}
void down (int A[3][3]) {
	int x, y;
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++)
			if (A[i][j] == 0) {
				x = i;
				y = j;
			}
	int n = x + 1;
	if (n < 3) {
		int temp = A[n][y];
		A[n][y] = A[x][y];
		A[x][y] = temp;
	}
}
void right (int A[3][3]) {
	int x, y;
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++)
			if (A[i][j] == 0) {
				x = i;
				y = j;
			}
	int n = y + 1;
	if (n < 3) {
		int temp = A[x][n];
		A[x][n] = A[x][y];
		A[x][y] = temp;
	}
}
void left (int A[3][3]) {
	int x, y;
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++)
			if (A[i][j] == 0) {
				x = i;
				y = j;
			}
	int n = y - 1;
	if (n >= 0) {
		int temp = A[x][n];
		A[x][n] = A[x][y];
		A[x][y] = temp;
	}
}
int DFID (int A[3][3], int val) {
	if (val == 0)
		if (isEqual (A))
			return 1;
		else
			return -1;
	else {
		char c;
		int B[3][3];
		copyArray (B, A);
		up (B);
		c = 'u';
		int ex = DFID (B, (val - 1));
		if (ex == -1) {
			copyArray (B, A);
			down (B);
			c ='d';
			ex = DFID(B, (val - 1));
			if (ex == -1) {
				copyArray (B, A);
				right (B);
				c = 'r';
				ex = DFID (B, (val - 1));
				if (ex == -1) {
					copyArray (B, A);
					left (B);
					c = 'l';
					ex = DFID (B, (val - 1));
					if (ex == -1)
						return -1;
				}
			}
		}
		store_in_stack (mystack, B, c);
		return ex;
	}
}
int runDFID (int A[3][3], int d) {
	int result;
	for (int i = 0; i <= d; i++) {
		result = DFID (A, i);
		if (result > 0)
			return i;
	}
	return -1;
}
int main () {
	int A [3][3];
	SetConsoleTextAttribute (hConsole, 14);
	cout << "Initial State:      Goal State:\n";
	SetConsoleTextAttribute (hConsole, 15);
	initializeArray (A);
	printArray (A, Goal);
	int d;
	cout << "Enter depth bound:";
	cin >> d;
	cout << endl;
	int found = runDFID (A, d);
	if (found == -1) {
		SetConsoleTextAttribute (hConsole, 7);
		cout << "no path goes to goal in this depth bound.\n";
		SetConsoleTextAttribute (hConsole, 15);
	}
	else {
		show_stack (A, mystack);
		SetConsoleTextAttribute (hConsole, 7);
		cout << "Found goal at depth: " << found << endl;
		SetConsoleTextAttribute (hConsole, 15);
	}
	return 0;
}

