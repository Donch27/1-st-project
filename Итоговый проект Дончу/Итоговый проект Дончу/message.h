#pragma once

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>
using namespace std;

class Message {
private:
    string from;
    string to;
    string text;

public:
    Message(const string& from, const string& to, const string& text);

    string getFrom() const;
    string getTo() const;
    string getText() const;
    void display() const;
};
#endif