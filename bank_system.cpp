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
    cout << "\n--- ATM MINI-STATEMENT ---" << endl;
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

    // Pre-loaded sample accounts 
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
