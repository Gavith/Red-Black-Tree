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
private:
	Node* head;

	void BSTinsert(Node* &root, Node* newNode);
	void printTreeUtil(Node* root, int space);

};

