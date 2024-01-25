#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <fstream>
#include <vector>

enum class TransactionType {
    Deposit,
    Withdraw
};

class Transaction {
public:
    struct TransactionInfo {
        int accountNumber;
        std::string type;
        double amount;
    };

    void deposit(int accountNumber, double amount);
    void withdraw(int accountNumber, double amount);
    void displayTransactions(int accountNumber) const;

    // Add these two functions for saving and loading transactions
    void saveTransactions(std::ofstream& outputFile) const;
    void loadTransactions(std::ifstream& inputFile);
    
    // Add this function to get transactions
    const std::vector<TransactionInfo>& getTransactions() const;

private:
    std::vector<TransactionInfo> transactions;
};

#endif