#include "user.h"
#include <iostream>
#include <fstream>
#include <algorithm>

User::User() {
    loadUsers(); // Load users from file on initialization
}

void User::loadUsers() {
    std::ifstream inputFile("txt/Users.txt");

    if (inputFile.is_open()) {
        int userId;
        std::string userName, password;

        while (inputFile >> userId >> userName >> password) {
            UserInfo userInfo{userId, userName, password};
            users.push_back(userInfo);
        }

        inputFile.close();

        std::cout << "Users loaded successfully." << std::endl;
    } else {
        std::cout << "Unable to open file for reading. Creating a new file." << std::endl;
    }
}

void User::saveUsers() const {
    std::ofstream outputFile("txt/Users.txt");

    if (outputFile.is_open()) {
        for (const auto& userInfo : users) {
            outputFile << userInfo.userId << " " << userInfo.userName << " " << userInfo.password << std::endl;
        }

        outputFile.close();

        std::cout << "Users saved successfully." << std::endl;
    } else {
        std::cout << "Unable to open file for writing." << std::endl;
    }
}

bool User::authenticate(const std::string& userName, const std::string& password) const {
    auto it = std::find_if(users.begin(), users.end(),
                           [userName, password](const UserInfo& userInfo) {
                               return userInfo.userName == userName && userInfo.password == password;
                           });

    return it != users.end();
}

void User::createUser(const std::string& userName, const std::string& password) {
    int newUserId = users.empty() ? 1 : users.back().userId + 1;
    UserInfo newUserInfo{newUserId, userName, password};
    users.push_back(newUserInfo);
    saveUsers(); // Save users after creating a new one
    std::cout << "User created successfully. User ID: " << newUserId << std::endl;
}

void User::deleteUser(const std::string& userName) {
    auto it = std::remove_if(users.begin(), users.end(),
                             [userName](const UserInfo& userInfo) {
                                 return userInfo.userName == userName;
                             });

    if (it != users.end()) {
        users.erase(it, users.end());
        saveUsers(); // Save users after deleting a user
        std::cout << "User deleted successfully." << std::endl;
    } else {
        std::cout << "User not found." << std::endl;
    }
}

void User::displayUsers() const {
    for (const auto& userInfo : users) {
        std::cout << "User ID: " << userInfo.userId
                  << ", Username: " << userInfo.userName
                  << ", Password: " << userInfo.password << std::endl;
    }
}