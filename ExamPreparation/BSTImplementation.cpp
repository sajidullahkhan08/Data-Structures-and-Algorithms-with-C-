#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

// Create new node
Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert into BST
Node* insert(Node* root, int value) {
    if (root == NULL) return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);

    return root;
}

// Search in BST
bool search(Node* root, int key) {
    if (root == NULL) return false;
    if (key == root->data) return true;
    if (key < root->data) return search(root->left, key);
    return search(root->right, key);
}

// In-order Traversal (LNR)
void inOrder(Node* root) {
    if (root == NULL) return;
    inOrder(root->left);
    cout << root->data << " ";
    inOrder(root->right);
}

// Pre-order Traversal (NLR)
void preOrder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

// Post-order Traversal (LRN)
void postOrder(Node* root) {
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

// Find Min
int findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

// Find Max
int findMax(Node* root) {
    while (root->right != NULL)
        root = root->right;
    return root->data;
}

// Delete Node
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node found
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            // Two children: find inorder successor
            int minVal = findMin(root->right);
            root->data = minVal;
            root->right = deleteNode(root->right, minVal);
        }
    }
    return root;
}


int main() {
    Node* root = NULL;

    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    cout << "In-order: ";
    inOrder(root);  // 20 30 40 50 60 70 80
    cout << "\n";

    cout << "Pre-order: ";
    preOrder(root); // 50 30 20 40 70 60 80
    cout << "\n";

    cout << "Post-order: ";
    postOrder(root); // 20 40 30 60 80 70 50
    cout << "\n";

    cout << "Min: " << findMin(root) << "\n"; // 20
    cout << "Max: " << findMax(root) << "\n"; // 80

    cout << "Search 60: " << (search(root, 60) ? "Found" : "Not Found") << "\n";

    root = deleteNode(root, 30);
    cout << "After deleting 30:\nIn-order: ";
    inOrder(root);  // 20 40 50 60 70 80
    cout << "\n";

    return 0;
}
