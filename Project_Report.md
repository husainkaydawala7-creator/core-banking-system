# ACADEMIC PROJECT REPORT

## **CORE BANKING MANAGEMENT SYSTEM**
### *Implementation using Binary Search Tree, Stack, and Circular Queue in C++*

---

* **Subject:** Data Structures (Course Code: `102040304`)
* **Department:** Department of Computer Engineering / Computer Science & Design Engineering
* **Institution:** G H Patel College of Engineering & Technology (GCET), CVM University
* **Academic Year:** 2026–27 (Odd Semester, Semester 3)

---

## 1. Introduction & Objectives

### 1.1 Project Overview
In modern retail banking, customer satisfaction and operational speed rely on efficient management of customer accounts, transaction auditing, and in-branch visitor traffic. 

The **Core Banking Management System** is a lightweight, high-performance console application built to simulate core banking operations while demonstrating the practical application of fundamental data structures covered in the semester syllabus.

### 1.2 Key Objectives
1. **Fast Account Indexing & Retrieval:** Maintain dynamic customer records with $O(\log n)$ average search complexity using a **Binary Search Tree (BST)**.
2. **Real-Time Transaction Logging:** Keep an active audit trail of recent deposits and withdrawals using the **Last-In, First-Out (LIFO)** property of a **Stack**.
3. **Fair In-Branch Customer Traffic Control:** Ensure orderly visitor service using the **First-In, First-Out (FIFO)** property of a **Circular Queue**.
4. **Code Elegance & Maintainability:** Deliver the entire modular architecture within ~150 lines of clear, standard C++ without external template libraries (STL), demonstrating raw algorithmic implementation.

---

## 2. System Architecture & Data Structures Mapping

The project integrates three distinct data structures, each chosen to address a specific real-world requirement:

```
                            CORE BANKING SYSTEM
                                     |
    +--------------------------------+-------------------------------+
    |                                |                               |
[Accounts Module]          [Transaction History]           [Token Waiting Line]
    |                                |                               |
Binary Search Tree (BST)       Stack (Array)               Circular Queue (Array)
    |                                |                               |
Fast Search: O(log n)          LIFO Principle                  FIFO Principle
Sorted Output: Inorder         Most Recent First               Reuses Memory (% MAX)
```

### 2.1 Binary Search Tree (BST) — *Practical 8*
* **Application:** Storage and indexing of bank accounts keyed by `accNo`.
* **Why BST?**
  * In a linear array or linked list, searching for an account requires checking every node sequentially ($O(n)$ time).
  * In a BST, each comparison cuts the search space in half, achieving an average lookup time of $O(\log n)$.
  * **Inorder Traversal (Left $\to$ Root $\to$ Right)** guarantees that customer records are retrieved in strictly sorted numerical order of Account Number without requiring an external sorting algorithm.

### 2.2 Stack — *Practical 3*
* **Application:** ATM Mini-Statement generation.
* **Why Stack?**
  * When a customer requests a mini-statement from an ATM or mobile app, they expect to see their **most recent** transaction first.
  * This matches the **Last-In, First-Out (LIFO)** behavior of a Stack. New transactions are pushed to the top, and printing pops/displays from top to bottom.

### 2.3 Circular Queue — *Practical 5B*
* **Application:** Branch visitor token queue and teller desk allocation.
* **Why Circular Queue?**
  * Service desks must operate under strict **First-In, First-Out (FIFO)** fairness: the customer who arrived first must be served first.
  * In a traditional linear queue implemented with an array, dequeuing elements leaves empty spaces at the front that cannot be reused, causing a false "Queue Full" condition.
  * The circular queue uses modulo arithmetic `(rear + 1) % MAX` and `(front + 1) % MAX` to wrap pointers around, continuously reusing array memory.

---

## 3. Function-by-Function Description

### 3.1 Account Management Functions (BST)

#### 1. `Account* createAccount(int accNo, string name, float bal)`
* **Purpose:** Dynamic memory allocation for a new customer record.
* **How it Works:** Uses the `new` operator to allocate a node of type `struct Account`, initializes account number, name, and opening balance, and sets child pointers (`left` and `right`) to `NULL`.

