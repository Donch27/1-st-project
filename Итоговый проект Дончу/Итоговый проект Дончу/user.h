#pragma once
#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
    string login;
    string password;
    string name;

public:
    User(const string& login, const string& password, const string& name);

    string getLogin() const;
    string getPassword() const;
    string getName() const;
    bool checkPassword(const string& inputPassword) const;
};

#endif