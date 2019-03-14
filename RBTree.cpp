#include "RBTree.h"



RBTree::RBTree()
{

}


RBTree::~RBTree()
{
}

void RBTree::insert(int val)
{
	Node* nn = new Node(val);
	nn->color = RED;

	BSTinsert(head, nn);

	
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


void RBTree::fixTree(Node* head, Node* x) {
	if (x == head) {
		x->color = BLACK;
		return;
	}

	Node* n = x;
	Node* parent = n->parent;
	Node* gParent;
	if(parent != nullptr)
		gParent = parent->parent;
	Node* uncle = getUncle(n);

	if (parent->color != BLACK) {
		if (uncle->color == RED) {
			parent->color = BLACK;
			uncle->color = BLACK;
			gParent->color = RED;
			fixTree(head, gParent);
		}
		else if (uncle->color == BLACK) {
			if (parent == gParent->left && n == parent->left) { //left left
				rotateRight(head, gParent);
				swapNodeColor(gParent, parent);
				fixTree(head, parent);
			}
			else if (parent == gParent->left && n == parent->right) { //left right
				rotateLeft(head, parent);
				n = parent;
				rotateRight(head, gParent);
				swapNodeColor(gParent, parent);
			}
			else if (parent == gParent->right && n == parent->right) { //right right
				rotateLeft(head, gParent);
				swapNodeColor(gParent, parent);
			}
			else if (parent == gParent->right && n == parent->left) { //right left
				rotateRight(head, parent);
				n = parent;
				rotateLeft(head, gParent);
				swapNodeColor(gParent, parent);
			}
			
		}
		
	}


}

void RBTree::printTreeColor()
{
	printTreeColorUtil(head, 0);
}
//TAKEN FROM https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void RBTree::printTreeColorUtil(Node * root, int space)
{
	// Base case 
	if (root == nullptr)
		return;

	// Increase distance between levels 
	space += SPACE;

	//print right side 
	printTreeColorUtil(root->right, space);

	// Print current node after space 
	// count 
	cout << '\n';
	for (int i = SPACE; i < space; i++)
		cout << " ";
	if (root->color == RED) {
		cout << "R" << endl;
	}
	else if (root->color == BLACK) {
		cout << "B" << endl;
	}

	// Process left child 
	printTreeColorUtil(root->left, space);
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

Node* RBTree::getUncle(Node* n) {
	if (n == nullptr || n->parent == nullptr || n->parent->parent == nullptr) {
		return nullptr;
	} else if (n->parent->parent->left == n->parent) {
		return n->parent->parent->right;
	} else if (n->parent->parent->right == n->parent) {
		return n->parent->parent->left;
	} else {
		return nullptr;
	}
}

void RBTree::rotateRight(Node* &head, Node * root)
{
	Node* leftTemp = root->left;

	root->left = root->left->right;
	if (root->left != nullptr) root->left->parent = root;

	leftTemp->right = root;
	leftTemp->parent = root->parent;

	if (leftTemp->parent == nullptr) head = leftTemp;
	else if (leftTemp->parent->right == root) leftTemp->parent->right = leftTemp;
	else leftTemp->parent->left = leftTemp;

	root->parent = leftTemp;
}

void RBTree::rotateLeft(Node* &head, Node * root)
{
	Node* rightTemp = root->right;

	root->right = root->right->left;
	if (root->right != nullptr) root->right->parent = root;

	rightTemp->left = root;
	rightTemp->parent = root->parent;

	if (rightTemp->parent == nullptr) head = rightTemp;
	else if (rightTemp->parent->left == root) rightTemp->parent->left = rightTemp;
	else rightTemp->parent->right = rightTemp;

	root->parent = rightTemp;
}

void RBTree::swapColor(Node * n)
{
	if (n->color == RED) n->color = BLACK;
	else n->color = RED;
}

void RBTree::swapNodeColor(Node * n, Node * n2)
{
	Color temp = n->color;
	n->color = n2->color;
	n2->color = temp;
}
