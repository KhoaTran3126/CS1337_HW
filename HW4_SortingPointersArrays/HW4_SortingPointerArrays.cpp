#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

const int ArrSize = 40;

// Function Prototypes
void swapIntPtr(int **ptr1, int **ptr2);
void bubbleSort(int *ptrArray[]);
void displayDataArray(int dataArray[], int arrSize);
void displayPtrArray(int *ptrArray[], int arrSize);

int main() {
    // Gets seed from user and seeds the process
    int seed;
    cout << "Enter seed: ";
    cin >> seed;
    srand(seed);
    cout << endl;

    // Dynamically allocate memory for dataArray and ptrArray
    int dataArray[ArrSize] = {0};
    int *ptrArray[ArrSize];

    // Initialize dataArray with random values and ptrArray to point to dataArray
    for (int i = 0; i < ArrSize; i++) {
        dataArray[i] = rand() % 3000;
        ptrArray[i]  = &dataArray[i];
    }

    // Display data before sorting
    cout << "Before Sorting, values in Data Array:\n";
    displayDataArray(dataArray, ArrSize);

    // Display address and data content before sorting
    cout << "Before Sorting, values in Pointer Array and the value it is pointing at:\n";
    displayPtrArray(ptrArray, ArrSize);

    // Sort the pointer array based on the values they point to
    bubbleSort(ptrArray);

    // Display address and data content after sorting
    cout << "After Sorting, values in Pointer Array and the value it is pointing at:\n";
    displayPtrArray(ptrArray, ArrSize);

    // Display data again to show the original order
    cout << "After Sorting, values in Data Array:\n";
    displayDataArray(dataArray, ArrSize);

    return 0;
}

// Function to display the data in the original data array
void displayDataArray(int dataArray[], int ArrSize) {
    for (int i = 0; i < ArrSize; i++) {
        cout << right << setw(6) << dataArray[i];
        // New line every 10 values
        if ((i + 1)%10 == 0)
            cout << endl;
    }
    cout << endl;
}

// Function to display the data pointed to by the pointer array
void displayPtrArray(int *ptrArray[], int ArrSize) {
    for (int i = 0; i < ArrSize; i++) {
        cout << left << setw(6) << ptrArray[i] << "  "  
            << setw(6) << *ptrArray[i];
        // New line every 4 values
        if ((i + 1)%4 == 0)
            cout << endl;
    }
    cout << endl;
}

// Function to swap two pointers
void swapIntPtr(int **ptr1, int **ptr2) {
    int *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

// Bubble Sort algorithm to sort the pointer array based on the values they point to
void bubbleSort(int *ptrArray[]) {
    for (int i=ArrSize-1; i>=1; i--) {
        for (int j=0; j<=i-1; j++) {
            // If big value appears before small value, swaps position
            if (*ptrArray[j] > *ptrArray[j+1]) 
                swapIntPtr(&ptrArray[j], &ptrArray[j+1]);
        }
    }
}

