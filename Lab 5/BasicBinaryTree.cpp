#include <iostream>
using namespace std;

// Binary Tree Node structure
struct BTNode {
    int data;
    BTNode* left;
    BTNode* right;

    BTNode(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Function to Print the Binary Tree in Preorder
void printPreorder(BTNode* node) {
    if (node == nullptr) return;
    cout << node->data << " ";
    printPreorder(node->left);
    printPreorder(node->right);
}

void printInorder(BTNode* node) {
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}

void printPostorder(BTNode* node) {
    if (node == nullptr) return;
    printPostorder(node->left);
    printPostorder(node->right);
    cout << node->data << " ";
}



int main() {
    // Create a simple binary tree
    BTNode* root = new BTNode(2);
    root->left = new BTNode(1);
    root->right = new BTNode(3);
    root->left->left = new BTNode(4);
    root->left->right = new BTNode(5);

    root->right->left = new BTNode(6);
    root->right->right = new BTNode(7);

    cout << "Preorder Traversal: ";
    printPreorder(root);

    cout << "\nInorder Traversal: ";
    printInorder(root);

    cout << "\nPostorder Traversal: ";
    printPostorder(root);

    return 0;
}