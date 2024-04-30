#include <iostream>

using namespace std;

// Merge function to merge two sorted arrays
void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
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

    // Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        // Find the middle point
        int mid = left + (right - left) / 2;
#pragma omp parallel sections
        {

#pragma omp section
            {
                mergeSort(arr, left, mid);
            }

#pragma omp section
            {
                mergeSort(arr, mid + 1, right);
            }
        }

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int main()
{

    // This is random number arrray generation for testing
    /*
    const int size = 100000;
    int *arr = new int[size];

    // Generate random numbers
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 100000;
    }
*/

    // Comment the mentioned section of code for testing of time

    // Comment start - '/*'
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    int arr[n];
    cout << "Enter " << n << " elements:" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Given array is: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    // Comment end - '*/'

    // start =.......
    mergeSort(arr, 0, n - 1);
    // stop…….

    // cout<<"Time taken"<<stop-start;

    cout << "Sorted array is: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
