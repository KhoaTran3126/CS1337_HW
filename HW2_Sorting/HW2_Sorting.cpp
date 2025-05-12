#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// Initialize function prototypes
void modifiedSortGPA(double array1[], int array2[], string array3[], int size);
void modifiedSortID(int array2[], double array1[], string array3[], int size);
int linearSearchID(int arr[], int numElems, int value, int &nIter);
int binarySearchID(int arr[], int numElems, int value, int &nIter);

void displayData(int netID_arr[], string major_arr[], double GPA_arr[], int size);
int displayMenu();
int min(int a, int b);

const int NUM_ELMTS = 18;

int main(){
    // netID, major and GPA are parallel arrays
    int    netID[NUM_ELMTS]; // Original netID array
    string major[NUM_ELMTS]; // Original major array
    double GPA[NUM_ELMTS];   // Original GPA array

    // Arrays sorted by GPA
    // sortedNetIDbyGPA and sortedMajorbyGPA are parallel arrays
    int    sortedNetIDbyGPA[NUM_ELMTS];
    string sortedMajorbyGPA[NUM_ELMTS];
    double sortedGPAbyGPA[NUM_ELMTS];
   
    // Arrays sorted by netID
    // sortedMajorbyID and sortedGPAbyID are parallel arrays
    int    sortedNetIDbyID[NUM_ELMTS];
    string sortedMajorbyID[NUM_ELMTS];
    double sortedGPAbyID[NUM_ELMTS];

   
    // Reads user's filename
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    // If file cannot be opened, returns error
    ifstream inputFile(filename);
    if(!inputFile){
        cout << "Could not open file\n";
        cout << "Exiting\n";
        return 1;
    }

    // Reads file data into original arrays
    int arraySize = 0;
    while((arraySize < NUM_ELMTS) &&
          (inputFile >> netID[arraySize] >> major[arraySize] >> GPA[arraySize])){
        arraySize++;
    }

    // Copy contents of original arrays into custom-sorted arrays
    for(int i=0; i<arraySize; i++){
        sortedNetIDbyGPA[i] = netID[i];
        sortedMajorbyGPA[i] = major[i];
        sortedGPAbyGPA[i]   = GPA[i];

        sortedNetIDbyID[i] = netID[i];
        sortedMajorbyID[i] = major[i];
        sortedGPAbyID [i]  = GPA[i];
    }

    // Sort arrays by GPA, maintaining parallelism amongst arrays
    modifiedSortGPA(sortedGPAbyGPA, sortedNetIDbyGPA, sortedMajorbyGPA, arraySize);
    // Sort arrays by ID, maintaining parallelism amongst arrays
    modifiedSortID(sortedNetIDbyID, sortedGPAbyID, sortedMajorbyID, arraySize);
   
    // DISPLAYS ORIGINAL DATA (index, netID, major, GPA)
    cout << "Original arrays:\n";
    cout << "----------------\n";
    displayData(netID, major, GPA, arraySize);
   
    // DISPLAYS ascending-GPA-sorted DATA (index, netID, major, GPA)
    cout << "Arrays sorted by GPA:\n";
    cout << "---------------------\n";
    displayData(sortedNetIDbyGPA, sortedMajorbyGPA, sortedGPAbyGPA, arraySize);
   
    // DISPLAYS ascending-netID-sorted DATA (index, netID, major, GPA)
    cout << "Arrays sorted by netID:\n";
    cout << "-----------------------\n";
    displayData(sortedNetIDbyID, sortedMajorbyID, sortedGPAbyID, arraySize);
   
    // DISPLAYS menu of choices as long as user does not want to quit
    int userChoice;
    do{
        userChoice = displayMenu();

        if(userChoice == 1){
            int top_n;
            cout << "Enter n: ";
            cin >> top_n;
            while(top_n <= 0){
                cin >> top_n;
            }
            top_n = min(top_n, arraySize);
            cout << "Top " << top_n << " students are:\n\n";
            // Lists top-n students by GPA (traverses array backward because array is ascending-sorted)
            int upper = arraySize-1;
            int lower = upper - top_n;
            for(int i=upper; i>lower; i--){
                cout << "netID: " << sortedNetIDbyGPA[i] << ", "
                     << "major: " << sortedMajorbyGPA[i] << ", "
                     << "GPA: "   << sortedGPAbyGPA[i]   << endl;
            }
            cout << endl;
        }
        else if(userChoice==2){
            int netID_key;
            cout << "Enter netID: ";
            cin >> netID_key;
            cout << endl << endl;
           
            // Performs LINEAR SEARCH
            cout << "Result of linear search:\n";
            cout << "------------------------\n";
            int nIter;
            int index = linearSearchID(netID, arraySize, netID_key, nIter);
            if(index != -1){
               cout << "Student found at index " << index << ", GPA is " << GPA[index] << endl;
            }
            else{
                cout << "Student not found\n";
            }
            cout << "It took " << nIter << " iterations\n\n";
           
            // Performs BINARY SEARCH
            cout << "Result of binary search:\n";
            cout << "------------------------\n";
            index = binarySearchID(sortedNetIDbyID, arraySize, netID_key, nIter);
            if(index != -1){
                cout << "Student found at index " << index << ", GPA is " << sortedGPAbyID[index] << endl;
            }
            else{
                cout << "Student not found\n";
            }
            cout << "It took " << nIter << " iterations\n\n";
        }
    }while(userChoice != 3);
   
    // Closes file when done
    cout << "Exiting\n";
    inputFile.close();
    return 0;
}
/*
Function for displaying menu of choices and returning user's choice
*/
int displayMenu(){
    cout << "***************\n";
    cout << "Menu of choices\n";
    cout << "***************\n";
    cout << "1 - List top n students\n";
    cout << "2 - Search on a netID\n";
    cout << "3 - Quit\n";

    int userChoice;
    cin >> userChoice;
    // Ensures the choice ranges from 1-3
    while(userChoice!=1 && userChoice!=2 && userChoice!=3){
        cin >> userChoice;
    }
    return userChoice;
}

