#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename data_type>
struct Treap {

    struct TreeNode {
        data_type data;
        unsigned prio;      // heap: padre > hijos
        int sz;
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type data) :
            data(data), prio(rng()), sz(1), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    Treap() { root = nullptr; }
    ~Treap() { clear(root); }
    Treap(const Treap&) = delete;
    Treap& operator=(const Treap&) = delete;

    void clear(TreeNode* u) {
        if (u == nullptr) return;
        clear(u -> left);
        clear(u -> right);
        delete u;
    }

    int sz(TreeNode* u) { return u == nullptr ? 0 : u -> sz; }
    void update(TreeNode* u) { u -> sz = 1 + sz(u -> left) + sz(u -> right); }

    // ---------- split: L < key, R >= key
    void split(TreeNode* u, data_type key, TreeNode*& L, TreeNode*& R) {
        if (u == nullptr) { L = R = nullptr; return; }
        if (u -> data < key) {
            split(u -> right, key, u -> right, R);
            L = u;
        } else {
            split(u -> left, key, L, u -> left);
            R = u;
        }
        update(u);
    }

    // ---------- merge: todo L <= todo R
    TreeNode* merge(TreeNode* L, TreeNode* R) {
        if (L == nullptr) return R;
        if (R == nullptr) return L;
        if (L -> prio > R -> prio) {
            L -> right = merge(L -> right, R);
            update(L);
            return L;
        }
        R -> left = merge(L, R -> left);
        update(R);
        return R;
    }

    // ---------- insert
    void insert(data_type value) {
        TreeNode *L, *R;
        split(root, value, L, R);
        root = merge(merge(L, new TreeNode(value)), R);
    }

    // ---------- erase (una copia)
    TreeNode* erase(TreeNode* u, data_type value, bool& ok) {
        if (u == nullptr) return nullptr;
        if (u -> data == value) {
            ok = true;
            TreeNode* t = merge(u -> left, u -> right);
            delete u;
            return t;
        }
        if (value < u -> data) u -> left = erase(u -> left, value, ok);
        else u -> right = erase(u -> right, value, ok);
        update(u);
        return u;
    }

    bool erase(data_type value) {
        bool ok = false;
        root = erase(root, value, ok);
        return ok;
    }

    // ---------- búsqueda
    bool search(data_type key) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current -> data == key) return true;
            current = (key < current -> data) ? current -> left : current -> right;
        }
        return false;
    }

    TreeNode* kth(int k) {                         // 1-indexado
        TreeNode* current = root;
        while (current != nullptr) {
            int L = sz(current -> left);
            if (k == L + 1) return current;
            if (k <= L) current = current -> left;
            else { k -= L + 1; current = current -> right; }
        }
        return nullptr;
    }

    int count_less(data_type x) {                  // cuántos < x
        int r = 0;
        TreeNode* current = root;
        while (current != nullptr) {
            if (current -> data < x) { r += sz(current -> left) + 1; current = current -> right; }
            else current = current -> left;
        }
        return r;
    }

    int size() { return sz(root); }

    int height(TreeNode* u) {
        if (u == nullptr) return -1;
        return 1 + max(height(u -> left), height(u -> right));
    }

    void print_inorder() { print_subtree_inorder(root); cout << '\n'; }
    void print_subtree_inorder(TreeNode* u) {
        if (u == nullptr) return;
        print_subtree_inorder(u -> left);
        cout << u -> data << " ";
        print_subtree_inorder(u -> right);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    Treap<int> T;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        T.insert(x);
    }
    T.print_inorder();
    cout << T.size() << " " << T.height(T.root) << '\n';
    return 0;
}