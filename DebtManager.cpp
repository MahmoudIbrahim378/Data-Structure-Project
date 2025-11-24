#include "DebtManager.h"
#include "Person.h" // Needed for the Person structure
#include <iostream>
#include <algorithm> // For general algorithm use, though not strictly required for this exact version

DebtManager::DebtManager() : num_people(0) {}

void DebtManager::add_person(const std::string& name) {         //added a parameter (const std::string& name)
   
     num_people++;
    
    // Resize adjacency list (1-based indexing; index 0 unused)
    if (static_cast<int>(weighted_graph.size()) <= num_people) {
        weighted_graph.resize(num_people + 1);
    }

    // Ensure idToName is large enough and store the name at this ID
    if (static_cast<int>(idToName.size()) <= num_people) {
        idToName.resize(num_people + 1); // index 0 unused
    }
    idToName[num_people] = name;
}

// Calculate net position of a single person:
// net = total_owed_to_person - total_person_owes
double DebtManager::calculate_net_position(const Person& p) const {
    double owed = 0.0; 
    double debt = 0.0; 
    const int target_id = p.id;

    if (target_id <= 0 || target_id > num_people) {
        std::cout << "Error: Invalid Person ID (" << target_id << ")." << std::endl;
        return 0.0;
    }

    // 1. Calculate Liabilities (Debts Owed BY the person)
    if (target_id < weighted_graph.size()) {
        for (const auto& edge : weighted_graph[target_id]) {
            debt += edge.second;
        }
    }

    // 2. Calculate Assets (Debts Owed TO the person)
    for (int i = 1; i <= num_people; ++i) {
        if (i == target_id) continue; 
        
        for (const auto& edge : weighted_graph[i]) {
            if (edge.first == target_id) {
                owed += edge.second;
            }
        }
    }

    return owed - debt;
}

void DebtManager::record_debt(int from_id, int to_id, double amount) {
    if (from_id <= 0 || from_id > num_people ||
        to_id <= 0   || to_id > num_people) {
        std::cout << "Error: Invalid Person ID." << std::endl;
        return;
        }

    weighted_graph[from_id].push_back({to_id, amount});

    std::cout << "Debt recorded: Person " << from_id
         << " owes Person " << to_id
         << " $" << amount << std::endl;
}

void DebtManager::print_graph() {
    std::cout << "\n--- Current Debt Graph ---" << std::endl;

    for (int i = 1; i <= num_people; ++i) {
        if (!weighted_graph[i].empty()) {
            std::cout << "Person " << i << " owes:";
            for (const auto& e : weighted_graph[i]) {
                std::cout << " -> [ID: " << e.first << ", $" << e.second << "]";
            }
            std::cout << std::endl;
        }
    }
}

//addedby shaarawy
/ NEW: compute net balances for all people at once
std::vector<double> DebtManager::getNetBalances() const {
    // index 0 unused because IDs start from 1
    std::vector<double> balance(num_people + 1, 0.0);

    // For each edge i -> j with amount:
    //   i owes j  => balance[i] -= amount
    //   j is owed => balance[j] += amount
    for (int i = 1; i <= num_people; ++i) {
        if (i >= static_cast<int>(weighted_graph.size())) continue;

        for (const auto& e : weighted_graph[i]) {
            int    j      = e.first;
            double amount = e.second;
            if (j <= 0 || j > num_people) continue;

            balance[i] -= amount; // i owes j
            balance[j] += amount; // j is owed by i
        }
    }

    // Convert to 0-based result: result[0] = ID 1, result[1] = ID 2, ...
    std::vector<double> result;
    result.reserve(num_people);
    for (int id = 1; id <= num_people; ++id) {
        result.push_back(balance[id]);
    }
    return result;
}

// NEW: return names in the same order as balances
std::vector<std::string> DebtManager::getNames() const {
    std::vector<std::string> result;
    result.reserve(num_people);

    // idToName[id] holds the name for ID = id (1..num_people)
    for (int id = 1; id <= num_people; ++id) {
        if (id < static_cast<int>(idToName.size()) && !idToName[id].empty()) {
            result.push_back(idToName[id]);
        } else {
            // Fallback in case something is missing
            result.push_back("Person" + std::to_string(id));
        }
    }
    return result;
}
