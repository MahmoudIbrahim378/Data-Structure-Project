#include "DebtManager.h"
#include "Person.h"
#include "Debt.h"
#include <iostream>
#include <string>

int main() {
    // 1. Initialize the Debt Manager
    DebtManager m1;

    // 2. Create Person objects (P1=1, P2=2, P3=3)
    Person p1("Alice", "pass1", 500, m1);
    Person p2("Bob", "pass2", 500, m1);
    Person p3("Charlie", "pass3", 500, m1);

    // 3. Record Debts
    Debt d1(p1, p2, 300.0, m1); // P1 owes P2 $300.00
    Debt d2(p3, p1, 300.0, m1); // P3 owes P1 $300.00
    Debt d3(p1, p3, 50.0, m1);  // P1 owes P3 $50.00

    m1.print_graph();

    // 4. Calculate and Display Net Position
    double net_pos_p1 = m1.calculate_net_position(p1);

    std::cout << "\n--- Net Position ---" << std::endl;
    std::cout << "Person " << p1.id << " (" << p1.name << ") Net Position: $" << net_pos_p1 << std::endl;

    if (net_pos_p1 < 0) {
        std::cout << p1.name << " is a Net Debtor, owing $" << -net_pos_p1 << " more than owed." << std::endl;
    } else {
        std::cout << p1.name << " is a Net Creditor, owed $" << net_pos_p1 << " more than owed." << std::endl;
    }

    return 0;
}