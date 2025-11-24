#include "DebtManager.h"
#include "Person.h"
#include "Debt.h"
#include <iostream>
#include <string>
#include "optimizer.h"   // shaarawy (greedy minimizer)
#include <vector>        // for std::vector
#include <iomanip>       // for std::setprecision

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
//Shaarwyy add:
    std::vector<double> balances = m1.getNetBalances();
    std::vector<std::string> names = m1.getNames();

    // Keep a copy to show original net balances (because optimizer modifies balances)
    std::vector<double> originalBalances = balances;

    std::cout << "\n--- Net Balances (before optimization) ---\n";
    std::cout << "(positive = creditor, negative = debtor)\n\n";
    std::cout << std::fixed << std::setprecision(2);

    for (std::size_t i = 0; i < names.size(); ++i) {
        std::cout << names[i] << ": " << originalBalances[i] << "\n";
    }

    // Run Shaarawy greedy cash-flow minimizer
    std::vector<Transaction> result = minimizeCashFlow(balances, names);

    std::cout << "\n--- Minimized Cash-Flow Transactions ---\n";
    if (result.empty()) {
        std::cout << "No transactions needed. Everyone is settled.\n";
    } else {
        for (const auto& t : result) {
            std::cout << t.from << " pays " << t.to
                      << " : $" << std::fixed << std::setprecision(2)
                      << t.amount << "\n";
        }
    }
    //END OF SHAARAWY ADD
    
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
