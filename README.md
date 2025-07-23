# 🧑‍💼 Employee Data Management System

This is a simple **Employee Data Management System** written in C that allows users to manage employee records including adding, editing, deleting, and viewing details using binary file operations.

---

## 🚀 Features

- **Add Employee**: Insert new employee records with ID, name, designation, and salary.
- **Delete Employee**: Remove an employee record based on ID.
- **Edit Employee**: Modify an existing employee's information.
- **Display by ID**: Search and display details of an employee using their ID.
- **Display All**: View all stored employee records.
- **Persistent Storage**: Stores data in a binary file (`employee_data.dat`).

---

## 📁 File Structure

- `employee_data.dat`: Binary file used to store employee records persistently.
- `temp.txt`: Temporary file used during deletion to reconstruct the database.

---

## 🧰 Requirements

- C compiler (e.g., GCC)
- Command line terminal (Linux / Windows)

---

## ▶️ How to Run

1. Compile the program:
   ```bash
   gcc employee_management.c -o employee_management
