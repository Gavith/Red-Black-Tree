#include <iostream>

#define SPACE 5
enum Color {RED, BLACK};

using namespace std;

struct Node {
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int val;
	Color color = BLACK;

	Node(int val) {
		this->val = val;
	}
};

class RBTree
{
public:
	RBTree();
	~RBTree();
	void insert(int val);
	void printTree();
	void printTreeColor();
private:
	Node* head;

	void BSTinsert(Node* &root, Node* newNode);
	void printTreeColorUtil(Node * root, int space);
	void printTreeUtil(Node* root, int space);
	void fixTree(Node* head, Node* nn); 
	Node* getUncle(Node* n);
	void rotateRight(Node* &head, Node* root);
	void rotateLeft(Node* &head, Node* root);
	void swapColor(Node* n);
	void swapNodeColor(Node* n, Node* n2);

};

