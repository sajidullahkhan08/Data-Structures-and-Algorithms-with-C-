#include <iostream>
#include <cstring>
using namespace std;

const int MAX_CHILDREN = 10; // Max number of children for each folder

// Node structure
struct Node {
    char name[50];
    bool isFile; // true = file, false = folder
    Node* children[MAX_CHILDREN];
    int childCount;
    Node* parent;
};

// Create a new node
Node* createNode(const char* name, bool isFile) {
    Node* newNode = new Node;
    strcpy(newNode->name, name);
    newNode->isFile = isFile;
    newNode->childCount = 0;
    newNode->parent = NULL;
    for (int i = 0; i < MAX_CHILDREN; i++)
        newNode->children[i] = NULL;
    return newNode;
}

// Find a node by path (e.g., root/documents/projects)
Node* findNode(Node* root, const char* path) {
    if (strcmp(path, "root") == 0) return root;
    Node* current = root;
    char temp[200];
    strcpy(temp, path);
    char* token = strtok(temp, "/");
    token = strtok(NULL, "/"); // skip "root"
    while (token && current) {
        bool found = false;
        for (int i = 0; i < current->childCount; i++) {
            if (strcmp(current->children[i]->name, token) == 0) {
                current = current->children[i];
                found = true;
                break;
            }
        }
        if (!found) return NULL;
        token = strtok(NULL, "/");
    }
    return current;
}

// Add a folder
void mkdir(Node* root, const char* path) {
    char parentPath[200], folderName[50];
    strcpy(parentPath, path);
    char* lastSlash = strrchr(parentPath, '/');
    if (lastSlash) {
        strcpy(folderName, lastSlash + 1);
        *lastSlash = '\0';
    } else {
        strcpy(folderName, path);
        strcpy(parentPath, "root");
    }
    Node* parent = findNode(root, parentPath);
    if (parent && !parent->isFile && parent->childCount < MAX_CHILDREN) {
        Node* folder = createNode(folderName, false);
        folder->parent = parent;
        parent->children[parent->childCount++] = folder;
    }
}

// Add a file
void touch(Node* root, const char* path) {
    char parentPath[200], fileName[50];
    strcpy(parentPath, path);
    char* lastSlash = strrchr(parentPath, '/');
    if (lastSlash) {
        strcpy(fileName, lastSlash + 1);
        *lastSlash = '\0';
    } else {
        strcpy(fileName, path);
        strcpy(parentPath, "root");
    }
    Node* parent = findNode(root, parentPath);
    if (parent && !parent->isFile && parent->childCount < MAX_CHILDREN) {
        Node* file = createNode(fileName, true);
        file->parent = parent;
        parent->children[parent->childCount++] = file;
    }
}

// Display the tree recursively
void display(Node* node, int level = 0) {
    for (int i = 0; i < level; i++) cout << "|  ";
    cout << "|-- " << node->name << (node->isFile ? "" : "/") << endl;
    if (!node->isFile) {
        for (int i = 0; i < node->childCount; i++) {
            display(node->children[i], level + 1);
        }
    }
}

// Search by name
bool search(Node* node, const char* target) {
    if (strcmp(node->name, target) == 0) {
        cout << "Found: " << node->name << (node->isFile ? " (file)" : " (folder)") << endl;
        return true;
    }
    if (!node->isFile) {
        for (int i = 0; i < node->childCount; i++) {
            if (search(node->children[i], target)) return true;
        }
    }
    return false;
}

// Count files and folders
void countItems(Node* node, int& fileCount, int& folderCount) {
    if (node->isFile)
        fileCount++;
    else
        folderCount++;

    for (int i = 0; i < node->childCount; i++) {
        countItems(node->children[i], fileCount, folderCount);
    }
}

// Delete a file or folder
bool deleteNode(Node* root, const char* path) {
    Node* target = findNode(root, path);
    if (!target || target == root) return false;
    Node* parent = target->parent;
    int index = -1;
    for (int i = 0; i < parent->childCount; i++) {
        if (parent->children[i] == target) {
            index = i;
            break;
        }
    }
    if (index == -1) return false;

    // Recursively delete children if folder
    if (!target->isFile) {
        for (int i = 0; i < target->childCount; i++) {
            deleteNode(target, target->children[i]->name);
        }
    }
    // Shift children left
    for (int i = index; i < parent->childCount - 1; i++) {
        parent->children[i] = parent->children[i + 1];
    }
    parent->childCount--;
    delete target;
    return true;
}

// Move a node
bool moveNode(Node* root, const char* sourcePath, const char* destPath) {
    Node* source = findNode(root, sourcePath);
    Node* dest = findNode(root, destPath);
    if (!source || !dest || dest->isFile || source == root || dest->childCount >= MAX_CHILDREN) return false;

    // Detach from current parent
    Node* parent = source->parent;
    int index = -1;
    for (int i = 0; i < parent->childCount; i++) {
        if (parent->children[i] == source) {
            index = i;
            break;
        }
    }
    for (int i = index; i < parent->childCount - 1; i++) {
        parent->children[i] = parent->children[i + 1];
    }
    parent->childCount--;

    // Attach to new parent
    dest->children[dest->childCount++] = source;
    source->parent = dest;
    return true;
}

int main() {
    Node* root = createNode("root", false);

    mkdir(root, "root/documents");
    touch(root, "root/documents/resume.pdf");
    mkdir(root, "root/photos");
    touch(root, "root/photos/vacation.jpg");
    touch(root, "root/photos/birthday.png");
    mkdir(root, "root/documents/projects");
    touch(root, "root/documents/projects/code.py");

    cout << "File System:\n";
    display(root);

    cout << "\nSearching for 'code.py':\n";
    if (!search(root, "code.py")) cout << "Not found\n";

    int files = 0, folders = 0;
    countItems(root, files, folders);
    cout << "\nTotal Files: " << files << ", Folders: " << folders << endl;

    cout << "\nDeleting 'root/photos/birthday.png'...\n";
    deleteNode(root, "root/photos/birthday.png");
    display(root);

    cout << "\nMoving 'root/documents/projects' to 'root/photos'...\n";
    moveNode(root, "root/documents/projects", "root/photos");
    display(root);

    return 0;
}
