#include "Person.h"
#include "DebtManager.h"
#include <iostream>

// Static member definition and initialization
int Person::numpersons = 0;

Person::Person(std::string name, std::string password, double balance, DebtManager& manager) {
    this->name = name;
    this->password = password;
    this->balance = balance;
    
    // Assign ID and notify the manager
    numpersons++;
    this->id = numpersons;
    manager.add_person();
}