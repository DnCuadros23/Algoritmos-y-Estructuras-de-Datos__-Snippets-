#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<typename data_type>
struct AVL {

    struct TreeNode {
        int height;
        data_type data;
        TreeNode* left;
        TreeNode* right;

        TreeNode(data_type data = data_type(), int height = 0,
                    TreeNode* left = nullptr,
                    TreeNode* right = nullptr) :
                    data(data), height(height), left(left), right(right) {}
    };

    TreeNode* root;

    AVL() {
        root = nullptr;
    }

    void update(TreeNode* u) {
        u -> height = 1 + max(h(u -> left) , h(u -> right));
    }

    int h(TreeNode* u) {
        return u == nullptr ? -1 : u -> height;
    }

    int FB(TreeNode* u) {
        return h(u -> left) - h(u -> right);
    }

    bool search(data_type key) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (current->data == key) {
                return true;
            }
            if (current -> data > key) {
                current = current -> left;
            }
            else {
                current = current -> right;
            }
        }
        return false;
    }

    TreeNode* min_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current -> left != nullptr) {
            current = current -> left;
        }
        return current;
    }

    TreeNode* max_element(TreeNode* u) {
        if (u == nullptr) return nullptr;
        TreeNode* current = u;
        while (current -> right != nullptr) {
            current = current -> right;
        }
        return current;
    }

    TreeNode* min_element() {
        return min_element(root);
    }

    TreeNode* max_element() {
        return max_element(root);
    }

    TreeNode* rotate_left(TreeNode* u) {
        TreeNode* v = u -> right;
        u -> right = v -> left;
        v -> left = u;
        update(u);
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
        if (FB(u) > 1) {
            // L
            if (FB(u -> left) < 0) {
                // LR
                u -> left = rotate_left(u -> left);
            }
            return rotate_right(u);
        }
        if (FB(u) < -1) {
            // R
            if (FB(u -> right) > 0) {
                // RL
                u -> right = rotate_right(u -> right);
            }
            return rotate_left(u);
        }
        return u;
    }

    TreeNode* insert(TreeNode* u, data_type value) {
        if (u == nullptr) {
            return new TreeNode(value, 0);
        }
        if (value < u -> data) {
            u -> left = insert(u -> left, value);
        }
        else {
            u -> right = insert(u -> right, value);
        }
        return rebalance(u);
    }

    void insert(data_type value) {
        root = insert(root, value);
    }

    void print_inorder() {
        print_subtree_inorder(root);
        cout << endl;
    }

    void print_subtree_inorder(TreeNode* u) {
        if (u == nullptr) return;
        print_subtree_inorder(u -> left);
        cout << u -> data << " ";
        print_subtree_inorder(u -> right);
    }

    void print_preorder() {
        print_subtree_preorder(root);
        cout << endl;
    }

    void print_subtree_preorder(TreeNode* u) {
        if (u == nullptr) return;
        cout << u -> data << " ";
        print_subtree_preorder(u -> left);
        print_subtree_preorder(u -> right);
    }

    void print_postorder() {
        print_subtree_postorder(root);
        cout << endl;
    }

    void print_subtree_postorder(TreeNode* u) {
        if (u == nullptr) return;
        print_subtree_postorder(u -> left);
        print_subtree_postorder(u -> right);
        cout << u -> data << " ";
    }

    TreeNode* successor(TreeNode* x) {
        if (x -> right != nullptr) {
            return min_element(x -> right);
        }
        TreeNode* y = x -> parent;
        while (y != nullptr and y -> right == x) {
            x = y;
            y = y -> parent;
        }
        return y;
    }

    TreeNode* predecessor(TreeNode* x) {
        if (x -> left != nullptr) {
            return max_element(x -> left);
        }
        TreeNode* y = x -> parent;
        while (y != nullptr and y -> left == x) {
            x = y;
            y = y -> parent;
        }
        return y;
    }

    TreeNode* transplant(TreeNode* u, TreeNode* v) {
        if (u -> parent == nullptr) {
            root = v;
        }
        else if (u -> parent -> right == u) {
            u -> parent -> right = v;
        }
        else {
            u -> parent -> left = v;
        }
        if (v != nullptr) {
            v -> parent = u -> parent;
        }
        delete u;
    }

    TreeNode* erase(TreeNode* u, const data_type& value) {
        if (u == nullptr) return nullptr;

        if (value < u -> data) {
            u -> left = erase(u -> left, value);
        }
        else if (u -> data < value) {
            u -> right = erase(u -> right, value);
        }
        else {
            if (u -> left == nullptr or u -> right == nullptr) {
                TreeNode* child = (u -> left != nullptr) ? u -> left : u -> right;
                delete u;
                return child;
            }
            TreeNode* succ = min_element(u -> right);
            u -> data = succ -> data;
            u -> right = erase(u -> right, succ -> data);
        }
        return rebalance(u);
    }

    void erase(data_type value) {
        root = erase(root, value);
    }
};

template<typename data_type>
struct DoublyLinkedNode {
    data_type data;
    DoublyLinkedNode* next;
    DoublyLinkedNode* prev;

    DoublyLinkedNode() {
        next = prev = nullptr;
    }

