#include <iostream>
#include <string>

using namespace std;

class CourseNode {
public:
    int courseID;
    string courseName;
    int creditHours;
    CourseNode* left;
    CourseNode* right;

    CourseNode(int id, string name, int credits){
        courseID = id;
        courseName = name;
        creditHours = credits;
        left = right = NULL;}
};

class BSTCourseManager {
public:
    CourseNode* root;

    BSTCourseManager(){
        root = NULL;
    }

void insert(int id, string name, int credits){
    CourseNode* newNode = new CourseNode(id, name, credits);
    if (root == NULL) {
        root = newNode;
        return;
    }
    CourseNode* parent = NULL;
    CourseNode* current = root;
    while (current != NULL) {
        parent = current;
        if (id < current->courseID)
            current = current->left;
        else
            current = current->right;
    }
    if (id < parent->courseID)
        parent->left = newNode;
    else
        parent->right = newNode;
}
void addCourse(int id, string name, int credits){
    insert(id, name, credits);
    cout << "Course is added.\n";
}
    void inorder(CourseNode* node) {
        if(node){
            inorder(node->left);
            displayCourse(node);
            inorder(node->right);
        }
    }
    void displayAllCourses() {
        cout<< "\n--- All Courses (Inorder) ---\n";
        inorder(root);
        cout << "-----------------------------\n";
    }
    CourseNode* search(CourseNode* node, int id){
        if(!node || node->courseID == id)
            return node;
        if(id < node->courseID)
            return search(node->left, id);
        else
            return search(node->right, id);
    }
    void searchCourse(int id){
        CourseNode* found = search(root, id);
        if (found)
            displayCourse(found);
        else
            cout << "Course not found.\n";
    }
    CourseNode* findMin(CourseNode* node){
        while (node && node->left)
            node = node->left;
        return node;
    }
    CourseNode* findMax(CourseNode* node){
        while (node && node->right)
            node = node->right;
        return node;
    }
    void displayMinMax(){
        CourseNode* minNode = findMin(root);
        CourseNode* maxNode = findMax(root);
        if (minNode && maxNode) {
            cout << "Minimum Course ID: " << minNode->courseID <<endl;
            cout << "Maximum Course ID: " << maxNode->courseID <<endl;
        }
    }
    int count(CourseNode* node){
        if (!node) return 0;
        return 1 + count(node->left) + count(node->right);
    }
    void countCourses(){
        cout << "Total Courses: " << count(root) << endl;
    }
    CourseNode* deleteCourse(CourseNode* node, int id) {
        if (!node) return NULL;
        if (id < node->courseID)
            node->left = deleteCourse(node->left, id);
        else if (id > node->courseID)
            node->right = deleteCourse(node->right, id);
        else {
            if (!node->left && !node->right) {
                delete node;
                return NULL;
            }
            else if (!node->left) {
                CourseNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                CourseNode* temp = node->left;
                delete node;
                return temp;
            }
            CourseNode* successor = findMin(node->right);
            node->courseID = successor->courseID;
            node->courseName = successor->courseName;
            node->creditHours = successor->creditHours;
            node->right = deleteCourse(node->right, successor->courseID);
        }
        return node;
    }
    void deleteCourse(int id) {
        root = deleteCourse(root, id);
        cout << "Course deleted if existed.\n";
    }

    void displayCourse(CourseNode* c) {
        cout << "Course ID: " << c->courseID
             << ", Name: " << c->courseName
             << ", Credit Hours: " << c->creditHours << endl;
    }
};

int main() {
    BSTCourseManager manager;
    int choice;

    while (true) {
        cout << "\n===== Course Manager Menu =====\n";
        cout << "1. Add Course\n";
        cout << "2. Delete Course\n";
        cout << "3. Search Course\n";
        cout << "4. Display All Courses in Ascending order of Course ID\n";
        cout << "5. Count Total Courses\n";
        cout << "6. Find Min and Max Course ID\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 0) break;
        if(choice == 1){
            int id, credit;
            string name;
            cout << "Enter Course ID: "; cin >> id;
            cin.ignore();
            cout << "Enter Course Name: "; getline(cin, name);
            cout << "Enter Credit Hours: "; cin >> credit;
            manager.addCourse(id, name, credit);
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
