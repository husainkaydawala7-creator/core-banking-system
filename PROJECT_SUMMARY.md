# 📋 Project Executive Summary

## **Core Banking Management System**
*An Algorithmic Simulation of Retail Banking Operations using Core Data Structures in C++*

---

## 🎯 Executive Overview
The **Core Banking Management System** is an engineering project developed for the **Semester 3 Data Structures Laboratory (Course Code: `102040304`)** at **G H Patel College of Engineering & Technology (GCET), CVM University**. 

The goal of the project is to build an interactive, production-style banking terminal that models the real-world operational workflows of a retail bank branch—including account management, financial transaction auditing, and in-branch visitor queueing—using raw algorithmic implementations of classic data structures without relying on C++ Standard Template Library (STL) containers.

---

## 🏛️ Core Architectural Components & Mapping

```
                                 CORE BANKING SYSTEM
                                          │
         ┌────────────────────────────────┼───────────────────────────────┐
         ▼                                ▼                               ▼
   ACCOUNT DATABASE               TRANSACTION AUDIT               CUSTOMER SERVICE
  [Binary Search Tree]             [Bounded Stack]                [Circular Queue]
         │                                │                               │
  • O(log n) Search                • LIFO Mini-Statement           • FIFO Fairness
  • Left < Root < Right            • Most Recent First             • Pointer Wrap: % MAX
  • Inorder = Sorted Output        • Max 5 Active Records          • Zero Memory Leakage
```

---

## ⚙️ Data Structures & Complexity Analysis

| Subsystem | Data Structure | Principle | Operation | Time Complexity | Space Complexity |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Accounts Catalog** | Binary Search Tree (BST) | Hierarchical Node Partitioning | `insert()` | $O(\log n)$ avg, $O(n)$ worst | $O(1)$ auxiliary per node |
| | | | `search()` | $O(\log n)$ avg, $O(n)$ worst | $O(1)$ auxiliary |
| | | | `inorder()` | $O(n)$ | $O(h)$ recursion stack |
| **ATM Mini-Statement** | Linear Array Stack | Last-In, First-Out (LIFO) | `pushTrans()` | $O(1)$ amortized | $O(\text{MAX})$ |
| | | | `printMiniStatement()` | $O(k)$ where $k \le \text{MAX}$ | $O(1)$ |
| **Teller Token Counter** | Array-based Circular Queue | First-In, First-Out (FIFO) | `issueToken()` | $O(1)$ | $O(\text{MAX})$ |
| | | | `serveCustomer()` | $O(1)$ | $O(1)$ |

---

## 🛡️ Business Logic & Safety Mechanisms

1. **Overdraft Protection Guard:**
   * Before approving any debit request, the system verifies `if (a->balance < amount)`. If the withdrawal exceeds available funds, the transaction is rejected, the balance remains unmodified, and the event is barred from the audit stack.
2. **Circular Memory Optimization:**
   * Unlike basic linear queues where dequeuing creates inaccessible dead space at the front of the array, the circular queue leverages modulo arithmetic `(rear + 1) % MAX` to wrap around, guaranteeing 100% array utilization.
3. **Sliding Window Transaction Audit:**
   * The transaction stack maintains a rolling window of the last 5 transactions. When capacity is reached, earlier entries shift upwards by 1 index, ensuring the most recent financial activities remain visible on the customer's ATM slip.
4. **Automated Directory Sorting:**
   * Leveraging BST's **Inorder Traversal** (`Left -> Root -> Right`) eliminates the need for expensive secondary sorting passes (such as QuickSort or MergeSort), yielding an alphabetical/numerical account register naturally in $O(n)$ time.

---

## 📊 Practical Mapping to Syllabus

This project directly demonstrates and unifies practical exercises from the Data Structures Curriculum:
- **Practical 8:** Binary Search Tree Construction & Traversals (Inorder, Search, Insert)
- **Practical 3:** Stack Implementation & LIFO Demonstration
- **Practical 5B:** Circular Queue Implementation using Modulo Arithmetic
- **Practical 1 & 2:** Pointer Manipulation, Dynamic Memory Allocation (`new`/`delete`), and Struct Pointers

---

## 📂 Deliverables in this Repository

| File | Description |
| :--- | :--- |
| **[`bank_system.cpp`](bank_system.cpp)** | Fully functional, self-contained C++ source code (~155 lines) with zero external dependencies. |
| **[`Project_Report.pdf`](Project_Report.pdf)** | 10-page academic report complete with title page, system design, code walkthrough, test runs, and viva cheat sheet. |
| **[`Project_Report.md`](Project_Report.md)** | Full markdown documentation ready for reading on GitHub or conversion to other document formats. |
| **[`README.md`](README.md)** | Main repository landing page with visual badges, architecture diagrams, and quick-start instructions. |
| **[`LICENSE`](LICENSE)** | Official Apache License 2.0 open-source grant. |

---

## 🎓 Academic Metadata
* **Student:** Husain Kaydawala
* **Branch:** Computer Science & Design Engineering / Computer Engineering
* **Course:** Data Structures (`102040304`)
* **Semester:** 3 (Odd Semester 2026–27)
* **College:** G H Patel College of Engineering & Technology (GCET), CVM University
