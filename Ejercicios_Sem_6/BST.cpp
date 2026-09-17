#include <iostream>
using namespace std;

template<typename data_type>
struct BST {
    struct TreeNode {
        data_type data;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        TreeNode(data_type data= data_type(),
            TreeNode* left = nullptr,
            TreeNode* right = nullptr,
            TreeNode* parent = nullptr):
            data(data), left(left), right(right), parent(parent){}

    };
    TreeNode* root;
    BST() {
        root = nullptr;
    }
    bool search(data_type key) {
        TreeNode* current = root ;
        while (current != nullptr) {
            if (current->data == key) {
                return true;
            }
            if (current ->data >key) {
                current = current -> left;
            }
            else {
                current =current-> right;
            }
        }
        return false;
    }
    data_type min_element(TreeNode * u) {
        if (u== nullptr) {
            return data_type();
        }
        TreeNode* current= u;
        while (current -> left != nullptr) {
            current = current -> left;
        }
        return current->data;
    }

    data_type min_element() {
        return min_element(root);
    }
     data_type max_element() {
        return max_element(root);
    }


    data_type max_element(TreeNode * u) {
        if (u== nullptr) {
            return data_type();
        }
        TreeNode* current= u;
        while (current -> right != nullptr) {
            current = current -> right;
        }
        return current->data;
    }

    void insert(data_type value) {
        if (root==nullptr) {
            root = new TreeNode(value);
            return;
        }

        TreeNode* current =root;
        while (current!=nullptr) {
            if (current->data == value) return;
            if (current -> data <value) {
                if (current -> right!=nullptr) {
                    current = current -> right;
                }
                else {
                    current -> right = new TreeNode (value, nullptr, nullptr, current );
                    break;
                }
            }
            else {
                if (current -> left!=nullptr) {
                    current = current -> left;
                }
                else {
                    current -> left = new TreeNode (value, nullptr, nullptr, current );
                    break;
                }
            }
        }
    }
    void print_inorder() {

        print_subtree_inorder(root);
    }
    void print_subtree_inorder(TreeNode* u) {
        if (u==nullptr) return ;
        print_subtree_inorder(u -> left);
        cout << u->data << " ";
        print_subtree_inorder(u -> right);
    }


    data_type successor( TreeNode* x) {
        if (x-> right!= nullptr) {
            return min_element(x->right);

        }
        TreeNode * y = x -> parent;
        while (y!= nullptr and y -> right == x) {
            x= y ;
            y= y -> parent;
        }
        return  y ? y -> data : data_type();
    }
    data_type predecessor( TreeNode* x) {
        if (x-> left!= nullptr) {
            return max_element(x->left);

        }
        TreeNode * y = x -> parent;
        while (y!= nullptr and y -> left == x) {
            x= y ;
            y= y -> parent;
        }
        return  y ? y -> data : data_type();
    }
    void transplant(TreeNode* u, TreeNode* v) {
        if (u == nullptr) {
            root = v;
        }
        else if (u-> parent-> right == u) {
            u -> parent ->right= v;
        }


        else {
            u -> parent -> left = v;
        }
        if (v!= nullptr) {
            v-> parent  = u-> parent;
        }
        delete u;
    }


    void case_zero(TreeNode* u) {

    }
    void case_one(TreeNode* u) {
        if ( u-> left != nullptr ) {
        }
    }
    void case_two(TreeNode* u) {

    }
    void erase(TreeNode* u) {
        if (u-> left == nullptr and u-> right == nullptr) {
            transplant(u, u -> left);




        }
        else if (u-> left == nullptr and u-> right == nullptr) {
            
        }
    }

};





int main() {
    BST <int> B;
    B.insert(7);
    B.insert(4);

    B.insert(10);
    B.insert(9);
    B.insert(1);
    B.insert(3);

    cout<< B.min_element()<<" "<<endl;



    return 0;
}
