#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Initialize function prototypes
string tokenize(string &value);
bool isValidPrice(string value);
bool containDigitsOnly(string value);
bool containsNumber(string text);

int main(){
    // Reads file from user
    string fileName;
    cout << "Enter input file:";
    cin >> fileName;
    ifstream inputFile(fileName);
    cout << endl;
    // Prints error if file cannot be read
    if(!inputFile){
        cout << "Error opening File. Exiting.\n";
        return 1;
    }
   
    cout << "Checking " << fileName << endl;
    // If no number in filename, displays this
    if(containsNumber(fileName)==false)
        cout << "---------------" << endl;
    // If there is a number in filename, displays this
    else
        cout << "----------------" << endl;
    
    bool invalidMarker = false;
    string line;
   
    while(getline(inputFile, line)){
        string plu_code, name, sales_type, price, ivt_level;
        int tokenCount = 0;
       
        // Extract plu code token
        plu_code = tokenize(line);
        if(line.empty()){
            cout << "Line is emtpy";
            return 1;
        }
        // Extracts name token
        name = tokenize(line);
        if(line.empty()){
            cout << "Line is emtpy";
            return 1;
        }
        // Extracts sales type token
        sales_type = tokenize(line);
        if(line.empty()){
            cout << "Line is emtpy";
            return 1;
        }
        // Extracts price token
        price = tokenize(line);
        if(line.empty()){
            cout << "Line is emtpy";
            return 1;
        }
        // Extracts inventory level token
        ivt_level  = tokenize(line);

        // Extracts excess remaining token
        string excess_token = tokenize(line);
        
        // Validates code
        if(plu_code==""){
            invalidMarker=1;
            cout << "PLU Code is invalid, record has missing items\n";
            break;
        }
        else if(plu_code.length()!=4 ||
            !isalnum(plu_code[0]) ||
            !isalnum(plu_code[1]) ||
            !isalnum(plu_code[2]) ||
            !isalnum(plu_code[3])) {
            cout << "\nToken #1 is " << plu_code << ", PLU is invalid" << endl;
            invalidMarker = 1;
            break;
        }
        else
            cout << "\nToken #1 is " << plu_code << ", PLU is valid" << endl;
       
        // Validates name
        if(name==""){
            invalidMarker=1;
            cout << "Name is invalid, record has missing items\n";
            break;
        }
        else if (!isalpha(name[0])){
            cout << "Token #2 is " << name << ", Product name is invalid" << endl;
            invalidMarker = 1;
            break;
        }
        else
            cout << "Token #2 is " << name << ", Product name is valid" << endl;
       
        // Validates sales type
        if(sales_type==""){
            invalidMarker=1;
            cout << "Sales Type is invalid, record has missing items\n";
            break;
        }
        else if (sales_type != "0" && sales_type != "1"){
            cout << "Token #3 is " << sales_type << ", Sales type is invalid" << endl;
            invalidMarker = 1;
            break;
        }
        else
            cout << "Token #3 is " << sales_type << ", Sales type is valid" << endl;
       
        // Validates price
        if(price==""){
            invalidMarker=1;
            cout << "Price is invalid, record has missing items\n";
            break;
        }
        else if (isValidPrice(price)==false){
            cout << "Token #4 is " << price << ", Price is invalid" << endl;
            invalidMarker = 1;
            break;
         }
        else
            cout << "Token #4 is " << price << ", Price is valid" << endl;
       
        // Validates inventory level
        if(ivt_level==""){
            invalidMarker=1;
            cout << "Inventory is invalid, record has missing items\n";
            break;
        }
        else if (containDigitsOnly(ivt_level)==false){
            cout << "Token #5 is " << ivt_level << ", Inventory is invalid" << endl;
            invalidMarker = 1;
            break;
        }
        else
            cout << "Token #5 is " << ivt_level << ", Inventory is valid" << endl;
        
        if(excess_token!=""){
            cout << "Token #6 is " << excess_token << ", Too many items in record\n";
            invalidMarker = 1;
            break;
        }
    }

    // Reports whether the file contains valid/invalid content
    if(invalidMarker==1)
        cout << "\n######## " << fileName << " has invalid content ########\n";
    else
        cout << "\n######## " << fileName << " has valid content ########\n";
    inputFile.close();
    return 0;
}


// Function for extracting one token at a time from a string
string tokenize(string &value){
    // Trim leading delimiters
    int start = 0;
    int stringLength = int(value.length());
   
    while (start < stringLength &&
           (value[start]=='\t' || value[start]==' ' || value[start]=='\n' || value[start]=='\r'))
        start++;
   

    // If string is empty after trimming, returns empty string
    if (start == stringLength){
        value.clear();
        return "";
    }

    // Find the token's ending
    int end = start;
    while (end < stringLength &&
           value[end] !='\t' &&
           value[end] != ' ' &&
           value[end] != '\n' &&
           value[end] != '\r')
        end++;

    // Extracts token
    string token = value.substr(start, end-start);

    // Modify the original string to remove extracted token and leading delimiters
    value = value.substr(end);
    return token;
}

// Function for checking that a string must only contain digits
bool containDigitsOnly(string value){
    int stringLength = int(value.length());
    for(int i=0; i<stringLength; i++){
          if(!isdigit(value[i]))
              return false;
    }
    return true;
}

// Function for determining whether a price is correctly formatted
bool isValidPrice(string value) {
    int dotCount = 0;
    int dotPos = -1;
    int decimalValueCount = 0;
    int stringLength = int(value.length());
   
    // Tracks count of dot and ensure all values are numeric
    for(int i=0; i<stringLength; i++){
        if(value[i]=='.'){
            dotCount++;
            dotPos = i;
        }
        else if (!isdigit(value[i]))
            return false;
    }

    // If there are more than 2 dots, returns false
    if(dotCount > 1)
        return false;
   
    // Ensures the number of values after decimal is at most 2
    if(dotPos!=-1){
        decimalValueCount = stringLength - dotPos - 1;
        if (decimalValueCount > 2)
            return false;
    }
    return true;
}

// Function checking if a string contains a digit
bool containsNumber(string text){
    int size = int(text.length());
    for (int i=0; i<size; i++){
        if (isdigit(text[i]))
            return true;
    }
    return false;
}