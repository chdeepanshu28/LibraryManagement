#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Book class representing a single book in the library
class Book {
public:
    int id;
    string title;
    string author;
    bool isBorrowed;

    Book(int id, string title, string author) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->isBorrowed = false;
    }

    void displayInfo() {
        cout << "Book ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Status: " << (isBorrowed ? "Borrowed" : "Available") << endl;
        cout << "-----------------------------------" << endl;
    }
};

// Library class containing books and handling operations
class Library {
private:
    vector<Book> books;

public:
    void loadBooks();
    void saveBooks();
    void addBook();
    void displayBooks();
    void borrowBook();
    void returnBook();
};

// Load books from a file
void Library::loadBooks() {
    ifstream file("books.txt");
    if (!file.is_open()) {
        cout << "No previous records found." << endl;
        return;
    }

    int id;
    string title, author;
    bool isBorrowed;
    while (file >> id >> ws && getline(file, title) && getline(file, author) && file >> isBorrowed) {
        Book book(id, title, author);
        book.isBorrowed = isBorrowed;
        books.push_back(book);
    }
    file.close();
}

// Save books to a file
void Library::saveBooks() {
    ofstream file("books.txt");
    for (auto &book : books) {
        file << book.id << endl
             << book.title << endl
             << book.author << endl
             << book.isBorrowed << endl;
    }
    file.close();
}

// Add a new book to the library
void Library::addBook() {
    int id;
    string title, author;
    cout << "Enter book ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter book title: ";
    getline(cin, title);
    cout << "Enter author name: ";
    getline(cin, author);

    books.push_back(Book(id, title, author));
    saveBooks();
    cout << "Book added successfully!" << endl;
}

// Display all books
void Library::displayBooks() {
    if (books.empty()) {
        cout << "No books available in the library." << endl;
        return;
    }

    for (auto &book : books) {
        book.displayInfo();
    }
}

// Borrow a book
void Library::borrowBook() {
    int id;
    cout << "Enter book ID to borrow: ";
    cin >> id;

    for (auto &book : books) {
        if (book.id == id) {
            if (book.isBorrowed) {
                cout << "This book is already borrowed." << endl;
            } else {
                book.isBorrowed = true;
                saveBooks();
                cout << "You have successfully borrowed the book!" << endl;
            }
            return;
        }
    }
    cout << "Book with ID " << id << " not found." << endl;
}

// Return a book
void Library::returnBook() {
    int id;
    cout << "Enter book ID to return: ";
    cin >> id;

    for (auto &book : books) {
        if (book.id == id) {
            if (book.isBorrowed) {
                book.isBorrowed = false;
                saveBooks();
                cout << "You have successfully returned the book!" << endl;
            } else {
                cout << "This book was not borrowed." << endl;
            }
            return;
        }
    }
    cout << "Book with ID " << id << " not found." << endl;
}

int main() {
    Library library;
    library.loadBooks();

    int choice;
    do {
        cout << "\n=== Library Management System ===" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display All Books" << endl;
        cout << "3. Borrow Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.displayBooks();
                break;
            case 3:
                library.borrowBook();
                break;
            case 4:
                library.returnBook();
                break;
            case 5:
                cout << "Exiting the system." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
