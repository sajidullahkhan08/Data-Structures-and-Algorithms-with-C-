#include <iostream>
using namespace std;

int main() {
    int arr[6] = {21, 4, 78, 5, 90, 15};
    int n = 6;
    int max = arr[0], min = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    cout << "Largest = " << max << endl;
    cout << "Smallest = " << min << endl;
}
