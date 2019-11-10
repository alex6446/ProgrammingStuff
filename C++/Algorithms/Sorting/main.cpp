#include <iostream>
#include <ctime>

using namespace std;

void Fill (int arr[], int N) {
	for (int i = 0; i < N; i++)
		arr[i] = rand()%1000;
}

void Show (int arr[], int N) {
	for (int i = 0; i < N; i++)
		cout << arr[i] << endl;
}

void BubbleSort (int arr[], int N) {
	for (int i = N-1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if (arr[j] > arr[j+1])
				swap(arr[j], arr[j+1]);
}

void SelectionSort (int arr[], int N) {
	for (int i = 0; i < N; i++) {
		int min = i;
		for (int j = i+1; j < N; j++)
			if (arr[j] < arr[min])
				min = j;
		swap(arr[i], arr[min]);
	}
}

void QuickSort (int arr[], int l, int r) {
	int i = l;
	int j = r;
	int middle = arr[(i+j)/2];

	do {

		while (middle > arr[i]) i++;
		while (middle < arr[j]) j--;

		if (i <= j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}

	} while (i < j);

	if (i < r) QuickSort(arr, i, r);
	if (j > l) QuickSort(arr, l, j);

}

void CountingSort (int arr[], int N) {
	int max = arr[0];
	for (int i = 1; i < N; i++)
		if (arr[i] > max)
			max = arr[i];
	max++;

	int *count = new int[max];
	for (int i = 0; i < max; i++)
		count[i] = 0;

	for (int i = 0; i < N; i++)
		count[arr[i]]++;

	for (int i = 1; i < max; i++)
		count[i] += count[i-1];

	int *temp = new int[N];
	for (int i = 0; i < N; i++) {
		temp[count[arr[i]]-1] = arr[i];
		count[arr[i]]--;
	}

	for (int i = 0; i < N; i++)
		arr[i] = temp[i];
}

void Merge (int arr[], int l, int m, int r) { 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 =  r - m; 
	
	int L[n1], R[n2]; 

	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j]; 

	i = 0; 
	j = 0; 
	k = l; 
	while (i < n1 && j < n2) { 
		if (L[i] <= R[j]) { 
			arr[k] = L[i]; 
			i++; 
		} else { 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 
	while (i < n1) { 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 
	while (j < n2) { 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 

void MergeSort (int arr[], int l, int r) { 
    if (l < r) { 
        int m = l+(r-l)/2; 
  
        MergeSort(arr, l, m); 
        MergeSort(arr, m+1, r); 
  
        Merge(arr, l, m, r); 
    } 
} 

void ShellSort (int arr[], int N) {
	for (int gap = N/2; gap > 0; gap /= 2) {
		for (int i = gap; i < N; i++) {
			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j-gap] > temp; j -= gap)
				arr[j] = arr[j-gap];
			arr[j] = temp;
		}
	}
}

void heapify (int arr[], int n, int i) { 
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest]) 
        largest = l; 

    if (r < n && arr[r] > arr[largest]) 
        largest = r; 

    if (largest != i) { 
        swap(arr[i], arr[largest]); 
        heapify(arr, n, largest); 
    } 
} 

void HeapSort (int arr[], int n) { 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 

    for (int i=n-1; i>=0; i--) { 
        swap(arr[0], arr[i]); 
        heapify(arr, i, 0); 
    } 
} 

int getMax(int arr[], int n) 
{ 
    int mx = arr[0]; 
    for (int i = 1; i < n; i++) 
        if (arr[i] > mx) 
            mx = arr[i]; 
    return mx; 
} 

void countSort(int arr[], int n, int exp) 
{ 
    int output[n];
    int i, count[10] = {0}; 

    for (i = 0; i < n; i++) 
        count[ (arr[i]/exp)%10 ]++; 

    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    for (i = n - 1; i >= 0; i--) { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    } 

    for (i = 0; i < n; i++) 
        arr[i] = output[i]; 
} 

void RadixSort(int arr[], int n) { 
    int m = getMax(arr, n); 

    for (int exp = 1; m/exp > 0; exp *= 10) 
        countSort(arr, n, exp); 
} 

int main() {

	srand(time(NULL));
	int N = 50;
	int *arr = new int[N];
	Fill(arr, N);
	Show(arr, N);
	cout << "--------------------------" << endl;

	//BubbleSort(arr, N);
	//SelectionSort(arr, N);
	//QuickSort(arr, 0, N-1);
	//CountingSort(arr, N);
	//MergeSort(arr, 0, N-1);
	//ShellSort(arr, N);
	//HeapSort(arr, N);
	RadixSort(arr, N);

	Show(arr, N);
}

// Bubble Sort
// Selection Sort
// Quick Sort
// Counting Sort
// Merge Sort
// Shell Sort
// Heap Sort
// Radix (LSD)


//////////////////////////////////////////////////////////////


/*int* Merge (int arrOne[], int arrTwo[], int nOne, int nTwo) {
	int *arr = new int[nOne+nTwo];
	int i = 0;
	int j = 0;
	int index = 0;

	while (i < nOne && j < nTwo) {
		if (arrOne[i] < arrTwo[j]) {
			arr[index] = arrOne[i];
			i++;
		} else { 
			arr[index] = arrTwo[j];
			j++;
		}
		index++;
	}
	while (i < nOne) {
		arr[index] = arrOne[i];
		index++;
		i++;
	}
	while (j < nTwo) {
		arr[index] = arrTwo[j];
		index++;
		j++;
	}
	return arr;
}

int* MergeSort (int arr[], int N) {
	if (N == 1)
		return arr;

	int mid = N/2;

	int *arrOne = new int[mid];
	int *arrTwo = new int[N-mid];

	for (int i = 0; i < mid; i++)
		arrOne[i] = arr[i];
	for (int i = mid; i < N; i++)
		arrTwo[i] = arr[i];

	arrOne = MergeSort(arrOne, mid);
	arrTwo = MergeSort(arrTwo, N-mid);

	return Merge(arrOne, arrTwo, mid, N-mid);
}*/