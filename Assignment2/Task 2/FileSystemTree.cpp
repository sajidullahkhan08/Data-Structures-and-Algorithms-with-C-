#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

class TreeNode {
public:
    string name;
    string type; // "folder" or "file"
    vector<TreeNode*> children;

    TreeNode(string n, string t) {
        name = n;
        type = t;
    }

    // Find child folder by name
    TreeNode* findChild(string childName) {
        for (auto child : children) {
            if (child->name == childName && child->type == "folder")
                return child;
        }
        return nullptr;
    }
};

class FileSystem {
private:
    TreeNode* root;

    // Helper: Split path by '/'
    vector<string> splitPath(const string& path) {
        vector<string> parts;
        stringstream ss(path);
        string token;
        while (getline(ss, token, '/')) {
            if (!token.empty()) parts.push_back(token);
        }
        return parts;
    }

    // Recursive display
    void display(TreeNode* node, string indent = "") {
        cout << indent << (node->type == "folder" ? "|-- " : "   - ") << node->name << endl;
        if (node->type == "folder") {
            for (auto child : node->children) {
                display(child, indent + "    ");
            }
        }
    }

    // Recursive search
    void search(TreeNode* node, const string& target, bool& found) {
        if (node->name == target) {
            cout << "Found: " << node->name << " (" << node->type << ")\n";
            found = true;
        }
        for (auto child : node->children)
            search(child, target, found);
    }

    // Recursive count
    void count(TreeNode* node, int& files, int& folders) {
        if (node->type == "file") files++;
        else folders++;
        for (auto child : node->children)
            count(child, files, folders);
    }

public:
    FileSystem() {
        root = new TreeNode("root", "folder");
    }

    // Create folder
    void mkdir(string path) {
        vector<string> parts = splitPath(path);
        TreeNode* current = root;

        for (int i = 1; i < parts.size(); ++i) {
            TreeNode* child = current->findChild(parts[i]);
            if (!child) {
                TreeNode* newFolder = new TreeNode(parts[i], "folder");
                current->children.push_back(newFolder);
                current = newFolder;
            } else {
                current = child;
            }
        }
        cout << "Folder created: " << path << endl;
    }

    // Create file
    void touch(string path) {
        vector<string> parts = splitPath(path);
        TreeNode* current = root;

        for (int i = 1; i < parts.size() - 1; ++i) {
            TreeNode* child = current->findChild(parts[i]);
            if (!child) {
                TreeNode* newFolder = new TreeNode(parts[i], "folder");
                current->children.push_back(newFolder);
                current = newFolder;
            } else {
                current = child;
            }
        }

        string fileName = parts.back();
        TreeNode* newFile = new TreeNode(fileName, "file");
        current->children.push_back(newFile);

        cout << "File created: " << path << endl;
    }

    // Display tree
    void displayTree() {
        cout << "File System Tree:\n";
        display(root);
    }

    // Search
    void searchByName(string name) {
        bool found = false;
        search(root, name, found);
        if (!found)
            cout << "Not found: " << name << endl;
    }

    // Count
    void countAll() {
        int files = 0, folders = 0;
        count(root, files, folders);
        cout << "Total Folders: " << folders << ", Total Files: " << files << endl;
    }
};

// ---------------- Main Driver ----------------
int main() {
    FileSystem fs;
    int choice;
    string command, path;

    do {
        cout << "\n=== File System Menu ===\n";
        cout << "1. Create Folder (mkdir)\n";
        cout << "2. Create File (touch)\n";
        cout << "3. Display File System\n";
        cout << "4. Search for File/Folder\n";
        cout << "5. Count Files and Folders\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1 || choice == 2) {
            cout << "Enter full path (e.g., root/folder1/file.txt): ";
            getline(cin, path);
            if (choice == 1) fs.mkdir(path);
            else fs.touch(path);
        } else if (choice == 3) {
            fs.displayTree();
        } else if (choice == 4) {
            cout << "Enter name to search: ";
            getline(cin, path);
            fs.searchByName(path);
        } else if (choice == 5) {
            fs.countAll();
        } else if (choice == 0) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
