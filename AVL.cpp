#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename data_type>
struct AVL {

    struct TreeNode {
        data_type data;
        int height //altura
        , sz; //cuantos nodos hay en un subarbol, contandose a si mismo
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type data) :
            data(data), height(0), sz(1), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    AVL() { root = nullptr; }
    ~AVL() { clear(root); }
    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

    void clear(TreeNode* u) {
        if (u == nullptr) return;
        clear(u -> left);
        clear(u -> right);
        delete u;
    }

    // ---------- helpers
    int h(TreeNode* u) {
        return u == nullptr ? -1 : u -> height;
    }
    int sz(TreeNode* u) {
        return u == nullptr ? 0 : u -> sz;
    }
    int FB(TreeNode* u) {
        return h(u -> left) - h(u -> right);
    }

    void update(TreeNode* u) {
        u -> height = 1 + max(h(u -> left), h(u -> right));
        u -> sz = 1 + sz(u -> left) + sz(u -> right);
    }

    // ---------- rotaciones
    TreeNode* rotate_left(TreeNode* u) {
        TreeNode* v = u -> right;
        u -> right = v -> left;
        v -> left = u;
        update(u);      // u primero (queda abajo)
        update(v);
        return v;
    }

    TreeNode* rotate_right(TreeNode* u) {
        TreeNode* v = u -> left;
        u -> left = v -> right;
        v -> right = u;
        update(u);
        update(v);
        return v;
    }

    TreeNode* rebalance(TreeNode* u) {
        update(u);
        if (FB(u) > 1) {                            // L
            if (FB(u -> left) < 0)                  // LR
                u -> left = rotate_left(u -> left);
            return rotate_right(u);
        }
        if (FB(u) < -1) {                           // R
            if (FB(u -> right) > 0)                 // RL
                u -> right = rotate_right(u -> right);
            return rotate_left(u);
        }
        return u;
    }

    // ---------- insert
    TreeNode* insert(TreeNode* u, data_type value) {
        if (u == nullptr) return new TreeNode(value);
        if (value < u -> data) u -> left = insert(u -> left, value);
        else u -> right = insert(u -> right, value);
        return rebalance(u);
    }

    void insert(data_type value) { root = insert(root, value); }

    // ---------- erase
    TreeNode* erase(TreeNode* u, data_type value) {
        if (u == nullptr) return nullptr;           // no existe
        if (value < u -> data) u -> left = erase(u -> left, value);
        else if (u -> data < value) u -> right = erase(u -> right, value);
        else {
            if (u -> left == nullptr || u -> right == nullptr) {   // 0 o 1 hijo
                TreeNode* child = (u -> left != nullptr) ? u -> left : u -> right;
                delete u;
                return child;
            }
            TreeNode* m = min_element(u -> right);  // 2 hijos: sucesor
            u -> data = m -> data;
            u -> right = erase(u -> right, m -> data);
        }
        return rebalance(u);
    }

    void erase(data_type value) {
        root = erase(root, value);
    }

    // ---------- búsqueda
    bool search(data_type key) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current -> data == key) return true;
            if (key < current -> data) current = current -> left;
            else current = current -> right;
        }
        return false;
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        while (u -> left != nullptr) u = u -> left;
        return u;
    }

    TreeNode* max_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        while (u -> right != nullptr) u = u -> right;
        return u;
    }

    TreeNode* min_element() { return min_element(root); }
    TreeNode* max_element() { return max_element(root); }

    TreeNode* successor(data_type x) {             // menor > x
        TreeNode* current = root;
        TreeNode* ans = nullptr;
        while (current != nullptr) {
            if (x < current -> data) { ans = current; current = current -> left; }
            else current = current -> right;
        }
        return ans;
    }

    TreeNode* predecessor(data_type x) {           // mayor < x
        TreeNode* current = root;
        TreeNode* ans = nullptr;
        while (current != nullptr) {
            if (current -> data < x) { ans = current; current = current -> right; }
            else current = current -> left;
        }
        return ans;
    }

    // ---------- TDA con tamaño
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

    // ---------- recorridos
    void print_inorder() { print_subtree_inorder(root); cout << '\n'; }
    void print_subtree_inorder(TreeNode* u) {
        if (u == nullptr) return;
        print_subtree_inorder(u -> left);
        cout << u -> data << " ";
        print_subtree_inorder(u -> right);
    }

    void print_preorder() { print_subtree_preorder(root); cout << '\n'; }
    void print_subtree_preorder(TreeNode* u) {
        if (u == nullptr) return;
        cout << u -> data << " ";
        print_subtree_preorder(u -> left);
        print_subtree_preorder(u -> right);
    }

    void print_postorder() { print_subtree_postorder(root); cout << '\n'; }
    void print_subtree_postorder(TreeNode* u) {
        if (u == nullptr) return;
        print_subtree_postorder(u -> left);
        print_subtree_postorder(u -> right);
        cout << u -> data << " ";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //https://github.com/DnCuadros23/Algoritmos-y-Estructuras-de-Datos__-Snippets-.git
    int n;
    cin >> n;
    AVL<int> T;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        T.insert(x);
        cout << T.h(T.root) << " " << T.root -> data << '\n';
    }
    return 0;
}