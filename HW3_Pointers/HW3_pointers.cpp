#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Initialize function prototypes
int readInventory(string fileName, int arrSize, string *PLUptr, double *PRICEptr, string *PRODptr, int *SALESptr, int *INVptr);
void displayInventory(int arrSize, string *PLUptr, string *PRODptr, int *SALESptr, double *PRICEptr, int *INVptr);
int displayMenu();
int linearSearch(int arrSize, string *PLUptr, string key);
double checkout(int arrSize, string *PLUptr, double *PRICEptr, int *INVptr);
   
int main(){
    // Reads file from user
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;
    ifstream inputFile(fileName);
    // If file could not be opened, returns error and exits program
    if(!inputFile){
        cout << "Could not open file\n";
        cout << "Exiting\n";
        return 1;
    }
   
    // Determines the proper size for arrays by counting num of lines
    int arrSize = 0;
    string line;
    while(getline(inputFile, line))
        arrSize++;
    inputFile.close();
    // Initialize dynamic arrays
    string *PLUptr   = new string[arrSize];
    string *PRODptr  = new string[arrSize];
    int    *SALESptr = new int[arrSize];
    double *PRICEptr = new double[arrSize];
    int    *INVptr   = new int[arrSize];
   
    // Reads inventory records into parallel arrays
    readInventory(fileName, arrSize, PLUptr, PRICEptr, PRODptr, SALESptr, INVptr);

    // Print the records read from the file
    cout << "There are " << arrSize << " records in the file\n\n";
    cout << "Inventory read from file\n";
    cout << "------------------------\n";
    displayInventory(arrSize, PLUptr, PRODptr, SALESptr, PRICEptr, INVptr);

    // Displays menu and perform requested operations
    int choice;
    do{
        choice = displayMenu();
        // Checks out items
        if(choice == 1){
            double totalCost = checkout(arrSize, PLUptr, PRICEptr, INVptr);
            cout << "Total is: $" << totalCost << endl << endl;
        }
        // Prints current inventory
        else if(choice == 2){
            cout << "Current inventory\n";
            cout << "-----------------\n";
            displayInventory(arrSize, PLUptr, PRODptr, SALESptr, PRICEptr, INVptr);
        }
    }while(choice!=3);
    
    // Prints current inventory
    cout << "Updated inventory\n";
    cout << "-----------------\n";
    displayInventory(arrSize, PLUptr, PRODptr, SALESptr, PRICEptr, INVptr);
    
    // Frees dynamic memory and exits program
    delete [] PLUptr;
    delete [] PRODptr;
    delete [] SALESptr;
    delete [] PRICEptr;
    delete [] INVptr;
    cout << "Exiting\n";
    return 0;
}

// Function for reading inventory records into parallel arrays
int readInventory(string fileName, int arrSize, string *PLUptr, double *PRICEptr, string *PRODptr, int *SALESptr, int *INVptr){
    ifstream inputFile(fileName);
    // If file could not be opened, returns 0 and exits program
    if(!inputFile) return 0;
    // Place entries in records within appropriate arrays and their positions
    for(int linePos = 0; linePos < arrSize; linePos++){
        inputFile >> *(PLUptr   + linePos)
                  >> *(PRODptr  + linePos)
                  >> *(SALESptr + linePos)
                  >> *(PRICEptr + linePos)
                  >> *(INVptr   + linePos);
    }
    // Closes file and returns 1 (success)
    inputFile.close();
    return 1;
}

// Function for displaying the full inventory
void displayInventory(int arrSize, string *PLUptr, string *PRODptr, int *SALESptr, double *PRICEptr, int *INVptr){
    for(int row=0; row<arrSize; row++){
        if(*(PLUptr + row) != ""){
            cout << "PLU: " << *(PLUptr + row) << ", "
             << left << setw(17) << *(PRODptr + row) << ", "
             << "type: " << *(SALESptr + row) << ", "
             << "unit price:" << right << setw(6) << *(PRICEptr + row) << ", "
             << "inventory: " << *(INVptr + row);
            cout << endl;
        }
    }
}

// Function for displaying a menu of choices for a user to perform operations
int displayMenu(){
    cout << "1 - Checkout\n";
    cout << "2 - Print current inventory\n";
    cout << "3 - Quit\n";

    int choice;
    cin >> choice;
    while(choice!=1 && choice!=2 && choice!=3){
        cout << "Invalid choice, reenter: ";
        cin >> choice;
        cout << endl;
    }
    return choice;
}

// Function for checking out items and accumulating the total cost
double checkout(int arrSize, string *PLUptr, double *PRICEptr, int *INVptr){
   string userPLU;
   int userQuantity;
   double totalCost = 0;
   while(true){
        // Gets PLU code and item's quantity from user
        cout << "Enter PLU, 0 if done: ";
        cin >> userPLU;
       if (userPLU == "0") break;
        cout << "Enter quantity: ";
        cin >> userQuantity;
        while(userQuantity <= 0){
            cout << "Quantity must be positive, reenter: ";
            cin >> userQuantity;
            cout << endl;
        }
        // Searches array and see whether PLU exists
        int index = linearSearch(arrSize, PLUptr, userPLU);
        if(index == -1){
            cout << "PLU not found\n";
        }
        // If PLU exists, accumulates cost but subtracts the count of quantities carefully!
        else{
            // If the user quantity does not exceed the number of items in inventory,
            // accumulates the cost and updates inventory
            double price = *(PRICEptr + index);
            if((*(INVptr + index) - userQuantity) >= 0){
                totalCost += userQuantity*price;
                *(INVptr + index) -= userQuantity;
            }
            else{
                totalCost += *(INVptr + index) * price;
                *(INVptr + index) = 0;
            }
        }
    }
    return totalCost;
}

// Linear search function for determining whether a PLU key exists
int linearSearch(int arrSize, string *PLUptr, string key){
    for(int index=0; index<arrSize; index++){
        if(*(PLUptr + index) == key)
            return index;
    }
    return -1;
}