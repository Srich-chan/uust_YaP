#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "../1st_course/paths.h"

using namespace std;

class Branch {
public:
    double value=0.0;
    Branch* left=nullptr;
    Branch* right=nullptr;

    Branch*& at(const bool& ind) {
        if (ind) return right;
        return left;
    }

    Branch* max() {
        Branch* M = this;
        while (M->right) M = M->right;
        return M;
    }
    Branch* min() {
        Branch* m = this;
        while (m->left) m = m->left;
        return m;
    }

    double get_min() {
        return min()->value;
    }
    double get_max() {
        return max()->value;
    }

    Branch* insert(const double& val) {
        if (val == value) return this;

        const bool ind = value < val;
        Branch*& a = at(ind);
        if (a) {
            Branch* b = a->insert(val);
            rotate();
            return b;
        }
        a = new Branch{val};
        return a;
    }

    void insert(Branch* node) {
        if (node->value == value) {
            if (node != this)
                throw domain_error{"insert node: There are should not be copies"};
            cerr << "\ninsert(node->value=" << value << ")\nThere are should not be duplicats! No mne pohuy\n";
            return;
        }
        const bool ind = value < node->value;
        Branch*& a = at(ind);
        if (a) {
            a->insert(node);
            rotate();
        } 
        else a = node;
    }

    size_t size() {
        size_t c = 0;
        this->_size_rec(c);
        return c;
    }

    void _size_rec(size_t& c) {
        if (this) {
            ++c;
            if (left) left->_size_rec(c);
            if (right) right->_size_rec(c);
        }
    }

    size_t max_depth() {
        if (is_leaf()) return 1;

        size_t ld = !!left;
        if (ld) ld += left->max_depth();

        size_t rd = !!right;
        if (rd) rd += right->max_depth();

        return ld > rd? ld : rd;
    }

    size_t min_depth() {
        if (is_leaf()) return 1;

        size_t ld = !!left;
        if (ld) ld += left->min_depth();

        size_t rd = !!right;
        if (rd) rd += right->min_depth();

        return ld < rd? ld : rd;
    }

    void print_list(const char* file_name= nullptr) {
        ofstream f;
        if (file_name) f.open(file_name);
        ostream& out = file_name? f : cout;

        out << "[";
        print_list_rec(out);
        out << "\b\b]\n";
    }

    bool is_leaf() {
        return !left && !right;
    }

    void delete_tree() {
        if (!this) return;
        if (left) left->delete_tree();
        if (right) right->delete_tree();
        delete this;
    }

    // Node* copy_rec() {
    //     Node* copy = new Node{value};
    //     if (left) copy->left = left->copy_rec();
    //     if (right) copy->right = right->copy_rec();
    //     return copy;
    // }

    void print_layer(const size_t layer) {
        cout << "Layer " << layer << ": ";
        if (layer < max_depth())
            print_layer_rec(0, layer, this);
        else
            cout << " is empty";
        cout << "\n";
    }

    void print_tree() {
        size_t d = max_depth();
        for (size_t l=0; l < d; ++l) {
            print_layer(l);
        }
    }

    void print_info(const char* name=nullptr) {
        if (!this) {
            cout << "\nSize: 0\nList: []\n";
            return;
        }
        if (name) cout << "\n" << name;
        cout << "\nSize: " << size()
        <<"\nList: ";
        print_list();
        print_tree();
        cout << "\n";
    }

    Branch* seek(double val) {
        Branch* h = this;
        while (h) {
            if (h->value == val) return h;
            if (val < h->value) h = h->left;
            else h = h->right;
        }
        return nullptr;
    }

    // double remove(double val) {
    //     Node* puk = seek_and_retrieve(val);
    //     if (val != puk->value) {
    //         throw logic_error{"It is very sad"};
    //     }
    //     delete puk;
    //     return val;
    // }
    //
    // void remove_out(double val) {
    //     cout << remove(val) << " removed\n";
    // }
    // // Находит, и делает висячую вершину
    // Node* seek_and_retrieve(double val) {
    //     Node* s = seek(val);
    //     return s->retrieve();
    // }

