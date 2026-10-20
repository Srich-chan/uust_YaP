#include <iostream>
#include <string>

using namespace std;
#define DEBUG 0

class State {
    inline static State* head = nullptr;
    void add_to_the_list();
protected:
    State* next = nullptr;
    string name;

public:
    State();
    State(const string& name);
    ~State();

    virtual string_view classname() const;
    static void printAll();
};

class Monarchy : public State {
public:
    using State::State;
    std::string_view classname() const override;
};

class Kingdom : public Monarchy {
public:
    using Monarchy::Monarchy;
    std::string_view classname() const override;

};

class Republic : public State {
public:
    using State::State;
    std::string_view classname() const override;
};