#include "chat.h"
#include <iostream>
#include <limits>
using namespace std;

Chat::Chat() : currentUser(nullptr) {}

User* Chat::findUserByLogin(const string& login) {
    for (auto& user : users) {
        if (user.getLogin() == login) {
            return &user;
        }
    }
    return nullptr;
}

bool Chat::loginExists(const string& login) {
    return findUserByLogin(login) != nullptr;
}

void Chat::registerUser() {
    string login, password, name;

    cout << "=== РЕГИСТРАЦИЯ ===" << endl;
    cout << "Логин: ";
    cin >> login;

    if (loginExists(login)) {
        cout << "Ошибка: Логин уже существует!" << endl;
        return;
    }

    cout << "Пароль: ";
    cin >> password;
    cout << "Имя: ";
    cin >> name;

    users.push_back(User(login, password, name));
    cout << "Пользователь " << name << " успешно зарегистрирован!" << endl;
}

bool Chat::loginUser() {
    string login, password;

    cout << "=== ВХОД ===" << endl;
    cout << "Логин: ";
    cin >> login;
    cout << "Пароль: ";
    cin >> password;

    User* user = findUserByLogin(login);
    if (user && user->checkPassword(password)) {
        currentUser = user;
        cout << "Добро пожаловать, " << user->getName() << "!" << endl;
        return true;
    }

    cout << "Ошибка: Неверный логин или пароль!" << endl;
    return false;
}

void Chat::logout() {
    if (currentUser) {
        cout << "До свидания, " << currentUser->getName() << "!" << endl;
        currentUser = nullptr;
    }
}

void Chat::sendPrivateMessage() {
    if (!currentUser) {
        cout << "Ошибка: Вы не авторизованы!" << endl;
        return;
    }

    string recipientLogin, text;
    cout << "Логин получателя: ";
    cin >> recipientLogin;

    if (!loginExists(recipientLogin)) {
        cout << "Ошибка: Пользователь не найден!" << endl;
        return;
    }

    cout << "Сообщение: ";
    cin.ignore();
    getline(cin, text);

    messages.push_back(Message(currentUser->getLogin(), recipientLogin, text));
    cout << "Сообщение отправлено!" << endl;
}

void Chat::sendBroadcastMessage() {
    if (!currentUser) {
        cout << "Ошибка: Вы не авторизованы!" << endl;
        return;
    }

    string text;
    cout << "Сообщение для всех: ";
    cin.ignore();
    getline(cin, text);

    messages.push_back(Message(currentUser->getLogin(), "ALL", text));
    cout << "Сообщение отправлено всем пользователям!" << endl;
}

void Chat::showMyMessages() {
    if (!currentUser) {
        cout << "Ошибка: Вы не авторизованы!" << endl;
        return;
    }

    string currentLogin = currentUser->getLogin();
    cout << "=== ВАШИ СООБЩЕНИЯ ===" << endl;

    bool found = false;
    for (const auto& msg : messages) {
        if (msg.getTo() == currentLogin || msg.getTo() == "ALL" || msg.getFrom() == currentLogin) {
            msg.display();
            found = true;
        }
    }

    if (!found) {
        cout << "Сообщений нет" << endl;
    }
}

void Chat::showAllUsers() {
    cout << "=== ВСЕ ПОЛЬЗОВАТЕЛИ ===" << endl;
    for (const auto& user : users) {
        cout << user.getName() << " (" << user.getLogin() << ")" << endl;
    }
}

void Chat::run() {
    int choice;

    while (true) {
        if (!currentUser) {
            cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << endl;
            cout << "1. Регистрация" << endl;
            cout << "2. Вход" << endl;
            cout << "3. Выход" << endl;
            cout << "Выберите действие: ";
            cin >> choice;

            switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: return;
            default: cout << "Неверный выбор!" << endl;
            }
        }
        else {
            cout << "\n=== ЧАТ ===" << endl;
            cout << "Пользователь: " << currentUser->getName() << endl;
            cout << "1. Отправить личное сообщение" << endl;
            cout << "2. Отправить сообщение всем" << endl;
            cout << "3. Показать мои сообщения" << endl;
            cout << "4. Показать всех пользователей" << endl;
            cout << "5. Выход" << endl;
            cout << "Выберите действие: ";
            cin >> choice;

            switch (choice) {
            case 1: sendPrivateMessage(); break;
            case 2: sendBroadcastMessage(); break;
            case 3: showMyMessages(); break;
            case 4: showAllUsers(); break;
            case 5: logout(); break;
            default: cout << "Неверный выбор!" << endl;
            }
        }
    }
}