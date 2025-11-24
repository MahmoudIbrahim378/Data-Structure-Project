#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <vector>
#include <string>

struct Transaction {
    std::string from;   // debtor (payer)
    std::string to;     // creditor (receiver)
    double amount;
};

// Helper functions as in the spec
int getMaxCredit(std::vector<double>& balance);
int getMaxDebit(std::vector<double>& balance);
bool allSettled(std::vector<double>& balance);

// Core function:
// balance[i] = net balance of person i
//              (positive => creditor, negative => debtor)
// names[i]   = name of person i, same index as balance
std::vector<Transaction> minimizeCashFlow(std::vector<double>& balance,
                                          std::vector<std::string>& names);

#endif // OPTIMIZER_H
