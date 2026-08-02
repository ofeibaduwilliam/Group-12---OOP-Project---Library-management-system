#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

/*
Group Members
| Name                           | Index No   |
| ------------------------------ | ---------- |
| Ofei-Badu William              | 4104724    |
| Agyemang Simon Duah            | 4088424    |
| Paa Kwesi Okyireh              | 4105424    |
| Sarkodie Kwabena Adu-Aninkorah | 4108924    |
| Obu Isaac                      | 4104524    |
| Penelope Seyram Dafeamekpor    | 4095124    |
| Siabi Delali Kwame             | 4109124    |
| Amartey Kofi Nii Boye          | 4089124    |
| Richmond Eshun                 | 4096724    |

*/

class Book {
private:
    string title;
    string author;
    int bookID;
    bool isAvailable;

public:
    Book(int ID, const string& bookAuthor, const string& bookTitle) {
        bookID = ID;
        author = bookAuthor;
        title = bookTitle;
        isAvailable = true;
    }

    // Getters
    string getTitle() const {
        return title;
    }
    string getAuthor() const {
        return author;
    }
    int getBookID() const {
        return bookID;
    }
    bool getAvailability() const {
        return isAvailable;
    }
    void setAvailability(bool status) {
        isAvailable = status;
    }

    void displayBook() const {
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nBook ID: " << bookID;
        if (isAvailable) {
            cout << "\nStatus: Available\n";
        } else {
            cout << "\nStatus: Unavailable\n";
        }
    }
       void displayBook() {
      cout << "\nTitle: " << title;
      cout << "\nAuthor: " << author;
      cout << "\nBook ID: " << bookID;
    if (isAvailable) {
     cout << "\nStatus: Available\n";
      }
    else {
     cout << "\nStatus: Unavailable\n";
        }
            bool operator==(const Book& other) const {
        return bookID == other.bookID;
    }

    // NEW: Overloaded << operator
    friend ostream& operator<<(ostream& out, const Book& book) {
        out << "\nTitle: " << book.title;
        out << "\nAuthor: " << book.author;
        out << "\nBook ID: " << book.bookID;
        out << "\nStatus: " << (book.isAvailable ? "Available" : "Unavailable") << "\n";
        return out;
    }
};
    }

    // NEW: Overloaded == operator
    bool operator==(const Book& other) const {
        return bookID == other.bookID;
    }
};

class User {
private:
    int userID;
    string name;
    vector<int> borrowedBooks;

public:
    User(int id, const string& userName) {
        userID = id;
        name = userName;
    }

    // Getters
    int getUserID() const {
        return userID;
    }
    string getName() const {
        return name;
    }

    void borrowBook(int bookID) {
        borrowedBooks.push_back(bookID);
    }

    // Returns true if the user actually had the book
    bool returnBook(int bookID) {
        for (size_t i = 0; i < borrowedBooks.size(); i++) {
            if (borrowedBooks[i] == bookID) {
                borrowedBooks.erase(borrowedBooks.begin() + i);
                cout << "Book returned successfully.\n";
                return true;
            }
        }
        cout << "This user did not borrow that book.\n";
        return false;
    }

    void displayUser() const {
        cout << "\nUser ID: " << userID;
        cout << "\nName: " << name;
        cout << "\nNumber of borrowed books: "
             << borrowedBooks.size() << endl;
    }
};

class Librarian {
private:
    int librarianID;
    string name;
    vector<Book> inventory;

public:
     //getters
    string getName() {
     return name;
     }

    int getLibrarianID() {
    return librarianID;
    }

