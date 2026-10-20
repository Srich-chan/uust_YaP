//
// Created by srich on 16.10.2026.
//

#include "Classes.h"

void State::add_to_the_list() {
    if (!head) {
        head = this;
    } else {
        State* t = head;
        while (t->next != nullptr) {
            t = t->next;
        }
        t->next = this;
    }
}

State::State() : name{"без имени"} {
    add_to_the_list();
}

State::State(const string& name_) : name{name_} {
    add_to_the_list();
}

State::~State() {
    if (head == this) {
        head = next? next : nullptr;
    } else {
        State* t = head;
        while (t->next != this) {
            t = t->next;
            #if DEBUG
            if (t->next == nullptr)
                throw logic_error{"State is not in global list"};
            #endif
        }
        t->next = next? next : nullptr;
    }
}

void State::printAll() {
    int c = 1;
    static const string line = string(20, '-');
    cout << line << '\n';
    for (State* t=head; t != nullptr; t = t->next) {
        cout << c++ << ". " << t->classname() << " " << t->name << '\n';
    }
}

string_view State::classname() const {
    return "Страна";
}

string_view Monarchy::classname() const {
    return "Монархия";
}

string_view Kingdom::classname() const {
    return "Королевство";
}

string_view Republic::classname() const  {
    return "Республика";
}