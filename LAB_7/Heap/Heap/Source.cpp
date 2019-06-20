#include<iostream>
#include<string>
#include<vector>
using namespace std;


//bool isMaxHeap(int *arr, int size) {
//	for (int i = 0; i < size; i++) {
//		if (arr[i] < arr[2 * i + 1] || arr[i] < arr[2 * i + 2])
//			return false;
//		if (i > (size - 2) / 2)
//			break;
//	}
//	return true;
//}


int heightNode(int pos) {
	int h = 1;
	float parent = (float)(pos - 1) / 2.0;
	while (parent >= 0) {
		float child = parent;
		parent = (child - 1) / 2;
		h++;
	}
	return h;
}

int height(int size) {
	return log(size) / log(2) + 1;
}
void printNode(int num, int position,int size) {
	int h = height(size) - heightNode(position) + 1;

	if (h == 1) {
		if (num < 10 && num >= 0) cout << "00" + to_string(num);
		else if (num < 100 && num >= 10) cout << "0" + to_string(num);
		else cout << to_string(num);
		cout << "   ";
	}
	else {
		int k = (pow(2, h) - 1) / 4;
		for (int i = 0; i <= k; i++) cout << "   ";
		for (int i = 0; i < k; i++) cout << "---";

		if (num < 10 && num >= 0) cout << "00" + to_string(num);
		else if (num < 100 && num >= 10) cout << "0" + to_string(num);
		else cout << to_string(num);

		for (int i = 0; i < k; i++) cout << "---";
		for (int i = 0; i <= k + 1; i++) cout << "   ";
		int h1 = height(size) - heightNode(position + 1) + 1;
		if (h1 != h) cout << endl;
	}
	
}
void printHeap(int* maxHeap, int size) {
	for (int i = 0; i < size; i++)
		printNode(maxHeap[i], i, size);
}

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}


void reHeapUp(int *&maxHeap, int position) {
	if (position > 0) {
		int parent = (position - 1) / 2;
		if (maxHeap[position] > maxHeap[parent]) {
			swap(maxHeap[position], maxHeap[parent]);
			reHeapUp(maxHeap, parent);
		}
	}
}

void buildHeap(int *&heap, int size) {
	for (int i = 1; i < size; i++)
		reHeapUp(heap, i);
}






////=====================QUESTION 2=================

class Node {
public:
	int data;
	Node*left = NULL;
	Node*right = NULL;
	Node(int x) {
		data = x;
	}
};


void add(Node*&root, int data){
	if (root == NULL)
		root = new Node(data);
	else {
		if (data > root->data)
			add(root->right, data);
		else
			add(root->left, data);
	}
}

void addBST(Node*&root, int n) {
	int data;
	for (int i = 0; i < n; i++) {

		cout << "Insersion #" << i << ": ";
		cin >> data;
		add(root, data);
	}
}

void convertBSTToHeap(Node* root,int* &heap,int size){
	static int i = 0;
	if (root == NULL)
		return;
	else {
		heap[i] = root->data;
		i++;
		convertBSTToHeap(root->left,heap,size);
		convertBSTToHeap(root->right, heap,size);
	}
	buildHeap(heap, size);
}


//===================QUESTION 3===================

int f1(int* arr, int pos) {
	long result = 0;
	for (int i = 0; i <= pos; i++) {
		result += pow(arr[i], i);
	}
	result *= 7;
	int kq = result % 7719;
	return kq;
}

int f2(int* arr, int pos) {
	long result = 0;
	for (int i = 0; i <= pos; i++) {
		result += pow(arr[i], arr[i]);
	}
	result *= 7;
	int kq = result % 7719;
	return kq;
}

//===============QUESTION 4===================



/*void reHeapUp(int *&maxHeap, int position) {
	if (position > 0) {
		int parent = (position - 1) / 2;
		if (maxHeap[position] > maxHeap[parent]) {
			swap(maxHeap[position] , maxHeap[parent]);
			reHeapUp(maxHeap, parent);
		}
	}
}


void reheapDown(int *&maxHeap, int position, int size) {
	int leftChild = position * 2 + 1;
	int rightChild = position * 2 + 2;
	int largeChild;
	if (leftChild <= size - 1) {
		if (rightChild <= size - 1 && maxHeap[rightChild] > maxHeap[leftChild]) 
			largeChild = rightChild;
		else 
			largeChild = leftChild;
		if (maxHeap[largeChild] > maxHeap[position]) {
			swap(maxHeap[largeChild], maxHeap[position]);
			reheapDown(maxHeap, largeChild, size - 1);
		}
	}
}*/

void reHeapMinUp(int *&maxHeap, int position) {
	if (position > 0) {
		int parent = (position - 1) / 2;
		if (maxHeap[position] < maxHeap[parent]) {
			swap(maxHeap[position], maxHeap[parent]);
			reHeapMinUp(maxHeap, parent);
		}
	}
}

void convertMinHeap(int* &maxHeap, int size) {
	for (int i = 1; i < size; i++)
		reHeapMinUp(maxHeap, i);
}




int main() {
	int size = 8;
	int *maxHeap = new int[size];
	maxHeap[0] = 1;
	maxHeap[1] = 0;
	maxHeap[2] = 3;
	maxHeap[3] = 6;
	maxHeap[4] = 80;
	maxHeap[5] = 61;
	maxHeap[6] = 8;
	maxHeap[7] = 23;
	buildHeap(maxHeap, size);
	//convertMinHeap(maxHeap, size);
	printHeap(maxHeap, size);
	cout << endl;
	system("pause");
}




