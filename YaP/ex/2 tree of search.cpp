#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

class Node {
public:
    double value=0.0;
    Node* left=nullptr;
    Node* right=nullptr;

    double max() {
        Node* M = this;
        while (M->right) M = M->right;
        return M->value;
    }

    double min() {
        Node* m = this;
        while (m->left) m = m->left;
        return m->value;
    }

    Node* insert(const double& val) {
        if (val == value) return this;
        if (val < value) {
            if (left) return left->insert(val);
            left = new Node{val};
            return left;
        }
        if (right) return right->insert(val);
        right = new Node{val};
        return right;
    }

    size_t deepness() {
        if (is_leaf()) return 1;

        size_t ld = !!left;
        if (ld) ld += left->deepness();

        size_t rd = !!right;
        if (rd) rd += right->deepness();

        return ld > rd? ld : rd;
    }

    void print() {
        cout << "[";
        print_rec();
        cout << "\b\b]";
    }

    bool is_leaf() {
        return !left && !right;
    }

    // Дабы можно было копировать узлы.
    void delete_tree() {
        if (left) left->delete_tree();
        if (right) right->delete_tree();
        delete this;
    }

    // или
    static void delete_tree(Node* n) {
        n->delete_tree();
    }


    Node* copy_rec() {
        Node* copy = new Node{value};
        if (left) copy->left = left->copy_rec();
        if (right) copy->right = right->copy_rec();
        return copy;
    }

    void print_tree(const bool cringe = false) {
        size_t d = deepness();
        for (size_t l=0; l < d; ++l) {
            if (cringe) {
                for (int i=0; i < d - l; ++i) cout << "\t";
                if (l % 2 == 0) cout << "\b\b\b\b";
            }
            print_layer(l);
        }
    }

    void print_layer(const size_t layer) {
        cout << "Layer " << layer << ": ";
        if (layer < deepness())
            print_layer_rec(0, layer, this);
        else
            cout << " is empty";
        cout << "\n";
    }

    Node* seek(double val) {
        Node* h = this;
        while (h) {
            if (h->value == val) return h;
            if (val < h->value) h = h->left;
            else h = h->right;
        }
        return nullptr;
    }


    void remove(double val) {
        delete retrieve(val);
    }


private:
    Node* retrieve(double val, Node* parent=nullptr) {
       if (val == value) {
           if (parent) {
               Node*& replace = value < parent->value? parent->left : parent->right;

           }
           return this;
       }
    }

    Node* retrieve(Node* parent=nullptr) {

    }

    Node* seek_parent(double val) {
        if (val == value) return nullptr;
        Node* h = this;
        while (h) {
            if (h->is_child_have(val))
                return h;
            if (val < h->value)
                h = h->left;
            else
                h = h->right;
        }
        return nullptr;
    }

    bool is_child_have(double val) {
        return val == left->value || val == right->value;
    }

    void print_layer_rec(const size_t current, const size_t target, Node* head) {
        if (current == target)
            cout << "" << head->value << " ";
        else {
            if (head->left) print_layer_rec(current + 1, target, head->left);
            else print_layer_NULL_rec(target - current - 1);

            if (head->right) print_layer_rec(current + 1, target, head->right);
            else print_layer_NULL_rec(target - current - 1);
        }
    }

    void print_layer_NULL_rec(const size_t count) {
        size_t pupu=1;
        for (int i=0; i < count; ++i)
            pupu *= 2;

        for (size_t i=0; i < pupu; ++i) {
            cout << ". ";
        }
    }

    void print_rec() {
        if (left) left->print_rec();
        cout << value << ", ";
        if (right) right->print_rec();
    }
};


class STree{
    size_t _size=0;


    Node* retrieve(double val) {
        ;
    }

    Node* seek_parent(double val, bool& is_left) { //TODO
        if (val == root->value) return nullptr;
        Node* h = root;
        while (h) {
            if (h->value == val) return h;
            if (val < h->value) h = h->left;
            else h = h->right;
        }
        return nullptr;
    }
public:
    Node* root=nullptr;

    STree() = default;
    explicit STree(double val) {
        root = new Node{val};
        _size = 1;
    }

    ~STree() {
        root->delete_tree();
    }

    Node* insert(double val) {
        ++_size;
        return root->insert(val);
    }

    size_t size () {
        return _size;
    }

private:
};



string BOOL(bool cond) {
    return {cond? "true" : "false"};
}


#include <random>
int main () {
    STree t{123};
    Node*& root = t.root;

    t.insert(10);
    t.insert(9);
    t.insert(11);

    t.insert(1000);
    t.insert(1001);
    t.insert(999);
    t.insert(900);

    // mt19937 rand(root->value);
    // for (int i=0; i < 10; ++i) {
    //     t.insert(static_cast<double>(rand() % 200) - 100);
    //     // t.insert((static_cast<double>(rand() % 2000) - 1000) / 10);
    // }

    cout << "ROOT:\n";
    root->print_tree();

    cout << "\nLEFT:\n";
    root->left->print_tree();

    cout << "\nRIGHT:\n";
    root->right->print_tree();
    
    // cin.get();
}