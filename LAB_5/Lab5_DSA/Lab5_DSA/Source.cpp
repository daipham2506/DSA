#include <iostream>
#include <string>
using namespace std;

class TreeNode {
private:
	string character;
	int count;
	TreeNode * left = NULL;
	TreeNode* right = NULL;
	friend void insert1(TreeNode* &root, TreeNode* node) {
		if (root == NULL)
			root = node;
		else {
			if (node->character.compare(root->character) == -1)
				insert1(root->left, node);
			else if (node->character.compare(root->character) == 1)
				insert1(root->right, node);
			else
				root->count++;
		}
	}
	friend void remove1(TreeNode * &root, string character) {
		if (root == NULL)
			return;
		if (character.compare(root->character) == -1)
			remove1(root->left, character);
		else if (character.compare(root->character) == 1)
			remove1(root->right, character);
		else {
			// Node with only one child or no child 
			if (root->left == NULL) {
				TreeNode* temp = root;
				root = root->right;
				delete temp;
				return;
			}
			else if (root->right == NULL) {
				TreeNode* temp = root;
				root = root->left;
				delete temp;
				return;
			}
			// Node with two children
			// Find largest node a left subtree
			TreeNode* temp = root->left;
			while (temp->right != NULL)
				temp = temp->right;
			root->character = temp->character;
			remove1(root->left, temp->character);
		}
	}
	friend int search1(TreeNode* &root, string character) {
		if (root == NULL)
			return -1;
		else {
			if (root->getChar().compare(character) == -1)
				return search1(root->right, character);
			else if (root->getChar().compare(character) == 1)
				return search1(root->left, character);
			else
				return root->count;
		}
	}
	friend void print1(TreeNode* root) {
		if (root != NULL) {
			cout << root->getChar() << " ";
			print1(root->getLeft());
			print1(root->getRight());
		}
	}
public:
	TreeNode(string character) {
		this->character = character;
		count = 1;
	}
	TreeNode(char character) {
		this->character = character;
		count = 1;
	}
	~TreeNode()
	{
		this->character = "";
		count = 0;
		this->left = this->right = NULL;
	}
	void increaseCount() {
		count++;
	}
	// get/set methods
	int getCount() {
		return count;
	}
	void setCount(int newCount) {
		count = newCount;
	}
	string getChar() {
		return character;
	}
	void setChar(string newChar) {
		character = newChar;
	}
	TreeNode* getLeft() {
		return left;
	}
	void setLeft(TreeNode* newLeft)
	{
		left = newLeft;
	}
	TreeNode* getRight() {
		return right;
	}
	void setRight(TreeNode* newRight) {
		right = newRight;
	}

};

class BinarySearchTree {

public:


	TreeNode * root = NULL;

	void insert(TreeNode* node) {
		if (root != NULL) {
			TreeNode *current = root;
			TreeNode *parent = current;
			while (current != NULL) {
				if (current->getChar() == node->getChar()) {
					current->increaseCount();
					return;
				}
				parent = current;
				if (parent->getChar() > node->getChar()) {
					current = parent->getLeft();
				}
				else {
					current = parent->getRight();
				}
			}
			if (parent->getChar() > node->getChar()) {
				parent->setLeft(node);
				parent->getLeft()->increaseCount();
			}
			else {
				parent->setRight(node);
				parent->getRight()->increaseCount();
			}
		}
		else {
			root = node;
			root->increaseCount();
			return;
		}

	}

	/*void insert(TreeNode* node) {
		insert1(root, node);
	}*/

	void remove(string character) {
		remove1(root, character);
	}

	int search(string character) {
		return search1(root, character);
	}

	void print() {
		print1(root);
		cout << endl;
	}
};

//----------------Question 3--------------------- 
BinarySearchTree* buildTreeFromString(string str) {
	BinarySearchTree* BST = new BinarySearchTree();
	for (int i = 0; i < str.length(); i++) BST->insert(new TreeNode(str[i]));
	return BST;
}

int main() {

	string str = "A binary search tree is a binary tree with the following properties: All items in the left subtree are less than the root.All items in the right subtree are greater than or equal to the root.Each subtree is itself a binary search tree.";
	BinarySearchTree* bst = buildTreeFromString(str);
	bst->print();
	cout << endl;
	cout << "b = " << std::to_string(bst->search("b")) << endl; // 6 times
	cout << "s = " << std::to_string(bst->search("s")) << endl; // 13 times
	cout << "t = " << std::to_string(bst->search("t")) << endl; // 24 times
	system("pause");
	return 0;
}