    // Constructor
    Librarian(int id, string librarianName) {
    Librarian(int id, const string& librarianName) {
        librarianID = id;
        name = librarianName;
    }

    // Getters (fixed: these were missing, main() uses them)
    int getLibrarianID() const {
        return librarianID;
    }
    string getName() const {
        return name;
    }

    void addBook(const Book& book) {
        inventory.push_back(book);
        cout << book.getTitle() << " was added to the library.\n";
    }

    void displayInventory() const {
        cout << "\n LIBRARY INVENTORY \n";  // fixed: was "n"
        for (size_t i = 0; i < inventory.size(); i++) {
            inventory[i].displayBook();
        }
    }

    void issueBook(User& user, int bookID) {
        for (size_t i = 0; i < inventory.size(); i++) {
            if (inventory[i].getBookID() == bookID) {
                if (inventory[i].getAvailability()) {
                    inventory[i].setAvailability(false);
                    user.borrowBook(bookID);
                    cout << "\nBook issued successfully.\n";
                } else {
                    cout << "\nThis book is unavailable.\n";
                }
                return;
            }
        }
        cout << "\nBook not found.\n";
    }

    void returnBook(User& user, int bookID) {
        for (size_t i = 0; i < inventory.size(); i++) {
            if (inventory[i].getBookID() == bookID) {
                // fixed: only mark available if the user actually borrowed it
                if (user.returnBook(bookID)) {
                    inventory[i].setAvailability(true);
                }
                return;
            }
        }
        cout << "\nBook not found.\n";
    }

    double calculateFine(int lateDays) const {
        double finePerDay = 2.0;
        if (lateDays <= 0) {
            return 0;
        }
        return lateDays * finePerDay;
    }
};



int main() {
    cout << "=====================================\n";
    cout << "   WELCOME TO THE LIBRARY SYSTEM\n";
    cout << "=====================================\n";

    // Create Librarian using user input
    int librarianID;
    string librarianName;

    cout << "\nEnter Librarian ID: ";
    cin >> librarianID;
    cin.ignore();

    cout << "Enter Librarian Name: ";
    getline(cin, librarianName);

    Librarian librarian(librarianID, librarianName);

    cout << "\nLibrarian Created Successfully\n";
    cout << "Name: " << librarian.getName();
    cout << "\nID: " << librarian.getLibrarianID() << endl;

    // Add Books
    Book book1(101, "George Orwell", "1984");
    Book book2(102, "Harper Lee", "To Kill a Mockingbird");
    Book book3(103, "J.R.R. Tolkien", "The Hobbit");
    Book book4(104, "F. Scott Fitzgerald", "The Great Gatsby");
    Book book5(105, "J.K. Rowling", "Harry Potter and the Philosopher's Stone");
    Book book6(106,"Chinua Achebe", "Things Fall Apart");


    librarian.addBook(book1);
    librarian.addBook(book2);
    librarian.addBook(book3);
    librarian.addBook(book4);
    librarian.addBook(book5);

    // Create Users
    librarian.addBook(book6);
    librarian.addBook(book7);
    librarian.addBook(book8);
    librarian.addBook(book9);
    librarian.addBook(book10);

    // 3. Display All Books in Inventory
    librarian.displayInventory();

    // 4. Create Users
    cout << "\n--- CREATING USERS ---\n";
    User user1(201, "Alice Johnson");
    User user2(202, "Bob Williams");
    User user3(203, "Charlie Brown");
    User user4(204, " Gideon Osei");

    int choice;
    do {
        cout << "\n=====================================\n";
        cout << "          LIBRARY MENU\n";
        cout << "=====================================\n";
        cout << "1. Display all books\n";
        cout << "2. Issue a book\n";
        cout << "3. Return a book\n";
        cout << "4. Display users\n";
        cout << "5. Calculate fine\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
        case 1:
            librarian.displayInventory();
            break;

        case 2:
        {
            int userChoice;
            int bookID;
            cout << "\nSelect User\n";
            cout << "1. " << user1.getName() << endl;
            cout << "2. " << user2.getName() << endl;
            cout << "3. " << user3.getName() << endl;
            cout << "4." << user4.getName() << endl;
            cout << "Choice: ";
            cin >> userChoice;
            cout << "Enter Book ID: ";
            cin >> bookID;
            if(userChoice == 1)
                librarian.issueBook(user1, bookID);
            else if(userChoice == 2)
                librarian.issueBook(user2, bookID);
            else if(userChoice == 3)
                librarian.issueBook(user3, bookID);
            else
                cout << "Invalid user.\n";
            break;
        }

        case 3:
        {
            int userChoice;
            int bookID;
            cout << "\nSelect User\n";
            cout << "1. " << user1.getName() << endl;
            cout << "2. " << user2.getName() << endl;
            cout << "3. " << user3.getName() << endl;
            cout << "4. " << user4.getName() << endl;
            cout << "Choice: ";
            cin >> userChoice;
            cout << "Enter Book ID: ";
            cin >> bookID;
            if(userChoice == 1)
                librarian.returnBook(user1, bookID);
            else if(userChoice == 2)
                librarian.returnBook(user2, bookID);
            else if(userChoice == 3)
                librarian.returnBook(user3, bookID);
            else
                cout << "Invalid user.\n";
            break;
        }

        case 4:
            cout << "\n--- USER INFORMATION ---\n";
            cout << "\nUser 1";
            user1.displayUser();
            cout << "\nUser 2";
            user2.displayUser();
            cout << "\nUser 3";
            user3.displayUser();
            break;

        case 5:
        {
            int lateDays;
            cout << "Enter number of late days: ";
            cin >> lateDays;
            cout << "Fine: $"
                 << librarian.calculateFine(lateDays)
                 << endl;
            break;
        }

        case 6:
            cout << "\nThank you for using the Library System.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while(choice != 6);


    cout << "User 1: " << user1.getName() << " (ID: " << user1.getUserID() << ")\n";
    cout << "User 2: " << user2.getName() << " (ID: " << user2.getUserID() << ")\n";
    cout << "User 3: " << user3.getName() << " (ID: " << user3.getUserID() << ")\n";
    cout << "User 4: " << user4.getName() << " (ID: " << user4.getUserID() << ")\n";

    // 5. Issue Books to Users
    cout << "\n--- ISSUING BOOKS ---\n";

    cout << "Issuing '1984' (ID: 101) to Alice:\n";
    librarian.issueBook(user1, 101);

    cout << "\nIssuing 'The Hobbit' (ID: 103) to Bob:\n";
    librarian.issueBook(user2, 103);

    cout << "\nIssuing 'The Great Gatsby' (ID: 104) to Charlie:\n";
    librarian.issueBook(user3, 104);

    cout << "\nTrying to issue '1984' (ID: 101) again to Bob (should fail):\n";
    librarian.issueBook(user2, 101);

    // 6. Display Users' Borrowed Books
    cout << "\n--- USER BORROWING INFORMATION ---\n";
    user1.displayUser();
    user2.displayUser();
    user3.displayUser();
    user4.displayUser();

    // 7. Display Updated Inventory
    cout << "\n--- UPDATED INVENTORY ---\n";
    librarian.displayInventory();

    // 8. Return a Book
    cout << "\n--- RETURNING BOOKS ---\n";

    cout << "Alice returning '1984' (ID: 101):\n";
    librarian.returnBook(user1, 101);

    cout << "\nBob returning 'The Hobbit' (ID: 103):\n";
    librarian.returnBook(user2, 103);

    // 9. Display Final Inventory and User Info
    cout << "\n--- FINAL INVENTORY ---\n";
    librarian.displayInventory();

    cout << "\n--- FINAL USER INFORMATION ---\n";
    user1.displayUser();
    user2.displayUser();
    user3.displayUser();
    user4.dispalyUser();

    // 10. Calculate Late Fees
    cout << "\n--- LATE FEE CALCULATION ---\n";

    int lateDays = 5;
    double fine = librarian.calculateFine(lateDays);
    cout << "Fine for " << lateDays << " late days: $" << fine << endl;

    lateDays = 0;
    fine = librarian.calculateFine(lateDays);
    cout << "Fine for " << lateDays << " late days: $" << fine
         << " (No fine for on-time return)\n";

    cout << "  THANK YOU FOR USING THE LIBRARY SYSTEM\n";

    return 0;
}
