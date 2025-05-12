#include <iostream>
#include <string>
#include "Date.h"
using namespace std;

void Date::set(int month_, int day_, int year_, int hour_){
    // Set all values
    month = month_;
    day   = day_;
    year  = year_;
    hour  = hour_;
}

bool Date::operator<(const Date& rhs){
    // Compares year
    if(year < rhs.year) return true;
    if(year > rhs.year) return false;
    // Compares month
    if(month < rhs.month) return true;
    if(month > rhs.month) return false;
    // Compares day
    if(day < rhs.day) return true;
    if(day > rhs.day) return false;
    // Compares hour
    return (hour < rhs.hour);
}
   
bool Date::operator==(const Date& rhs){
    // If all members are the same, returns true
    return(
       (month==rhs.month) &&
       (day==rhs.day)     &&
       (year==rhs.year)   &&
       (hour==rhs.hour)   
    );
}

// Returns true if *this and rhs have identical elements OR date in *this < elements in rhs
bool Date::operator<=(const Date& rhs){
    return((*this==rhs) || (*this<rhs));
}

// Subtract dates between rhs and *this to get hours
int Date::operator-(const Date& rhs){
    if(*this==rhs) return 0;
    
    // Days in each month for non-leap years
    int daysInMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    int totalDays1 = 0; // Total day count for *this
    int totalDays2 = 0; // Total day count for rhs
    int i;

    // Calculate days for *this by looping years
    for(i=0; i<year; i++){
        int isLeapYear = ((i%4 == 0) && (i%100 != 0)) || (i%400 == 0); // Checks for leap year
        // Adds 366 if leap year is true, else 365
        totalDays1 += isLeapYear?366:365;
    }
    
    // Calculate days for *this by looping months before current month
    for(i = 0; i<month-1; i++)
        totalDays1 += daysInMonth[i];
        
    // If current year is leap year and month is > 2, meaning Feb as a leap month  has not been accounted for,
    // Adds 1 extra day to ensure Feb is 29 days
    if(month>2){
        int isLeapYear = ((i%4 == 0) && (i%100 != 0)) || (i%400 == 0);
        if (isLeapYear)
            totalDays1 += 1;
    }
    totalDays1 += day;


    // Calculate days for rhs by looping years
    for (i=0; i<rhs.year; i++) {
        int isLeapYear = ((i%4 == 0) && (i%100 != 0)) || (i%400 == 0);
        // Adds 366 if leap year is true, else 365
        totalDays2 += isLeapYear?366:365;
    }
    
    // Calculate days for rhs by looping months before current month
    for (i=0; i<rhs.month-1; i++)
        totalDays2 += daysInMonth[i];
        
    // If current year is leap year and month is > 2, meaning Feb as a leap month has not been accounted for,
    // Adds 1 extra day to ensure Feb is 29 days
    if (rhs.month > 2) {
        int isLeapYear = ((i%4 == 0) && (i%100 != 0)) || (i%400 == 0);
        if (isLeapYear)
            totalDays2 += 1;
    }
    totalDays2 += rhs.day;

    // Total hours
    int hours1 = totalDays1*24 + hour;
    int hours2 = totalDays2*24 + rhs.hour;
    
    if (*this < rhs)
        return (hours1 - hours2);
    return -(hours2-hours1);
}

// Prints the date
void Date::print(){
    string months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
        
    // Displays date
    cout << months[month-1] << " " 
         << day << ", " 
         << year << ", " 
         << hour << ":00";
}
