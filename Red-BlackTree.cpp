#include "RBTree.h"
#include <iostream>

int main()
{
	RBTree t = RBTree();
	t.insert(10);
	t.insert(2);
	t.insert(20);
	t.printTree();
	t.printTreeColor();
}
