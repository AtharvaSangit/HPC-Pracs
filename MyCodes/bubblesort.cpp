#include <iostream>
#include <omp.h>

using namespace std;

void bubbleSort(int *arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        #pragma omp parallel for shared(arr)
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    
    int *arr = new int[size];
    
    cout << "Enter " << size << " elements of the array: ";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }
    
    cout << "Array before sorting: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    bubbleSort(arr, size);
    
    cout << "Array after sorting: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    //delete[] arr; // Free dynamically allocated memory
    
    return 0;
}
