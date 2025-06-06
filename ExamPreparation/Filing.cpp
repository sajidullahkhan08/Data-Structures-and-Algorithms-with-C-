#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string name = "Sajid";
    string reading;

    // ofstream outfile("Intro.txt");
    // outfile << "My name is " << name;
    // outfile.close();
    // cout << "Writing Successfull!" << endl;

    ifstream infile("Intro.txt");
    if(infile) {
        while(getline(infile, reading)) {
            cout << reading;
        }
    } else {
        cout << "Unable to open file" <<endl;
    return 0;
    }
}