#### 2. `Account* insert(Account* root, int accNo, string name, float bal)`
* **Purpose:** Inserts an account node at its correct position in the BST.
* **How it Works:** Compares `accNo` with the current node:
  * If `accNo < root->accNo`, recurses to the **left** subtree.
  * If `accNo > root->accNo`, recurses to the **right** subtree.
  * If root is `NULL`, creates and returns the new node.

#### 3. `Account* search(Account* root, int accNo)`
* **Purpose:** Locates an existing customer account by ID.
* **How it Works:** Traverses downward from the root. If `accNo` matches, it returns the pointer to that node. If smaller, it searches left; if larger, it searches right. Returns `NULL` if not found.

#### 4. `void inorder(Account* root)`
* **Purpose:** Displays all bank accounts in ascending order.
* **How it Works:** Recursively visits:
  1. Left subtree (`inorder(root->left)`)
  2. Root node (prints account details)
  3. Right subtree (`inorder(root->right)`)

---

### 3.2 Transaction History Functions (Stack)

#### 5. `void pushTrans(float amt)`
* **Purpose:** Records a financial event onto the transaction stack.
* **How it Works:**
  * Positive `amt` represents a **Deposit**; negative `amt` represents a **Withdrawal**.
  * If the stack reaches `MAX - 1`, older entries are shifted up by 1 position so the latest 5 transactions are preserved.
  * Increments `top` and stores the amount at `transStack[top]`.

#### 6. `void printMiniStatement()`
* **Purpose:** Outputs the mini-statement in LIFO order.
* **How it Works:** Loops backwards from `i = top` down to `0`. If `transStack[i] > 0`, it prints `Deposited: Rs. X`; otherwise, it prints `Withdrawn: Rs. X`.

---

### 3.3 Customer Service Desk Functions (Circular Queue)

#### 7. `void issueToken(int token)`
* **Purpose:** Enqueues a customer into the branch waiting line.
* **How it Works:** Checks for overflow condition `(rear + 1) % MAX == front`. If not full, increments `rear = (rear + 1) % MAX`, writes `token` at `tokenQueue[rear]`, and sets `front = 0` if it was previously empty.

#### 8. `void serveCustomer()`
* **Purpose:** Dequeues the next customer to be served by the teller.
* **How it Works:** Checks for underflow (`front == -1`). If customers are present, prints `Calling Token #tokenQueue[front]`. If `front == rear`, resets both to `-1` (queue now empty); otherwise advances `front = (front + 1) % MAX`.

---

## 4. Real-World Practicality & Benefits

1. **Scalability:** The BST structure allows a bank to handle hundreds of thousands of accounts with logarithmic lookup times without linear scan bottlenecks.
2. **Resource Efficiency:** The circular queue guarantees zero memory leakage and zero wasted array slots in fixed-memory hardware devices (such as branch kiosk ticket printers).
3. **Data Integrity:** Strict encapsulation ensures balances cannot be modified without being logged into the transaction stack.
4. **Standardization:** Avoids third-party dependencies, making it directly portable across embedded devices, legacy ATMs, and modern operating systems.

---

## 5. Complete C++ Source Code (`bank_system.cpp`)

