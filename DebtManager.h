#ifndef DEBTMANAGER_HPP
#define DEBTMANAGER_HPP

#include <vector>
#include <utility> // For std::pair
#include <string>

// Forward declaration for Person
class Person; 

// Edge: {Destination Person ID, Debt Amount (weight)}
using Edge = std::pair<int, double>;

class DebtManager {
private:
    std::vector<std::vector<Edge>> weighted_graph;
    int num_people;
    std::vector<std::string> idToName;  // idToName[id] = name of person with that ID (1-based index; 0 unused)

public:
    DebtManager();

    void add_person(const std::string& name);
    
    // const Person& is used here to get the ID without modifying the Person object
    double calculate_net_position(const Person& p) const;
    
    void record_debt(int from_id, int to_id, double amount);

    void print_graph();

 // NEW: return net balances for all people:
    // result[i-1] = net balance of person with ID = i
    // (positive => creditor, negative => debtor)
    std::vector<double> getNetBalances() const;

    // NEW: return names in the same order as balances:
    // names[0] = name of person with ID = 1, etc.
    std::vector<std::string> getNames() const;
};

#endif // DEBTMANAGER_HPP
