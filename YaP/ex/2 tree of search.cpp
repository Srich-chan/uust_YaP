#include <iostream>
#include <fstream>

using namespace std;







class Node {
public:
    double value;
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

    bool seek(double val) {
        Node* h = this;
        while (h) {
            if (h->value == val) return true;
            if (val < h->value) h = h->left;
            else h = h->right;
        }
        return false;
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

    void print_layer(size_t layer) {

    }



private:
    void print_layer_rec(size_t current, size_t target) {

    }


    void print_rec() {
        if (left) left->print_rec();
        cout << value << ", ";
        if (right) right->print_rec();
    }
};

auto f = Node::delete_tree;

class STree{
    size_t _size=0;
public:
    Node* root=nullptr;
    explicit STree(double val) {
        root = new Node{val};
        _size = 1;
    }

    ~STree() {
        root->delete_tree();
    }

    // void chain_left(Node* par=nullptr) {
    //     if (!par) par = root;
    //     if (par->left) {
    //
    //     }
    // }

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
    return {cond?
        "true" : "false"};
}


// #include <random>
int main () {
    STree t{123};
    t.insert(10);
    t.insert(9);
    t.insert(11);

    t.insert(1000);
    t.insert(1001);
    t.insert(999);
    t.insert(12313);

    auto root = t.root;
    // cout << root->deepness();
    root->print();

    cin.get();
}
