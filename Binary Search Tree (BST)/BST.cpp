#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* newNode(int key) {
    Node* temp = new Node();
    temp->key = key;
    temp->left = nullptr;
    temp->right = nullptr;
    return temp;
}

void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->key << " -> ";
        inorder(root->right);
    }
}

Node* insert(Node* root, int key) {

    if (root == nullptr)
        return newNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

Node* minValueNode(Node* root) {

    Node* current = root;

    while (current && current->left != nullptr)
        current = current->left;

    return current;
}

Node* deleteNode(Node* root, int key) {

    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {

        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }

        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = minValueNode(root->right);

        root->key = temp->key;

        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

int main() {

    Node* root = nullptr;

    root = insert(root, 8);
    root = insert(root, 3);
    root = insert(root, 1);
    root = insert(root, 6);
    root = insert(root, 7);
    root = insert(root, 10);
    root = insert(root, 14);
    root = insert(root, 4);

    cout << "Inorder traversal: ";
    inorder(root);

    cout << "\nAfter deleting 10\n";

    root = deleteNode(root, 10);

    cout << "Inorder traversal: ";
    inorder(root);
}
