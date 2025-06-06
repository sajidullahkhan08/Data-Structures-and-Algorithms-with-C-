#include <iostream>
#include <string>
// #include <vector>
using namespace std;

int main() {
    // vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    
    // for(int i = 0; i <= 10; i++) {
    //     array[i] = i;
    // }
    // array.pop_back();

    // cout << "[ ";
    // for(int j : array) {
    //     cout << j << " ";
    // }
    // cout << "]";
    int size;
    cout << "Enter the size: ";
    cin >> size;

    int* array = new int[size];

    for(int i = 1; i <= size; i++) {
        array[i];
    }

    for(int j = 1; j <= size; j++) {
        cout << j << " ";
    }

    return 0;
}