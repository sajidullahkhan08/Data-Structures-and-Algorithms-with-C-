#include <iostream>
#include <string>
using namespace std;

class AVLNode {
public:
    int courseCode, creditHours;
    string courseName;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int code, string name, int credit) {
        courseCode = code;
        courseName = name;
        creditHours = credit;
        left = right = NULL;
        height = 1;
    }
};

class AVLCourseManager {
public:
    AVLNode* root = NULL;

    int height(AVLNode* node){
        if(node != NULL)
            return node->height;
        else
            return 0;
    }

    int getBalance(AVLNode* node){
        if(node != NULL)
            return height(node->left) - height(node->right);
        else
            return 0;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }
AVLNode* rotateRight(AVLNode* unbalancedNode) {
    AVLNode* newRoot = unbalancedNode->left;
    AVLNode* orphanSubtree = newRoot->right;
    
    newRoot->right = unbalancedNode;
    unbalancedNode->left = orphanSubtree;
    
    unbalancedNode->height = 1 + max(height(unbalancedNode->left), 
    height(unbalancedNode->right));
    newRoot->height = 1 + max(height(newRoot->left), 
    height(newRoot->right));
    return newRoot;
}

AVLNode* rotateLeft(AVLNode* unbalancedNode) {
    AVLNode* newRoot = unbalancedNode->right;
    AVLNode* orphanSubtree = newRoot->left;
    
    newRoot->left = unbalancedNode;
    unbalancedNode->right = orphanSubtree;
    
    unbalancedNode->height = 1 + max(height(unbalancedNode->left), 
    height(unbalancedNode->right));
    newRoot->height = 1 + max(height(newRoot->left), 
    height(newRoot->right));
    return newRoot;
}

    AVLNode* insert(AVLNode* node, int code, string name, int credit) {
        if (!node) return new AVLNode(code, name, credit);
        if (code < node->courseCode)
            node->left = insert(node->left, code, name, credit);
        else
            node->right = insert(node->right, code, name, credit);
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && code < node->left->courseCode)
            return rotateRight(node);
        if (balance < -1 && code > node->right->courseCode)
            return rotateLeft(node);
        if (balance > 1 && code > node->left->courseCode) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && code < node->right->courseCode) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    void addCourse(int code, string name, int credit) {
        root = insert(root, code, name, credit);
        cout<<"Course added successfully (AVL Balanced).\n";
    }

    AVLNode* findMin(AVLNode* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    AVLNode* deleteCourse(AVLNode* node, int code) {
        if (!node) return node;

        if (code < node->courseCode)
            node->left = deleteCourse(node->left, code);
        else if (code > node->courseCode)
            node->right = deleteCourse(node->right, code);
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            AVLNode* temp = findMin(node->right);
            node->courseCode = temp->courseCode;
            node->courseName = temp->courseName;
            node->creditHours = temp->creditHours;
            node->right = deleteCourse(node->right, temp->courseCode);
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rotateRight(node);
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0)
            return rotateLeft(node);
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    void removeCourse(int code) {
        root = deleteCourse(root, code);
        cout << "Course deleted if found (AVL Balanced).\n";
    }

    AVLNode* search(AVLNode* node, int code) {
        if (!node || node->courseCode == code)
            return node;
        return code < node->courseCode ? search(node->left, code) : search(node->right, code);
    }

    void searchCourse(int code) {
        AVLNode* result = search(root, code);
        if (result)
            displayCourse(result);
        else
            cout << "Course not found.\n";
    }

    void displayCourse(AVLNode* c) {
        cout << "Course ID: " << c->courseCode
             << ", Name: " << c->courseName
             << ", Credit Hours: " << c->creditHours
             << ", Balance Factor: " << getBalance(c) << endl;
    }

    void inorder(AVLNode* node) {
        if (node) {
            inorder(node->left);
            displayCourse(node);
            inorder(node->right);
        }
    }

    void displayAllCourses(){
        cout << "\n- In-Order Traversal with Balance Factors -\n";
        inorder(root);
        cout << "-------------\n";
    }

    int count(AVLNode* node){
        if(node != NULL)
            return 1 + count(node->left) + count(node->right);
        else
            return 0;
    }
    void countCourses() {
        cout << "Total Courses: " << count(root) << endl;
    }

    void displayMinMax() {
        AVLNode* minNode = findMin(root);
        AVLNode* maxNode = root;
        while (maxNode && maxNode->right)
            maxNode = maxNode->right;
        if (minNode) cout << "minimum Course ID: " << minNode->courseCode << endl;
        if (maxNode) cout << "maximum Course ID: " << maxNode->courseCode << endl;
    }
};

int main(){
    AVLCourseManager manager;
    int choice;

    while (true) {
        cout << "\n= AVL Course Manager Menu =\n";
        cout << "1. Add Course\n";
        cout << "2. Delete Course\n";
        cout << "3. Search Course\n";
        cout << "4. Display All Courses\n";
        cout << "5. Count Total Courses\n";
        cout << "6. Display Min and Max Course IDs\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            int id, credit;
            string name;
            cout << "Enter Course ID: "; cin >> id;
            cin.ignore();
            cout << "Enter Course Name: "; getline(cin, name);
            cout << "Enter Credit Hours: "; cin >> credit;
            manager.addCourse(id, name, credit);
        } else if (choice == 2) {
            int id;
            cout << "Enter Course ID to delete: ";
            cin >> id;
            manager.removeCourse(id);
        } else if (choice == 3) {
            int id;
            cout << "Enter Course ID to search: ";
            cin >> id;
            manager.searchCourse(id);
        } else if (choice == 4) {
            manager.displayAllCourses();
        } else if (choice == 5) {
            manager.countCourses();
        } else if (choice == 6) {
            manager.displayMinMax();
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }
    cout << "Program exited.\n";
    return 0;
}

/* Discussion: Why AVL Rebalancing Improves Lookup Performance?
In a normal Binary Search Tree (BST), if we insert nodes in sorted or nearly sorted order, 
the tree becomes skewed — like a linked list — making search, insertion, and deletion operations slower (O(n)).

An AVL Tree solves this problem by automatically rebalancing itself after every insertion and deletion. 
It ensures that the height difference (balance factor) between the left and right subtrees of any node stays within -1, 0, or +1.

This self-balancing keeps the tree height-balanced, maintaining logarithmic height, 
which ensures that search, insert, and delete operations all run in O(log n) time. As a result, even with large amounts of data, 
the system remains consistently fast and efficient for course lookups.*/