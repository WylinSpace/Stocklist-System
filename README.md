# Inventory and Item Management System

## Contributors:
Code and designed by **LIEW WEN HAO**, with multiples references taken. Including books such as: "Starting Out with C++ Early Objects 7th Edition by Tony Gaddis"

## Introduction

The **Inventory and Item Management System** is designed to streamline the management of various items, track their availability, and handle user interactions such as borrowing and returning items. The system features both user-level and admin-level operations to provide a comprehensive solution for inventory control, overdue fine calculation, and reporting. This project was developed in **C++** and relies on **CSV** files for persistent storage, allowing users to log in, manage items, and track overdue fines efficiently. The system provides an easy-to-use command-line interface, and it can be extended with more advanced features such as a graphical user interface (GUI) or integration with a database.

*****

## Features

### 1. **User Authentication**
   - **How It Works**: 
     - Users log in by entering their email and password. The system checks these credentials against the `user.csv` or `admin.csv` file.
     - The system supports two types of users:
       - **Regular Users**: These users can borrow and return items and see their overdue fines.
       - **Admins**: Admin users have additional privileges, such as adding items, updating quantities, and managing purchase requests.
     - **Example**:
       - User `wen.wylin@student.usm.my` enters their credentials. The system checks if the email and password match the `user.csv` file. If successful, the user gains access to borrow or return items.

### 2. **Item Borrowing and Returning**
   - **How It Works**: 
     - When a user borrows an item, the system checks if the item is available by reviewing its quantity in the `item.csv` file.
     - On returning the item, the system updates the item quantity and calculates any overdue fines if the return is late.
     - **Example**:
       - User borrows `Resistor` from the inventory, and the system checks if the quantity is greater than 0. After borrowing, the quantity is updated in the `item.csv` file (e.g., from 100 to 99).
       - The user returns the `Resistor` late, and the system calculates a fine based on the overdue days.

### 3. **Overdue Fine Calculation**
   - **How It Works**: 
     - The system calculates fines for overdue items based on the number of overdue days.
     - A fixed fine rate is applied (e.g., RM 2 per day) to calculate overdue charges.
     - **Example**:
       - If a user returns an item 5 days late, the fine will be `5 days * RM 2 = RM 10`.
       - The fine is stored and updated in the system for later reporting.

### 4. **Admin Controls**
   - **How It Works**: 
     - Admins have the ability to manage the system by adding new items, updating quantities, and managing user data.
     - Admins can also approve and manage purchase requests from users.
     - **Example**:
       - Admin can add a new item `Breadboard` with a quantity of 50 into the system by updating the `item.csv` file.

### 5. **Reporting**
   - **How It Works**: 
     - The system tracks overdue items and fines, generating reports that can be accessed by the admin.
     - **Example**:
       - A report is generated showing the list of overdue items and the associated fines, which is saved in the `overDueList.csv` file.

*****

## How It Works

1. **User Login**: 
   - When a user enters their email and password, the system checks the `user.csv` or `admin.csv` file for a matching entry.
   - If the credentials are valid, the user is logged in and can proceed with borrowing or returning items.
   
2. **Item Borrowing**: 
   - After logging in, the user selects an item to borrow. The system checks if the item is available (i.e., its quantity is greater than 0).
   - If available, the system updates the item's quantity in the inventory.
   - **Example**: 
     - If the user borrows a `Resistor`, and the current quantity is 100, the system updates the quantity to 99.

3. **Item Returning**: 
   - When returning an item, the user must specify the date it was returned.
   - The system checks if the return date exceeds the due date and calculates overdue fines accordingly.
   - **Example**: 
     - If the return is 7 days late, and the fine is RM 2 per day, the system calculates the fine as `RM 14`.

4. **Admin Actions**: 
   - Admins can add new items, update quantities, and view reports of overdue fines and items.
   - **Example**: 
     - Admin adds `Multimeter` to the inventory with a starting quantity of 150.

5. **Overdue Fine Calculation**: 
   - The system calculates overdue fines by multiplying the number of overdue days by the fine rate.
   - **Example**: 
     - If the overdue fine rate is RM 2 per day, and a user returns an item 5 days late, the fine would be `5 * RM 2 = RM 10`.

*****

## Advantages

- **Simplicity**: The system provides an easy-to-understand interface with basic functionality to manage items and track overdue fines.
- **Modularity**: The code is organized into separate modules for user management, item management, borrowing/returning, and reporting, which makes the system easy to maintain and extend.
- **Efficient File Handling**: Uses CSV files to store data, which are easily editable and portable. It's suitable for small to medium-sized data storage.
- **Low System Requirements**: The system runs in a command-line interface, which doesn't require a GUI or heavy resources, making it suitable for low-resource environments.
  
*****

## Disadvantages

- **Limited Scalability**: The use of CSV files for data storage is not scalable for larger applications. As the number of users and items grows, the system may experience performance issues.
- **Lack of GUI**: A command-line interface may not be user-friendly for non-technical users. A GUI would make the system more accessible.
- **Manual Data Management**: Admins need to manually edit CSV files to update items or users, which could lead to errors. A database-based solution would be more efficient.
  
*****

## Future Improvements

- **Database Integration**: Moving from CSV files to a relational database (e.g., MySQL or SQLite) to improve data management, scalability, and performance.
- **GUI Development**: Developing a graphical user interface to make the system more accessible to non-technical users.
- **Automated Notification System**: Adding a feature to automatically send notifications (via email or SMS) to users when their items are due or overdue.
- **Advanced Reporting**: Implementing more advanced reporting features, such as tracking item usage patterns, generating periodic reports, and calculating average overdue fines.
- **Security Enhancements**: Storing user passwords securely (e.g., by hashing) to prevent unauthorized access.

*****

## Conclusion

This **Inventory and Item Management System** provides a basic but functional solution for tracking items, managing user interactions, and calculating overdue fines. While it is simple and easy to use, there are several opportunities for improvement in terms of scalability, user interface, and security. By implementing features such as database integration and a graphical interface, this system can be expanded into a more robust solution for managing large inventories in an efficient and user-friendly manner.

*****

## To Know:

Please include the snippets at follow to make sure every file is compiled:

Snippets-A :
"args": [
                "-fdiagnostics-color=always",
                "-g",
                "main.cpp",
                "cppFiles/admin.cpp",
                "cppFiles/borrow.cpp",
                "cppFiles/textstyle.cpp",
                "cppFiles/item.cpp",
                "cppFiles/user.cpp",
                "cppFiles/return.cpp",
                "-o",
                "${fileDirname}\\Stocklist_Tracker.exe"
            ],

*****
