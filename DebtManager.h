#ifndef DEBTMANAGER_HPP
#define DEBTMANAGER_HPP

#include <vector>
#include <utility> // For std::pair

// Forward declaration for Person
class Person; 

// Edge: {Destination Person ID, Debt Amount (weight)}
using Edge = std::pair<int, double>;

class DebtManager {
private:
    std::vector<std::vector<Edge>> weighted_graph;
    int num_people;

public:
    DebtManager();

    void add_person();
    
    // const Person& is used here to get the ID without modifying the Person object
    double calculate_net_position(const Person& p) const;
    
    void record_debt(int from_id, int to_id, double amount);

    void print_graph();
};

#endif // DEBTMANAGER_HPP