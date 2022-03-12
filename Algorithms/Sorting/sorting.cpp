#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

/* 
I have performed the sorting into ascending order, that sorted array starts from
smallest element and ends with the largest element.
*/

int MergeCount;  // a counter for comparison in mergesort
int QuickCount; // a counter for comparison in quicksort
int HeapCount;  // a counter for comparison in heapsort

unsigned int seed=1;  // the random generator seed

/* ================================================================ 
					BASIC ARRAY FUNCTIONS
   ================================================================ */

void displayArray(int arr[], int length) {
	// display function for an array
	cout << "[ ";
	for (int i = 0; i < length; i++) {
		cout << arr[i] << ", ";
	}
	cout << "]" << endl;
}

void generateArray(int arr[], int length) {
	srand(seed); // set random seed
	seed += 1;
	// generate elements of a given array
	for (int i = 0; i < length; i++) {
		arr[i] = rand() % 10000; //some randomnumber
	}
}


/* ================================================================ 
						MERGESORT
   ================================================================ */

void mergestep(int arr[], int left, int middle, int right) {
	
	int length = (right - left + 1);
	int temp[length];  // a temporary subarray
	
	int l = left; // index of left subarray
	int r = (middle+1); // index of right subarray
	int i = 0; // index of temporary subarray
	
	while (l <= middle && r <= right) {
		if (arr[l] < arr[r]) {
			MergeCount++;  // a comparison is performed <----------------
			temp[i] = arr[l];
			l++;
		}
		
		else {
			// here arr[l] >= arr[r]
			MergeCount++; // a comparison is performed <-----------------------
			temp[i] = arr[r];
			r++;
		}
		
		// after updatation, move onto next position of temporary subarray
		i++;
	}
	
	// copy the remaining elements, to the temporary array
	while (l <= middle) {
		// that means there are elements to pursue from left subarray
		temp[i] = arr[l];
		l++; i++;
	}
	
	while (r <= right) {
		// that means there are elements to pursue from right subarray
		temp[i] = arr[r];
		r++; i++;
	}
	
	// now copy the temporary array onto the original array;
	
	for (int j = left; j <= right; j++) {
		arr[j] = temp[(j-left)];
	}
	
}

void mergesort(int arr[], int left, int right) {
	// accepts the left and the right index of the array
	if (left < right) {
		int middle = (left + right)/2;
		
		mergesort(arr, left, middle);  // sort the left half
		mergesort(arr, middle+1, right);  // sort the right half
		mergestep(arr, left, middle, right);  // merges the two sorted halves
	}
	
	// else keep it at the same position, and do nothing.
	
}


/* ================================================================ 
						QUICKSORT
   ================================================================ */


int partition(int arr[], int left, int right) {
	// choose the leftmost element as pivot
	int pivot = arr[left];
	int l = left; // the moving index on left side
	int r = right;  // the moving index on right side
	
	while (l < r) {
		while (arr[r] > pivot && l < r) {
			QuickCount++; // a comparison is made <-------------------------------------------
			r--; // decrease the right index if it is already bigger than pivot
		}
		while (arr[l] <= pivot && l < r) {
			QuickCount++;   // a comparison is made <-------------------------------------
			l++;  // increase the left index if it is already smaller than pivot
		}
		// now, there is a number bigger than pivot on left, and smaller than pivot on right, so swap them,
		int temp = arr[l];
		arr[l] = arr[r];
		arr[r] = temp;
	}
	
	// now l=r, however, as r decreases first, so l = r will be somewhere where the element is less than pivot
	// so, swap the current arr[r] or arr[l] with the pivot
	
	
	arr[left] = arr[r];
	arr[r] = pivot;
	
	return l; // return the pivot index
}


void quicksort(int arr[], int left, int right) {
	if (left < right) {
		// the array is of atleast length 1
		int pivotIndex = partition(arr, left, right);
		
		quicksort(arr, left, (pivotIndex - 1));
		quicksort(arr, (pivotIndex + 1), right);
	}
		
}


/* ================================================================ 
						HEAPSORT
   ================================================================ */


void addElemtoHeap(int heap[], int elem, int index) {
	// adds element to the max-heap
	heap[index] = elem;
	if (index!= 0) {
		while (heap[(index-1)/2] < heap[index]) {
			HeapCount++; // a comparison is made <--------------------------------------
			// that means we need to swap it with its parent
			int temp = heap[index];
			heap[index] = heap[(index-1)/2];
			heap[(index-1)/2] = temp;
			
			// update the index to be the parent's index
			index = (index-1)/2;
			
			if (index==0) {
				// then we have reached the root
				break;
			}
		}
	}
}

