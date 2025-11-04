📚 C++ Library Management System (LMS)
A robust and scalable application built using object-oriented C++ to manage a library's catalog of books and journals, demonstrating key OOP principles, memory management, and file I/O.
✨ Features
This project was specifically designed to demonstrate mastery over the following advanced C++ concepts:
 * Polymorphism: Managing different item types (Book, Journal) via a single base class pointer.
 * Abstract Classes: Using a pure virtual function (calculateFine) in the base class to enforce implementation.
 * Dynamic Memory Management: Proper use of new, delete, constructors, and destructors to prevent memory leaks.
 * Operator Overloading: Custom comparison logic for library items.
 * Persistent Data Storage: Using file handling (fstream) to save and load the entire catalog.
 * Robust Error Handling: Implementing try/catch blocks for exceptions like ItemNotFound.

🚀 How to Run the Project
Prerequisites
You need a C++ compiler installed (e.g., GCC or Clang) that supports C++11 standards or newer.
Compilation
Use your preferred compiler to compile the source file (assuming the main file is named lms.cpp):
g++ lms.cpp -o lms

Execution
Run the compiled executable:
./lms

The program will demonstrate adding items, saving the catalog to catalog.txt, loading the data back, and triggering an exception.
📁 Code Structure Highlights
The core functionality resides in the following areas:
 * LibraryItem (Base Class): Contains protected common data members and a pure virtual function calculateFine().
 * Book and Journal (Derived Classes): Implement the abstract base methods and contain specific data (e.g., isbn, issueNumber).
 * main() function: Orchestrates the demonstration, including the use of dynamic memory allocation and the file handling logic to persist data.
🤝 Contribution
This project is a personal demonstration of advanced C++ concepts. While general contributions aren't expected, feel free to fork the repository to adapt the concepts to a different system (e.g., Inventory Management).
Would you like me to generate a simple license file (LICENSE.md) or a basic .gitignore file for this repository?