    DoublyLinkedNode(data_type data, DoublyLinkedNode<data_type>* next = nullptr, DoublyLinkedNode<data_type>* prev = nullptr) : data(data), next(next), prev(prev) {}

};

template<typename data_type>
struct DoublyLinkedList {
    DoublyLinkedNode<data_type>* head;
    DoublyLinkedNode<data_type>* tail;

    DoublyLinkedList() {
        head = tail = nullptr;
    };

    void push_front(data_type value) {
        DoublyLinkedNode<data_type>* new_node = new DoublyLinkedNode<data_type>(value, head);
        if (head == nullptr) {
            tail = new_node;
        }
        else {
            head -> prev = new_node;
        }
        head = new_node;
    }

    void erase(DoublyLinkedNode<data_type>* node) {
        // Eliminamos un nodo "node" no nulo
        if (node == head) {
            pop_front();
        }
        else if (node == tail) {
            pop_back();
        }
        else {
            DoublyLinkedNode<data_type>* predecessor = node -> prev;
            DoublyLinkedNode<data_type>* successor = node -> next;
            predecessor -> next = successor;
            successor -> prev = predecessor;
            delete node;
        }
    }

    void delete_first(data_type key) {
        DoublyLinkedNode<data_type>* current = head;
        while (current != nullptr) {
            if (current -> data == key) {
                erase(current);
                break;
            }
            current = current -> next;
        }
    }

    void pop_front() {
        DoublyLinkedNode<data_type>* node = head;
        if (head == tail) {
            delete node;
            head = tail = nullptr;
        }
        else {
            head = head -> next;
            head -> prev = nullptr;
            delete node;
        }
    }

    void pop_back() {
        DoublyLinkedNode<data_type>* node = tail;
        if (head == tail) {
            delete node;
            head = tail = nullptr;
        }
        else {
            tail = tail -> prev;
            tail -> next = nullptr;
            delete node;
        }
    }

    void print() {
        DoublyLinkedNode<data_type>* current = head;
        while (current != nullptr) {
            cout << current -> data << " ";
            current = current -> next;
        }
        cout << '\n';
    }
    // no estaba en la estructura de la clase se añadio
    void push_back(data_type value) {
        DoublyLinkedNode<data_type>* new_node=new DoublyLinkedNode<data_type>(value, nullptr, tail);
        if (tail ==nullptr){
            head=new_node;
        }
        else {
            tail->next=new_node;
        }
        tail=new_node;
    }


};

//Par guarda suma y la posicion del bloque izquierdo
struct Par {
    long long suma;
    int pos;
    bool operator<(const Par&otro)const {
        if (suma!=otro.suma) {
            return suma<otro.suma;

        }
        return pos<otro.pos;
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(false);
    //utilizando la lista doblemente enlazada de la clase
    // se utilizo tmb el AVL de clase
    long n,k;
    cin>>n>>k;
    vector<long long> peso(n);
    for (int i=0; i<n;i++) {
        cin>>peso[i];
    }

    //lista que guarda las posiciones
    DoublyLinkedList<int> lista;
    vector<DoublyLinkedNode<int>*>nodos(n);
    for (int i = 0; i<n; i++) {
        lista.push_back(i);
        nodos[i]=lista.tail;
    }
    //guarda todos ordenados por suma
    AVL<Par> todos_los_pares;
    for (int i=0; i+1<n; i++) {
        Par nuevo ;
        nuevo.suma=peso[i]+peso[i+1];
        nuevo.pos=i;
        todos_los_pares.insert(nuevo);

    }
    long actuales=n;
    while (actuales>k) {
        //el par con menor suma
        Par menorsuma=todos_los_pares.min_element()->data;
        todos_los_pares.erase(menorsuma);
        int izquierdo=menorsuma.pos;
        int derecho=nodos[izquierdo]->next->data;

        if (nodos[izquierdo]->prev!=nullptr) {
            int antes=nodos[izquierdo]->prev->data;
            Par antiguo;
            antiguo.suma=peso[antes]+peso[izquierdo];
            antiguo.pos=antes;
            todos_los_pares.erase(antiguo);
        }
        if (nodos[derecho]->next!=nullptr) {
            int despues=nodos[derecho]->next->data;
            Par antiguo;
            antiguo.suma=peso[derecho]+peso[despues];
            antiguo.pos=derecho;
            todos_los_pares.erase(antiguo);
        }
        //juntamos
        peso[izquierdo]=peso[izquierdo]+peso[derecho];
        lista.erase(nodos[derecho]);
        if (nodos[izquierdo]->prev!=nullptr) {
            int antes =nodos[izquierdo]->prev->data;
            Par nuevo;
            nuevo.suma=peso[antes]+peso[izquierdo];
            nuevo.pos=antes;
            todos_los_pares .insert(nuevo);

        }
        if (nodos[izquierdo]->next!=nullptr) {
            int despues=nodos[izquierdo]->next->data;
            Par nuevo;
            nuevo.suma=peso[izquierdo]+peso[despues];
            nuevo.pos=izquierdo;
            todos_los_pares .insert(nuevo);
        }
        actuales--;
    }
    DoublyLinkedNode<int>* actual=lista.head;
    while (actual!=nullptr) {
        cout<<peso[actual->data]<<" ";
        actual=actual->next;
    }
    cout<<"\n";



    return 0;
}