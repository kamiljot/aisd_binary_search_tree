#include <iostream>
using namespace std;

struct Node{
    int key;
    Node *parent;
    Node *left;
    Node *right;
};

void AddNode(Node *&root, int k){
    Node *parent;
    Node *node;

    node = new Node;

    node->left = nullptr;
    node->right = nullptr;
    node->key = k;

    parent = root;

    if (parent == nullptr){
        root = node;
    } else{
        while (true){
            if (k <= parent->key){
                if (parent->left == nullptr){
                    parent->left = node;
                    break;
                } else{
                    parent = parent->left;
                }
            } else{
                if (parent->right == nullptr){
                    parent->right = node;
                    break;
                } else {
                    parent = parent->right;
                }
            }
        }
    }
    node->parent = parent;
}

void InorderPrint(Node *root){
    if (root != nullptr){
        InorderPrint(root->left);
        cout << root->key << endl;
        InorderPrint(root->right);
    }
}

void PreorderPrint(Node *root){
    if (root != nullptr){
        cout << root->key << endl;
        PreorderPrint(root->left);
        PreorderPrint(root->right);
    }
}

void PostorderPrint(Node *root){
    if (root != nullptr){
        PostorderPrint(root->left);
        PostorderPrint(root->right);
        cout << root->key << endl;
    }
}

int Max(int a, int b){
    if (a > b){
        return a;
    } else{
        return b;
    }
}

int TreeHeight(Node *root){
    int hl, hr;
    if (root == nullptr){
        return 0;
    }
    hl = TreeHeight(root->left);
    hr = TreeHeight(root->right);
    return Max(hl, hr) + 1;
}

Node *FindKey(Node *root, int k){
    if (root == nullptr || root->key == k){
        return root;
    }
    if (k < root->key){
        return FindKey(root->left, k);
    } else{
        return FindKey(root->right, k);
    }
}

void DeleteTree(Node *node){
    if (node != nullptr) {
        DeleteTree(node->left);
        DeleteTree(node->right);
        delete node;
    }
}

Node *MinKey(Node *root){
    if (root == nullptr || root->left == nullptr){
        return root;
    } else{
        return MinKey(root->left);
    }
}

Node *MaxKey(Node *root){
    Node *current;
    if (root == nullptr){
        return nullptr;
    }
    current = root;
    while (current->right != nullptr){
        current = current->right;
    }
    return current;
}

Node *FindConsequentKey(Node *node, int k){
    Node *current = node;
    Node *parent;
    
    if (current->right != nullptr){
        return MinKey(current->right);
    }
    parent = current->parent;
    while (parent != nullptr && current == parent->right){
        current = parent;
        parent = parent->parent
    }
    return parent;
}

int main() {
    int n, k;
    cin >> n;
    Node *root = nullptr;

    for (int i = 0; i < n; i++){
        cin >> k;
        AddNode(root, k);
    }

    InorderPrint(root);
    PreorderPrint(root);
    PostorderPrint(root);

    cout << TreeHeight(root);
    cout << " " << MinKey(root)->key;
    DeleteTree(root);
    return 0;
}
