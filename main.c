#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure for Book
struct Book {
    int book_id;
    char title[50];
    char author[50];
    float price;
    int quantity;
};

// Structure for a book that has been issued
struct IssuedBook {
    int book_id;
    char student_name[50];
    int issue_day;
    int issue_month;
    int issue_year;
};

// Function Prototypes
void menu(void);
void addBook();
void displayBooks();
void deleteBook();
void updateBook();
void issueBook();
void returnBook();
void viewIssuedBooks();

// Main function
int main() {
    menu();
    return 0;
}

// Menu & Functionalities
void menu() {
    int choice;
    do {
        printf("\n==================================\n");
        printf("   LIBRARY MANAGEMENT SYSTEM\n");
        printf("==================================\n");
        printf("1. Add New Book\n");
        printf("2. Display All Books\n");
        printf("3. Update a Book's Details\n");
        printf("4. Delete a Book\n");
        printf("5. Issue a Book\n");
        printf("6. Return a Book\n");
        printf("7. View Issued Books\n");
        printf("8. Exit\n");
        printf("----------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                getchar();
                break;
            case 2:
                displayBooks();
                getchar();
                break;
            case 3:
                updateBook();
                getchar();
                break;
            case 4:
                deleteBook();
                getchar();
                break;
            case 5:
                issueBook();
                break;
            case 6:
                returnBook();
                break;
            case 7:
                viewIssuedBooks();
                getchar();
                break;
            case 8:
                printf("\nThank you for using the Library Management System!\n");
                getchar();
                break;
            default:
                printf("\n>> Invalid choice! Please enter a number between 1 and 8. <<\n");
                getchar();
        }
        if (choice != 8) {
            printf("\nPress Enter to continue...");
            getchar();
        }
        system("cls || clear");
    } while (choice != 8);
}

