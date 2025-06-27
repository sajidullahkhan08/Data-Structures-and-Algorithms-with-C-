#include <iostream>
using namespace std;

int main() {
    int arr[6] = {10, 20, 30, 40, 50};
    int size = 5;
    int pos = 2;  // index where to insert
    int value = 99;

    for (int i = size; i > pos; i--) {
        arr[i] = arr[i - 1]; // shift right
    }
    arr[pos] = value;
    size++;

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}