int RemovefromHeap(int heap[], int n) {
	// n is the size of the heap
	int root = heap[0];
	
	heap[0] = heap[n-1]; // move the last added element at the root
	int index = 0;
	
	while ((2*index)+1 <n || (2*index)+2 < n) {
		
		// that means we have atleast one child
		if ((2*index)+1 <n && (2*index)+2 <n) {
			// that means both the child is present, so we need to swap the maximum valued child with its parents, 
			// if it exceeds the parent, so two comparisons are performed
			HeapCount += 2;
			if (heap[(2*index)+1] >= heap[(2*index)+2] && heap[(2*index)+1] > heap[index]) {
				// that means child one is bigger than child two and the parent, so we swap
				int temp = heap[index];
				heap[index] = heap[(2*index)+1];
				heap[(2*index)+1] = temp;
				
				// update the index
				index = (2*index)+1;
			}
			
			else if (heap[(2*index)+2] > heap[(2*index)+1] && heap[(2*index)+2] > heap[index]) {
				// that means child two is larged than child one and the parent, so we swap
				int temp = heap[index];
				heap[index] = heap[(2*index)+2];
				heap[(2*index)+2] = temp;
				
				// update the index
				index = (2*index)+2;
			}
			
			else {
				// nothing to update, so break
				break;
			}
			
		}
		else {
			// there is only one child
			HeapCount++; // a comparison is performed <---------------------
			if(heap[index] < heap[(2*index)+1]) {
				// that means parent is larger and we need to swap
				int temp = heap[index];
				heap[index] = heap[(2*index)+1];
				heap[(2*index)+1] = temp;
				
				// update the index
				index = (2*index)+1;
			}
			
			else {
				// nothing to update, so break
				break;
			}
		}
			
	}
	
	return root;
}

void heapsort(int arr[], int n) {
	// create a blank heap
	int heap[n];
	
	for (int i=0; i<n; i++) {
		addElemtoHeap(heap, arr[i], i);
	}
	
	for (int i=(n-1); i>=0; i--) {
		arr[i] = RemovefromHeap(heap, (i+1));
	}	
	
}

/*  ====================================================================== 
						SIMULATION FUNCTION
 ==========================================================================*/

void simulateComparison(int n, int repeat) {
	// simulate generation of array and compare number of comparisons
	int array1[n], array2[n], array3[n];  // these 3 arrays holds the copy of same generated array
	
	int MergeTotalCount = 0;
	int QuickTotalCount = 0;
	int HeapTotalCount = 0;
	
	for (int i=0; i<repeat; i++) {
		generateArray(array1, n);
		for (int i=0; i<n; i++)
			array2[i] = array1[i];    // copy the generated array to 2nd one
		for (int i=0; i<n; i++)
			array3[i] = array1[i];    // copy the generated array to 3rd one
	
		MergeCount = 0;
		QuickCount = 0;
		HeapCount = 0;
		
		// now perform comparing
		mergesort(array1, 0, (n-1));
		quicksort(array2, 0, (n-1));
		heapsort(array3, n);
		
		MergeTotalCount += MergeCount;  // contains the number of comparison for only this arrays
		QuickTotalCount += QuickCount; 
		HeapTotalCount += HeapCount;
		
		ofstream myfile;
		myfile.open("ComparisonData.txt", ios::app);
		myfile << n << "\t" << MergeCount <<"\t" << QuickCount << "\t" << HeapCount << "\n";
		myfile.close();
	}
	
	cout << "Comparison:\tMerge Sort: " << (MergeTotalCount/repeat) << "\tQuick Sort: " 
	     << (QuickTotalCount/repeat) << "\tHeap Sort: " << (HeapTotalCount/repeat) << endl;
	
}

void simulateTime(int n) {
	clock_t t1, t2, t3, t4;
	
	t1 = clock();
	for (int i=0; i<5000; i++) {
		int arr[n];
		generateArray(arr, n);
		mergesort(arr, 0, n-1);
	}
	t2 = clock();
	for (int i=0; i<5000; i++) {
		int arr[n];
		generateArray(arr, n);
		quicksort(arr, 0, n-1);
	}
	t3 = clock();
	for (int i=0; i<5000; i++) {
		int arr[n];
		generateArray(arr, n);
		heapsort(arr, n);
	}
	t4 = clock();
	
	cout << "Time:  \t\tMerge Sort: " << (t2-t1) << "\tQuick Sort: " << (t3-t2) << "\tHeap Sort: " << (t4-t3) << endl;
}


int main() {
	int lengths[8] = {10, 50, 100, 200, 500, 1000, 2500, 5000};
	
	ofstream myfile;
	myfile.open("ComparisonData.txt");
	myfile << "N\tMergeSort\tQuickSort\tHeapSort\n";
	myfile.close();
	
	for (int i=0; i<8; i++) {
		cout << "For n = " << lengths[i] << ":" << endl;
		simulateComparison(lengths[i], 25);
		simulateTime(lengths[i]);
	}
		
	return 0;
}










