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

    // bool operator==(Node o) {return value == o.value;}
    // bool operator<(Node o) {return value < o.value;}
    // bool operator>(Node o) {return o < *this;}


    ~Node() {
        delete left;
        delete right;
    }
};

class STree{
public:
    Node* root;
    STree(double val) {
        root = new Node{val};
    }

    ~STree() {
        delete root;
    }

    // Node* insert(double val) {
    //     Node* h = root;
    //     Node* back = nullptr;
    //     while (h) {
    //         back = h;
    //         if (h->value == val) return h;
    //         if (val < h->value) {
    //             h = h->left;
    //         } else {
    //             h = h->right;
    //         }
    //     }
    // }

    Node* insert(double val) {
        return root->insert(val);
    }


private:
};



int main () {
    STree t{0};

    for (int i=)

    cout << t.root->max();
}
