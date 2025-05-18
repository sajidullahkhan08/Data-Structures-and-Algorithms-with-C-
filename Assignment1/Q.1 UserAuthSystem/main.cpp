#include <iostream>
#include <fstream> // For file operations
#include <string>
#include <sstream> // For string stream operations
#include <limits> // For numeric limits

using namespace std;

// User class to handle authentication and profile management
class User {
private:
    string username;
    int password;
    string name, fatherName, dob, className, regNo;
    int age;

public:
    // Constructor
    User() {
        username = "";
        password = 0;
    }

    // Function to validate numeric input
    int getValidNumber() {
        int num;
        while (true) {
            cin >> num;
            if (cin.fail()) { // fail() checks if the last input operation failed
                cout << "Invalid input! Please enter a numeric value: ";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            } else {
                return num;
            }
        }
    }

    // Register a new user (bool returns true if registration is successful)
    bool registerUser() {
        do {
            cout << "\nEnter a Username to start registration (or type 4 to return): ";
            cin >> username;

            if (username == "4") return false; // Go back to main menu

            if (!isUniqueUsername(username)) {
                cout << "Username already exists. Try a different one.\n";
                continue; // go back to the start of the loop
            }

            cout << "Enter a numeric password (10000-65000): ";
            password = getValidNumber(); 

            if (password < 10000 || password > 65000) {
                cout << "Invalid password. Must be between 10000-65000.\n";
                continue;
            }

            // Save credentials
            ofstream file("users.txt", ios::app); // ios::app opens the file in append mode, so new data is added at the end of the file without overwriting existing data.
            if (!file) {
                cout << "Error: Unable to open users.txt for writing.\n";
                return false;
            }
            file << username << " " << password << "\n";
            file.close();

            cout << "User registered successfully!\n";

            // Create user profile
            createProfile();
            return true;

        } while (true);
    }

    // Validate login credentials
    bool validateCredentials(const string& inputUsername, int inputPassword) {
        ifstream file("users.txt"); // Open the file in read mode
        if (!file) return false;

        string storedUsername;
        int storedPassword;
        while (file >> storedUsername >> storedPassword) {
            if (storedUsername == inputUsername && storedPassword == inputPassword) {
                return true;
            }
        }
        return false;
    }

    // Login a user
    bool loginUser() {
        ifstream checkFile("users.txt"); // Check if the file exists
        if (!checkFile) {
            cout << "No users registered yet. Redirecting to registration...\n";
            return registerUser();
        }

        do {
            cout << "\nEnter Username (or type 4 to return): ";
            cin >> username;

            if (username == "4") return false; // Go back to main menu

            cout << "Enter password: ";
            password = getValidNumber(); // Ensure valid numeric input

            if (validateCredentials(username, password)) {
                cout << "Login successful!\n";

                int choice;
                do {
                    cout << "\n1. Read Your Profile\n2. Overwrite Your Profile\n3. Go Back\nEnter choice: ";
                    choice = getValidNumber(); // to Ensure valid numeric input

                    if (choice == 1) {
                        readProfile();
                    } else if (choice == 2) {
                        overwriteProfile();
                    } else if (choice == 3) {
                        return true; // Go back to main menu
                    } else {
                        cout << "Invalid choice. Try again.\n";
                    }
                } while (true);

            } else {
                cout << "Invalid credentials. Try again or register first.\n";
                cout << "Would you like to register instead? (1 for Yes, 2 for No): ";
                int option = getValidNumber();
                if (option == 1) {
                    return registerUser();
                }
            }
        } while (true);
    }

    // Check if username is unique
    bool isUniqueUsername(const string& username) {
        ifstream file("users.txt"); // Open the file in read mode
        if (!file) return true; // If file doesn't exist, username is unique

        string user;
        int pass;

        while (file >> user >> pass) {
            if (user == username) {
                return false;
            }
        }
        return true;
    }

    // Create user profile
    void createProfile() {
        cout << "Enter Full Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Father's Name: ";
        getline(cin, fatherName);
        cout << "Enter Age: ";
        age = getValidNumber(); // Ensure valid numeric input
        cin.ignore();
        cout << "Enter Date of Birth (DD-MM-YYYY): ";
        getline(cin, dob);
        cout << "Enter Class Name: ";
        getline(cin, className);
        cout << "Enter Registration No: ";
        getline(cin, regNo);

        // Save profile data
        ofstream file(username + ".txt"); // Create a file named after the username (ofstream creates a new file or overwrites an existing one)
        file << "Name: " << name << endl;
        file << "Father Name: " << fatherName << endl;
        file << "Age: " << age << endl;
        file << "DOB: " << dob << endl;
        file << "Class: " << className << endl;
        file << "Registration No: " << regNo << endl;
        file.close(); // Close the file after writing

        cout << "Profile created successfully!\n";
    }

    // Read user profile
    void readProfile() {
        ifstream file(username + ".txt"); // Open the file in read mode (ifstream opens a file for reading)
        if (!file) {
            cout << "Profile not found.\n";
            return;
        }

        string line;
        cout << "\n----- Your Profile -----\n";
        while (getline(file, line)) { // Read line by line
            // Display each line of the profile
            cout << line << endl;
        }
        cout << "------------------------\n";
    }

    // Overwrite user profile
    void overwriteProfile() { 
        cout << "Overwriting profile...\n";
        createProfile();
    }
};

// Main function
int main() {
    User user;
    int choice;

    do {
        cout << "\n--- User Authentication System ---\n";
        cout << "1. Login\n2. Register\n3. Exit\n";
        cout << "Enter choice: ";
        choice = user.getValidNumber(); // to Ensure valid numeric input

        switch (choice) {
            case 1:
                user.loginUser();
                break;
            case 2:
                user.registerUser();
                break;
            case 3:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (true);
}
