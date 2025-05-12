#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Product.h"
using namespace std;

// Function for displaying menu of options
int menu();
// Function for searching whether the given PLU exists
int searchPLU(string plu, Product* obj, int recordCount);

struct Transaction {
    int id;
    string plu;
    string operation; // addition or subtraction
    int amount;
};

int main(){
    // Reads filename
    string fileName;
    cout <<"Enter the file name: ";
    cin >> fileName;
    ifstream inputFile(fileName);
    
    // File cannot be opened; returns error
    if(!inputFile){
        cout << "Error opening File. Exiting.\n";
        return 1;
    }
    
    // Dynamic array for storing transaction details
    Transaction* transactHistory = new Transaction[100]; 
    int transactCounter = 0;
    
    // Counts the number of records 
    int recordCount = 0;
    string line;
    while(getline(inputFile, line)){
        recordCount++;    
    }
    cout << "There are " << recordCount << " records in the file\n\n";
    cout << "Content of object array\n";
    cout << "-----------------------\n";
    inputFile.clear();
    inputFile.seekg(0, ios::beg);
    
    // Dynamically allocate Product objects array and display records
    line = "";
    Product* products = new Product[recordCount];
    string plu, name;
    int sales_type, inventory;
    double price;
    int counter = 0;
    
    while(getline(inputFile, line)){
        istringstream mystream(line);
        
        mystream >> plu >> name >> sales_type >> price >> inventory;
        // Set attributes for product ith
        products[counter].setProductAttributes(plu, name, sales_type, price, inventory);
        // Print records
        cout << "PLU: " << plu << ", " 
             << setw(17) << left << name 
             << ", type: " << sales_type
             << ", unit price: " << right << setw(5) << price 
             << ", inventory: " << inventory
             << endl;
             
        counter++;
    }
    cout << endl;
    
    // Displays menu
    while(true){
        // Gets user's menu choice
        int choice = menu();
        
        if(choice==1){
            // Gets PLU from user
            string plu;
            cout << "Enter the PLU: ";
            cin >> plu;
            // Searches to ensure PLU provided is valid
            int index = searchPLU(plu, products, recordCount);
            // If PLU is valid, adds more to inventory
            if(index==-1)
                cout << "PLU not found" << endl;
            else{
                int amount;
                cout << "Enter amount to add: ";
                cin >> amount;
                
                if(amount<=0)
                    cout << "Amount must be > 0" << endl;
                else{
                    int new_inventory = products[index].getInventory() + amount;
                    products[index].setInventory(new_inventory);
                    // Log transaction
                    transactHistory[transactCounter].id = transactCounter + 1;
                    transactHistory[transactCounter].plu = products[index].getPLU();
                    transactHistory[transactCounter].operation = "addition";
                    transactHistory[transactCounter].amount = amount;
                    transactCounter++;
                }
            }
        }
        
        else if(choice==2){
            // Gets PLU from user
            string plu;
            cout << "Enter the PLU: ";
            cin >> plu;
            // Searches to ensure PLU provided is valid
            int index = searchPLU(plu, products, recordCount);
            // If PLU is valid, subtracts from inventory if possible
            if(index==-1)
                cout << "PLU not found" << endl;
            else{
                int amount;
                cout << "Enter amount to subtract: ";
                cin >> amount;
                int full_subtraction;
                
                if(amount<=0)
                    cout << "Amount must be > 0" << endl;
                else if(amount > products[index].getInventory()){
                    full_subtraction = products[index].getInventory();
                    products[index].setInventory(0);
                    // Log transaction
                    transactHistory[transactCounter].id = transactCounter + 1;
                    transactHistory[transactCounter].plu = products[index].getPLU();
                    transactHistory[transactCounter].operation = "subtraction";
                    transactHistory[transactCounter].amount = full_subtraction;
                    transactCounter++;
                }
                else{
                    full_subtraction = amount;
                    int new_inventory = products[index].getInventory() - amount;
                    products[index].setInventory(new_inventory);
                    // Log transaction
                    transactHistory[transactCounter].id = transactCounter + 1;
                    transactHistory[transactCounter].plu = products[index].getPLU();
                    transactHistory[transactCounter].operation = "subtraction";
                    transactHistory[transactCounter].amount = full_subtraction;
                    transactCounter++;
                }
            }
        }
        
        else if(choice==3){
            // Displays current inventory
            cout << "Current inventory" << endl;
            cout << "-----------------" << endl;
            for(int k=0; k<recordCount; k++){
                cout << "PLU: " << products[k].getPLU() << ", " 
                     << setw(17) << left << products[k].getName() 
                     << ", type: " << products[k].getType()
                     << ", unit price: " << right << setw(5) << products[k].getPrice() 
                     << ", inventory: " << products[k].getInventory()
                     << endl;
            }
        }
        
        else if(choice==4){
            if(transactCounter > 0){
                cout << endl;
                cout << "History of transactions\n";
                cout << "-----------------------\n";
                // Lower boundary for listing transactions
                int lowerLim = 5;
                if (transactCounter < 5) 
                    lowerLim = transactCounter;
                
                // List up to 5 most recent transactions
                for(int i=transactCounter-1; i>=transactCounter-lowerLim; i--){
                    string operation_phrase;
                    if(transactHistory[i].operation=="addition")
                        operation_phrase="Add to inventory, amount: ";
                    else
                        operation_phrase="Subtract from inventory, amount: ";
                        
                    cout << "Transaction #: " << transactHistory[i].id
                         << ", PLU: " << transactHistory[i].plu 
                         << ", type: " << operation_phrase << transactHistory[i].amount << endl;
                }
            }
            break;
        }
            
        cout << endl;
    }
    
    inputFile.close();
    delete[] products;
}

// Function for displaying a menu of options
int menu(){
    int choice;
    cout << "Menu\n";
    cout << "----\n";
    cout << "1->Add to inventory           , "
         << "2->Subtract from inventory" 
         << endl
         << "3->Print info for all products, "
         << "4->Exit" 
         << endl;
    cin >> choice;
    return choice;
}

// Function for searching whether the given PLU exists
int searchPLU(string plu, Product* obj, int recordCount){
    for(int k=0; k<recordCount; k++){
        if(obj[k].getPLU() == plu)
            return k;
    }
    return -1;

}