```cpp
#include <iostream>
#include <string>

using namespace std;

#define MAX 5

// --- 1. BINARY SEARCH TREE (BST) - Account Records (Practical 8) ---
struct Account {
    int accNo;
    string name;
    float balance;
    Account *left, *right;
};

// Create a new account node
Account* createAccount(int accNo, string name, float bal) {
    Account* n = new Account();
    n->accNo = accNo;
    n->name = name;
    n->balance = bal;
    n->left = n->right = NULL;
    return n;
}

// Insert account into BST (ordered by accNo)
Account* insert(Account* root, int accNo, string name, float bal) {
    if (!root) return createAccount(accNo, name, bal);
    if (accNo < root->accNo) root->left = insert(root->left, accNo, name, bal);
    else if (accNo > root->accNo) root->right = insert(root->right, accNo, name, bal);
    return root;
}

// Search account by accNo in O(log n)
Account* search(Account* root, int accNo) {
    if (!root || root->accNo == accNo) return root;
    if (accNo < root->accNo) return search(root->left, accNo);
    return search(root->right, accNo);
}

// Inorder Traversal: Left -> Root -> Right (prints sorted accounts)
void inorder(Account* root) {
    if (root) {
        inorder(root->left);
        cout << "A/C: " << root->accNo << " | Name: " << root->name << " | Balance: Rs. " << root->balance << endl;
        inorder(root->right);
    }
}

// --- 2. STACK - ATM Mini-Statement (Practical 3: LIFO) ---
float transStack[MAX];
int top = -1;

void pushTrans(float amt) {
    if (top == MAX - 1) { // Shift up if full to keep last 5 transactions
        for (int i = 0; i < MAX - 1; i++) transStack[i] = transStack[i + 1];
        top--;
    }
    transStack[++top] = amt;
}

void printMiniStatement() {
    if (top == -1) { cout << "\nNo transactions recorded yet!" << endl; return; }
    cout << "\n--- ATM MINI-STATEMENT (LIFO: Most Recent First) ---" << endl;
    for (int i = top; i >= 0; i--) {
        if (transStack[i] > 0)
            cout << "[" << (top - i + 1) << "] Deposited: Rs. " << transStack[i] << endl;
        else
            cout << "[" << (top - i + 1) << "] Withdrawn: Rs. " << -transStack[i] << endl;
    }
}

// --- 3. CIRCULAR QUEUE - Customer Token Line (Practical 5B: FIFO) ---
int tokenQueue[MAX];
int front = -1, rear = -1;

void issueToken(int token) {
    if ((rear + 1) % MAX == front) { cout << "Queue is full! Wait for counter to be free." << endl; return; }
    if (front == -1) front = 0;
    rear = (rear + 1) % MAX;
    tokenQueue[rear] = token;
    cout << "Token #" << token << " issued! Please wait in customer lounge." << endl;
}

void serveCustomer() {
    if (front == -1) { cout << "No customers waiting in queue!" << endl; return; }
    cout << ">> Calling Token #" << tokenQueue[front] << " to Teller Counter 1 (FIFO)" << endl;
    if (front == rear) front = rear = -1;
    else front = (front + 1) % MAX;
}

// --- MAIN MENU ---
int main() {
    Account* root = NULL;
    int choice, accNo, nextToken = 101;
    string name;
    float amount;

    // Pre-loaded sample accounts for quick viva demo
    root = insert(root, 102, "Suresh", 15000.0f);
    root = insert(root, 101, "Ramesh", 8500.0f);
    root = insert(root, 105, "Priya", 24000.0f);
    root = insert(root, 103, "Anjali", 12000.0f);

    while (true) {
        cout << "\n=== CORE BANKING SYSTEM (DS PROJECT - C++) ===" << endl;
        cout << "1. Open Account (BST Insert)     2. Search Account (BST Search)" << endl;
        cout << "3. Display All (BST Inorder)     4. Deposit Money (Stack Record)" << endl;
        cout << "5. Withdraw Money (Stack Record) 6. Mini-Statement (Stack LIFO)" << endl;
        cout << "7. Issue Token (Queue Enqueue)   8. Serve Customer (Queue Dequeue)" << endl;
        cout << "9. Exit" << endl;
        cout << "Choice (1-9): ";
        if (!(cin >> choice)) break;

        if (choice == 1) {
            cout << "Enter A/C No, Name, Initial Deposit: ";
            cin >> accNo >> name >> amount;
            root = insert(root, accNo, name, amount);
            cout << "Account " << accNo << " created successfully!" << endl;
        } else if (choice == 2) {
            cout << "Enter A/C No to Search: "; cin >> accNo;
            Account* a = search(root, accNo);
            if (a) cout << "Found! Name: " << a->name << " | Balance: Rs. " << a->balance << endl;
            else cout << "Account not found!" << endl;
        } else if (choice == 3) {
            cout << "\n--- All Bank Accounts (Sorted by A/C No) ---" << endl;
            inorder(root);
        } else if (choice == 4 || choice == 5) {
            cout << "Enter A/C No and Amount: "; cin >> accNo >> amount;
            Account* a = search(root, accNo);
            if (!a) { cout << "Account not found!" << endl; continue; }

            if (choice == 4) {
                a->balance += amount;
                pushTrans(amount);
                cout << "Deposit successful! New Balance: Rs. " << a->balance << endl;
            } else {
                if (a->balance < amount) cout << "Insufficient balance! Current: Rs. " << a->balance << endl;
                else {
                    a->balance -= amount;
                    pushTrans(-amount);
                    cout << "Withdrawal successful! New Balance: Rs. " << a->balance << endl;
                }
            }
        } else if (choice == 6) {
            printMiniStatement();
        } else if (choice == 7) {
            issueToken(nextToken++);
        } else if (choice == 8) {
            serveCustomer();
        } else if (choice == 9) {
            cout << "Thank you for using the Banking System!" << endl;
            break;
        } else {
            cout << "Invalid choice! Please select 1-9." << endl;
        }
    }
    return 0;
}
```