    Branch* retrieve() {
        // cout << "Trying to retrieve " << value << "...\n";
        if (!left && !right)
            throw logic_error{"Cannot retrieve from a leaf!"};
        Branch* to_delete;
        if (!right ^ !left) {
            to_delete = retrieve_crit(!!right);
        } else {
            to_delete = retrieve_crit(left->size() < right->size());
        }
        // cout << "--> Retrieved "<< value << "!\n";
        swap(value, to_delete->value);
        return to_delete;
    }

    // Передаю родителя т.к. this константный указатель
    Branch* retrieve(Branch* parent) {
        // cout << "trying to retrieve " << value << " with parent " << parent->value << "...\n";
        if (value == parent->value) throw domain_error{"Useless Error"};
        const bool is_right = parent->value < value;
        Branch*& parat = parent->at(is_right);
        if (is_leaf()) {
            parat = nullptr;
        } if (!right) {
            parat = left;
            left = nullptr;
        } else if (!left) {
            parat = right;
            right = nullptr;
        } else {
            throw logic_error{"Not implemented"};
        }
        // cout << "==> Retrieved "<< value << " from parent " << parent->value << "!\n";
        return this;
    }

    Branch* retrieve_crit(const bool& ind) {
        Branch* par = at(ind);
        // cout << "Calling retrieve_crit("<<ind<<") \n";
        if (!par) return this->retrieve();
        if (!par->at(!ind)) return par->retrieve(this);
        // cout << "( - .-) Retrieving "<< (ind?"right":"left") <<" crit from ("<< par->value <<") for " << value << "...\n";

        while(par->at(!ind)->at(!ind)) {
            par = par->at(!ind);
        }

        Branch* res = par->at(!ind)->retrieve(par);
        // cout << "( + _ + )7 Retreaved "<< (ind?"right":"left") <<" crit ("<< res->value <<") for " << par->value <<"!\n";
        return res;
    }


    void rotate() {
        if (size() < 3) return;
        // cout << " rotating " << value << "...\n";
        // print_info("ROTATE START");
        long double diff_left = double(left->size()) - double(right->size());

        while (2 <= diff_left) {
            Branch* m = retrieve();
            if (right) right->insert(m);
            else right = m;
            // print_info("ROTATE TO RIGHT");
            // cout << diff_left;
            diff_left -= 2;
            // cout << " --> " << diff_left << "\n";
        }
        while (diff_left <= -2) {
            Branch* m = retrieve();
            if (left) left->insert(m);
            else left = m;
            // print_info("ROTATE TO LEFT");
            // cout << diff_left;
            diff_left += 2;
            // cout << " --> " << diff_left << "\n";
        }
        right->rotate();
        left->rotate();
    }

    void print_layer_rec(const size_t current, const size_t target, Branch* head) {
        if (current == target)
            cout << "" << head->value << " ";
        else {
            if (head->left) print_layer_rec(current + 1, target, head->left);
            else print_layer_NULLs(target - current - 1);

            if (head->right) print_layer_rec(current + 1, target, head->right);
            else print_layer_NULLs(target - current - 1);
        }
    }

    void print_layer_NULLs(const size_t count) {
        size_t pupu=1;
        for (int i=0; i < count; ++i)
            pupu *= 2;

        for (size_t i=0; i < pupu; ++i) {
            cout << ". ";
        }
    }

    void print_list_rec(ostream& out) {
        if (left) left->print_list_rec(out);
        out << value << ", ";
        if (right) right->print_list_rec(out);
    }
};

class BinaryTree{
public:
    Branch* root=nullptr;

    BinaryTree() = default;
    explicit BinaryTree(double val) {
        root = new Branch{val};
    }
    explicit BinaryTree(vector<double>& els) {
        if (els.empty()) throw length_error{"to small"};
        root = new Branch{};
        root->value = els[0];
        for (size_t i=1; i < els.size(); ++i) {
            root->insert(els[i]);
        }
    }
    ~BinaryTree() {
        root->delete_tree();
    }
};

int main () {
    mt19937 rand{1000};
    vector<double> els = {};
    for (int i=0; i < 10; ++i) {
        els.push_back(double(rand() % 2000) - 1000);
    }

    BinaryTree t{els};
    Branch*& root = t.root;

    root->print_info();
    root->print_list(p_PROJECT "../ex/2 out.txt");

    return 0;
}
