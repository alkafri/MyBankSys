#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <vector>
#include <fstream>
#include "transaction.h"
#include "account.h"

class Bank {
public:
    Bank();
    ~Bank(); // Destructor for cleanup
    
    void createAccount(const std::string& accountHolder);
    void closeAccount(int accountNumber);
    void displayAccounts() const;
    void saveAccounts(std::ofstream& outputFile) const;
    void loadAccounts(std::ifstream& inputFile);
    void updateAccountDetails(int accountNumber, const std::string& newHolder);
    void deposit(int accountNumber, double amount);
    void withdraw(int accountNumber, double amount);
    void updateAccountBalances(const Transaction& transactionManager);
    void transfer(int fromAccount, int toAccount, double amount);

private:
    std::vector<Account*> accounts; // Use pointers for heap allocation

    void loadAccounts();
    void saveAccounts() const;

    Transaction transactionManager;
};

#endif