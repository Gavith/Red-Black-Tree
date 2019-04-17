#include "RBTree.h"

//THIS IS A TEST COMMENT

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
	deleteUtil(val);
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
	if (root->color == RED) {
		cout << "\033[91m";
	}
	cout << root->val << "\033[0m" << endl; 

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

void RBTree::deleteUtil (int key)
{
	Node* v = nullptr;
	Node* u = nullptr;
	v = BSTdeleteUtil(head, key);//get the v node
	if (v->right) u = v->right;//get u node
	else if (v->left) u = v->left;

	cout << v->val << endl;

	if (v->color == RED) { //---Red Case
		if (v == v->parent->right) v->parent->right = u; //set parent's downwards connection
		else if (v == v->parent->left) v->parent->left = u;
		if (u) {//if u is an actual node
			u->parent = v->parent; //set its parent
			u->color = BLACK;
		}
		delete v;
	}
	else if (v->color == BLACK) { //---Double Black Case
		
		if (v == v->parent->right) v->parent->right = u; //set parent's downwards connection
		else if (v == v->parent->left) v->parent->left = u;
		if (u) {//if u is an actual node
			u->parent = v->parent; //set its parent
		}
		Node* p = v->parent;
		delete v;
		removeDoubleBlack(u, p);
		
	}

}


void RBTree::removeDoubleBlack(Node* &u, Node* parent)
{
	Node* s = nullptr;
	Node* p = parent;
	Node* r = nullptr;

	//delete it
	
	//Modifying the tree
	if (p) {//if its not head
		if (u == p->right)  s = p->left;//get sibling
		else if (u == p->left) s = p->right;
		if (s->color == BLACK) {
			if ((s->right && s->right->color == RED) || (s->left && s->left->color == RED)) {//--one of s's children is red


				if (s->right && s->right->color == RED) r = s->right;
				else if (s->left && s->left->color == RED) r = s->left;

				if (p->right == s && s->right == r) {//-Right Right Case
					s->color = p->color;
					rotateLeft(head, p);
					p->color = BLACK;
					r->color = BLACK;
				}
				else if (p->right == s && s->left == r) {//-Right Left Case
					rotateRight(head, s);
					swapNodeColor(s, s->parent);
					r->color = p->color;
					rotateLeft(head, p);
					p->color = BLACK;
					s->color = BLACK;
				}
				else {//left cases
					//if r can be either I want it to be left during left and right during right
					//so I repeat this with left priority
					if (s->left && s->left->color == RED) r = s->left;
					else if (s->right && s->right->color == RED) r = s->right;

					if (p->left == s && s->left == r) {//-Left Left
						s->color = p->color;
						rotateLeft(head, p);
						p->color = BLACK;
						r->color = BLACK;
					}
					else if (p->left == s && s->right == r) {//-Left Right
						rotateLeft(head, s);
						swapNodeColor(s, s->parent);
						r->color = p->color;
						rotateRight(head, p);
						p->color = BLACK;
						s->color = BLACK;
					}
				}

			}
			else if (s->color == BLACK && ((!s->left || s->left->color == BLACK) && (!s->right || s->right->color == BLACK))) {//--all black case
				s->color = RED;//This is some janky-ass recursion
				if (p->color = RED) {
					p->color = BLACK;
				}
				else {
					removeDoubleBlack(p, p->parent);
				}
			}
			else if (s->color == RED) {//sibling red
				if (p->left == s) {
					rotateRight(head, p);
					removeDoubleBlack(u, u->parent);
				}
				else if (p->right == s) {
					rotateLeft(head, p);
					removeDoubleBlack(u, u->parent);
				}
			}
		}
	}
}


//deletes the node from a given key
//modified for RBTree
Node* RBTree::BSTdeleteUtil(Node *&root, int key) {
	if (root == nullptr) {//if theres nothing in the root
		return nullptr;
	}
	if (root->val > key) {//if the node we're looking for is less than the current node
		return BSTdeleteUtil(root->left, key);
	}
	else if (root->val < key) {//if the node we're looking for is greater than the current node
		return BSTdeleteUtil(root->right, key);
	}
	else {//if its equal

		if (root->left && root->right) { //it has two children
			Node* min = minval(root->right);//find the minimum value of the right nodes
			root->val = min->val;//set the node found
			return BSTdeleteUtil(root->right, min->val);//delete the node found
		}
		else {//if it has one or 0 children we are clear to delete so pass it back
			return root;
		}

	}
	return nullptr;

}

Node* RBTree::minval(Node * root)
{
	Node* cn = root;

	while (cn->left) {
		cn = cn->left;
	}

	return cn;
}
