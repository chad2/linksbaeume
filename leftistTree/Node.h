#ifndef NODE_H_
#define NODE_H_

class Node {
public:
	Node(int key, Node* leftLeaf = nullptr, Node* rightLeaf = nullptr);
	virtual ~Node();

	int getDistance() const;
	int getKey() const;
	void setKey(int key);
	Node* getLeftLeaf() const;
	void setLeftLeaf(Node* leftLeaf = nullptr);
	Node* getRightLeaf() const;
	void setRightLeaf(Node* rightLeaf = nullptr);

	void destroyLeafs();
	static Node *unionNode(Node *A, Node *B);
	Node *findAndDeleteNode(Node *toDelete);
	static Node *findAndDeleteNode(Node *root, Node *start, Node **toDelete_ptr);

protected:
	int key = 0;
	int distance = 0;
	Node *leftLeaf = nullptr;
	Node *rightLeaf = nullptr;

	void measureDistance();
};

#endif
