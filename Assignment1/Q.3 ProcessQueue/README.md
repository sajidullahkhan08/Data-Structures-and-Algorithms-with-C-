# Process Queue Management (C++)

## 📌 Overview
This project implements a **Priority-Based Process Queue** using a **Doubly Linked List** in **C++**.  
Processes are **ordered by priority** (higher priority dequeues first), and if priorities are equal, **FIFO (First In, First Out) order is maintained**.  
The program also supports **file handling** to store and retrieve process data from `process.txt`.

---

## 🚀 Features
✅ **Priority Queue using a Doubly Linked List**  
✅ **Higher priority processes are dequeued first**  
✅ **FIFO order for processes with the same priority**  
✅ **File Handling for Data Persistence (`process.txt`)**  
✅ **User Menu to Manage the Process Queue**  
✅ **Processes can be Enqueued, Dequeued, and Displayed**  

---

## 📂 File Structure
```
/ProcessQueue
│── process.txt    # Stores process data (saved between runs)
│── main.cpp       # Full implementation (queue operations + menu)
│── README.md      # Documentation
```

---

## 🛠️ How to Compile & Run
### **1️⃣ Compile the Program**
```sh
g++ main.cpp -o process_manager
```

### **2️⃣ Run the Program**
```sh
./process_manager
```

---

## 🎮 How It Works
### **Main Menu**
```
--- Process Queue Management ---
1. Enqueue Process
2. Dequeue Process
3. Display Queue
4. Save & Exit
Enter choice: 
```
✅ **Enter `1` to add a new process**  
✅ **Enter `2` to remove the highest-priority process**  
✅ **Enter `3` to view the current queue**  
✅ **Enter `4` to save and exit the program**  

---

## 📜 Example Input & Output
### **📄 Example `process.txt` (Initial Data)**
```
101 3 1
102 2 2
103 1 3
104 3 4
105 2 5
```

### **🖥️ Running the Program**
```
--- Process Queue Management ---
1. Enqueue Process
2. Dequeue Process
3. Display Queue
4. Save & Exit
Enter choice: 3
```

### **📜 Expected Output**
```
Current Process Queue:
PID     Priority    Arrival Time
101     3          1
104     3          4
102     2          2
105     2          5
103     1          3
```

---

## 📌 Notes
- **Priority Queue Logic**:  
  - **Higher priority processes** are dequeued first.  
  - **If priorities are equal**, the **earliest arrival process** dequeues first (FIFO).  
- **File Handling (`process.txt`)**:  
  - Queue data is **stored and loaded** automatically.  
  - Ensures **data persistence** between program runs.  
- **Implemented using a Doubly Linked List** for **efficient insertion & deletion**.  

---

## 📜 License
This project is **free to use** for learning purposes.

---

## 👨‍💻 Author
**Sajidullah Khan**
**4995-FOC/BSCS/F23-B**  
📍 **International Islamic University Islamabad**  
```