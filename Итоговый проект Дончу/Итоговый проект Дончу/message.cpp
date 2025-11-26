#include "message.h"

Message::Message(const string& from, const string& to, const string& text)
    : from(from), to(to), text(text) {
}

string Message::getFrom() const { return from; }
string Message::getTo() const { return to; }
string Message::getText() const { return text; }

void Message::display() const {
    if (to == "ALL") {
        cout << "[ALL] " << from << ": " << text << endl;
    }
    else {
        cout << "[PRIVATE from " << from << "] " << text << endl;
    }
}