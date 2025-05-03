#include <iostream>
#include <string>
using namespace std;

// Course structure
struct Course {
    int courseCode;
    string courseName;
    int creditHours;
};

// Node of AVL Tree
struct AVLNode {
    Course data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Course course) {
        data = course;
        left = right = nullptr;
        height = 1; // New node is initially at height 1
    }
};

// AVL Tree class
class AVLCourseManager {
private:
    AVLNode* root;

    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVLNode* insert(AVLNode* node, Course course) {
        if (!node)
            return new AVLNode(course);

        if (course.courseCode < node->data.courseCode)
            node->left = insert(node->left, course);
        else if (course.courseCode > node->data.courseCode)
            node->right = insert(node->right, course);
        else {
            cout << "\nCourse code already exists!" << endl;
            return node; // Duplicates not allowed
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && course.courseCode < node->left->data.courseCode)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && course.courseCode > node->right->data.courseCode)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && course.courseCode > node->left->data.courseCode) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && course.courseCode < node->right->data.courseCode) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node; // return unchanged node
    }

    void inorder(AVLNode* node) {
        if (!node) return;
        inorder(node->left);
        displayCourse(node->data);
        inorder(node->right);
    }

    AVLNode* search(AVLNode* node, int code) {
        if (!node || node->data.courseCode == code) return node;
        if (code < node->data.courseCode) return search(node->left, code);
        return search(node->right, code);
    }

    void displayCourse(Course c) {
        cout << "\nCourse Code: " << c.courseCode
             << ", Name: " << c.courseName
             << ", Credit Hours: " << c.creditHours << endl;
    }

public:
    AVLCourseManager() {
        root = nullptr;
    }

    void insertCourse() {
        Course c;
        cout << "\nEnter course code: "; cin >> c.courseCode;
        cout << "Enter course name: "; cin.ignore(); getline(cin, c.courseName);
        cout << "Enter credit hours: "; cin >> c.creditHours;
        root = insert(root, c);
        cout << "Course inserted successfully!\n";
    }

    void searchCourse() {
        int code;
        cout << "\nEnter course code to search: "; cin >> code;
        AVLNode* res = search(root, code);
        if (res) displayCourse(res->data);
        else cout << "Course not found!\n";
    }

    void displayInOrder() {
        cout << "\nCourses in order (sorted by course code):\n";
        inorder(root);
    }
};

int main() {
    AVLCourseManager manager;
    int choice;

    do {
        cout << "\n===== AVL Course Enrollment Menu =====";
        cout << "\n1. Insert Course";
        cout << "\n2. Search Course";
        cout << "\n3. Display Courses (In-order)";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.insertCourse(); break;
            case 2: manager.searchCourse(); break;
            case 3: manager.displayInOrder(); break;
            case 4: cout << "\nExiting program...\n"; break;
            default: cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
