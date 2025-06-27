#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int size = 5;
    int pos = 2;

    for (int i = pos; i < size - 1; i++) {
        arr[i] = arr[i + 1]; // shift left
    }
    size--;

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
}
