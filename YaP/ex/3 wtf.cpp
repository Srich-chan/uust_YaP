#include <iostream>


class node {
public:
    double value;
    node* next=nullptr;
};


class list {
    node* ptr_at(size_t ind) {
        if (size == 0) throw std::domain_error{"sdf"};
        if (ind >= size) throw std::domain_error{"www"};
        if (ind == 0) return tail;
        node* w = head;
        while (size - ind > 1) {
            w = w->next;
            ++ind;
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
        if (ind >= size) {
            push(val);
        } else if (ind == 0) {
            tail->next = new node{val};
            ++size;
        } else {
            node* pr = ptr_at(ind);
            node* t = pr->next;
            pr->next = new node{val, t};
            ++size;
        }
    }

    ~list() {
        while (head) {
            node* t = head;
            head = head->next;
            delete t;
        }
    }
};

int main() {
    list puk{1};
    for (int i=2; i < 20; ++i) {
        puk.push(i);
    }
    `
}