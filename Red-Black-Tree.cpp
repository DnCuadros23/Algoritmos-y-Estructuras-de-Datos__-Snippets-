#include <iostream>
#include <vector>
using namespace std;

template<typename data_type>
struct RBT {

    enum Color { RED, BLACK };

    struct TreeNode {
        data_type data;
        Color color;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
    };

    TreeNode* NIL;      // centinela negro
    TreeNode* root;

    RBT() {
        NIL = new TreeNode{data_type(), BLACK, nullptr, nullptr, nullptr};
        NIL -> left = NIL -> right = NIL -> parent = NIL;
        root = NIL;
    }
    ~RBT() { clear(root); delete NIL; }
    RBT(const RBT&) = delete;
    RBT& operator=(const RBT&) = delete;

    void clear(TreeNode* u) {
        if (u == NIL) return;
        clear(u -> left);
        clear(u -> right);
        delete u;
    }

    // ---------- rotaciones
    void rotate_left(TreeNode* x) {
        TreeNode* y = x -> right;
        x -> right = y -> left;
        if (y -> left != NIL) y -> left -> parent = x;
        y -> parent = x -> parent;
        if (x -> parent == NIL) root = y;
        else if (x == x -> parent -> left) x -> parent -> left = y;
        else x -> parent -> right = y;
        y -> left = x;
        x -> parent = y;
    }

    void rotate_right(TreeNode* x) {
        TreeNode* y = x -> left;
        x -> left = y -> right;
        if (y -> right != NIL) y -> right -> parent = x;
        y -> parent = x -> parent;
        if (x -> parent == NIL) root = y;
        else if (x == x -> parent -> right) x -> parent -> right = y;
        else x -> parent -> left = y;
        y -> right = x;
        x -> parent = y;
    }

    // ---------- insert
    void insert(data_type value) {
        TreeNode* z = new TreeNode{value, RED, NIL, NIL, NIL};
        TreeNode* y = NIL;
        TreeNode* x = root;
        while (x != NIL) {                          // BST normal
            y = x;
            x = (value < x -> data) ? x -> left : x -> right;
        }
        z -> parent = y;
        if (y == NIL) root = z;
        else if (value < y -> data) y -> left = z;
        else y -> right = z;
        insert_fixup(z);
    }

    void insert_fixup(TreeNode* z) {
        while (z -> parent -> color == RED) {
            TreeNode* g = z -> parent -> parent;
            if (z -> parent == g -> left) {
                TreeNode* uncle = g -> right;
                if (uncle -> color == RED) {                 // tío rojo: recolorear, subir
                    z -> parent -> color = BLACK;
                    uncle -> color = BLACK;
                    g -> color = RED;
                    z = g;
                } else {
                    if (z == z -> parent -> right) {         // triángulo
                        z = z -> parent;
                        rotate_left(z);
                    }
                    z -> parent -> color = BLACK;            // línea
                    g -> color = RED;
                    rotate_right(g);
                }
            } else {
                TreeNode* uncle = g -> left;
                if (uncle -> color == RED) {
                    z -> parent -> color = BLACK;
                    uncle -> color = BLACK;
                    g -> color = RED;
                    z = g;
                } else {
                    if (z == z -> parent -> left) {
                        z = z -> parent;
                        rotate_right(z);
                    }
                    z -> parent -> color = BLACK;
                    g -> color = RED;
                    rotate_left(g);
                }
            }
        }
        root -> color = BLACK;
    }

    // ---------- erase
    void transplant(TreeNode* u, TreeNode* v) {
        if (u -> parent == NIL) root = v;
        else if (u == u -> parent -> left) u -> parent -> left = v;
        else u -> parent -> right = v;
        v -> parent = u -> parent;
    }

    bool erase(data_type key) {
        TreeNode* z = find(key);
        if (z == NIL) return false;
        TreeNode* y = z;
        Color y_color = y -> color;
        TreeNode* x;
        if (z -> left == NIL) {                     // 0 o 1 hijo
            x = z -> right;
            transplant(z, z -> right);
        } else if (z -> right == NIL) {
            x = z -> left;
            transplant(z, z -> left);
        } else {                                    // 2 hijos: sucesor
            y = min_element(z -> right);
            y_color = y -> color;
            x = y -> right;
            if (y -> parent == z) x -> parent = y;
            else {
                transplant(y, y -> right);
                y -> right = z -> right;
                y -> right -> parent = y;
            }
            transplant(z, y);
            y -> left = z -> left;
            y -> left -> parent = y;
            y -> color = z -> color;
        }
        delete z;
        if (y_color == BLACK) erase_fixup(x);       // falta un negro
        return true;
    }

