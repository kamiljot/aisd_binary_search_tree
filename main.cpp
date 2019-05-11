#include <iostream>
using namespace std;

struct Node{
    int key;
    Node *parent;
    Node *left;
    Node *right;
};

void AddNode(Node *&root, int k){    //   a
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

Node *MinKey(Node *root){
    if (root == nullptr || root->left == nullptr){
        return root;
    } else{
        return MinKey(root->left);
    }
}

Node *FindConsequentKey(Node *node){
    Node *current = node;
    Node *parent;

    if (current->right != nullptr){
        return MinKey(current->right);
    }
    parent = current->parent;
    while (parent != nullptr && current == parent->right){
        current = parent;
        parent = parent->parent;
    }
    return parent;
}


void DeleteNode(Node *&root, Node *node){   //   d
    Node *removable;
    Node *child;
    
    if (node->left == nullptr || node->right == nullptr){
        removable = node;
    }
    else{
        removable = FindConsequentKey(node);
    }
    if (removable->left != nullptr) {
        child = removable->left;
    }
    else{
        child = removable->right;
    }
    if (child != nullptr){
        child->parent = removable->parent;
    }
    if (removable->parent == nullptr){
        root = child;
    }
    else{
        if (removable == removable->parent->left){
            removable->parent->left = child;
        }
        else{
            removable->parent->right = child;
        }
    }
    if (removable != node){
        node->key = removable->key;
    }
    
    delete removable;
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

void DeleteTree(Node *&root){   //   r
    if (root != nullptr) {
        DeleteTree(root->left);
        DeleteTree(root->right);
        delete root;
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
void Default(){
    cout << "Press:" << endl;
    cout << "> 'a x' to add node with x value" << endl;
    cout << "> 'd x' to delete node with x value" << endl;
    cout << "> 'r' to remove the tree" << endl;
    cout << "> 'm' to find maximum value" << endl;
    cout << "> 'n' to find minimum value" << endl;
    cout << "> 'f x' to find consequent of x" << endl;
    cout << "> 'h' to print height of the tree" << endl;
    cout << "> 'i' to inorder print the tree" << endl;
    cout << "> 'p' to preorder print the tree" << endl;
    cout << "> 'o' to postorder print the tree" << endl;
}

int main() {
    int n, k;
    char p;
    Node *root = nullptr;

    Default();

    while(cin >> p){
        switch (p){
            case 'q':
                DeleteTree(root);
                return 0;
            case 'a':
                cin >> k;
                AddNode(root, k);
                break;
            case 'd':
                cin >> k;
                DeleteNode(root, FindKey(root, k));
                break;
            case 'r':
                DeleteTree(root);
                break;
            case 'm':
                cout << MaxKey(root)->key << endl;
                break;
            case 'n':
                cout << MinKey(root)->key << endl;
                break;
            case 'f':
                cin >> k;
                cout << FindConsequentKey(FindKey(root, k))->key << endl;
                break;
            case 'h':
                cout << TreeHeight(root) << endl;
                break;
            case 'i':
                InorderPrint(root);
                break;
            case 'p':
                PreorderPrint(root);
                break;
            case 'o':
                PostorderPrint(root);
                break;
            default:
                Default();
                break;
        }
    }
}
