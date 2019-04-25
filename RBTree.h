#include <iostream>

#define SPACE 5
enum Color {RED, BLACK, BBLUE, RBLUE}; //BBLUE and RBLUE are for saving the old color when finding

using namespace std;

struct Node {
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int val = 0;
	Color color = BLACK;

	Node(int val) {
		this->val = val;
	}//h
};

class RBTree
{
public:
	RBTree();
	~RBTree();
	void insert(int val);
	void printTree();
	void resetTree();
	bool searchForNode(int val);
	Node* search(int val);
	void remove(int val);

private:
	Node* head;

	

	void resetTreeUtil(Node* root);
	void BSTinsert(Node* &root, Node* newNode);
	void printTreeUtil(Node* root, int space);
	void fixTree(Node* &head, Node* nn); 
	Node* getUncle(Node* n);
	void rotateRight(Node* &head, Node* root);
	void rotateLeft(Node* &head, Node* root);
	void swapColor(Node* n);
	void swapNodeColor(Node* n, Node* n2);
	Node* searchUtil(Node* root, int val);
	void deleteUtil(int key);
	Node* BSTdeleteUtil(Node *& root, int key);
	void removeDoubleBlack(Node* &u, Node* parent);
	Node* minval(Node *root);



};

