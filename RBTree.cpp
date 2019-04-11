#include "RBTree.h"



RBTree::RBTree()
{
	head = nullptr;
}


RBTree::~RBTree()
{	//deletes the tree, nothin else really
	resetTree();
}

void RBTree::insert(int val)
{
	//makes a node
	Node* nn = new Node(val);
	//base color is red
	nn->color = RED;
	//inserts through bst
	BSTinsert(head, nn);
	//then the complicated stuff
	fixTree(head, nn);

	
}

void RBTree::resetTree()
{	//util stuff
	if(head) resetTreeUtil(head);
	head = nullptr;
}

bool RBTree::search(int val)
{
	return searchUtil(head, val);
}

void RBTree::remove(int val)
{
	BSTdelete(val);
}

bool RBTree::searchUtil(Node* root, int val) {
	if (root == nullptr) {
		return false;
	}
	else if (root->val == val) {
		return true;
	}
	else if (val < root->val) {
		return searchUtil(root->left, val);
	}
	else if (val > root->val) {
		return searchUtil(root->right, val);
	}
	return false;
}

void RBTree::resetTreeUtil(Node * root)
{	//deletes the sub-trees before
	if (root->left) resetTreeUtil(root->left);
	if (root->right) resetTreeUtil(root->right);
	delete root;
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

void RBTree::fixTree(Node* &head, Node* x) 
{	//arg this was annoying
	if (x == head) {//if the node is the head
		x->color = BLACK;//make sure it follows the rules
		return;
	}
	//getting all the things
	Node* n = x;
	Node* parent = n->parent;
	Node* gParent = nullptr;
	if(parent != nullptr)//make sure no errors happen
		gParent = parent->parent;
	Node* uncle = getUncle(n);

	if (parent != nullptr && parent->color == RED) {//overarching check
		if (uncle != nullptr && uncle->color == RED) {//case 1
			parent->color = BLACK; //just changes colors and repeats
			uncle->color = BLACK;
			gParent->color = RED;
			fixTree(head, gParent);
		}
		else if ((uncle == nullptr || uncle->color == BLACK) && parent->color == RED) {//case 2
			if (parent == gParent->left && n == parent->left) { //left left
				rotateRight(head, gParent);
				swapNodeColor(gParent, parent);
			}
			else if (parent == gParent->left && n == parent->right) { //left right
				rotateLeft(head, parent);
				rotateRight(head, gParent);
				swapNodeColor(gParent, n);
			}
			else if (parent == gParent->right && n == parent->right) { //right right
				rotateLeft(head, gParent);
				swapNodeColor(gParent, parent);
			}
			else if (parent == gParent->right && n == parent->left) { //right left
				rotateRight(head, parent);
				rotateLeft(head, gParent);
				swapNodeColor(gParent, n);
			}
			
		}
		
	}


}

void RBTree::printTreeColor()
{
	if (head != nullptr) printTreeColorUtil(head, 0);
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
	if (head != nullptr) printTreeUtil(head, 0);
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

Node* RBTree::getUncle(Node* n) 
{	//this function is a mess
	//pretty just checks that nothign is null and then checks if the parent node is the left or right 
	//then returns the other
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
{	//rotation n stuff
	Node* leftTemp = root->left; //make sure nothing is lost

	root->left = root->left->right;
	if (root->left != nullptr) root->left->parent = root; //moving the stuff up

	leftTemp->right = root; //moving the new top node up
	leftTemp->parent = root->parent;

	if (leftTemp->parent == nullptr) head = leftTemp; //set parent
	else if (leftTemp->parent->right == root) leftTemp->parent->right = leftTemp; //make sure the node actually connects to the tree
	else leftTemp->parent->left = leftTemp;

	root->parent = leftTemp; //parents again
}

void RBTree::rotateLeft(Node* &head, Node * root)
{
	Node* rightTemp = root->right;//make sure nothing is lost

	root->right = root->right->left;
	if (root->right != nullptr) root->right->parent = root; //moving the stuff up

	rightTemp->left = root; //moving the new top node up
	rightTemp->parent = root->parent;

	if (rightTemp->parent == nullptr) head = rightTemp; //set parent
	else if (rightTemp->parent->left == root) rightTemp->parent->left = rightTemp; //make sure the node actually connects to the tree
	else rightTemp->parent->right = rightTemp;

	root->parent = rightTemp; //parents again
}

void RBTree::swapColor(Node * n)
{	//unused pay no attention
	if (n->color == RED) n->color = BLACK;
	else n->color = RED;
}

void RBTree::swapNodeColor(Node * n, Node * n2)
{	//swaps the colors of two nodes
	//was lazy, its easy
	Color temp = n->color;
	n->color = n2->color;
	n2->color = temp;
}

void RBTree::BSTdelete(int key)
{
	head = BSTdeleteUtil(head, key);
}
//deletes the node from a given key
Node* RBTree::BSTdeleteUtil(Node *&root, int key) {
	if (root == nullptr) {//if theres nothing in the root
		return root;
	}
	if (root->val > key) {//if the node we're looking for is less than the current node
		root->left = BSTdeleteUtil(root->left, key);
	}
	else if (root->val < key) {//if the node we're looking for is greater than the current node
		root->right = BSTdeleteUtil(root->right, key);
	}
	else {

		if (!root->left && !root->right) { //it has no children
			delete root;
			return nullptr;
		}
		else if (!root->left) {//it has one children
			Node* r = root->right;//move up the single child
			root->right = nullptr;
			delete root;
			return r;
		}
		else if (!root->right) {//it has one children
			Node* r = root->left;//move up the single child
			root->left = nullptr;
			delete root;
			return r;
		}
		else {//i fit has 2 children
			Node* min = minval(root->right);//find the minimum value of the right nodes
			root->val = min->val;//set the node found
			root->right = BSTdeleteUtil(root->right, min->val);//delete the node found
			return root;
		}
	}
	return root;
}

Node* RBTree::minval(Node * root)
{
	Node* cn = root;

	while (cn->left) {
		cn = cn->left;
	}

	return cn;
}
