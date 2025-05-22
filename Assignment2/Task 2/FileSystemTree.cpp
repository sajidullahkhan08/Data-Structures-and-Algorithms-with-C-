#include <iostream>
#include <string>
using namespace std;

class TreeNode {
public:
    string name;
    string type;
    TreeNode* children[50];
    int childCount;

    TreeNode(string n, string t) {
        name = n;
        type = t;
        childCount = 0;
    }

    TreeNode* findChild(string childName) {
        for (int i = 0; i < childCount; ++i) {
            if (children[i]->name == childName && children[i]->type == "folder")
                return children[i];
        }
        return NULL;
    }

    bool hasDuplicate(string childName, string childType) {
        for (int i = 0; i < childCount; ++i) {
            if (children[i]->name == childName && children[i]->type == childType)
                return true;
        }
        return false;
    }
};

class FileSystem {
private:
    TreeNode* root;

public:
    FileSystem() {
        root = new TreeNode("root", "folder");
    }

    int splitPath(string& path, string parts[]) {
        int count = 0;
        string temp = "";
        for (char ch : path) {
            if (ch == '/') {
                if (!temp.empty()) {
                    parts[count++] = temp;
                    temp = "";
                }
            } else{
                temp += ch;
            }
        }
        if (!temp.empty()) parts[count++] = temp;
        return count;
    }

    void display(TreeNode* node, string indent) {
        cout << indent << (node->type == "folder" ? "|-- " : "   - ") << node->name << endl;
        if (node->type == "folder") {
            for (int i = 0; i < node->childCount; ++i)
                display(node->children[i], indent + "    ");
        }
    }

    void search(TreeNode* node, string& target, bool& found) {
        if (node->name == target) {
            cout << "Found: " << node->name << " (" << node->type << ")\n";
            found = true;
        }
        for (int i = 0; i < node->childCount; ++i)
            search(node->children[i], target, found);
    }

    void count(TreeNode* node, int& files, int& folders) {
        if (node->type == "file") files++;
        else folders++;
        for (int i = 0; i < node->childCount; ++i)
            count(node->children[i], files, folders);
    }

    void mkdir(string path) {
        string parts[20];
        int count = splitPath(path, parts);
        if (count == 0 || parts[0] != "root") {
            cout << "Path must start from root.\n";
            return;
        }

        TreeNode* current = root;
        for (int i = 1; i < count; ++i) {
            TreeNode* child = current->findChild(parts[i]);
            if (!child) {
                TreeNode* newFolder = new TreeNode(parts[i], "folder");
                current->children[current->childCount++] = newFolder;
                current = newFolder;
            } else {
                current = child;
            }
        }
        cout << "Folder created: " << path << endl;
    }

    void touch(string path) {
        string parts[20];
        int count = splitPath(path, parts);
        if (count == 0 || parts[0] != "root") {
            cout << "Path must start from root.\n";
            return;
        }

        TreeNode* current = root;
        for (int i = 1; i < count - 1; ++i) {
            TreeNode* child = current->findChild(parts[i]);
            if (!child) {
                TreeNode* newFolder = new TreeNode(parts[i], "folder");
                current->children[current->childCount++] = newFolder;
                current = newFolder;
            } else {
                current = child;
            }
        }

        string fileName = parts[count - 1];
        if (current->hasDuplicate(fileName, "file")) {
            cout << "File already exists: " << fileName << endl;
            return;
        }

        TreeNode* newFile = new TreeNode(fileName, "file");
        current->children[current->childCount++] = newFile;
        cout << "File created: " << path << endl;
    }

    void displayTree() {
        cout << "File System Tree:\n";
        display(root, "");
    }

    void searchByName(string name) {
        bool found = false;
        search(root, name, found);
        if (!found)
            cout << "Not found: " << name << endl;
    }

    void countAll() {
        int files = 0, folders = 0;
        count(root, files, folders);
        cout << "Total Folders: " << folders << ", Total Files: " << files << endl;
    }
};

int main() {
    FileSystem fs;
    int choice;
    string path;

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
