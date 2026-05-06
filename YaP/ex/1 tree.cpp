#include <iostream>
#include <random>


using namespace std;


class tree{
public:

    class branch {
    public:
        branch* add_child(int value=10) {
            if (child == nullptr) {
                child = new branch{this};
                child->_value = value;
                return child;
            }
            return child->add_sibling(value);
        }
        branch* add_sibling(int value=228) {
            branch* head = this;
            while (head->next_sibling != nullptr) {
                head = head->next_sibling;
            }
            branch*& sib = head->next_sibling;
            sib = new branch{head->parent};
            sib->prev_sibling = head;
            sib->_value = value;

            return sib;
        }

        void _tree_size_rec(size_t& c) {
            ++c;
            if (this->child)
                child->_tree_size_rec(c);
            if (this->next_sibling)
                next_sibling->_tree_size_rec(c);
        }

        void _count_leaves_rec(size_t& c) {
            c += !this->child;
            if (child)
                child->_count_leaves_rec(c);

            if (next_sibling)
                next_sibling->_count_leaves_rec(c);
        }



        size_t tree_size() {
            if (!this->child) return 1;
            size_t c = 1;
            _tree_size_rec(c);
            return c;
        }

        size_t count_leaves() {
            if (!this->child) return 1;
            size_t c = 0;
            _count_leaves_rec(c);
            return c;
        }


        // Cчитает кол-во детей, но не внуков;
        size_t count_childs() {
            if (!child) return 0;

            branch* head = child;
            size_t c = 1;
            while (head->next_sibling) {
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

        int _value=67;

        ~branch() {
            delete child;
            delete next_sibling;
        }
    };

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
    tree VELIKOE_DREVO(gen);

    cout << "Leaves: " << VELIKOE_DREVO.root->count_leaves();
    cout << "\nTotal Size: " << VELIKOE_DREVO.root->tree_size();
}
