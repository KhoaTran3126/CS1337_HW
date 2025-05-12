#include <iostream>
#include <string>
#include "Product.h"
using namespace std;

// Set all attributes
void Product::setProductAttributes(string plu_val, string name_val, int type_val, double price_val, int inventory_val){
    PLU       = plu_val;
    name      = name_val;
    type      = type_val;
    price     = price_val;
    inventory = inventory_val;
}

// Sets inventory level to new count
void Product::setInventory(int inventory_val){
    inventory = inventory_val;
}

// Returns plu
string Product::getPLU() const{
    return PLU;
}

// Returns name
string Product::getName() const{
    return name;
}

// Returns sales type
int Product::getType() const{
    return type;
}

// Returns price
double Product::getPrice() const{
    return price;
}

// Returns inventory
int Product::getInventory() const{
    return inventory;
}

