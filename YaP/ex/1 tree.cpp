#include <iostream>
#include <random>


using namespace std;

class branch {
    branch* add_sibling(int value=228) {
        branch* head = this;
        while (head->next_sibling != nullptr) {
            head = head->next_sibling;
        }
        branch*& sib = head->next_sibling;
        sib = new branch{head->parent};
        sib->prev_sibling = head;
        sib->ass = value;

        return sib;
    }

    size_t count_with_siblings() {
        size_t c = 1;
        if (child != nullptr) c += child->count_with_siblings();
        if (next_sibling != nullptr) c += next_sibling->count_with_siblings();
        return c;
    }

    size_t _count_leaves() {
        size_t c = child == nullptr;
        if (child != nullptr) c += child->_count_leaves();
        if (next_sibling != nullptr) c += next_sibling->_count_leaves();
        return c;
    }
public:

    branch* add_child(int value=10) {
        if (child == nullptr) {
            child = new branch{this};
            child->ass = value;
            return child;
        }
        return child->add_sibling(value);
    }

    size_t tree_size() {
        if (child) return 1 + child->count_with_siblings();
        return 1;
    }

    size_t count_leaves() {
        if (child) return child->_count_leaves();
        return 1;
    }

    size_t count_childs() {
        if (!child) return 0;

        branch* head = child;
        size_t c = 1;
        while (head->next_sibling != nullptr) {
            head = head->next_sibling;
            ++c;
        }
        return c;
    }

    branch* operator[](size_t ind) {
        if (!child) throw std::domain_error{"puk"};
        if (ind >= count_childs()) throw std::domain_error{"srenk"};
        branch* head=child;
        for (size_t i=1; i < ind; ++i) {
            head = head->next_sibling;
        }
        return head;
    }

    branch* parent=nullptr;
    branch* child=nullptr;
    branch* prev_sibling=nullptr;
    branch* next_sibling=nullptr;
    int ass=67;

    ~branch() {
        delete child;
        delete next_sibling;
    }
};


class tree{
public:
    branch* root;
    // Пустое древо
    tree() {
        root = new branch();
    }

    // Дерево созданное броском кубика, где есть хотя бы 10 веток-узлов
    tree(std::mt19937 rand) {
        enum actions {
            new_child,
            mov_up,
            mov_down,
            finish
        };
        root = new branch();
        branch* head = root->add_child(rand() % 666);
        size_t c = 1;

        bool puk = true;
        while (puk) {
            switch (rand() % (finish + 1)) {
                case new_child:
                    head->add_child();
                    ++c;
                    break;

                case mov_up:
                    if (head->parent != root)
                        head = head->parent;
                    break;

                case mov_down:
                    if (head->child) head = (*head)[rand() % head->count_childs()];
                    break;

                case finish:
                    if (c > 10) puk = false;
                    break;

                default:
                    throw std::domain_error("wtf");
            }
        }
    }

    ~tree() {
        delete root;
    }
};


int main() {
    std::mt19937 gen(123);
    tree puk(gen);

    cout << "Leaves: " << puk.root->count_leaves();
    cout << "\nTotal Size: " << puk.root->tree_size();
}
