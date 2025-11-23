#include "DebtManager.h"
#include "Person.h" // Needed for the Person structure
#include <iostream>
#include <algorithm> // For general algorithm use, though not strictly required for this exact version

DebtManager::DebtManager() : num_people(0) {}

void DebtManager::add_person() {
    num_people++;
    weighted_graph.resize(num_people + 1);
}

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