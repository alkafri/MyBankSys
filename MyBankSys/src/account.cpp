#include "account.h"
#include <iostream>

Account::Account(int number, const std::string& holder, double initialBalance)
    : accountNumber(number), balance(initialBalance) {
    accountHolder = new std::string(holder); // Heap allocation for dynamic string
}

Account::~Account() {
    delete accountHolder; // Release heap-allocated memory in the destructor
}

int Account::getAccountNumber() const {
    return accountNumber;
}

std::string Account::getAccountHolder() const {
    return *accountHolder; // Dereference to get the string value
}

double Account::getBalance() const {
    return balance;
}

void Account::setAccountHolder(const std::string& newHolder) {
    *accountHolder = newHolder; // Modify heap-allocated string data
}

void Account::deposit(double amount) {
    balance += amount;
}

void Account::withdraw(double amount) {
    if (amount <= balance) {
        balance -= amount;
    } else {
        std::cout << "Insufficient funds." << std::endl;
    }
}

void Account::displayDetails() const {
    std::cout << "Account Number: " << accountNumber << "   ||||   ";
    std::cout << "Account Holder: " << *accountHolder << "   ||||   ";
    std::cout << "Balance: " << balance << std::endl;
    std::cout << "==========================================================================\n";
}