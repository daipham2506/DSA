#include<iostream>
#include<string>
#include<fstream>
using namespace std;

// An AVL tree node 
struct Node
{
	string name;
	string phone;
	Node *left;
	Node *right;
	int height;
};


// A utility function to get height of the tree 
int height(Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

// A utility function to get maximum of two integers 
int max(int a, int b)
{
	return (a > b) ? a : b;
}


Node* newNode(string name, string phone)
{
	Node* node = new Node();
	node->name = name;
	node->phone = phone;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return node;
}


Node *rightRotate(Node *&y)
{
	struct Node *x = y->left;
	struct Node *T2 = x->right;

	// Perform rotation 
	x->right = y;
	y->left = T2;

	// Update heights 
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	// Return new root 
	return x;
}


Node *leftRotate(Node *&x)
{
	Node *y = x->right;
	Node *T2 = y->left;

	// Perform rotation 
	y->left = x;
	x->right = T2;

	//  Update heights 
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	// Return new root 
	return y;
}

// Get Balance factor of node N 
int getBalance(Node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}


//===============Question 1====================

Node* insert(Node* &node, Node* p)
{
	/* 1.  Perform the normal BST rotation */
	if (node == NULL)
		return p;

	if (p->name.compare(node->name) < 0)
		node->left=insert(node->left, p);
	else if (p->name.compare(node->name) > 0)
		node->right=insert(node->right, p);

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left),
		height(node->right));

	/* 3. Get the balance factor of this ancestor
	node to check whether this node became
	unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then there are 4 cases 

	// Left Left Case 
	if (balance > 1 && p->name.compare(node->left->name)<0)
		return rightRotate(node);

	// Right Right Case 
	if (balance < -1 && p->name.compare(node->right->name)>0)
		return leftRotate(node);

	// Left Right Case 
	if (balance > 1 && p->name.compare(node->left->name)>0)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case 
	if (balance < -1 && p->name.compare(node->right->name)<0)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}



//===============Question 2====================

Node * minValueNode(Node* node)
{
	Node* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

Node* deleteNode(Node* &root,string name)
{
	// STEP 1: PERFORM STANDARD BST DELETE 

	if (root == NULL)
		return root;

	// If the key to be deleted is smaller than the 
	// root's key, then it lies in left subtree 
	if (name.compare(root->name)<0)
		root->left = deleteNode(root->left, name);

	// If the key to be deleted is greater than the 
	// root's key, then it lies in right subtree 
	else if (name.compare(root->name)<0)
		root->right = deleteNode(root->right, name);

	// if key is same as root's key, then This is 
	// the node to be deleted 
	else
	{
		// node with only one child or no child 
		if ((root->left == NULL) || (root->right == NULL))
		{
			Node *temp = root->left ? root->left : root->right;
			// No child case 
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case 
				*root = *temp; // Copy the contents of 
							   // the non-empty child 
			delete temp;
		}
		else
		{
			// node with two children: Get the inorder 
			// successor (smallest in the right subtree) 
			Node* temp = minValueNode(root->right);

			// Copy the inorder successor's data to this node 
			root->name = temp->name;
			root->phone = temp->phone;
			// Delete the inorder successor 
			root->right = deleteNode(root->right, name);
		}
	}

	// If the tree had only one node then return 
	if (root == NULL)
		return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
	root->height = 1 + max(height(root->left),
		height(root->right));

	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
	// check whether this node became unbalanced) 
	int balance = getBalance(root);

	// If this node becomes unbalanced, then there are 4 cases 

	// Left Left Case 
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case 
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case 
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case 
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}


// =====================Question 3=======================
Node* readingInsertTreeAVL(Node* &root, string filename) {
	ifstream fin;
	fin.open(filename);
	string name, phone;
	while (!fin.eof()) {
		getline(fin, name, ',');
		if (name == "")
			return root;
		getline(fin, phone, '\n');
		Node*p = newNode(name, phone);
		root=insert(root, p);
	}
	return root;
}


void preOderPhone(Node* root) {
	if (root != NULL) {
		cout << root->phone << endl;
		preOderPhone(root->left);
		preOderPhone(root->right);
	}
}


void checkName(Node* root, string name) {
	if (root != NULL) {
		if (name.compare(root->name) < 0)
			checkName(root->left, name);
		else if (name.compare(root->name) > 0)
			checkName(root->right, name);
		else {
			cout << root->name << " - " << root -> phone;
			return;
		}
	}
}

Node*checkName1(Node* root, string name) {
	if (root != NULL) {
		if (name.compare(root->name) < 0)
			checkName(root->left, name);
		else if (name.compare(root->name) > 0)
			checkName(root->right, name);
		else {
			return root;
		}
	}
}

void writefile(Node* root) {
	ofstream fout;
	fout.open("FileOutput.csv",ios::app);
	if (root != NULL) {
		fout << root->name << ",";
		fout << root->phone << endl;
		writefile(root->left);
		writefile(root->right);
	}
	fout.close();
}
void menu(Node* &root) {

	cout << "================YOUR SELECT================" << endl;
	cout << "1. Search the list for a specified name" << endl;
	cout << "2. Insert a new name" << endl;
	cout << "3. Delete a existing name" << endl;
	cout << "4. Print the entire phone list" << endl;
	cout << "5. Write the data in the list back to the file" << endl;
	int select;
	do {
		cout << "Enter your select: ";
		cin >> select;
	} while (select < 1 || select>5);
	string name, phone;
	if (select == 1) {
		cin.ignore();
		cout << "Enter name: ";
		getline(cin, name);
		checkName(root, name);
	}
	else if (select == 2) {
		cin.ignore();
		cout << "Enter name need insert: ";
		getline(cin, name);
		cout << "Enter phone need insert: ";
		getline(cin, phone);
		Node*p = newNode(name, phone);
		root=insert(root, p);
	}
	else if (select == 3) {
		cin.ignore();
		cout << "Enter name need delete: ";
		getline(cin, name);
		root = deleteNode(root, name);
	}
	else if (select == 4) {
		preOderPhone(root);
	}
	else if (select == 5) {
		writefile(root);
		cout << "Write file successfully" << endl;
	}

}

int main() {
	Node* root = NULL;
	root = readingInsertTreeAVL(root, "list.csv");
	menu(root);
	system("pause");
}



