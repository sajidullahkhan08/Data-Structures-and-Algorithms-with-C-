#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User {
private:
    string username;
    int password;
    string name, fatherName, dob, className, regNo;
    int age;

public:
    User() {
        username = "";
        password = 0;
    }

    // Simple numeric input (assumes user inputs correctly)
    int getNumber() {
        int num;
        cin >> num;
        return num;
    }

    // Check if username is already taken
    bool isUniqueUsername(string uname) {
        ifstream file("users.txt");
        string user;
        int pass;

        while (file >> user >> pass) {
            if (user == uname) {
                return false;
            }
        }
        return true;
    }

    // Register new user
    bool registerUser() {
        while (true) {
            cout << "\nEnter a username to register (or type 4 to go back): ";
            cin >> username;

            if (username == "4") return false;

            if (!isUniqueUsername(username)) {
                cout << "That username is already taken. Try another one.\n";
                continue;
            }

            cout << "Enter a password (between 10000 and 65000): ";
            password = getNumber();

            if (password < 10000 || password > 65000) {
                cout << "Invalid password. Please try again.\n";
                continue;
            }

            ofstream file("users.txt", ios::app);
            file << username << " " << password << endl;
            file.close();

            cout << "Registration successful!\n";

            createProfile();
            return true;
        }
    }

    // Login existing user
    bool loginUser() {
        ifstream check("users.txt");
        if (!check) {
            cout << "No user found. Please register first.\n";
            return registerUser();
        }

        while (true) {
            cout << "\nEnter Username (or 4 to go back): ";
            cin >> username;
            if (username == "4") return false;

            cout << "Enter Password: ";
            password = getNumber();

            if (validateLogin(username, password)) {
                cout << "Login successful!\n";

                int choice;
                while (true) {
                    cout << "\n1. View Profile\n2. Edit Profile\n3. Go Back\nYour choice: ";
                    choice = getNumber();

                    if (choice == 1) readProfile();
                    else if (choice == 2) overwriteProfile();
                    else if (choice == 3) return true;
                    else cout << "Try again.\n";
                }
            } else {
                cout << "Invalid login. Try again.\n";
                cout << "Do you want to register? (1 = Yes, 2 = No): ";
                int option;
                option = getNumber();
                if (option == 1) return registerUser();
            }
        }
    }

    // Validate login credentials
    bool validateLogin(string uname, int pass) {
        ifstream file("users.txt");
        string u;
        int p;
        while (file >> u >> p) {
            if (u == uname && p == pass) return true;
        }
        return false;
    }

    // Create profile file
    void createProfile() {
        cin.ignore(); // clear buffer
        cout << "Enter Full Name: ";
        getline(cin, name);
        cout << "Enter Father's Name: ";
        getline(cin, fatherName);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Date of Birth (DD-MM-YYYY): ";
        getline(cin, dob);
        cout << "Enter Class Name: ";
        getline(cin, className);
        cout << "Enter Registration No: ";
        getline(cin, regNo);

        ofstream file(username + ".txt");
        file << "Name: " << name << endl;
        file << "Father's Name: " << fatherName << endl;
        file << "Age: " << age << endl;
        file << "DOB: " << dob << endl;
        file << "Class: " << className << endl;
        file << "Registration No: " << regNo << endl;
        file.close();

        cout << "Profile saved!\n";
    }

    void readProfile() {
        ifstream file(username + ".txt");
        if (!file) {
            cout << "Profile not found.\n";
            return;
        }

        string line;
        cout << "\n--- Your Profile ---\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        cout << "--------------------\n";
    }

    // to Overwrite profile
    void overwriteProfile() {
        cout << "Let's update your profile...\n";
        createProfile();
    }
};

int main() {
    User user;
    int choice;

    while (true) {
        cout << "\n--- Welcome to User System ---\n";
        cout << "1. Login\n2. Register\n3. Exit\nEnter your choice: ";
        choice = user.getNumber();

        if (choice == 1) {
            user.loginUser();
        } else if (choice == 2) {
            user.registerUser();
        } else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}