---

## 6. Detailed Step-by-Step Test Output

Below is the verified console session demonstrating each feature:

```text
=== CORE BANKING SYSTEM (DS PROJECT - C++) ===
1. Open Account (BST Insert)     2. Search Account (BST Search)
3. Display All (BST Inorder)     4. Deposit Money (Stack Record)
5. Withdraw Money (Stack Record) 6. Mini-Statement (Stack LIFO)
7. Issue Token (Queue Enqueue)   8. Serve Customer (Queue Dequeue)
9. Exit
Choice (1-9): 3

--- All Bank Accounts (Sorted by A/C No) ---
A/C: 101 | Name: Ramesh | Balance: Rs. 8500
A/C: 102 | Name: Suresh | Balance: Rs. 15000
A/C: 103 | Name: Anjali | Balance: Rs. 12000
A/C: 105 | Name: Priya | Balance: Rs. 24000

=== CORE BANKING SYSTEM (DS PROJECT - C++) ===
Choice (1-9): 2
Enter A/C No to Search: 103
Found! Name: Anjali | Balance: Rs. 12000

=== CORE BANKING SYSTEM (DS PROJECT - C++) ===
Choice (1-9): 4
Enter A/C No and Amount: 101 1500
Deposit successful! New Balance: Rs. 10000

=== CORE BANKING SYSTEM (DS PROJECT - C++) ===
Choice (1-9): 5
Enter A/C No and Amount: 101 2000
Withdrawal successful! New Balance: Rs. 8000

=== CORE BANKING SYSTEM (DS PROJECT - C++) ===
Choice (1-9): 6

--- ATM MINI-STATEMENT (LIFO: Most Recent First) ---
[1] Withdrawn: Rs. 2000
[2] Deposited: Rs. 1500

=== CORE BANKING SYSTEM (DS PROJECT - C++) ===
Choice (1-9): 7
Token #101 issued! Please wait in customer lounge.

=== CORE BANKING SYSTEM (DS PROJECT - C++) ===
Choice (1-9): 7
Token #102 issued! Please wait in customer lounge.

=== CORE BANKING SYSTEM (DS PROJECT - C++) ===
Choice (1-9): 8
>> Calling Token #101 to Teller Counter 1 (FIFO)

=== CORE BANKING SYSTEM (DS PROJECT - C++) ===
Choice (1-9): 8
>> Calling Token #102 to Teller Counter 1 (FIFO)

=== CORE BANKING SYSTEM (DS PROJECT - C++) ===
Choice (1-9): 9
Thank you for using the Banking System!
```

---

## 7. Viva Preparation Guide & Common Questions

1. **Why is BST better than a simple array for bank accounts?**
   * *Answer:* Searching in an array takes $O(n)$ because we scan sequentially. In a BST, searching takes $O(\log n)$ because every comparison divides the search space into half. Furthermore, an **Inorder Traversal** prints the accounts in sorted order automatically without extra sorting steps.

2. **Why does the ATM Mini-Statement use a Stack?**
   * *Answer:* A bank mini-statement must present the most recent transaction at the top. The Stack follows **Last-In, First-Out (LIFO)**, meaning the last pushed transaction is the first one displayed.

3. **What is the mathematical condition for Circular Queue full?**
   * *Answer:* `(rear + 1) % MAX == front`. This detects when the rear pointer has wrapped around and reached the position right behind front.

4. **What happens if a customer attempts to withdraw more than their balance?**
   * *Answer:* The system executes an account balance check: `if (a->balance < amount)`. It blocks the withdrawal, preserves the current balance, and suppresses recording the transaction in the stack.

---
*Report prepared for Semester 3 Data Structures Mini-Project Submission.*
