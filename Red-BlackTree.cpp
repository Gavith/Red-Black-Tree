#include "RBTree.h"
#include <iostream>

int main()
{
	RBTree t = RBTree();
	t.insert(10);

	t.insert(20);

	t.insert(30);
	
	t.insert(15);
	t.printTree();
	t.printTreeColor();

}
