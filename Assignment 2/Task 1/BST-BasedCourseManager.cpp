#include <iostream>
#include <string>
using namespace std;

// Structure to store Course Information
struct Course {
    int courseID;   
    string courseName;    
    int creditHours; 
};

// Node of BST that holds Course
class CourseNode {
public:
    Course data;          
    CourseNode* left;        
    CourseNode* right;  

    CourseNode(Course c) {
        data = c;
        left = right = nullptr;
    }
};

// BST Manager to handle insertion, deletion, search, etc.
class BSTCourseManager {
private:
    CourseNode* root;

    // Helper for inserting a node recursively
    CourseNode* insert(CourseNode* node, Course c) {
        if (node == nullptr) {
            return new CourseNode(c);
        }
        if (c.courseID < node->data.courseID) {
            node->left = insert(node->left, c);
        } else {
            node->right = insert(node->right, c);
        }
        return node;
    }

    // Helper for in-order traversal
    void inorder(CourseNode* node) {
        if (node != nullptr) {
            inorder(node->left);
            displayCourse(node->data);
            inorder(node->right);
        }
    }

    // Helper to search by Course ID
    CourseNode* search(CourseNode* node, int id) {
        if (node == nullptr || node->data.courseID == id)
            return node;
        if (id < node->data.courseID)
            return search(node->left, id);
        else
            return search(node->right, id);
    }

    // Helper to count total nodes
    int countCourses(CourseNode* node) {
        if (node == nullptr) return 0;
        return 1 + countCourses(node->left) + countCourses(node->right);
    }

    // Helper to find minimum node
    CourseNode* findMin(CourseNode* node) {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }

    // Helper to find maximum node
    CourseNode* findMax(CourseNode* node) {
        while (node && node->right != nullptr)
            node = node->right;
        return node;
    }

    // Helper to delete a node by Course ID
    CourseNode* deleteCourse(CourseNode* node, int id) {
        if (node == nullptr) return nullptr;

        if (id < node->data.courseID) {
            node->left = deleteCourse(node->left, id);
        } else if (id > node->data.courseID) {
            node->right = deleteCourse(node->right, id);
        } else {
            // Node found
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                CourseNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                CourseNode* temp = node->left;
                delete node;
                return temp;
            } else {
                // Node with two children
                CourseNode* successor = findMin(node->right);
                node->data = successor->data;
                node->right = deleteCourse(node->right, successor->data.courseID);
            }
        }
        return node;
    }

    // Display course details
    void displayCourse(Course c) {
        cout << "Course ID: " << c.courseID << ", Name: " << c.courseName
             << ", Credit Hours: " << c.creditHours << endl;
    }

public:
    // Constructor
    BSTCourseManager() {
        root = nullptr;
    }

    // Public insert
    void addCourse(Course c) {
        root = insert(root, c);
        cout << "Course added.\n";
    }

    // Public delete
    void deleteCourse(int id) {
        root = deleteCourse(root, id);
        cout << "Course deleted if existed.\n";
    }

    // Public search
    void searchCourse(int id) {
        CourseNode* found = search(root, id);
        if (found)
            displayCourse(found->data);
        else
            cout << "Course not found.\n";
    }

    // Display all courses (ascending order)
    void displayAllCourses() {
        cout << "\n--- All Courses (Inorder) ---\n";
        inorder(root);
        cout << "-----------------------------\n";
    }

    // Count total courses
    void countCourses() {
        cout << "Total Courses: " << countCourses(root) << endl;
    }

    // Find min & max course ID
    void displayMinMax() {
        CourseNode* minNode = findMin(root);
        CourseNode* maxNode = findMax(root);
        if (minNode && maxNode) {
            cout << "Minimum Course ID: " << minNode->data.courseID << endl;
            cout << "Maximum Course ID: " << maxNode->data.courseID << endl;
        }
    }
};

//------------------------------------------
// Main Program (for testing)
//------------------------------------------
int main() {
    BSTCourseManager manager;
    int choice;

    while (true) {
        cout << "\n===== Course Manager Menu =====\n";
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
            cout << "Enter Course ID: "; cin >> c.courseID;
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

    cout << "Exiting program.\n";
    return 0;
}