    void erase_fixup(TreeNode* x) {
        while (x != root && x -> color == BLACK) {
            if (x == x -> parent -> left) {
                TreeNode* w = x -> parent -> right;          // hermano
                if (w -> color == RED) {                     // caso 1
                    w -> color = BLACK;
                    x -> parent -> color = RED;
                    rotate_left(x -> parent);
                    w = x -> parent -> right;
                }
                if (w -> left -> color == BLACK && w -> right -> color == BLACK) {   // caso 2
                    w -> color = RED;
                    x = x -> parent;
                } else {
                    if (w -> right -> color == BLACK) {      // caso 3
                        w -> left -> color = BLACK;
                        w -> color = RED;
                        rotate_right(w);
                        w = x -> parent -> right;
                    }
                    w -> color = x -> parent -> color;       // caso 4
                    x -> parent -> color = BLACK;
                    w -> right -> color = BLACK;
                    rotate_left(x -> parent);
                    x = root;
                }
            } else {
                TreeNode* w = x -> parent -> left;
                if (w -> color == RED) {
                    w -> color = BLACK;
                    x -> parent -> color = RED;
                    rotate_right(x -> parent);
                    w = x -> parent -> left;
                }
                if (w -> right -> color == BLACK && w -> left -> color == BLACK) {
                    w -> color = RED;
                    x = x -> parent;
                } else {
                    if (w -> left -> color == BLACK) {
                        w -> right -> color = BLACK;
                        w -> color = RED;
                        rotate_left(w);
                        w = x -> parent -> left;
                    }
                    w -> color = x -> parent -> color;
                    x -> parent -> color = BLACK;
                    w -> left -> color = BLACK;
                    rotate_right(x -> parent);
                    x = root;
                }
            }
        }
        x -> color = BLACK;
    }

    // ---------- búsqueda
    TreeNode* find(data_type key) {
        TreeNode* current = root;
        while (current != NIL && !(current -> data == key))
            current = (key < current -> data) ? current -> left : current -> right;
        return current;                              // NIL si no está
    }

    bool search(data_type key) { return find(key) != NIL; }

    TreeNode* min_element(TreeNode* u) {
        while (u -> left != NIL) u = u -> left;
        return u;
    }

    TreeNode* max_element(TreeNode* u) {
        while (u -> right != NIL) u = u -> right;
        return u;
    }

    TreeNode* successor(TreeNode* x) {               // con parent
        if (x -> right != NIL) return min_element(x -> right);
        TreeNode* y = x -> parent;
        while (y != NIL && x == y -> right) { x = y; y = y -> parent; }
        return y;
    }

    TreeNode* predecessor(TreeNode* x) {
        if (x -> left != NIL) return max_element(x -> left);
        TreeNode* y = x -> parent;
        while (y != NIL && x == y -> left) { x = y; y = y -> parent; }
        return y;
    }

    // ---------- verificar reglas (debug)
    int black_height(TreeNode* u) {                  // -1 = inválido
        if (u == NIL) return 0;
        if (u -> color == RED &&
            (u -> left -> color == RED || u -> right -> color == RED)) return -1;
        int a = black_height(u -> left);
        int b = black_height(u -> right);
        if (a == -1 || b == -1 || a != b) return -1;
        return a + (u -> color == BLACK ? 1 : 0);
    }

    bool valid() { return root -> color == BLACK && black_height(root) != -1; }

    int height(TreeNode* u) {
        if (u == NIL) return -1;
        return 1 + max(height(u -> left), height(u -> right));
    }

    // ---------- recorridos
    void print_inorder() { print_subtree_inorder(root); cout << '\n'; }
    void print_subtree_inorder(TreeNode* u) {
        if (u == NIL) return;
        print_subtree_inorder(u -> left);
        cout << u -> data << (u -> color == RED ? "R " : "N ");
        print_subtree_inorder(u -> right);
    }

    void print_preorder() { print_subtree_preorder(root); cout << '\n'; }
    void print_subtree_preorder(TreeNode* u) {
        if (u == NIL) return;
        cout << u -> data << (u -> color == RED ? "R " : "N ");
        print_subtree_preorder(u -> left);
        print_subtree_preorder(u -> right);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    RBT<int> T;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        T.insert(x);
    }
    T.print_preorder();
    cout << T.height(T.root) << " " << T.black_height(T.root) << '\n';
    return 0;
}