// Function to Add new books to Inventory
void addBook() {
    FILE *file;
    struct Book newBook;

    file = fopen("books.dat", "ab");
    if (file == NULL) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    printf("\n--- Add New Book ---\n");
    printf("Enter Book ID: ");
    scanf("%d", &newBook.book_id);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter Title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;

    printf("Enter Author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;

    printf("Enter Price: ");
    scanf("%f", &newBook.price);

    printf("Enter Quantity: ");
    scanf("%d", &newBook.quantity);
    while ((c = getchar()) != '\n' && c != EOF);

    fwrite(&newBook, sizeof(struct Book), 1, file);
    fclose(file);

    printf("\n>> Book added successfully! <<\n");
}

// Displays all books stored
void displayBooks() {
    FILE *file;
    struct Book b;
    int count = 0;

    file = fopen("books.dat", "rb");
    if (file == NULL) {
        printf("\n>> No books in the library. Please add a book first. <<\n");
        return;
    }

    printf("\n--- All Books in Library ---\n");
    printf("------------------------------------------------------------------\n");
    printf("ID\tTitle\t\tAuthor\t\tPrice\tQuantity\n");
    printf("------------------------------------------------------------------\n");

    while (fread(&b, sizeof(struct Book), 1, file)) {
        printf("%d\t%-15s\t%-15s\t$%.2f\t%d\n", b.book_id, b.title, b.author, b.price, b.quantity);
        count++;
    }
    printf("------------------------------------------------------------------\n");

    if (count == 0) {
        printf("\n>> The library is empty. <<\n");
    }

    fclose(file);
}

// Updates the details of an existing book
void updateBook() {
    FILE *file, *tempFile;
    struct Book b;
    int id, found = 0;

    file = fopen("books.dat", "rb");
    tempFile = fopen("temp.dat", "wb");

    if (file == NULL || tempFile == NULL) {
        printf("\nError: Could not open files for updating.\n");
        if(file) fclose(file);
        if(tempFile) fclose(tempFile);
        return;
    }

    printf("\nEnter Book ID to update: ");
    scanf("%d", &id);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    while (fread(&b, sizeof(struct Book), 1, file)) {
        if (b.book_id == id) {
            printf("\n--- Updating Book ID: %d ---\n", id);
            printf("Enter new Title: ");
            fgets(b.title, sizeof(b.title), stdin);
            b.title[strcspn(b.title, "\n")] = 0;

            printf("Enter new Author: ");
            fgets(b.author, sizeof(b.author), stdin);
            b.author[strcspn(b.author, "\n")] = 0;

            printf("Enter new Price: ");
            scanf("%f", &b.price);

            printf("Enter new Quantity: ");
            scanf("%d", &b.quantity);
            while ((c = getchar()) != '\n' && c != EOF);

            found = 1;
        }
        fwrite(&b, sizeof(struct Book), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("books.dat");
        rename("temp.dat", "books.dat");
        printf("\n>> Book updated successfully! <<\n");
    } else {
        remove("temp.dat");
        printf("\n>> Book with ID %d not found. <<\n", id);
    }
}

// Deletes a book
void deleteBook() {
    FILE *file, *tempFile;
    struct Book b;
    int id, found = 0;

    file = fopen("books.dat", "rb");
    tempFile = fopen("temp.dat", "wb");

    if (file == NULL || tempFile == NULL) {
        printf("\nError: Could not open files for deletion.\n");
        if(file) fclose(file);
        if(tempFile) fclose(tempFile);
        return;
    }

    printf("\nEnter Book ID to delete: ");
    scanf("%d", &id);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    while (fread(&b, sizeof(struct Book), 1, file)) {
        if (b.book_id == id) {
            found = 1;
            printf("\n>> Book '%s' (ID: %d) has been deleted. <<\n", b.title, id);
        } else {
            fwrite(&b, sizeof(struct Book), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("books.dat");
        rename("temp.dat", "books.dat");
    } else {
        remove("temp.dat");
        printf("\n>> Book with ID %d not found. <<\n", id);
    }
}

// Issues a book to a student
void issueBook() {
    FILE *booksFile, *issuedFile;
    struct Book book;
    struct IssuedBook issued;
    int id, found = 0;

    printf("\nEnter Book ID to issue: ");
    scanf("%d", &id);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    booksFile = fopen("books.dat", "rb+");
    if (booksFile == NULL) {
        printf("\n>> Library data file not found. <<\n");
        return;
    }

    while (fread(&book, sizeof(struct Book), 1, booksFile)) {
        if (book.book_id == id) {
            if (book.quantity > 0) {
                issuedFile = fopen("issued.dat", "ab");
                if (issuedFile == NULL) {
                    printf("\nError: Could not open issued books file.\n");
                    fclose(booksFile);
                    return;
                }

                printf("Enter Student Name: ");
                fgets(issued.student_name, sizeof(issued.student_name), stdin);
                issued.student_name[strcspn(issued.student_name, "\n")] = 0;
                issued.book_id = id;

                // Get current date
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                issued.issue_day = tm.tm_mday;
                issued.issue_month = tm.tm_mon + 1;
                issued.issue_year = tm.tm_year + 1900;

                fwrite(&issued, sizeof(struct IssuedBook), 1, issuedFile);
                fclose(issuedFile);

                book.quantity--;
                fseek(booksFile, -sizeof(struct Book), SEEK_CUR);
                fwrite(&book, sizeof(struct Book), 1, booksFile);

                printf("\n>> Book ID %d issued to %s on %d-%d-%d successfully. <<\n", id, issued.student_name, issued.issue_day, issued.issue_month, issued.issue_year);
                found = 1;
            } else {
                printf("\n>> Book is out of stock. <<\n");
                found = 2;
            }
            break;
        }
    }

    if (found == 0) {
        printf("\n>> Book with ID %d not found. <<\n", id);
    }

    fclose(booksFile);
}

// Returns an issued book
void returnBook() {
    FILE *booksFile, *issuedFile, *tempFile;
    struct Book book;
    struct IssuedBook issued;
    int id, issuedFound = 0, bookFound = 0;

    printf("\nEnter Book ID to return: ");
    scanf("%d", &id);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    issuedFile = fopen("issued.dat", "rb");
    tempFile = fopen("temp_issued.dat", "wb");
    if (issuedFile == NULL || tempFile == NULL) {
        printf("\n>> No books are currently issued. <<\n");
        if(issuedFile) fclose(issuedFile);
        if(tempFile) fclose(tempFile);
        return;
    }

    while (fread(&issued, sizeof(struct IssuedBook), 1, issuedFile)) {
        if (issued.book_id == id && !issuedFound) {
            issuedFound = 1;

            time_t now_t = time(NULL);

            struct tm issue_tm = {0};
            issue_tm.tm_year = issued.issue_year - 1900;
            issue_tm.tm_mon = issued.issue_month - 1;
            issue_tm.tm_mday = issued.issue_day;
            time_t issue_t = mktime(&issue_tm);

            double seconds_kept = difftime(now_t, issue_t);
            int days_kept = seconds_kept / (60 * 60 * 24);

            int fine = 0;
            if (days_kept <= 10) {
                fine = 100;
            } else if (days_kept <= 30) {
                fine = 500;
            } else {
                fine = 1500;
            }
            printf("\nBook was issued on %d-%d-%d and kept for %d day(s).\n", issued.issue_day, issued.issue_month, issued.issue_year, days_kept);
            printf("Applicable fine: %d Rs\n", fine);

        } else {
            fwrite(&issued, sizeof(struct IssuedBook), 1, tempFile);
        }
    }
    fclose(issuedFile);
    fclose(tempFile);

    if (!issuedFound) {
        remove("temp_issued.dat");
        printf("\n>> This book (ID: %d) was not recorded as issued. <<\n", id);
        return;
    }

    remove("issued.dat");
    rename("temp_issued.dat", "issued.dat");

    booksFile = fopen("books.dat", "rb+");
    if (booksFile == NULL) {
        printf("\nError: Could not open library data file.\n");
        return;
    }

    while (fread(&book, sizeof(struct Book), 1, booksFile)) {
        if (book.book_id == id) {
            book.quantity++;
            fseek(booksFile, -sizeof(struct Book), SEEK_CUR);
            fwrite(&book, sizeof(struct Book), 1, booksFile);
            bookFound = 1;
            break;
        }
    }
    fclose(booksFile);

    if (bookFound) {
        printf("\n>> Book ID %d returned successfully. <<\n", id);
    } else {
        printf("\nCritical Error: Book was in issued list but not found in main library data.\n");
    }
}

// Displays all books that are currently issued
void viewIssuedBooks() {
    FILE *issuedFile, *booksFile;
    struct IssuedBook issued;
    struct Book book;
    int count = 0;

    issuedFile = fopen("issued.dat", "rb");
    if (issuedFile == NULL) {
        printf("\n>> No books are currently issued. <<\n");
        return;
    }

    printf("\n--- All Issued Books ---\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("Book ID\tTitle\t\tIssued To\t\tIssue Date\n");
    printf("----------------------------------------------------------------------------------\n");

    while (fread(&issued, sizeof(struct IssuedBook), 1, issuedFile)) {
        booksFile = fopen("books.dat", "rb");
        if (booksFile == NULL) {
            printf("Error reading library data.\n");
            fclose(issuedFile);
            return;
        }

        char title[50] = "N/A";
        while(fread(&book, sizeof(struct Book), 1, booksFile)) {
            if (book.book_id == issued.book_id) {
                strcpy(title, book.title);
                break;
            }
        }
        fclose(booksFile);

        printf("%d\t%-15s\t%-20s\t%02d-%02d-%d\n", issued.book_id, title, issued.student_name, issued.issue_day, issued.issue_month, issued.issue_year);
        count++;
    }
    printf("----------------------------------------------------------------------------------\n");

    if (count == 0) {
        printf("\n>> No books are currently issued. <<\n");
    }

    fclose(issuedFile);
}
