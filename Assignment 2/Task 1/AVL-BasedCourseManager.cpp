#include <iostream>
#include <string>
using namespace std;

// Course structure
struct Course {
    int courseCode;
    string courseName;
    int creditHours;
};

// AVL Node structure
class AVLNode {
public:
    Course data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Course c) {
        data = c;
        left = right = nullptr;
        height = 1;
    }
};

// AVL Tree Course Manager
class AVLCourseManager {
private:
    AVLNode* root;

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }

    AVLNode* insert(AVLNode* node, Course c) {
        if (!node) return new AVLNode(c);

        if (c.courseCode < node->data.courseCode)
            node->left = insert(node->left, c);
        else
            node->right = insert(node->right, c);

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && c.courseCode < node->left->data.courseCode)
            return rotateRight(node);
        if (balance < -1 && c.courseCode > node->right->data.courseCode)
            return rotateLeft(node);
        if (balance > 1 && c.courseCode > node->left->data.courseCode) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && c.courseCode < node->right->data.courseCode) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* deleteCourse(AVLNode* node, int code) {
        if (!node) return node;

        if (code < node->data.courseCode)
            node->left = deleteCourse(node->left, code);
        else if (code > node->data.courseCode)
            node->right = deleteCourse(node->right, code);
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                AVLNode* temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteCourse(node->right, temp->data.courseCode);
            }
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

    AVLNode* search(AVLNode* node, int code) {
        if (!node || node->data.courseCode == code)
            return node;
        if (code < node->data.courseCode)
            return search(node->left, code);
        return search(node->right, code);
    }

    void inorder(AVLNode* node) {
        if (node) {
            inorder(node->left);
            displayCourse(node->data);
            inorder(node->right);
        }
    }

    int countCourses(AVLNode* node) {
        if (!node) return 0;
        return 1 + countCourses(node->left) + countCourses(node->right);
    }

    AVLNode* findMin(AVLNode* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    AVLNode* findMax(AVLNode* node) {
        while (node && node->right)
            node = node->right;
        return node;
    }

    void displayCourse(Course c) {
        cout << "Course ID: " << c.courseCode
             << ", Name: " << c.courseName
             << ", Credit Hours: " << c.creditHours << endl;
    }

public:
    AVLCourseManager() {
        root = nullptr;
    }

    void addCourse(Course c) {
        root = insert(root, c);
        cout << "Course added successfully (AVL Balanced).\n";
    }

    void deleteCourse(int code) {
        root = deleteCourse(root, code);
        cout << "Course deleted if found (AVL Balanced).\n";
    }

    void searchCourse(int code) {
        AVLNode* result = search(root, code);
        if (result)
            displayCourse(result->data);
        else
            cout << "Course not found.\n";
    }

    void displayAllCourses() {
        cout << "\n--- All Courses (In-Order Traversal) ---\n";
        inorder(root);
        cout << "----------------------------------------\n";
    }

    void countCourses() {
        cout << "Total number of courses: " << countCourses(root) << endl;
    }

    void displayMinMax() {
        AVLNode* min = findMin(root);
        AVLNode* max = findMax(root);
        if (min) cout << "Minimum Course ID: " << min->data.courseCode << endl;
        if (max) cout << "Maximum Course ID: " << max->data.courseCode << endl;
    }
};

// -------- Main Menu --------
int main() {
    AVLCourseManager manager;
    int choice;

    do {
        cout << "\n===== AVL Course Management Menu =====\n";
        cout << "1. Add Course\n";
        cout << "2. Delete Course\n";
        cout << "3. Search Course\n";
        cout << "4. Display All Courses\n";
        cout << "5. Count Courses\n";
        cout << "6. Display Min and Max Course IDs\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Course c;
                cout << "Enter Course ID: ";
                cin >> c.courseCode;
                cin.ignore();
                cout << "Enter Course Name: ";
                getline(cin, c.courseName);
                cout << "Enter Credit Hours: ";
                cin >> c.creditHours;
                manager.addCourse(c);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Course ID to delete: ";
                cin >> id;
                manager.deleteCourse(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter Course ID to search: ";
                cin >> id;
                manager.searchCourse(id);
                break;
            }
            case 4:
                manager.displayAllCourses();
                break;
            case 5:
                manager.countCourses();
                break;
            case 6:
                manager.displayMinMax();
                break;
            case 7:
                cout << "Exiting... Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
