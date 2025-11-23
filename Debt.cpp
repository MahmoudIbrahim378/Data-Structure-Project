#include "Debt.h"
#include "Person.h"
#include "DebtManager.h"
#include <iostream>

Debt::Debt(Person& from, Person& to, double amount, DebtManager& manager) {
    // Delegates the actual graph update to the manager
    manager.record_debt(from.id, to.id, amount);
}