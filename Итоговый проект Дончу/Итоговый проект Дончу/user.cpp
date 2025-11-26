#include "user.h"

User::User(const string& login, const string& password, const string& name)
    : login(login), password(password), name(name) {
}

string User::getLogin() const { return login; }
string User::getPassword() const { return password; }
string User::getName() const { return name; }

bool User::checkPassword(const string& inputPassword) const {
    return password == inputPassword;
}