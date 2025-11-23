#ifndef DEBT_HPP
#define DEBT_HPP

// Forward declarations
class Person;
class DebtManager;

class Debt {
public:
    // Constructor takes references to the two people and the manager
    Debt(Person& from, Person& to, double amount, DebtManager& manager);
};

#endif // DEBT_HPP