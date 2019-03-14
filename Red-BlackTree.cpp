#include "RBTree.h"
#include <iostream>

using namespace std;

int main()
{
	RBTree t = RBTree();
	char* input = new char(10);
	while (input[0] != 'q') {
		cin >> input;
		if (input[0] == 'r') {
			t.resetTree();
		}
		else {
			t.insert(atoi(input));
		}
		cout << "Numbers:" << endl;
		t.printTree();
		cout << "Colors:" << endl;
		t.printTreeColor();

	}
	

}
