#include <iostream>

using namespace std;

void printHeap(int* arr, int size) {
	if (size <= 0) return;
	int h = 0;
	int i = 0;
	while (i < size) {
		h++;
		i = 2 * i + 1;
	}
	int max = (int)pow(2, h) - 1;
	for (i = 0; i < max; i++) {
		for (int j = h; j > 0; j--) {
			if ((i + 1) % (int)pow(2, j) == (int)pow(2, j - 1)) {
				int index = (int)pow(2, h - j) - 1 + (max - i) / (int)pow(2, j);
				if (index < size)
					cout << arr[index];
				cout << endl;
				break;
			}
			else cout << "\t\t";
		}
	}
}

bool isMaxHeap(int* arr, int size) {
	for (int i = 0; i < size / 2; i++) {
		if (2 * i + 1 < size && arr[2 * i + 1] > arr[i]) return false;
		if (2 * i + 2 < size && arr[2 * i + 2] > arr[i]) return false;
	}
	return true;
}

void heapDown(int* heap, int position, int size) {
	int left = position * 2 + 1;
	int right = position * 2 + 2;
	if (left < size) {
		int index;
		if (right < size && heap[right] > heap[left])
			index = right;
		else index = left;
		if (heap[index] > heap[position]) {
			swap(heap[index], heap[position]);
			heapDown(heap, index, size);
		}
	}
}

void heapUp(int* heap, int position) {
	if (position > 0) {
		int index = (position - 1) / 2;
		if (heap[position] > heap[index]) {
			swap(heap[position], heap[index]);
			heapUp(heap, index);
		}
	}
}

bool deleteHeapNode(int *&maxHeap, int delPosition, int &size, int &dataOut) {
	if (delPosition < 0 || delPosition >= size) return false;
	dataOut = maxHeap[delPosition];
	swap(maxHeap[delPosition], maxHeap[size - 1]);
	size--;
	if (size == 0) {
		delete[] maxHeap;
		maxHeap = NULL;
		return true;
	}
	int* temp = new int[size];
	for (int i = 0; i < size; i++) {
		temp[i] = maxHeap[i];
	}
	delete[] maxHeap;
	maxHeap = temp;
	if (delPosition < size) {
		if (delPosition > 0 && maxHeap[delPosition] > maxHeap[(delPosition - 1) / 2])
			heapUp(maxHeap, delPosition);
		else heapDown(maxHeap, delPosition, size);
	}
	return true;
}



int main() {
	int size = 6;
	int* arr = new int[6]{ 1200, 523, 1001, 321, 14, 807 };
	printHeap(arr, size);
	int out;
	deleteHeapNode(arr, 3, size, out);
	printHeap(arr, size);
	deleteHeapNode(arr, 1, size, out);
	printHeap(arr, size);
	return 0;
}