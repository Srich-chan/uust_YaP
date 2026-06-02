#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <stack>

using std::vector, std::cout, std::stack, std::queue;

class Branch {
    public:
    vector<Branch*> kids;
    double val = 67;
    Branch(double puk=67) {
        val = puk;
    }

    Branch& operator[](size_t ind) {
        return *kids[ind];
    }
    Branch*& at(size_t ind) {
        return kids[ind];
    }
    void kill_all() {
        for (auto kid : kids) {
            delete kid;
        }
    }

    void add_kid(double value=67) {
        add_kid(new Branch(value));
    }
    void add_kid(Branch* kid) {
        kids.push_back(kid);
    }

    [[nodiscard]] size_t max_depth() const {
        if (is_leaf()) return 1;

        std::queue<const Branch*> q;
        q.push(this);

        size_t depth = 0;
        while (!q.empty()) {
            ++depth;
            size_t level = q.size();

            for (size_t i = 0; i < level; ++i) {
                const Branch* curr = q.front();
                q.pop();
                for (const Branch* kid : curr->kids) {
                    q.push(kid);
                }
            }
        }
        return depth;
    }

    [[nodiscard]] size_t tree_size() const {
        if (is_leaf()) return 1;
        size_t c=1;
        stack<const Branch*> ds;
        ds.push(this);
        while (!ds.empty()) {
            const Branch* curr = ds.top(); ds.pop();
            for (Branch* kid : curr->kids) {
                ds.push(kid);
                ++c;
            }
        }
        return c;
    }

    [[nodiscard]] size_t count_leaves() const {
        if (is_leaf()) return 1;
        size_t c = 0;
        stack<const Branch*> ds;
        ds.push(this);
        while (!ds.empty()) {
            const Branch* curr = ds.top();
            ds.pop();

            for (Branch* kid : curr->kids) {
                if (kid->is_leaf()) ++c;
                else {
                    ds.push(kid);
                }
            }
        }
        return c;
    }

    [[nodiscard]] bool is_leaf() const {
        return kids.empty();
    }

    void print_layer(size_t ind) const {
        cout << "Layer " << ind << ": ";

        if (ind == 0) {
            cout  << "root=" << val<< '\n';
            return;
        }
        if (ind >= max_depth()) {
            cout << "is Empty\n"; return;
        }
        if (ind == 1) {
            cout << "[" << kids[0]->val;
            for (size_t i=1; i < kids.size(); ++i) {
                cout << ", " << kids[i]->val;
            }
            cout << "]\n";
            return;
        }
        size_t curr_depth=1;
        queue<const Branch*> q;
        q.push(this);
        while (!q.empty() && curr_depth < ind) {
            ++curr_depth;
            size_t layer = q.size();
            for (size_t _i=0; _i < layer; ++_i) {
                const Branch* curr = q.front();
                q.pop();

                for (Branch* kid : curr->kids) {
                    if (kid) q.push(kid);
                }
            }
        }
        size_t layer=q.size();
        for (size_t _i=0; _i < layer; ++_i) {
            const Branch* curr = q.front();
            q.pop();
            cout << "[";
            if (!curr->kids.empty()) cout << curr->kids[0]->val;
            for (size_t i=1; i < curr->kids.size(); ++i) {
                cout << ", " << curr->kids[i]->val;
            }
            cout << "] ";
        }
        cout << "\n";
    }
    void print_info(const char* name=nullptr) {
        cout << "\n";
        if (name) cout << name << "\n";
        cout << "Size: " << tree_size() << "\n"
        << "Leaves: " << count_leaves() << "\n";
        for (size_t i =0; i <= max_depth(); ++i) {
            print_layer(i);
        }
    }

};

class Tree : public Branch{
public:

    ~Tree() {
        kill_all();
    }
};

int main() {

    Tree root;
    root.add_kid(123);
    root[0].add_kid(2);
    root[0].add_kid(12341);
    // root[0][0].add_kid(3);

    root.add_kid(0.);
    root[1].add_kid(123);
    root[1][0].add_kid(4);
    root[1][0][0].add_kid(5);
    root[1][0][0][0].add_kid(6);
    root.add_kid(123);

    cout << "Size: " << root.tree_size() << "\n";

    Tree* ptr = &root;
    cout << "Leaves: " << ptr->count_leaves() << "\n";

    ptr->print_info("Krutoe Derevo");
}