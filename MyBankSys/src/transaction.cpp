#include "transaction.h"

void Transaction::deposit(int accountNumber, double amount) {
    TransactionInfo depositTransaction{accountNumber, "DEPOSIT", amount};
    transactions.push_back(depositTransaction);
}

void Transaction::withdraw(int accountNumber, double amount) {
    TransactionInfo withdrawTransaction{accountNumber, "WITHDRAW", amount};
    transactions.push_back(withdrawTransaction);
}

void Transaction::displayTransactions(int accountNumber) const {
    std::ifstream inputFile("txt/Transactions.txt");

    if (inputFile.is_open()) {
        std::cout << "Transactions for Account " << accountNumber << ":\n";

        while (true) {
            int fileAccountNumber;
            std::string fileType;
            double fileAmount;

            inputFile >> fileAccountNumber >> fileType >> fileAmount;

            if (inputFile.eof()) {
                break;  // Exit the loop if end of file is reached
            }

            if (fileAccountNumber == accountNumber) {
                std::cout << "Type: " << fileType << ", Amount: " << fileAmount << "\n";
            }
        }

        inputFile.close();
    } else {
        std::cout << "Unable to open file for reading transaction data." << std::endl;
    }
}

void Transaction::saveTransactions(std::ofstream& outputFile) const {
    // Keep track of the last saved transaction
    static size_t lastSavedIndex = 0;

    // Check if there are new transactions to save
    if (lastSavedIndex < transactions.size()) {
        // Save only the new transactions
        for (size_t i = lastSavedIndex; i < transactions.size(); ++i) {
            const auto& transaction = transactions[i];
            outputFile << transaction.accountNumber << " "
                       << transaction.type << " "
                       << transaction.amount << "\n";
        }

        // Update the last saved index
        lastSavedIndex = transactions.size();
    }
}


void Transaction::loadTransactions(std::ifstream& inputFile) {
    int accountNumber;
    std::string type;
    double amount;

    while (inputFile >> accountNumber >> type >> amount) {
        TransactionInfo loadedTransaction{accountNumber, type, amount};
        transactions.push_back(loadedTransaction);
    }
}

const std::vector<Transaction::TransactionInfo>& Transaction::getTransactions() const {
    return transactions;
}