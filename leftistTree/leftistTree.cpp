#include "leftistTree.h"

#include <stdexcept>
#include <queue>
#include <ctime>
#include <iostream>

using namespace std;

LeftistTree::LeftistTree() {

}

LeftistTree::LeftistTree(int key) {
	makeHeap(key);
}

LeftistTree::~LeftistTree() {
	if(this->start != nullptr) {
		this->start->destroyLeafs();
		delete this->start;
		this->start = nullptr;
	}
}


Node *LeftistTree::makeHeap(int key) {
	if(this->start != nullptr) {
		throw logic_error("this->start != nullptr");
	}

	this->start = new Node(key);

	return this->start;
}

int LeftistTree::getMinimum() const {
	if(this->start == nullptr) {
		throw logic_error("this->start == null");
	}

	this->start->getKey();
}

const Node* LeftistTree::insert(int key) {
	if(this->start == nullptr) {
		return this->makeHeap(key);
	}

	Node *newNode = new Node(key);

	this->start = Node::unionNode(this->start, newNode);

	return newNode;
}

int LeftistTree::extractMin() {
	if(this->start == nullptr) {
		throw logic_error("this->start == nullptr");
	}

	int retKey = this->start->getKey();

	Node *temp = this->start;

	this->start = Node::unionNode(this->start->getLeftLeaf(), this->start->getRightLeaf());

	delete temp;
	temp = nullptr;

	return retKey;
}

LeftistTree LeftistTree::merge(LeftistTree& tree) {
	LeftistTree result;

	//if one of the trees is empty
	if(this->start == nullptr) {
		result = LeftistTree(tree);
		tree.start = nullptr;

		return result;
	} else if(tree.start == nullptr) {
		result = LeftistTree(*this);
		this->start = nullptr;

		return result;
	}

	result.start = Node::unionNode(this->start, tree.start);
	tree.start = nullptr;
	this->start = nullptr;

	return result;
}

void LeftistTree::deleteNode(Node *toDelete) {
	if(toDelete == nullptr) {
		throw invalid_argument("toDelete is null");
	}
	if(this->start == nullptr) {
		throw logic_error("this->start == nullptr");
	}

	this->start = this->start->findAndDeleteNode(toDelete);
}

void LeftistTree::decreaseKey(Node *toDecrease, int newKey) {
	if(toDecrease == nullptr) {
		throw invalid_argument("toDecrease is NULL");
	}
	if(this->start == nullptr) {
		throw logic_error("this->start == nullptr");
	}

	this->deleteNode(toDecrease);
	this->insert(newKey);
}

int main(int argc, char **argv) {
	LeftistTree tree1;
	priority_queue<int, std::vector<int>, std::greater<int>> tree2;

	srand(time(NULL));

	for(int i=0; i < 1000; i++) {
		int temp = rand() % RAND_MAX + 1;
		tree1.insert(temp);
		tree2.push(temp);
	}

	while(tree2.empty() == false) {
		int temp1 = tree1.extractMin();
		int temp2 = tree2.top();
		tree2.pop();

		if(temp1 != temp2) {
			throw;
		}
	}
	cout << "insert & extractMin successful" << endl;


	for(int j=0; j < 10; j++) {
		Node *toDelete = nullptr;
		for(int i=0; i < 1000; i++) {
			int temp = rand() % RAND_MAX + 1;
			if(i == 10) {
				toDelete = (Node*) tree1.insert(temp);
			} else {
				tree1.insert(temp);
				tree2.push(temp);
			}
		}

		tree1.deleteNode(toDelete);
		toDelete = NULL;

		while(tree2.empty() == false) {
			int temp1 = tree1.extractMin();
			int temp2 = tree2.top();
			tree2.pop();

			if(temp1 != temp2) {
				throw;
			}
		}
	}
	cout << "insert & deleteNode successful" << endl;


	for(int i=0; i < 1000; i++) {
		int temp = rand() % RAND_MAX + 1;
		Node *temp_node = (Node*) tree1.insert(temp *2);
		tree2.push(temp);

		tree1.decreaseKey(temp_node, temp);

		for(int i=0; i < 10; i++) {
			int temp = rand() % RAND_MAX + 1;
			tree1.insert(temp);
			tree2.push(temp);
		}
	}

	while(tree2.empty() == false) {
		int temp1 = tree1.extractMin();
		int temp2 = tree2.top();
		tree2.pop();

		if(temp1 != temp2) {
			throw;
		}
	}
	cout << "insert & decreaseKey successful" << endl;

	LeftistTree treeA;
	LeftistTree treeB;

	for(int i=0; i<1000; i++){
		int temp = rand() % RAND_MAX + 1;
		tree2.push(temp);
		i%2 ? treeA.insert(temp) : treeB.insert(temp);
	}

	LeftistTree treeC = treeA.merge(treeB);

	for(int i=0; i<1000; i++){
		int temp1 = treeC.extractMin();
		int temp2 = tree2.top();
		tree2.pop();

		if(temp1 != temp2) {
			throw;
		}
	}
	cout << "insert & merge successful" << endl;

	return 0;
}
