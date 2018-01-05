#ifndef LEFTISTTREE_H_
#define LEFTISTTREE_H_

#include "Node.h"

using namespace std;

class LeftistTree {
public:
	LeftistTree();
	LeftistTree(int key);
	virtual ~LeftistTree();

	int getMinimum() const;
	const Node* insert(int key);
	int extractMin();
	LeftistTree merge(LeftistTree& tree);
	void deleteNode(Node *toDelete);
	void decreaseKey(Node *toDecrease, int newKey);

protected:
	Node *makeHeap(int key);

	Node *start = nullptr;
};

#endif
