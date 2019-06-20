

//=====================================AVL=========================================

#include<iostream>
using namespace std;

class Node
{
public:
	unsigned int key;
	Node *left = NULL;
	Node *right = NULL;
	int height;
	Node(unsigned int data) {
		this->height = 1;
		this->key = data;
	}
};

int max(int a, int b)
{
	return (a > b) ? a : b;
}


int height( Node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}


 // right rotation
Node *rightRotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;

	// Perform rotation 
	x->right = y;
	y->left = T2;

	// Update heights 
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	// Return new root 
	return x;
}

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
Node *leftRotate(Node *x)
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

Node* insert(Node* node, int key)
{
	/* 1.  Perform the normal BST insertion */
	if (node == NULL)
		return new Node(key);

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else // Equal keys are not allowed in BST 
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left),
		height(node->right));

	/* 3. Get the balance factor of this ancestor
	node to check whether this node became
	unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);

	// Right Right Case 
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);

	// Left Right Case 
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case 
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}


/* Given a non-empty binary search tree, return the
node with minimum key value found in that tree.
Note that the entire tree does not need to be
searched. */
Node * minValueNode(Node* node)
{
	Node* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}


Node* deleteNode(Node* root, unsigned int key)
{
	// STEP 1: PERFORM STANDARD BST DELETE 

	if (root == NULL)
		return root;

	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);

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
				*root = *temp; 
			delete temp;
		}
		else
		{
			Node* temp = minValueNode(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right, temp->key);
		}
	}

	// If the tree had only one node then return 
	if (root == NULL)
		return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
	root->height = 1 + max(height(root->left), height(root->right));


	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
	// check whether this node became unbalanced
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


// print PreOder
void preOrder(Node *root)
{
	if (root != NULL)
	{
		
		cout << "(";
		cout << root->key;
		preOrder(root->left);
		preOrder(root->right);
		cout << ")";
		
	}
}


int main()
{
	Node *root = NULL;
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 25);
	root = insert(root, 50);
	root = insert(root, 80);
	root = insert(root, 90);

	root = deleteNode(root, 50);


	cout << "Preorder traversal of the constructed AVL: \n";
	preOrder(root);
	system("pause");
	return 0;
}