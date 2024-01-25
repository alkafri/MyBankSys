#include "bank.h"
#include "transaction.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Bank::Bank() {
    loadAccounts(); // Load accounts from file on initialization
}

Bank::~Bank() {
    // Clean up heap-allocated memory in the destructor
    for (auto& account : accounts) {
        delete account;
    }
}

void Bank::loadAccounts(std::ifstream& inputFile) {
    int accountNumber;
    std::string accountHolder;
    double balance;

    while (inputFile >> accountNumber >> accountHolder >> balance) {
        Account* loadedAccount = new Account(accountNumber, accountHolder, balance);
        accounts.push_back(loadedAccount);
    }

    std::cout << "Accounts loaded successfully." << std::endl;
}

void Bank::loadAccounts() {
    std::ifstream inputFile("txt/Accounts.txt");

    if (inputFile.is_open()) {
        loadAccounts(inputFile);
        inputFile.close();
    } else {
        std::cout << "Unable to open file for reading. Creating a new file." << std::endl;
    }
}

void Bank::saveAccounts(std::ofstream& outputFile) const {
    for (const auto& account : accounts) {
        outputFile << account->getAccountNumber() << " "
                   << account->getAccountHolder() << " "
                   << account->getBalance() << std::endl;
    }

    std::cout << "Accounts saved successfully." << std::endl;
}

void Bank::saveAccounts() const {
    std::ofstream outputFile("txt/Accounts.txt");

    if (outputFile.is_open()) {
        saveAccounts(outputFile);
        outputFile.close();
    } else {
        std::cout << "Unable to open file for writing." << std::endl;
    }
}

void Bank::createAccount(const std::string& accountHolder) {
    Account* newAccount = new Account(accounts.size() + 1, accountHolder, 0.0);
    accounts.push_back(newAccount);
    saveAccounts(); // Save accounts after creating a new one
    std::cout << "Account created successfully. Account Number: " << newAccount->getAccountNumber() << std::endl;
}

void Bank::displayAccounts() const {
    for (const auto& account : accounts) {
        account->displayDetails();
    }
}

void Bank::updateAccountDetails(int accountNumber, const std::string& newHolder) {
    auto it = std::find_if(accounts.begin(), accounts.end(),
                           [accountNumber](const Account* account) {
                               return account->getAccountNumber() == accountNumber;
                           });

    if (it != accounts.end()) {
        (*it)->setAccountHolder(newHolder);
        std::cout << "Account details updated successfully." << std::endl;
        saveAccounts(); // Save accounts after updating details
    } else {
        std::cout << "Account not found." << std::endl;
    }
}

void Bank::closeAccount(int accountNumber) {
    auto it = std::remove_if(accounts.begin(), accounts.end(),
                             [accountNumber](const Account* account) {
                                 return account->getAccountNumber() == accountNumber;
                             });

    if (it != accounts.end()) {
        delete *it; // Release memory for the closed account
        accounts.erase(it, accounts.end());
        saveAccounts(); // Save accounts after closing an account
        std::cout << "Account closed successfully." << std::endl;
    } else {
        std::cout << "Account not found." << std::endl;
    }
}

void Bank::deposit(int accountNumber, double amount) {
    auto it = std::find_if(accounts.begin(), accounts.end(),
                           [accountNumber](const Account* account) {
                               return account->getAccountNumber() == accountNumber;
                           });

    if (it != accounts.end()) {
        (*it)->deposit(amount);
        std::cout << "Deposit successful. New balance: " << (*it)->getBalance() << std::endl;
        saveAccounts(); // Save accounts after deposit
        updateAccountBalances(transactionManager); // Update account balances after each transaction
    } else {
        std::cout << "Account not found." << std::endl;
    }
}

void Bank::withdraw(int accountNumber, double amount) {
    auto it = std::find_if(accounts.begin(), accounts.end(),
                           [accountNumber](const Account* account) {
                               return account->getAccountNumber() == accountNumber;
                           });

    if (it != accounts.end()) {
        (*it)->withdraw(amount);
        std::cout << "Withdrawal successful. New balance: " << (*it)->getBalance() << std::endl;
        saveAccounts(); // Save accounts after withdrawal
        updateAccountBalances(transactionManager); // Update account balances after each transaction
    } else {
        std::cout << "Account not found." << std::endl;
    }
}

void Bank::updateAccountBalances(const Transaction& transactionManager) {
    const auto& transactions = transactionManager.getTransactions();

    // Keep track of the last processed transaction index
    static size_t lastProcessedIndex = 0;

    // Process only new transactions
    for (size_t i = lastProcessedIndex; i < transactions.size(); ++i) {
        const auto& transaction = transactions[i];

        auto accountIt = std::find_if(accounts.begin(), accounts.end(),
                                      [&transaction](const Account* account) {
                                          return account->getAccountNumber() == transaction.accountNumber;
                                      });

        if (accountIt != accounts.end()) {
            if (transaction.type == "DEPOSIT") {
                (*accountIt)->deposit(transaction.amount);
            } else if (transaction.type == "WITHDRAW") {
                (*accountIt)->withdraw(transaction.amount);
            }
        }
    }

    // Update the last processed transaction index
    lastProcessedIndex = transactions.size();

    saveAccounts(); // Save updated account balances to file
    std::cout << "Account balances updated successfully." << std::endl;
}