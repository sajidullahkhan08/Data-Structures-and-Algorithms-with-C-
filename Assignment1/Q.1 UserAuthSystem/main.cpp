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
    User(){
        username="";
        password=0; }

    bool isUniqueUsername(string uname){
        ifstream file("users.txt");
        string user;
        int pass;

        while (file >> user >> pass){
            if(user == uname){
                return false;
            }
        }
        return true;
    }

    // it is for reegistering new user
    bool registerUser(){
        while (true) {
            cout << "\nEnter a username to register (or type 4 to go back): ";
            cin>>username;
            if (username == "4") 
            return false;

            if(!isUniqueUsername(username)) 
            {
                cout << "That username is already taken. Try another one.\n";
                continue;
            }

            cout <<"Enter a password (between 10000 and 65000): ";
            cin >> password;

            if(password < 10000 || password > 65000)
            {
                cout<<"Invalid password. Please try again.\n";
                continue;
            }

            ofstream file("users.txt", ios::app);
            file << username << " " << password << endl;
            file.close();

            cout<<"Registration is successful!\n";

            createProfile();
            return true;
        }
    }

    bool loginUser() {
        ifstream check("users.txt");
        if (!check) {
            cout<<"No user found. Please register first.\n";
            return registerUser();
        }

        while (true) {
            cout<<"\nEnter Username (or 4 to go back): ";
            cin>> username;
            if(username == "4") return false;

            cout << "Enter Password: ";
            cin >> password;

            if (validateLogin(username, password)) 
            {
                cout<< "Login successful!\n";

                int choice;
                while (true) {
                    cout<<"\n1. View Profile\n2. Edit Profile\n3. Go Back\nYour choice: ";
                    cin >> choice;

                    if (choice == 1) readProfile();
                    else if (choice == 2) overwriteProfile();
                    else if (choice == 3) return true;
                    else cout << "Try again.\n";
                }
            } else {
                cout << "Invalid username or password. Try again.\n";
                cout << "Do you want to register first? (1 = Yes, 2 = No): ";
                int option;
                cin >> option;
                if (option == 1) return registerUser();
            }
        }
    }

    // this is for validating login credentials
    bool validateLogin(string uname, int pass) {
        ifstream file("users.txt");
        string u;
        int p;
        while (file >> u >> p) {
            if (u == uname && p == pass) return true;
        }
        return false;
    }

    void createProfile() {
        cin.ignore();
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

        cout <<"Profile saved!\n";
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

    // to overrwwrite the profile or to update the profile
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
        cin>>choice;

        if(choice == 1) {
            user.loginUser();
        }else if (choice == 2) {
            user.registerUser();
        }else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        }else {
            cout << "Invalid option. Try again.\n";
        }
    }
    return 0;
}