#include <iostream>
#include <sstream>


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
            throw domain_error{"Puk puken"};
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
        ss << "]";
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
        if (0 <= first_negative) return;

        for (h = head; !!h->next; h = h->next) {
            if (h->next->value == 20) {
                // h->value = first_negative;
                // ИЛИ
                insert(first_negative, h);
                h = h->next;
            }
        }
    }
};


int main() {
    list test_list{1};
    for (int i=2; i < 20; ++i) {
        test_list.push(20);
    }
    test_list.push(-123);
    test_list.push(-23);
    test_list.push(-4321);
    test_list.push(-1);
    test_list.print();

    test_list.TASK();

    test_list.print();
}