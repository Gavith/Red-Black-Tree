#include "RBTree.h"



RBTree::RBTree()
{

}


RBTree::~RBTree()
{
}

void RBTree::insert(int val)
{
	BSTinsert(head, new Node(val));
}



void RBTree::BSTinsert(Node * &root, Node * newNode)
{
	if (root == nullptr) {
		root = newNode;//if theres nothing in the tree
	}
	else if (!root->val) {
		return;//if theres something wrong
	}
	else if (newNode->val >= root->val) {//if the key is bigger or equal
		if (!root->right) {//if theres no node
			root->right = newNode;//add it
			newNode->parent = root;
		}
		else {
			BSTinsert(root->right, newNode);//otherwise, go to the next node
		}
	}
	else if (newNode->val < root->val) {//if the ket is less than
		if (!root->left) {//i ftheres nothing in the node
			root->left = newNode;//add it
			newNode->parent = root;
		}
		else {
			BSTinsert(root->left, newNode);//otherwise, go to the next node
		}
	}
}



void RBTree::printTree()
{
	printTreeUtil(head, 0);
}
//TAKEN FROM https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void RBTree::printTreeUtil(Node * root, int space)
{
	// Base case 
	if (root == nullptr)
		return;

	// Increase distance between levels 
	space += SPACE;

	//print right side 
	printTreeUtil(root->right, space);

	// Print current node after space 
	// count 
	cout << '\n';
	for (int i = SPACE; i < space; i++)
		cout << " ";
	cout << root->val << endl;

	// Process left child 
	printTreeUtil(root->left, space);
}