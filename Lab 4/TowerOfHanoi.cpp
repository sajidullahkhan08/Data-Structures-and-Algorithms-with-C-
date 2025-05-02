#include <iostream>
using namespace std;

// Recursive function to solve Tower of Hanoi
void tower(char source, char destination, char intermediate, int n) {
    if (n == 1) {
        cout << "Move disk 1 from needle " << source << " to needle " << destination << endl;
    } else {
        // Move n-1 disks from source to intermediate using destination as auxiliary
        tower(source, intermediate, destination, n - 1);
        
        // Move the nth disk directly from source to destination
        cout << "Move disk " << n << " from needle " << source << " to needle " << destination << endl;
        
        // Move n-1 disks from intermediate to destination using source as auxiliary
        tower(intermediate, destination, source, n - 1);
    }
}

int main() {
    int num_disks;

    // Taking input from user
    cout << "Enter the number of disks: ";
    cin >> num_disks;

    // Calling the recursive function
    cout << "Steps to solve Tower of Hanoi with " << num_disks << " disks:" << endl;
    tower('A', 'C', 'B', num_disks);

    return 0;
}
