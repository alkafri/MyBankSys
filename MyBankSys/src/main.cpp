#include "bank.h"
#include "user.h"
#include "transaction.h"
#include <iostream>
#include <fstream>
#include <limits>

void saveAccountData(const Bank& bank) {
    std::ofstream outputFile("txt/Accounts.txt");

    if (outputFile.is_open()) {
        bank.saveAccounts(outputFile);
        outputFile.close();
    } else {
        std::cout << "Unable to open file for writing account data." << std::endl;
    }
}

void loadAccountData(Bank& bank) {
    std::ifstream inputFile("txt/Accounts.txt");

    if (inputFile.is_open()) {
        bank.loadAccounts(inputFile);
        inputFile.close();
    } else {
        std::cout << "Unable to open file for reading account data." << std::endl;
    }
}

void saveTransactionData(Transaction& transactionManager) {
    std::ofstream outputFile("txt/Transactions.txt", std::ios::app); // Open in append mode

    if (outputFile.is_open()) {
        transactionManager.saveTransactions(outputFile);
        outputFile.close();
        std::cout << "Transactions saved successfully." << std::endl;
    } else {
        std::cout << "Unable to open file for writing transaction data." << std::endl;
    }
}


void loadTransactionData(Transaction& transactionManager) {
    std::ifstream inputFile("txt/Transactions.txt");

    if (inputFile.is_open()) {
        transactionManager.loadTransactions(inputFile);
        inputFile.close();
        std::cout << "Transactions loaded successfully." << std::endl;

        const auto& transactions = transactionManager.getTransactions();
        for (const auto& transaction : transactions) {
            std::cout << "Account: " << transaction.accountNumber << ", Type: " << transaction.type << ", Amount: " << transaction.amount << "\n";
        }
    } else {
        std::cout << "Unable to open file for reading transaction data." << std::endl;
    }
}

void clearScreen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

int main() {
    User userManager;
    Bank bank;
    Transaction transactionManager;

    std::string userName, password;

    // User authentication loop
    while (true) {
        std::cout<<"\n";
        std::cout<<"\n";
        std::cout << "*******************************************" << std::endl;
        std::cout << "Enter your username: ";
        std::cin >> userName;

        std::cout << "Enter your password: ";
        std::cin >> password;

        if (userManager.authenticate(userName, password)) {
            std::cout << "Authentication successful." << std::endl;
            break; // Exit the authentication loop if successful
        } else {
            std::cout << "Authentication failed. Please try again." << std::endl;
        }
        std::cout << "*******************************************" << std::endl << std::endl;
    }

    int choice;

    while (true) {
        // Display menu
        std::cout << "\nOptions:\n";
        std::cout << "1. List all users\n";
        std::cout << "2. Add user\n";
        std::cout << "3. Delete a user\n";
        std::cout << "4. List all accounts\n";
        std::cout << "5. Create new account\n";
        std::cout << "6. Delete an account\n";
        std::cout << "7. List all transactions related to a specific account\n";
        std::cout << "8. Make a deposit transaction into an account\n";
        std::cout << "9. Make a withdraw transaction from an account\n";
        std::cout << "10. Exit the application\n";
        std::cout << "*******************************************" << std::endl << std::endl;

        // Get user choice
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << "*******************************************" << std::endl << std::endl;

        switch (choice) {
            case 1:
                clearScreen();
                // List all users
                userManager.displayUsers();
                std::cout << "*******************************************" << std::endl << std::endl;
                break;
            case 2:
                clearScreen();
                // Add user
                std::cout << "Enter the new username: ";
                std::cin >> userName;
                std::cout << "Enter the new password: ";
                std::cin >> password;
                userManager.createUser(userName, password);
                std::cout << "*******************************************" << std::endl << std::endl;
                break;
            case 3:
                clearScreen();
                // Delete a user
                std::cout << "Enter the username to delete: ";
                std::cin >> userName;
                userManager.deleteUser(userName);
                std::cout << "*******************************************" << std::endl << std::endl;
                break;
            case 4:
                clearScreen();
                // List all accounts
                bank.displayAccounts();
                break;
            case 5:
                clearScreen();
                // Create new account
                std::cout << "Enter the account holder's name: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, userName);
                bank.createAccount(userName);
                saveAccountData(bank);  // Save account data after creating a new account
                std::cout << "*******************************************" << std::endl << std::endl;
                break;
            case 6:
                clearScreen();
                // Delete an account
                int accountNumber;
                std::cout << "Enter the account number to delete: ";
                std::cin >> accountNumber;
                bank.closeAccount(accountNumber);
                saveAccountData(bank);  // Save account data after deleting an account
                std::cout << "*******************************************" << std::endl << std::endl;
                break;
            case 7:
                clearScreen();
                // List all transactions related to a specific account
                int accountNumberToDisplay;
                std::cout << "Enter the account number to display transactions: ";
                std::cin >> accountNumberToDisplay;
                transactionManager.displayTransactions(accountNumberToDisplay);
                std::cout << "*******************************************" << std::endl << std::endl;
                break;
            case 8:
                clearScreen();
                // Make a deposit transaction into an account

                // User chooses to make a deposit
                int depositAccountNumber;
                double depositAmount;
                std::cout << "Enter the account number for the deposit: ";
                std::cin >> depositAccountNumber;
                std::cout << "Enter the deposit amount: ";
                std::cin >> depositAmount;

                // Initiating the deposit through the Transaction class
                transactionManager.deposit(depositAccountNumber, depositAmount);

                // Updating account balances in the Bank class
                bank.updateAccountBalances(transactionManager);  // Update account balances

                // Saving the transaction data
                saveTransactionData(transactionManager);  // Save transaction data after a deposit
                std::cout << "*******************************************" << std::endl << std::endl;
                break;
            case 9:
                clearScreen();
                // Make a withdraw transaction from an account
                int withdrawAccountNumber;
                double withdrawAmount;
                std::cout << "Enter the account number for the withdrawal: ";
                std::cin >> withdrawAccountNumber;
                std::cout << "Enter the withdrawal amount: ";
                std::cin >> withdrawAmount;
                transactionManager.withdraw(withdrawAccountNumber, withdrawAmount);
                bank.updateAccountBalances(transactionManager);  // Update account balances
                saveTransactionData(transactionManager);  // Save transaction data after a withdrawal
                std::cout << "*******************************************" << std::endl << std::endl;
                break;
            case 10:
                clearScreen();
                // Exit the application
                std::cout << "Exiting the application.\n";
                std::cout << "*******************************************" << std::endl << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}