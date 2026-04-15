#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

struct node {
    int val = 0;
    node* prev=nullptr;
    node* next=nullptr;
    explicit node (int v, node* prv=nullptr, node* nxt=nullptr)
        : val {v}, prev{prv}, next{nxt}
    {}
};

struct list {
private:
    enum state {
        DECL,
        ALIVE,
        DEAD
    };

    node* head=nullptr;
    size_t pos = 0;
    size_t len = 0;
    state state = DECL;

public:
    list() = default;
    list(int el, ...) {
        auto beg = &el;

    };
    list(list& L)
        : head {L.head} {
        state = ALIVE;
    }


    void push (int val) {
        head = new node(val, head);
    }

    void move_to(size_t i) {
        if (i >= len)
    }
    //
    // int pop () {
    //     int val = head->val;
    //     head = head->next;
    //     return val;
    // }

    ~list() {
        while (head) {
            auto t = head;
            head = head->next;
            delete[] t;
        }
    }
};



int main () {
    list L1{};
    list L2{};

    list L{};
    std::string some;

}