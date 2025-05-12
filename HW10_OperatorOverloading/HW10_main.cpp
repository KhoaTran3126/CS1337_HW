#include <iostream>
#include <fstream>
#include <string>
#include "Date.h"
using namespace std;

// Function prototypes
int getMonth(string);
int getDay(string);
int getYear(string);
int getHour(string);

int main(){
    int month, day, year, hour; 

    const int NUM_DATES_SUBTRACT = 4, NUM_DATES_RELATIONAL = 5;
    string dateArraySubtract[NUM_DATES_SUBTRACT] = {"01/01/2097/20", "02/12/2098/00", "02/13/2100/13","12/31/2103/23"}; // Used to test overloaded -
    string dateArrayRelational[NUM_DATES_RELATIONAL] = {"01/01/2097/20", "01/01/2097/21", "01/02/2097/20","02/01/2097/20", "01/01/2098/20"}; // Used to test overloaded <, ==, <=

    // Driver for the Date class
    string title = "Overloaded relational operators";
    string underline;
    underline.assign(title.length(), '-');
    cout << title << endl << underline << endl;

    Date d1, d2;
    for (int i = 0; i < NUM_DATES_RELATIONAL; i++) // Nested loop to test all the pairwise combinations of d1, d2
        for (int j = 0; j < NUM_DATES_RELATIONAL; j++)
        {
            // Extract components from ith date
            month = getMonth(dateArrayRelational[i]);
            day   = getDay(dateArrayRelational[i]);
            year  = getYear(dateArrayRelational[i]);
            hour  = getHour(dateArrayRelational[i]);
            d1.set(month, day, year, hour);
            cout << endl << "============================================\n";
            cout << "d1: ";
            d1.print();
            
            // Extract components from jth date
            month = getMonth(dateArrayRelational[j]);
            day   = getDay(dateArrayRelational[j]);
            year  = getYear(dateArrayRelational[j]);
            hour  = getHour(dateArrayRelational[j]);
            d2.set(month, day, year, hour);
            cout << ", d2: ";
            d2.print();
            
            cout << endl;

            if (d1 < d2)
                cout << "(d1 < d2) ";
            if (d2 < d1)
                cout << "(d2 < d1) ";
            if (d1 == d2)
                cout << "(d2 == d1) ";
            if (d1 <= d2)
                cout << "(d1 <= d2) ";
            if (d2 <= d1)
                cout << "(d2 <= d1) ";
        }
    
    
    
    title = "Overloaded - operator";
    underline.assign(title.length(), '-');
    cout << endl << endl << title << endl << underline << endl;

    for (int i = 0; i < NUM_DATES_SUBTRACT; i++) // Nested loop to test all the pairwise combinations of d1, d2
        for (int j = 0; j < NUM_DATES_SUBTRACT; j++)
        {
            
            // Extract components from ith date
            month = getMonth(dateArraySubtract[i]);
            day = getDay(dateArraySubtract[i]);
            year = getYear(dateArraySubtract[i]);
            hour = getHour(dateArraySubtract[i]);
            d1.set(month, day, year, hour);
            cout << endl << "============================================\n";
            cout << "d1: ";
            d1.print();
            
            // Extract components from jth date
            month = getMonth(dateArraySubtract[j]);
            day = getDay(dateArraySubtract[j]);
            year = getYear(dateArraySubtract[j]);
            hour = getHour(dateArraySubtract[j]);
            d2.set(month, day, year, hour);
            cout << ", d2: ";
            d2.print();
            
            cout << endl;
            
            cout << "d2 - d1 = " << d2 - d1 << " hours"<< endl;
        }

}

/* 
Takes string in format mm/dd/yyyy/hh, returns month (int)
Assumptions:
1 Format is followed by string
2. No input validation is needed
*/
int getMonth(string d){
    return stoi(d.substr(0, 2));
}


/* 
Takes string in format mm/dd/yyyy/hh format returns day (int)
Assumptions:
1 Format is followed by string
2. No input validation is needed
*/
int getDay(string d){
    return stoi(d.substr(3, 2));
}

/* 
Takes string in format mm/dd/yyyy/hh format returns year (int)
Assumptions:
1 Format is followed by string
2. No input validation is needed
*/
int getYear(string d){
    return stoi(d.substr(6, 4));
}

/* 
Takes string in format mm/dd/yyyy/hh format returns hour (int)
Assumptions:
1 Format is followed by string
2. No input validation is needed
*/
int getHour(string d){
  return stoi(d.substr(11));
}


