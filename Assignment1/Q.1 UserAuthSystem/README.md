# User Authentication System (C++)

##  Overview
This is a **User Authentication and Profile Management System** implemented in **C++**, featuring:
- **User Registration & Login**
- **Profile Management (Read & Overwrite)**
- **File Handling (storing users & profiles)**
- **Robust Input Validation (prevents crashes)**
- **User-Friendly Menus with "Go Back" Options**

---

##  Features
 **Register a New User**
- Users provide a **unique username** and **numeric password** (10000-65000).
- After registration, users create their **profile**.

 **Login System**
- Users log in with their **username & password**.
- If credentials are incorrect, they can **retry or register**.

 **Profile Management**
- Users can **read** or **overwrite** their profile after logging in.

 **Data Storage**
- **Users & passwords** are stored in `users.txt`.
- **User profiles** are saved in `username.txt` (e.g., `sajid.txt`).

 **Input Validation**
- Prevents **program crashes** by ensuring numeric input for **menus, passwords, and ages**.

 **Navigation & Go Back Options**
- Users can **return to the main menu** instead of being forced to exit.

---

##  File Structure
```
/UserAuthSystem
│── main.cpp        # C++ source code
│── users.txt       # Stores usernames & passwords
│── [username].txt  # Stores user profiles (e.g., sajid.txt)
│── README.md       # Documentation
```

---

##  Installation & Setup
### **1️ Compile the Program**
Open **VS Code terminal** (or command prompt) and run:
```sh
g++ main.cpp -o user_auth_system
```

### **2️ Run the Program**
```sh
./user_auth_system
```
---

## 🎮 How to Use
### **Main Menu**
```
--- User Authentication System ---
1. Login
2. Register
3. Exit
Enter choice: 
```
 **Enter `1` to Login**  
 **Enter `2` to Register**  
 **Enter `3` to Exit**  

---

### **Registration Flow**
1. Enter a **unique username**.
2. Enter a **numeric password** (10000-65000).
3. Provide profile details (Full Name, Age, DOB, etc.).
4. **Profile is saved & user is registered!**

🔹 **Go Back Option**: Enter `4` to return to the main menu.

---

### **Login Flow**
1. Enter **username & password**.
2. If correct, choose:
   ```
   1. Read Your Profile
   2. Overwrite Your Profile
   3. Go Back
   ```
3. **Go back to main menu anytime!**  
4. If **login fails**, choose to **retry or register**.

---

##  Example Usage
### ** Successful Registration**
```
Enter a Username to start registration (or type 4 to return): sajid
Enter a numeric password (10000-65000): 12345
User registered successfully!

Enter Full Name: Sajid Khan
Enter Father's Name: XYZ Khan
Enter Age: 22
Enter Date of Birth (DD-MM-YYYY): 12-05-2003
Enter Class Name: BSCS
Enter Registration No: 123456
Profile created successfully!
```

### ** Successful Login**
```
Enter Username (or type 4 to return): sajid
Enter password: 12345
Login successful!

1. Read Your Profile
2. Overwrite Your Profile
3. Go Back
Enter choice: 1
```

### ** Invalid Login**
```
Enter Username (or type 4 to return): unknown
Enter password: 54321
Invalid credentials. Try again or register first.
Would you like to register instead? (1 for Yes, 2 for No): 1
```

---

##  Notes
- User credentials are stored in **plain text** (`users.txt`).
- Each user has a separate **profile file** (`username.txt`).
- The program **prevents crashes** by ensuring valid numeric inputs.
- `"Go Back"` options allow **smooth navigation** between menus.

---

##  Future Improvements (Optional)
-  **Encrypt passwords** instead of storing them in plain text.
-  **Store user data in a database** instead of text files.
-  **Create a GUI version** using C++ frameworks.

---

##  License
This project is **free to use** for learning purposes.

---

## 👨 Author
**Sajidullah Khan**
**4995-FOC/BSCS/F23-B**  
 **International Islamic University Islamabad**  
```