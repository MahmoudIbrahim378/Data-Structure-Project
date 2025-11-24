#include "optimizer.h"
#include <cmath>  // std::fabs

// Small epsilon to treat "almost zero" as settled
static const double EPS = 1e-6;

// Find index of maximum creditor (largest positive balance)
int getMaxCredit(std::vector<double>& balance) {
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

// Find index of maximum debtor (most negative balance)
int getMaxDebit(std::vector<double>& balance) {
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

// Check if everyone is approximately settled (|balance| <= EPS)
bool allSettled(std::vector<double>& balance) {
    for (double b : balance) {
        if (std::fabs(b) > EPS) {
            return false;
        }
    }
    return true;
}

// Greedy minimize cash flow
std::vector<Transaction> minimizeCashFlow(std::vector<double>& balance,
                                          std::vector<std::string>& names) {
    std::vector<Transaction> result;

    // Safety: sizes must match
    if (balance.size() != names.size()) {
        return result; // or handle error differently if you want
    }

    // Repeat until all balances are settled
    while (!allSettled(balance)) {
        int cred = getMaxCredit(balance); // index of max creditor
        int debt = getMaxDebit(balance);  // index of max debtor

        // If we can't find a valid creditor or debtor, we stop
        if (cred == -1 || debt == -1) {
            break;
        }

        double creditAmount = balance[cred];   // > 0
        double debitAmount  = -balance[debt];  // > 0

        // Amount to transfer is the smaller of the two
        double amount = (creditAmount < debitAmount) ? creditAmount : debitAmount;

        if (amount <= EPS) {
            // Nothing meaningful left to move
            break;
        }

        // Record transaction: debtor -> creditor
        Transaction t;
        t.from   = names[debt];
        t.to     = names[cred];
        t.amount = amount;
        result.push_back(t);

        // Update balances
        balance[cred] -= amount;  // creditor moves towards 0
        balance[debt] += amount;  // debtor moves towards 0
    }

    return result;
}

