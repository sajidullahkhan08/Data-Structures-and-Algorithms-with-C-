#include <iostream>
using namespace std;

int main() {
    int arr1[3] = {1, 3, 5};
    int arr2[3] = {2, 4, 6};
    int merged[6];

    for (int i = 0; i < 3; i++) merged[i] = arr1[i];
    for (int i = 0; i < 3; i++) merged[i + 3] = arr2[i];

    cout << "Merged array: ";
    for (int i = 0; i < 6; i++) {
        cout << merged[i] << " ";
    }
}
