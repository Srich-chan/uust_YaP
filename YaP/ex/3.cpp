#include <iostream>
#include <sstream>
#include <windows.h>


using namespace std;

class node {
public:
    double value;
    node* next=nullptr;
};


class list {
    node* ptr_at(size_t ind) {
        if (size == 0) throw std::domain_error{"sdf"};
        if (ind >= size) throw std::domain_error{"www"};
        if (ind == size - 1) return tail;
        node* w = head;
        while (ind > 0) {
            w = w->next;
            --ind;
        }
        return w;
    }
public:
    node* head=nullptr;
    node* tail=nullptr;
    size_t size=0;

    list() = default;
    list(double val) {
        tail = new node{val};
        head = tail;
        ++size;
    }

    double operator[](size_t ind) {
        return ptr_at(ind)->value;
    }

    void push(double val) {
        head = new node{val, head};
        ++size;
    }

    void insert(double val, size_t ind) {
        if (ind > size)
            throw domain_error{"PROBLEM"};
        if (ind == 0) {
            push(val);
            return;
        }
        insert(val, ptr_at(ind-1));
    }

    void insert(double val, node* par) {
        node *t = par->next;
        par->next = new node{val, t};
        ++size;
    }

    ~list() {
        while (head) {
            node* t = head;
            head = head->next;
            delete t;
        }
    }

    string str() {
        ostringstream ss;
        ss << "[" << head->value;
        node* h = head;
        while (h->next) {
            h = h->next;
            ss << ", " << h->value;
        }
        ss << "] Size: " << size << "\n";
        return ss.str();
    }

    void print() {
        cout << str() << '\n';
    }

    void TASK() {
        double first_negative=0;
        node* h = head;
        while (h) {
            if (h->value < 0) {
                first_negative = h->value;
                break;
            }
            h = h->next;
        }
        if (0 <= first_negative) // aka отрицательного нет
            return;


        for (h = head; !!h->next; h = h->next) {
            if (h->next->value == 20) {
                insert(first_negative, h);
                h = h->next;
            }
        }
    }
};


void test(list& l) {
    const static string line(120, '+');
    static size_t case_count = 1;
    cout << "Case " << case_count++ << "\n";

    cout << "Before:\n";
    l.print();

    l.TASK();

    cout << "After:\n";
    l.print();
    cout << line << "\n";
}

void legacy_case() {
    list test_list;
    for (int i=0; i < 20; ++i) {
        test_list.push(20);
    }
    test_list.push(-123);
    test_list.push(-23);
    test_list.push(-4321);
    test_list.push(-1);

    test(test_list);
}

void neutral_case() {
    list l;
    for (int i = 0; i < 10; ++i) {
        l.push(9999);
    }
    test(l);
}

void without_twenty() {
    list l;
    for (int i = 0; i < 5; ++i) {
        l.push(100);
        l.push(-123);
    }
    test(l);
}

void with_twenty() {
    list l;
    for (int i = 0; i < 5; ++i) {
        l.push(100);
        l.push(-123);
        l.push(20);
    }
    test(l);
}



int main() {
    legacy_case();
    neutral_case();
    without_twenty();
}