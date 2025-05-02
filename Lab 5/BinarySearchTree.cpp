#include <iostream>
using namespace std;

// Implementation of BST with All Features

// Binary Search Tree Node structure
class BSTNode {
public:
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Binary Search Tree class
class BST {
private:
    BSTNode * root;

    // Recursive Insert
    BSTNode * insert(BSTNode* node, int val) {
        if (node == nullptr) {
            return new BSTNode(val);
        }
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        }
        return node;
    }

    // Traversal functions
    void printPreorder(BSTNode* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }
    void printInorder(BSTNode* node) {
        if (node == nullptr) return;
        printInorder(node->left);
        cout << node->data << " ";
        printInorder(node->right);
    }
    void printPostorder(BSTNode* node) {
        if (node == nullptr) return;
        printPostorder(node->left);
        printPostorder(node->right);
        cout << node->data << " ";
    }
    // Search function
    bool search(BSTNode * node, int key) {
        if (node == nullptr) return false;
        if (node->data == key) return true;
        if (key < node->data) return search(node->left, key);
        return search(node->right, key);
    }
    // Function to find Minimum
    BSTNode* findMin(BSTNode * node) {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) return node = node->left;
        return node;
    }
    // Function to find Maximum
    BSTNode* findMax(BSTNode * node) {
        if (node == nullptr) return nullptr;
        while (node->right != nullptr) return node = node->right;
        return node;
    }
    // Function to delete a node
    BSTNode* deleteNode(BSTNode* node, int key) {
        if (node == nullptr) return nullptr;
        if (key < node->data) node->left = deleteNode(node->left, key);
        else if (key > node->data) node->right = deleteNode(node->right, key);
        else {
            // node found
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            else {
                BSTNode* successor = findMin(node->right);
                node->data = successor->data;
                node->right = deleteNode(node->right, successor->data);
            }
        }
        return node;
    }
    // Function to find Height of tree
    int height(BSTNode* node) {
        if (node == nullptr) return -1;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    // Function to find Depth of a Node
    int depth(BSTNode* node, int key, int level) {
        if (node == nullptr) return -1;
        if (node->data == key) return level;
        if (key < node->data) return depth(node->left, key, level + 1);
        else return depth(node->right, key, level + 1);
    }
    // Function to Check if tree is a BST
    bool isBST(BSTNode* node, int minVal, int maxVal) {
        if (node == nullptr) return true;
        if (node->data < minVal || node->data > maxVal) return false;
        return isBST(node->left, minVal, node->data) && isBST(node->right, node->data, maxVal);
    }

    // Function for BST to sorted array using manual array
    void bstToArray(BSTNode* node, int arr[], int &index) {
        if (node != nullptr) {
            bstToArray(node->left, arr, index);
            arr[index++] = node->data;
            bstToArray(node->right, arr, index);
        }
    }

public:
    BST() {
        root = nullptr;
    }
    void insert(int val) {
        root = insert(root, val);
    }
    void displayTraversals() {
        cout << "Inorder Traversal: ";
        printInorder(root);
        cout << "\nPreorder Traversal: ";
        printPreorder(root);
        cout << "\nPostorder Traversal: ";
        printPostorder(root);
    }
    void searchKey(int key) {
        cout << "Searching for " << key << "...\nPath: ";
        bool found = search(root, key);
        if (found) {
            cout << "Key " << key << " found in the BST.\n";
        } else {
            cout << "Key " << key << " not found in the BST.\n";
        }
    }
    void findMinMax() {
        BSTNode* minNode = findMin(root);
        BSTNode* maxNode = findMax(root);
        if (minNode) cout << "Minimum value: " << minNode->data << "\n";
        if (maxNode) cout << "Maximum value: " << maxNode->data << "\n";
    }
    void deleteKey(int key) {
        root = deleteNode(root, key);
        cout << "Deleted node " << key << " from the BST.\n";
    }
    void getHeightAndDepth(int key) {
        cout << "Height of the BST: " << height(root) << "\n";
        int d = depth(root, key, 0);
        if (d != -1) {
            cout << "Depth of node " << key << ": " << d << "\n";
        } else {
            cout << "Node " << key << " not found in the BST.\n";
        }
    }
    void checkIsBST() {
        if (isBST(root, -100000, 100000)) {
            cout << "The tree is a valid BST.\n";
        } else {
            cout << "The tree is not a valid BST.\n";
        }
    }
    void convertToSortedArray() {
        int arr[100]; // Assuming a maximum of 100 nodes
        int index = 0;
        bstToArray(root, arr, index);
        cout << "Sorted array: ";
        for (int i = 0; i < index; i++) {
            cout << arr[i] << " ";
        cout << "\n";
        }
    }
};

int main() {
    BST tree;
    int choice, value;
    do {
        cout << "\nBinary Search Tree Menu:\n";
        cout << "1. Insert\n";
        cout << "2. Display Traversals\n";
        cout << "3. Search\n";
        cout << "4. Find Min/Max\n";
        cout << "5. Delete Node\n";
        cout << "6. Height and Depth\n";
        cout << "7. Check if BST\n";
        cout << "8. Convert to Sorted Array\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;
            case 2:
                tree.displayTraversals();
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                tree.searchKey(value);
                break;
            case 4:
                tree.findMinMax();
                break;
            case 5:
                cout << "Enter value to delete: ";
                cin >> value;
                tree.deleteKey(value);
                break;
            case 6:
                cout << "Enter node value to find depth: ";
                cin >> value;
                tree.getHeightAndDepth(value);
                break;
            case 7:
                tree.checkIsBST();
                break;
            case 8:
                tree.convertToSortedArray();
                break;
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}