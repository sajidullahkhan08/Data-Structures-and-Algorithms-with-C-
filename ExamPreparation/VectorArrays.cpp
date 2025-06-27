#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;

    v.push_back(5);
    v.push_back(10);
    v.push_back(15);

    cout << "Elements: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }

    v.pop_back();

    cout << "\nAfter pop_back: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }

    v.insert(v.begin() + 1, 99); // Insert 99 at index 1

    cout << "\nAfter insertion: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }

    v.erase(v.begin()); // Delete first element

    cout << "\nAfter erase: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }

    return 0;
}