// Function for finding the min between two numbers
int min(int a, int b){
    if(a<b) 
        return a;
    return b;
}
/*
This function sorts array1 and maintains the parallelism
of array2 and array3
Whenever elements of array1 are swapped, the elements of array2
and array3 at the same indices are also swapped
*/
void modifiedSortGPA(double array1[], int array2[], string array3[], int size)
{
    for(int i=0; i<size-1; i++){
      // Assumes the next smallest number is the current number
      int min_index = i;
      // Finds the next smallest number after the current number
      for(int j=i+1; j<size; j++){
         if(array1[j] < array1[min_index]){
            min_index = j;
         }  
      }
      // If the next smallest number is not the current number, swaps them
      if(min_index!=i){
         // Swap positions in GPA array to sort it
         double tempGPA = array1[i];
         array1[i] = array1[min_index];
         array1[min_index] = tempGPA;
        // Swap corresponding positions in ID array
         int tempID = array2[i];
         array2[i] = array2[min_index];
         array2[min_index] = tempID;
        // Swap corresponding positions in major array
         string tempMajor = array3[i];
         array3[i] = array3[min_index];
         array3[min_index] = tempMajor;
      }    
   }
}

/*
This function sorts array2 and maintains the parallelism
of array1 and array3
Whenever elements of array2 are swapped, the elements of array1
and array3 at the same indices are also swapped
*/
void modifiedSortID(int array2[], double array1[], string array3[], int size)
{
   for(int i=0; i<size-1; i++){
      // Assumes the next smallest number is the current number
      int min_index = i;
      // Finds the next smallest number after the current number
      for(int j=i+1; j<size; j++){
         if(array2[j] < array2[min_index]){
            min_index = j;
         }  
      }
      // If the next smallest number is not the current number, swaps them
      if(min_index!=i){
         // Swap positions in ID array to sort it
         int tempID = array2[i];
         array2[i] = array2[min_index];
         array2[min_index] = tempID;
        // Swap corresponding positions in GPA array
         double tempGPA = array1[i];
         array1[i] = array1[min_index];
         array1[min_index] = tempGPA;
        // Swap corresponding positions in major array
         string tempMajor = array3[i];
         array3[i] = array3[min_index];
         array3[min_index] = tempMajor;
      }    
   }
}

// Function for displaying the data table given the corresponding arrays
void displayData(int netID_arr[], string major_arr[], double GPA_arr[], int size){
    // Display headers for both columns
    cout << setw(7) << "index" << setw(7) << "netID" << setw(7) << "major" << setw(7) << "GPA"
         << "    "  // Space between columns
         << setw(7) << "index" << setw(7) << "netID" << setw(7) << "major" << setw(7) << "GPA"
         << endl;

    // Vars for iterating even and odd indices
    int evenIndex = 0, oddIndex = 1;
    
    // Iterate while either evenIndex or oddIndex is within bounds
    while (evenIndex < size || oddIndex < size) {
        // Print even-indexed row (left column)
        if (evenIndex < size) {
            cout << setw(7) << evenIndex
                 << setw(7) << netID_arr[evenIndex]
                 << setw(7) << major_arr[evenIndex]
                 << fixed << setprecision(2) << setw(7) << GPA_arr[evenIndex];
        } else {
            cout << string(28, ' '); // Empty space if no more even indices
        }

        cout << "    "; // Space between columns

        // Displays right column (odd indices)
        if (oddIndex < size) {
            cout << setw(7) << oddIndex
                 << setw(7) << netID_arr[oddIndex]
                 << setw(7) << major_arr[oddIndex]
                 << fixed << setprecision(2) << setw(7) << GPA_arr[oddIndex];
        }
        cout << endl;
        evenIndex += 2; 
        oddIndex += 2; 
    }
    cout << endl;
}
/*
This function implements linear search on an array. It takes the following arguments:
arr: the array
numElems: number of elements in array
value: search value
nIter: a reference variable used
to pass the number of iterations back to the calling function.

The function returns the index where the match is found, -1 if no
match is found
*/
int linearSearchID(int arr[], int numElems, int value, int &nIter)
{
    nIter = 0;
    for(int pos=0; pos<numElems; pos++){
        nIter++;
        if(arr[pos] == value)
            return pos;
    }
    return -1;
}

/*
This function implements binary search on an array. It takes the following arguments:
arr: the array
numElems: number of elements of array
value: search value
nIter: a reference variable used to pass the number of iterations
back to the calling function.

The function returns the index where the match is found, -1 if no
match is found
*/
int binarySearchID(int arr[], int numElems, int value, int &nIter)
{
    int low  = 0;
    int high = numElems-1;
    nIter = 0;
    while(low <= high){
        int mid = (low + high)/2;
        nIter++;
        if(arr[mid] == value)
            return mid;
        else if(arr[mid] < value)
            low = mid+1;
        else
            high = mid-1;
    }
    return -1;
}