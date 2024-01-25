#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    int accountNumber;
    std::string* accountHolder; // Using heap allocation for dynamic string data
    double balance;

public:
    Account(int number, const std::string& holder, double initialBalance);
    ~Account(); // Destructor to release heap-allocated memory

    int getAccountNumber() const;
    std::string getAccountHolder() const;
    double getBalance() const;

    void setAccountHolder(const std::string& newHolder);
    void deposit(double amount);
    void withdraw(double amount);
    void displayDetails() const;
};

#endif