// optimizer.cpp
#include "optimizer.h"
#include <cmath>    // std::fabs

// Small epsilon to treat "almost zero" as settled
static const double EPS = 1e-6;

// Returns index of person with maximum positive balance (most creditor).
// If no positive balance exists, returns -1.
int getMaxCredit(const std::vector<double>& balance) {
    int idx = -1;
    double maxVal = 0.0; // we only care about > 0

    for (int i = 0; i < static_cast<int>(balance.size()); ++i) {
        if (balance[i] > maxVal) {
            maxVal = balance[i];
            idx = i;
        }
    }
    return idx;
}

// Returns index of person with most negative balance (most debtor).
// If no negative balance exists, returns -1.
int getMaxDebit(const std::vector<double>& balance) {
    int idx = -1;
    double minVal = 0.0; // we only care about < 0

    for (int i = 0; i < static_cast<int>(balance.size()); ++i) {
        if (balance[i] < minVal) {
            minVal = balance[i];
            idx = i;
        }
    }
    return idx;
}

// Checks if everyone is (approximately) settled.
bool allSettled(const std::vector<double>& balance) {
    for (double b : balance) {
        if (std::fabs(b) > EPS) {
            return false;
        }
    }
    return true;
}

// Main greedy minimizer
std::vector<Transaction> minimizeCashFlow(std::vector<double>& balance,
                                          const std::vector<std::string>& names) {
    std::vector<Transaction> result;

    // Safety: sizes must match
    if (balance.size() != names.size()) {
        // In a real project you might throw, assert, or handle the error.
        return result;
    }

    // Repeat until everyone is settled
    while (!allSettled(balance)) {
        int cred = getMaxCredit(balance);  // index of max creditor
        int debt = getMaxDebit(balance);   // index of max debtor

        // If we have no valid creditor or debtor, stop
        if (cred == -1 || debt == -1) {
            break;
        }

        double creditAmount = balance[cred];    // > 0
        double debitAmount  = -balance[debt];   // > 0

        // Amount to transfer is the smaller of the two
        double amount = (creditAmount < debitAmount) ? creditAmount : debitAmount;

        if (amount <= EPS) {
            // Nothing meaningful left to transfer
            break;
        }

        // Record the transaction: debtor -> creditor
        Transaction t;
        t.from   = names[debt];
        t.to     = names[cred];
        t.amount = amount;
        result.push_back(t);

        // Update balances after this transaction
        balance[cred] -= amount; // creditor's balance moves down towards 0
        balance[debt] += amount; // debtor's balance moves up towards 0
    }

    return result;
}
