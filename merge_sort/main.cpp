#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <climits> // for INT_MAX
#include <cstdlib> // rand function
#include <ctime> // time function

// function prototypes
void mergeSort(int [], int, int);
void merge(int [], int, int, int);

// begin program execution
int main(void)
{
	// prompt user for array size
	int size;
	cout << "Enter the array size: ";
	cin >> size;

	// create and initialize the array with random numbers
	int *a = new int[size]; // doesn't check if there is enough memory to allocate
	srand(time(NULL)); // seed the rand function
	cout << "The array contains:\n";
	for(int i = 0; i < size; i++) {
		a[i] = (rand() % 100) + 1;
		cout << ' ' << a[i];
	}
	cout << '\n' << endl;
	
	// call merge sort
	mergeSort(a,0,size-1);

	// print the array
	cout << "After calling merge sort, the array contains:\n";
	for(int i = 0; i < size; i++)
		cout << ' ' << a[i];
	cout << endl;

	// release the memory
	delete [] a;

	return 0;
} // end main function

// splits the array
void mergeSort(int a[], int p, int r)
{
	if(p < r) { // if more than 2 elements
		int q = (p + r)/2; // split array at this index
		mergeSort(a, p, q); // sort left array
		mergeSort(a, q+1, r); // sort right array
		merge(a, p, q, r); // merge both arrays
	}
} // end mergeSort function

// merge the array
void merge(int a[], int p, int q, int r)
{
	int n1 = q - p + 1; // size of left array
	int n2 = r - q; // size of right arrray

	// create two new temporary arrays because the original array will be overwritten
	int *left = new int[n1+1]; // length+1 for optimizing
	int *right = new int[n2+1]; // doesn't check if there is enough memory to allocate

	// initialize the arrays with values from original array
	int i, j;	// declared outside of for loop because it will also be used later
	for(i = 0; i < n1; i++)
		left[i] = a[p + i]; // copy the left half of the original array into the temporary left array
	for(j = 0; j < n2; j++)
		right[j] = a[q + 1 + j]; // copy the right half of the original array into the temporary right array

	// optimizing part: set the last elements to a high number
	left[n1] = right[n2] = INT_MAX;

	// merging part
	i = j = 0; // reinitialize to the beginning of the left and right temporary array
	for(int k = p; k <= r; k++) { // the number of iterations is known since p is the first index and r is the last index
		if(left[i] <= right[j]) { // if the value at the index of the left array is less or equal to the value at the index of the right array 
			a[k] = left[i++]; // insert the value into the original array from the left array
		}
		else { // otherwise
			a[k] = right[j++]; // insert the value into the original array from the right array
		}
	}

	delete [] left; // release the memory
	delete [] right; // release the memory
} // end merge function
