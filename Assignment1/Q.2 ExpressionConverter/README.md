# Expression Conversion System (C++)

##  Overview
This project implements **mathematical expression conversions** between **Infix, Postfix, and Prefix** using **Stacks (Singly Linked List & Templates)**.  
Each conversion is handled in a **separate C++ file** for modularity and easier debugging.  

---

##  Features
 **Infix to Postfix (`infix_to_postfix.cpp`)**  
 **Postfix to Infix (`postfix_to_infix.cpp`)**  
 **Infix to Prefix (`infix_to_prefix.cpp`)**  
 **Prefix to Infix (`prefix_to_infix.cpp`)**  
 **Stack Implemented as a Singly Linked List (`stack.h`)**  
 **File Handling for Expression Input/Output**  

---

##  File Structure
```
/ExpressionConverter
│── infix.txt         # Input: Infix expression
│── postfix.txt       # Output: Postfix expression
│── infix1.txt        # Output: Postfix → Infix conversion
│── prefix.txt        # Output: Prefix expression
│── infix2.txt        # Output: Prefix → Infix conversion
│── infix_to_postfix.cpp   # Part (a) - Infix → Postfix
│── postfix_to_infix.cpp   # Part (b) - Postfix → Infix
│── infix_to_prefix.cpp    # Part (c) - Infix → Prefix
│── prefix_to_infix.cpp    # Part (d) - Prefix → Infix
│── stack.h          # Stack implementation (shared)
│── README.md        # Documentation
```

---

##  How to Compile & Run
Each conversion has **its own separate program**.  
To compile and run each file:

### **1️ Infix to Postfix**
```sh
g++ infix_to_postfix.cpp -o infix_to_postfix
./infix_to_postfix
```

### **2 Postfix to Infix**
```sh
g++ postfix_to_infix.cpp -o postfix_to_infix
./postfix_to_infix
```

### **3️ Infix to Prefix**
```sh
g++ infix_to_prefix.cpp -o infix_to_prefix
./infix_to_prefix
```

### **4️ Prefix to Infix**
```sh
g++ prefix_to_infix.cpp -o prefix_to_infix
./prefix_to_infix
```

---

##  How It Works
1️⃣ **Add an infix expression** to `infix.txt`.  
2️⃣ **Run `infix_to_postfix`** → Converts and stores in `postfix.txt`.  
3️⃣ **Run `postfix_to_infix`** → Converts back to infix and stores in `infix1.txt`.  
4️⃣ **Run `infix_to_prefix`** → Converts and stores in `prefix.txt`.  
5️⃣ **Run `prefix_to_infix`** → Converts back to infix and stores in `infix2.txt`.  

---

##  Example Input & Output
### ** Input (`infix.txt`)**
```
(A+B)*(C-D)
```

### ** Expected Outputs**
| Conversion  | Output |
|------------|------------|
| **Postfix (`postfix.txt`)** | `AB+CD-*` |
| **Postfix → Infix (`infix1.txt`)** | `(A+B)*(C-D)` |
| **Prefix (`prefix.txt`)** | `*+AB-CD` |
| **Prefix → Infix (`infix2.txt`)** | `(A+B)*(C-D)` |

---

##  Notes
- The **stack is implemented using a singly linked list** (`stack.h`).  
- **Each file handles a specific conversion task separately**.  
- **File handling is used** for input/output.  

---

##  License
This project is **free to use** for educational purposes.

---

##  Author
**Sajidullah Khan**
**4995-FOC/BSCS/F23-B**
 **International Islamic University Islamabad**  
```
