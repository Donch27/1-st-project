#pragma once
#ifndef CHAT_H
#define CHAT_H

#include "user.h"
#include "message.h"
#include <vector>
using namespace std;

class Chat {
private:
    vector<User> users;
    vector<Message> messages;
    User* currentUser;

    User* findUserByLogin(const string& login);
    bool loginExists(const string& login);

public:
    Chat();
    void registerUser();
    bool loginUser();
    void logout();
    void sendPrivateMessage();
    void sendBroadcastMessage();
    void showMyMessages();
    void showAllUsers();
    void run();
};

#endif