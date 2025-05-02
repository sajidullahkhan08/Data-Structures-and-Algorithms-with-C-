# Tower of Hanoi - C++ Implementation and Dry Run (n = 4)

## C++ Code for Tower of Hanoi

```cpp
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
```

---

## **Dry Run for n = 4**
When `n = 4`, we have three pegs:
- **Source (A)**
- **Destination (C)**
- **Intermediate (B)**

We aim to move **4 disks** from peg **A** to peg **C**, using peg **B** as an intermediate.

### **Recursive Breakdown**

#### **1st Call: `tower(A, C, B, 4)`**
- Move `n-1 = 3` disks from `A` to `B` using `C` as auxiliary.
- Move disk `4` from `A` to `C`.
- Move `n-1 = 3` disks from `B` to `C` using `A` as auxiliary.

#### **Breaking down `tower(A, B, C, 3)`**
- Move `n-1 = 2` disks from `A` to `C` using `B` as auxiliary.
- Move disk `3` from `A` to `B`.
- Move `n-1 = 2` disks from `C` to `B` using `A` as auxiliary.

#### **Breaking down `tower(A, C, B, 2)`**
- Move `n-1 = 1` disk from `A` to `B` using `C` as auxiliary.
- Move disk `2` from `A` to `C`.
- Move `n-1 = 1` disk from `B` to `C` using `A` as auxiliary.

#### **Breaking down `tower(A, B, C, 1)`**
- **Base case reached:** Move disk `1` from `A` to `B`.

### **Step-by-Step Moves**

| Step | Move Disk | From | To |
|------|-----------|------|----|
| 1 | 1 | A → B |
| 2 | 2 | A → C |
| 3 | 1 | B → C |
| 4 | 3 | A → B |
| 5 | 1 | C → A |
| 6 | 2 | C → B |
| 7 | 1 | A → B |
| 8 | 4 | A → C |
| 9 | 1 | B → C |
| 10 | 2 | B → A |
| 11 | 1 | C → A |
| 12 | 3 | B → C |
| 13 | 1 | A → B |
| 14 | 2 | A → C |
| 15 | 1 | B → C |

### **Final Output for `n = 4`**

```
Move disk 1 from needle A to needle B
Move disk 2 from needle A to needle C
Move disk 1 from needle B to needle C
Move disk 3 from needle A to needle B
Move disk 1 from needle C to needle A
Move disk 2 from needle C to needle B
Move disk 1 from needle A to needle B
Move disk 4 from needle A to needle C
Move disk 1 from needle B to needle C
Move disk 2 from needle B to needle A
Move disk 1 from needle C to needle A
Move disk 3 from needle B to needle C
Move disk 1 from needle A to needle B
Move disk 2 from needle A to needle C
Move disk 1 from needle B to needle C
```

### **Conclusion**
- **Total moves** = `(2ⁿ - 1) = 2⁴ - 1 = 15`.
- The recursive pattern follows a **divide-and-conquer** strategy:
  1. Move `n-1` disks to the auxiliary peg.
  2. Move the largest disk directly to the destination peg.
  3. Move the `n-1` disks from the auxiliary peg to the destination.

This Markdown file presents the **C++ program** along with a **detailed dry run** for easy understanding. 🚀

