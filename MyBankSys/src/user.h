#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
public:
    User();

    // Function to authenticate a user
    bool authenticate(const std::string& userName, const std::string& password) const;

    // Function to create a new user
    void createUser(const std::string& userName, const std::string& password);

    // Function to delete a user
    void deleteUser(const std::string& userName);

    // Function to display all users
    void displayUsers() const;

private:
    struct UserInfo {
        int userId;
        std::string userName;
        std::string password;
    };

    std::vector<UserInfo> users;

    // Function to load users from file
    void loadUsers();

    // Function to save users to file
    void saveUsers() const;
};

#endif