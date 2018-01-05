#include "Node.h"

#include <stdexcept>

using namespace std;

Node::Node(int key, Node *leftLeaf, Node *rightLeaf) {
	this->setKey(key);
	this->distance = 1;
	this->setLeftLeaf(leftLeaf);
	this->setRightLeaf(rightLeaf);

	this->measureDistance();
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

Node *Node::unionNode(Node *A, Node *B) {
	if(A == nullptr) {
		return B;
	}
	if(B == nullptr) {
		return A;
	}

	if(A->getKey() > B->getKey()) {
		Node *temp = A;
		A = B;
		B = temp;
	}

	A->rightLeaf = Node::unionNode(A->rightLeaf, B);

	if(A->leftLeaf == nullptr) {
		A->leftLeaf = A->rightLeaf;
		A->rightLeaf = nullptr;
	} else {
		if(A->leftLeaf->distance < A->rightLeaf->distance) {
			Node *temp = A->leftLeaf;
			A->leftLeaf = A->rightLeaf;
			A->rightLeaf = temp;
		}

		A->distance = A->rightLeaf->distance + 1;
	}

	return A;
}

Node *Node::findAndDeleteNode(Node *toDelete) {
	if(toDelete == nullptr) {
		throw invalid_argument("toDelete is null");
	}

	return Node::findAndDeleteNode(this, this, &toDelete);
}

Node *Node::findAndDeleteNode(Node *root, Node *start, Node **toDelete_ptr) {
	if(root == nullptr) {
		throw invalid_argument("root is NULL");
	}
	if(start == nullptr) {
		throw invalid_argument("start is NULL");
	}
	if(toDelete_ptr == nullptr) {
		throw invalid_argument("toDelete_ptr is NULL");
	}
	if((*toDelete_ptr) == nullptr) {
		throw invalid_argument("*toDelete_ptr is NULL");
	}

	Node *toDelete = *toDelete_ptr;

	Node *result = nullptr;

	if(start == toDelete) {
		result = Node::unionNode(start->getLeftLeaf(), start->getRightLeaf());

		delete start;
		start = nullptr;
		toDelete = nullptr;

		*toDelete_ptr = nullptr;

		return result;
	} else {
		if(start->getLeftLeaf() == toDelete) {
			result = Node::findAndDeleteNode(root, toDelete, toDelete_ptr);
			start->setLeftLeaf(nullptr);
			toDelete = nullptr;

			if(start == root) {
				return Node::unionNode(root, result);
			} else {
				return result;
			}
		} else if(start->getRightLeaf() == toDelete) {
			result = Node::findAndDeleteNode(root, toDelete, toDelete_ptr);
			start->setRightLeaf(nullptr);
			toDelete = nullptr;

			if(start == root) {
				return Node::unionNode(root, result);
			} else {
				return result;
			}
		} else {
			if(start->getLeftLeaf() != nullptr) {
				result = Node::findAndDeleteNode(root, start->getLeftLeaf(), toDelete_ptr);

				if((*toDelete_ptr) == nullptr) {
					if(start == root) {
						return Node::unionNode(root, result);
					} else {
						return result;
					}
				} else if((result != nullptr) && (*toDelete_ptr != nullptr)) {
					throw logic_error("result is not NULL but the toDelete Node has not been deleted");
				}
			}
			if(start->getRightLeaf() != nullptr) {
				result = Node::findAndDeleteNode(root, start->getRightLeaf(), toDelete_ptr);
				start->measureDistance();

				if((*toDelete_ptr) == nullptr) {
					if(start == root) {
						return Node::unionNode(root, result);
					} else {
						return result;
					}
				} else if((result != nullptr) && (*toDelete_ptr != nullptr)) {
					throw logic_error("result is not NULL but the toDelete Node has not been deleted");
				}
			}

			//no Node found
			if(root == start) {
				throw logic_error("toDelete not found in heap");
			}

			return nullptr;
		}
	}
}

void Node::destroyLeafs() {
	if(this->rightLeaf != nullptr) {
		this->rightLeaf->destroyLeafs();

		delete this->rightLeaf;
		this->rightLeaf = nullptr;
	}
	if(this->leftLeaf != nullptr) {
		this->leftLeaf->destroyLeafs();

		delete this->leftLeaf;
		this->leftLeaf = nullptr;
	}
}

int Node::getDistance() const {
	return distance;
}

int Node::getKey() const {
	return key;
}

void Node::setKey(int key) {
	this->key = key;
}

Node* Node::getLeftLeaf() const {
	return leftLeaf;
}

void Node::setLeftLeaf(Node* leftLeaf) {
	this->leftLeaf = leftLeaf;
}

Node* Node::getRightLeaf() const {
	return rightLeaf;
}

void Node::setRightLeaf(Node* rightLeaf) {
	this->rightLeaf = rightLeaf;

	this->measureDistance();
}

void Node::measureDistance() {
	if(this->rightLeaf != nullptr) {
		this->distance = 1 + this->rightLeaf->getDistance();
	} else {
		this->distance = 1;
	}
}
