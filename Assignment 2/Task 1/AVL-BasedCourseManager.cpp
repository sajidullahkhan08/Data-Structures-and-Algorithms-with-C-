#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Course structure
struct Course {
    int courseCode;
    string courseName;
    int creditHours;
};

// Node of AVL Tree
class AVLNode {
public:
    Course data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Course course) {
        data = course;
        left = right = nullptr;
        height = 1;
    }
};

// AVL Tree Manager
class AVLCourseManager {
private:
    AVLNode* root;

    // Get height of node
    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    // Get balance factor
    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    // Right rotate
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    // Left rotate
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    // Insert helper
    AVLNode* insert(AVLNode* node, Course c) {
        if (!node) return new AVLNode(c);

        if (c.courseCode < node->data.courseCode)
            node->left = insert(node->left, c);
        else
            node->right = insert(node->right, c);

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // Left Left
        if (balance > 1 && c.courseCode < node->left->data.courseCode)
            return rotateRight(node);
        // Right Right
        if (balance < -1 && c.courseCode > node->right->data.courseCode)
            return rotateLeft(node);
        // Left Right
        if (balance > 1 && c.courseCode > node->left->data.courseCode) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        // Right Left
        if (balance < -1 && c.courseCode < node->right->data.courseCode) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // In-order traversal
    void inorder(AVLNode* node) {
        if (node) {
            inorder(node->left);
            displayCourse(node->data);
            inorder(node->right);
        }
    }

    // Search by Course Code
    AVLNode* search(AVLNode* node, int code) {
        if (!node || node->data.courseCode == code)
            return node;
        if (code < node->data.courseCode)
            return search(node->left, code);
        else
            return search(node->right, code);
    }

    // Count total nodes
    int countCourses(AVLNode* node) {
        if (!node) return 0;
        return 1 + countCourses(node->left) + countCourses(node->right);
    }

    // Find min node
    AVLNode* findMin(AVLNode* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    // Find max node
    AVLNode* findMax(AVLNode* node) {
        while (node && node->right)
            node = node->right;
        return node;
    }

    // Delete course helper
    AVLNode* deleteCourse(AVLNode* root, int code) {
        if (!root) return root;

        if (code < root->data.courseCode)
            root->left = deleteCourse(root->left, code);
        else if (code > root->data.courseCode)
            root->right = deleteCourse(root->right, code);
        else {
            if (!root->left || !root->right) {
                AVLNode* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            } else {
                AVLNode* successor = findMin(root->right);
                root->data = successor->data;
                root->right = deleteCourse(root->right, successor->data.courseCode);
            }
        }

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        // Rebalance if needed
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    // Display course details
    void displayCourse(Course c) {
        cout << "Course ID: " << c.courseCode << ", Name: " << c.courseName
             << ", Credit Hours: " << c.creditHours << endl;
    }

public:
    AVLCourseManager() {
        root = nullptr;
    }

    void addCourse(Course c) {
        root = insert(root, c);
        cout << "Course added (AVL balanced).\n";
    }

    void deleteCourse(int code) {
        root = deleteCourse(root, code);
        cout << "Course deleted if existed (AVL rebalanced).\n";
    }

    void searchCourse(int code) {
        AVLNode* found = search(root, code);
        if (found)
            displayCourse(found->data);
        else
            cout << "Course not found.\n";
    }

    void displayAllCourses() {
        cout << "\n--- All Courses (Inorder - AVL) ---\n";
        inorder(root);
        cout << "-----------------------------------\n";
    }

    void countCourses() {
        cout << "Total Courses: " << countCourses(root) << endl;
    }

    void displayMinMax() {
        AVLNode* minNode = findMin(root);
        AVLNode* maxNode = findMax(root);
        if (minNode && maxNode) {
            cout << "Minimum Course ID: " << minNode->data.courseCode << endl;
            cout << "Maximum Course ID: " << maxNode->data.courseCode << endl;
        }
    }
};

// Main program
int main() {
    AVLCourseManager manager;
    int choice;

    while (true) {
        cout << "\n===== AVL Course Manager Menu =====\n";
        cout << "1. Add Course\n";
        cout << "2. Delete Course\n";
        cout << "3. Search Course\n";
        cout << "4. Display All Courses\n";
        cout << "5. Count Total Courses\n";
        cout << "6. Find Min and Max Course ID\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            Course c;
            cout << "Enter Course ID: "; cin >> c.courseCode;
            cin.ignore();
            cout << "Enter Course Name: "; getline(cin, c.courseName);
            cout << "Enter Credit Hours: "; cin >> c.creditHours;
            manager.addCourse(c);
        } else if (choice == 2) {
            int id;
            cout << "Enter Course ID to delete: "; cin >> id;
            manager.deleteCourse(id);
        } else if (choice == 3) {
            int id;
            cout << "Enter Course ID to search: "; cin >> id;
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

    cout << "Exiting AVL program.\n";
    return 0;
}
