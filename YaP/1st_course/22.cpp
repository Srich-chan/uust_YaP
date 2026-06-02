#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <map>

using namespace std;


class Node {
public:
    const double value=0.;
    Node* next=nullptr;

    Node () = default;
    Node (const double& val, Node* nxt=nullptr) : value(val) {
        next = nxt;
    }
};


Node* next(Node*& node) {
    node = node->next;
    return node;
}


class List {
public:
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t _size = 0;

    Node* find(const double& val) const {
        for (Node* node = head; node; node = node->next) {
            if (node->value == val)
                return node;
        }
        return nullptr;
    }

   ///////  Копирование
    List copy() const {
        List res;
        for (Node* node = head; node; next(node)) {
            res.push_tail(node->value);
        }
        return move(res);
    }

    List copy_reverse() const {
        List res;
        for (Node* node=head; node; next(node)) {
            res.push(node->value);
        }
        return move(res);
    }

    List& operator=(const List& list) {
        cout << "Coping...\n";
        List l_copy = list.copy(); // move copy
        swap(head, l_copy.head);
        swap(_size, l_copy._size);
        tail = l_copy.tail;
        cout << "Copied!\n";
        return *this;
    }

    List& operator=(List&& list) noexcept {
        swap(head, list.head);
        swap(tail, list.tail);
        swap(_size, list._size);

        list.~List();
        // cout << "Moved!\n";
        return *this;
    }

    List(const List& l)  {
        *this = l;
    }
    List(List&& l) noexcept {
        *this = move(l);
    }
    //////

    List() = default;
    ~List() {
        // cout << "Killing...-";
        Node* h = head;
        while (h) {
            Node* t = h;
            next(h);
            delete t;
        }
        // if (!head)
        //     cout << "Killed empty List!\n";
        // else
        //     cout << "Killed List with size: "<<_size<<"\n";

    }
    size_t size() const {
        return _size;
    }

    void push_tail(const double& a) {
        if (!tail) {
            head = new Node{a};
            tail = head;
        } else {
            tail->next = new Node{a, nullptr};
            next(tail);
        }
        ++_size;
    }

    void push(const double& a) {
        if (!head) {
            head = new Node{a};
            tail = head;
        } else {
            head = new Node{a, head};
        }
        ++_size;
    }

    void print_info() const {
        cout << "[";
        if (head) {
            Node* node = head;
            cout << node->value;
            next(node);
            for (; node; next(node)) {
                cout << ", " << node->value;
            }
        }
        cout << "] Size: " << _size << "\n";
    }
};


List shitty_merge(const List &L1, const List &L2) {
    List res;

    if (L1.size()) {
        // Счёт элементов L2
        map<double, size_t> l2_count;
        for (Node* node = L2.head; node; next(node)) {
            ++l2_count[node->value];
        }

        // Merge
        for (Node* node = L1.head; node; next(node)) {
            // if (l2_count[node->value] >= 2) continue;  // 2 и более вхождения
            if (l2_count[node->value] == 2) continue;  // 2 вхождения
            res.push_tail(node->value);
        }
    }
    return res;
 }

mt19937 random(0);
List gen_list(size_t size = 10, long unsigned _ceil = -1, bool neg = false, size_t seed = 0xbebebe) {
    if (seed != 0xbebebe)
        random.seed(seed);

    const size_t ceil = (neg + 1) * _ceil;
    List result;

    for (size_t i=0; i < size; ++i) {
        double gen = random() % ceil - neg * (ceil / 2.0);

        result.push(gen);
    }

    return move(result);
}


void test(const List &L1, const List &L2) {
    static const string line(100, '-');

    static int case_count = 1;
    cout << "Case " << case_count++ << '\n';


    cout << "L1 = ";
    L1.print_info();
    cout << "L2 = ";
    L2.print_info();
    cout << "\nL = ";
    shitty_merge(L1, L2).print_info();

    cout << line << '\n';
}

void case_67() {
    List l1;
    List l2;

    for (int i = 0; i < 10; i++)
        l1.push(123);
    for (int i=0; i < 10; ++i) {
        l1.push(67);
    }

    for (int i=0; i < 2; ++i) {
        l2.push(67);
    }

    test(l1, l2);
}

void emptyness() {
    List l = gen_list(10, 10, 1, 123);
    List e;

    test(e, e);
    test(l, e);
    test(e, l);
}

void case_some() {
    List pi;
    List l1;
    List l2;

    for (double el : {314, 314, 314}) {
        pi.push(el);
    }

    for (double el : {1, 2, 3, 0xaa, 0xaa, 4, 5, 6, -123, -123}) {
        l2.push_tail(el);
    }

    test(pi, l2);

    for (double el : {1, 2, 3, 4, 5}) {
        l1.push_tail(el);
        l1.push_tail(0xaa);
        l1.push(-123);
    }

    test(l1, l2);
}

void different() {
    List l1, l2;
    l1 = gen_list(10, 10, 1, 123);
    l2 = gen_list(10, 10, 1);

    test(l1, l2);
}

void random_cases(int kolvo = 10) {
    gen_list(0, 10, 0, 100);
    for (int i = 0; i < kolvo; ++i) {
        test(gen_list(100, 10, 0),
             gen_list(10, 10, 0));
    }
}



int main () {
    random_cases(10);
    emptyness();
    case_67();
    case_some();
}