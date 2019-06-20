

#include<iostream>
using namespace std;

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}


//==============PRINT=============
void print(int arr[], int size) {
	for (int i = 0; i < size; i++) cout << arr[i] << " ";
}

//================INSERTION SORT========================

//void insertionSort(int arr[], int n)
//{
//	for (int i = 1; i < n; i++)
//	{
//		int key = arr[i];
//		int j;
//
//		/* Move elements of arr[0..i-1], that are
//		greater than key, to one position ahead
//		of their current position */
//		for (j = i - 1; j >= 0 && arr[j] > key; j--)
//			arr[j + 1] = arr[j];
//		arr[j + 1] = key;
//		// print step-by-step
//		print(arr, n);
//		cout << endl;
//	}
//}
void insertionSort(int a[], int n) {
	int curr = 1;
	while (curr < n) {
		int temp = a[curr];
		int walker = curr - 1;
		while (walker >= 0 && temp < a[walker]) {
			a[walker + 1] = a[walker];
			walker = walker - 1;
		}
		a[walker + 1] = temp;
		curr++;
		// print step-by-step
		print(a, n);
		cout << endl;
	}
}

void shellSort(int arr[], int n)
{
	// Start with a big gap, then reduce the gap 
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		// Do a gapped insertion sort for this gap size. 
		// The first gap elements a[0..gap-1] are already in gapped order 
		// keep adding one more element until the entire array is 
		// gap sorted  
		for (int i = gap; i < n; i += 1)
		{
			// add a[i] to the elements that have been gap sorted 
			// save a[i] in temp and make a hole at position i 
			int temp = arr[i];

			// shift earlier gap-sorted elements up until the correct  
			// location for a[i] is found 
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];

			//  put temp (the original a[i]) in its correct location 
			arr[j] = temp;
		}
	}
}


//==================SELECTION SORT=====================
void selectionSort(int arr[], int n)
{
	// One by one move boundary of unsorted subarray 
	for (int i = 0; i < n - 1; i++)
	{
		// Find the minimum element in unsorted array 
		int min_idx = i;
		for (int j = i + 1; j < n; j++) 
			if (arr[j] < arr[min_idx]) min_idx = j;

		// Swap the found minimum element with the first element 
		swap(arr[min_idx], arr[i]);
		// print step-by-step
		print(arr, n);
		cout << endl;
	}
}


// ReHeapDown for  Heap Sort
void reheapDown(int *&maxHeap, int position, int size) {
	int leftChild = position * 2 + 1;
	int rightChild = position * 2 + 2;
	int largeChild = leftChild;
	if (leftChild <= size - 1) {
		if (rightChild <= size - 1 && maxHeap[rightChild] > maxHeap[leftChild])
			largeChild = rightChild;
		if (maxHeap[largeChild] > maxHeap[position]) {
			swap(maxHeap[largeChild], maxHeap[position]);
			reheapDown(maxHeap, largeChild, size - 1);
		}
	}
}

// main function to do heap sort 
void heapSort(int arr[], int n)
{
	// Build heap (rearrange array) 
	for (int i = n / 2 - 1; i >= 0; i--) {
		reheapDown(arr, i, n);
		print(arr, n);
		cout << endl;
	}
	// One by one extract an element from heap 
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end 
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap 
		reheapDown(arr, 0, i);
		print(arr, n);
		cout << endl;
	}
}

//=============EXCHANGE SORT===================

void bubbleSort(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++) {
		// Last i elements are already in place    
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) 
				swap(arr[j], arr[j + 1]);
			print(arr, n);
			cout << endl;
		}
	}
				
}


//============== DEVIDE AND CONQUER==================

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(int arr[], int low, int high)
{
	int pivot = arr[high];    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or 
		// equal to pivot 
		if (arr[j] <= pivot)
		{
			i++;    // increment index of smaller element 
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low  --> Starting index,
high  --> Ending index */
void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}


// Merges two subarrays of arr[].
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int *L = new int[n1]; 
	int *R = new int[n2];
	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}



//=============Main====================

int main() {
	int a[] = { 3,7,5,1,9,15,4,8,6 };
	insertionSort(a, 9);
	//shellSort(a, 8);
	//selectionSort(a, 9);
	//heapSort(a, 9);
	//bubbleSort(a, 9);
	//mergeSort(a, 0, 8);
	//quickSort(a,0 ,8);
	//print(a, 9);
	system("pause");
}

