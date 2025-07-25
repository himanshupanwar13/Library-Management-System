Library Management System
A comprehensive console-based application written in C, designed to streamline the management of a library's inventory and member records. This system uses a straightforward command-line interface and stores data persistently in binary files.

✨ Key Features
This system provides a robust set of features accessible through a console menu:

📚 Book Management:

Add New Book: Add books with details like ID, Title, Author, Price, and Quantity.

Display All Books: View a formatted list of all books in the library's inventory.

Update a Book's Details: Modify the information for an existing book using its ID.

Delete a Book: Remove a book from the inventory.

🔄 Circulation Management:

Issue a Book: Record a book being issued to a student, decreasing its quantity.

Return a Book: Process a book's return, increasing its quantity and calculating fines based on the duration.

View Issued Books: Display a list of all books currently issued to students.

💰 Fine Calculation:

Automatically calculates fines for returned books based on how long they were kept.

💾 Data Persistence:

All book and issuance data is saved locally in books.dat and issued.dat files, ensuring data is not lost between sessions.

🛠️ Technologies Used
Programming Language: C

Data Storage: Binary File I/O (.dat files)

IDE (Project Files Included): Code::Blocks (.cbp project file)

📋 Prerequisites
Before you begin, ensure you have the following installed on your system:

A C Compiler: GCC is recommended. It can be installed on Windows via MinGW or is standard on most Linux distributions.

An IDE (Optional, Recommended):

Code::Blocks - You can directly open the Library Management System.cbp file with this IDE.

Visual Studio Code with a C/C++ extension.

🚀 Getting Started
Follow these steps to get a local copy up and running.

Method 1: Using an IDE (Recommended)
Clone the Repository:

git clone https://github.com/himanshupanwar13/Library-Management-System.git

Open the Project:

Launch Code::Blocks.

Go to File -> Open....

Navigate to the cloned directory and open the Library Management System.cbp file.

Build and Run:

Press F9 (or go to Build -> Build and run) to compile and execute the project.

Method 2: Using the Command Line
Clone the Repository:

git clone https://github.com/himanshupanwar13/Library-Management-System.git

Navigate to the Project Directory:

cd Library-Management-System

Compile the Code:
Use your C compiler (like GCC) to compile the main.c source file.

gcc main.c -o library_management

This command compiles main.c and creates an executable file named library_management.

Run the Application:
Execute the compiled program from your terminal.

On Windows:

library_management.exe

On macOS / Linux:

./library_management

📖 How to Use the Application
Launch the application using one of the methods above.

The main menu will appear in the console, presenting you with the following options:

1. Add New Book
2. Display All Books
3. Update a Book's Details
4. Delete a Book
5. Issue a Book
6. Return a Book
7. View Issued Books
8. Exit

Enter the number corresponding to the action you want to perform and press Enter.

Follow the on-screen prompts to enter book details, member information, or transaction data.

After each operation, press Enter to return to the main menu.

🤝 Contributing
Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are greatly appreciated.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".

Fork the Project

Create your Feature Branch (git checkout -b feature/AmazingFeature)

Commit your Changes (git commit -m 'Add some AmazingFeature')

Push to the Branch (git push origin feature/AmazingFeature)

Open a Pull Request

📄 License
This project is licensed under the MIT License. See the LICENSE.txt file for more information.

<p align="center">
<em>Created with ❤️ by Himanshu Panwar</em>
</p>
