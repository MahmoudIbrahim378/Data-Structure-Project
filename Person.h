#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

// Forward declaration: tells the compiler that DebtManager exists,
// so we can use a reference to it in the Person constructor.
class DebtManager; 

class Person {
public:
    std::string name;
    int  id;
    std::string password;
    double balance;
    
    // Static member declaration
    static int numpersons; 
    
    // Constructor requires a reference to the manager
    Person(std::string name, std::string password, double balance, DebtManager& manager);
};

#endif // PERSON_HPP