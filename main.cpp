#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>
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

// Sentinel returned by readInt when input runs out (EOF / Ctrl+D).
const int INPUT_EOF = numeric_limits<int>::min();

// Reads a whole number, re-prompting on bad input instead of leaving cin
// in a failed state (which previously spun the menu into an infinite loop).
// Returns INPUT_EOF if the input stream ends.
int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }
        if (cin.eof()) {
            return INPUT_EOF;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a whole number.\n";
    }
}

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

    Book(int ID, const string& bookAuthor, const string& bookTitle, string available) {
        bookID = ID;
        author = bookAuthor;
        title = bookTitle;
        if (available == "1"){
            isAvailable = true;
        }else{
            isAvailable = false;
        }
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

    // Overloaded == operator
    bool operator==(const Book& other) const {
        return bookID == other.bookID;
    }

    // Overloaded << operator
    friend ostream& operator<<(ostream& out, const Book& book) {
        out << "\nTitle: " << book.title;
        out << "\nAuthor: " << book.author;
        out << "\nBook ID: " << book.bookID;
        out << "\nStatus: " << (book.isAvailable ? "Available" : "Unavailable") << "\n";
        return out;
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
    // Needed so borrowing state can be written back to disk
    const vector<int>& getBorrowedBooks() const {
        return borrowedBooks;
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
    // Constructor
    Librarian(int id, const string& librarianName) {
        librarianID = id;
        name = librarianName;
    }

    // Getters
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

    //A created friend function to help with the automatic loading of the books in the database
    friend void addNewBook(Librarian& lib,const Book& book);

    void displayInventory() const {
        cout << "\n LIBRARY INVENTORY \n";
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
                // only mark available if the user actually borrowed it
                if (user.returnBook(bookID)) {
                    inventory[i].setAvailability(true);
                }
                return;
            }
        }
        cout << "\nBook not found.\n";
    }

    // Adds a brand-new book (starts Available). Refuses a duplicate ID,
    // since the ID is the unique key used everywhere else.
    bool addBookToCatalog(int id, const string& author, const string& title) {
        for (size_t i = 0; i < inventory.size(); i++) {
            if (inventory[i].getBookID() == id) {
                cout << "A book with ID " << id << " already exists.\n";
                return false;
            }
        }
        inventory.push_back(Book(id, author, title));
        cout << title << " (ID: " << id << ") was added to the catalog.\n";
        return true;
    }

    // Removes a book by ID. Refuses if the book is currently issued out,
    // so we never delete a book that a user is still holding.
    bool removeBookFromCatalog(int id) {
        for (size_t i = 0; i < inventory.size(); i++) {
            if (inventory[i].getBookID() == id) {
                if (!inventory[i].getAvailability()) {
                    cout << "Cannot remove: this book is currently borrowed. "
                         << "Have it returned first.\n";
                    return false;
                }
                cout << inventory[i].getTitle() << " (ID: " << id
                     << ") was removed from the catalog.\n";
                inventory.erase(inventory.begin() + i);
                return true;
            }
        }
        cout << "Book not found.\n";
        return false;
    }

    double calculateFine(int lateDays) const {
        double finePerDay = 2.0;
        if (lateDays <= 0) {
            return 0;
        }
        return lateDays * finePerDay;
    }

    // Writes the current inventory back to the CSV so the file matches
    // any availability changes made during this session.
    // Column order matches the loader: title,author,bookID,isAvailable
    void saveInventory(const string& filename) const {
        ofstream out(filename, ios::out | ios::trunc);
        if (!out.is_open()) {
            cout << "\nWarning: could not open " << filename
                 << " for writing. Book changes were NOT saved.\n";
            return;
        }
        for (size_t i = 0; i < inventory.size(); i++) {
            out << inventory[i].getTitle() << ","
                << inventory[i].getAuthor() << ","
                << inventory[i].getBookID() << ","
                << (inventory[i].getAvailability() ? "1" : "0") << "\n";
        }
        cout << "Inventory saved to " << filename << ".\n";
    }
};


//Definition of the referenced friend function
void addNewBook(Librarian& lib,const Book& book){
    lib.inventory.push_back(book);
    cout << book.getTitle() << " was added to the library.\n";

}

// ---- User persistence (free functions, mirroring the book loader) ----
// Format per line: userID,name,borrowedID1;borrowedID2;...
vector<User> loadUsers(const string& filename) {
    vector<User> users;
    ifstream in(filename);
    if (!in.is_open()) {
        return users; // caller seeds defaults when this is empty
    }
    string line;
    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        stringstream s(line);
        string idStr, name, borrowedStr;
        getline(s, idStr, ',');
        getline(s, name, ',');
        getline(s, borrowedStr); // remainder of the line (may be empty)

        if (idStr.empty()) {
            cout << "Skipping malformed user row (no ID): " << line << "\n";
            continue;
        }
        try {
            User u(stoi(idStr), name);
            if (!borrowedStr.empty()) {
                stringstream bs(borrowedStr);
                string bid;
                while (getline(bs, bid, ';')) {
                    if (bid.empty()) {
                        continue;
                    }
                    try {
                        u.borrowBook(stoi(bid));
                    } catch (const exception&) {
                        // skip a single bad borrowed-id but keep the user
                    }
                }
            }
            users.push_back(u);
        } catch (const exception&) {
            cout << "Skipping malformed user row (bad ID): " << line << "\n";
        }
    }
    return users;
}

void saveUsers(const string& filename, const vector<User>& users) {
    ofstream out(filename, ios::out | ios::trunc);
    if (!out.is_open()) {
        cout << "\nWarning: could not open " << filename
             << " for writing. User changes were NOT saved.\n";
        return;
    }
    for (size_t i = 0; i < users.size(); i++) {
        out << users[i].getUserID() << "," << users[i].getName() << ",";
        const vector<int>& borrowed = users[i].getBorrowedBooks();
        for (size_t j = 0; j < borrowed.size(); j++) {
            if (j != 0) {
                out << ";";
            }
            out << borrowed[j];
        }
        out << "\n";
    }
    cout << "Users saved to " << filename << ".\n";
}


int main() {
    const string dataFile  = "file.csv";
    const string usersFile = "users.csv";

    cout << "=====================================\n";
    cout << "   WELCOME TO THE LIBRARY SYSTEM\n";
    cout << "=====================================\n";

    // Create Librarian using user input
    int librarianID = readInt("\nEnter Librarian ID: ");
    if (librarianID == INPUT_EOF) {
        cout << "\nNo input received. Exiting.\n";
        return 0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline before getline

    string librarianName;
    cout << "Enter Librarian Name: ";
    getline(cin, librarianName);

    Librarian librarian(librarianID, librarianName);

    cout << "\nLibrarian Created Successfully\n";
    cout << "Name: " << librarian.getName();
    cout << "\nID: " << librarian.getLibrarianID() << endl;

    // ---- Load books from CSV ----
    cout<< "---- Load books from CSV ----"<< endl;
    fstream file(dataFile, ios::in);
    if (!file.is_open()) {
        cout << "\nWarning: could not open " << dataFile
             << ". Starting with an empty library.\n";
    } else {
        string line, title, author, bookID, isAvailable;
        while (getline(file, line)) {
            // Strip a trailing carriage return so Windows (CRLF) files parse correctly
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.empty()) {
                continue;
            }

            stringstream s(line);
            getline(s, title, ',');
            getline(s, author, ',');
            getline(s, bookID, ',');
            getline(s, isAvailable);

            if (bookID.empty()) {
                cout << "Skipping malformed row (no ID): " << line << "\n";
                continue;
            }
            try {
                Book loadingBook(stoi(bookID), author, title, isAvailable);
                addNewBook(librarian, loadingBook);
            } catch (const exception&) {
                cout << "Skipping malformed row (bad ID '" << bookID
                     << "'): " << line << "\n";
            }
        }
        file.close();
    }

    // ---- Load users, or seed defaults on first run ----
    vector<User> users = loadUsers(usersFile);
    if (users.empty()) {
        cout << "\nNo saved users found. Creating default users.\n";
        users.push_back(User(201, "Alice Johnson"));
        users.push_back(User(202, "Bob Williams"));
        users.push_back(User(203, "Charlie Brown"));
        users.push_back(User(204, "Gideon Osei"));
    }

    // ---- Menu (now the whole program) ----
    int choice = 0;
    do {
        cout << "\n=====================================\n";
        cout << "          LIBRARY MENU\n";
        cout << "=====================================\n";
        cout << "1. Display all books\n";
        cout << "2. Issue a book\n";
        cout << "3. Return a book\n";
        cout << "4. Add a book\n";
        cout << "5. Remove a book\n";
        cout << "6. Display users\n";
        cout << "7. Create new user\n";
        cout << "8. Calculate fine\n";
        cout << "9. Exit\n";

        choice = readInt("Enter choice: ");
        if (choice == INPUT_EOF) {
            cout << "\nInput ended. Exiting.\n";
            choice = 9;
        }

        switch (choice) {
        case 1:
            librarian.displayInventory();
            break;

        case 2:
        case 3:
        {
            cout << "\nSelect User\n";
            for (size_t i = 0; i < users.size(); i++) {
                cout << (i + 1) << ". " << users[i].getName() << endl;
            }
            int userChoice = readInt("Choice: ");
            int bookID = readInt("Enter Book ID: ");

            if (userChoice >= 1 && userChoice <= static_cast<int>(users.size())) {
                if (choice == 2) {
                    librarian.issueBook(users[userChoice - 1], bookID);
                } else {
                    librarian.returnBook(users[userChoice - 1], bookID);
                }
            } else {
                cout << "Invalid user.\n";
            }
            break;
        }

        case 4:
        {
            int newBookID = readInt("Enter new book ID: ");
            if (newBookID == INPUT_EOF) {
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline before getline

            string newAuthor, newTitle;
            cout << "Enter author: ";
            getline(cin, newAuthor);
            cout << "Enter title: ";
            getline(cin, newTitle);

            // Add, and persist immediately if it succeeded
            if (librarian.addBookToCatalog(newBookID, newAuthor, newTitle)) {
                librarian.saveInventory(dataFile);
            }
            break;
        }

        case 5:
        {
            int removeID = readInt("Enter ID of book to remove: ");
            if (removeID == INPUT_EOF) {
                break;
            }
            // Remove, and persist immediately if it succeeded
            if (librarian.removeBookFromCatalog(removeID)) {
                librarian.saveInventory(dataFile);
            }
            break;
        }

        case 6:
            cout << "\n--- USER INFORMATION ---\n";
            for (size_t i = 0; i < users.size(); i++) {
                cout << "\nUser " << (i + 1);
                users[i].displayUser();
            }
            break;

        case 7:
        {
            int newID = readInt("Enter new user ID: ");
            if (newID == INPUT_EOF) {
                break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline before getline

            // Reject a duplicate ID so it stays a unique key
            bool exists = false;
            for (size_t i = 0; i < users.size(); i++) {
                if (users[i].getUserID() == newID) {
                    exists = true;
                    break;
                }
            }
            if (exists) {
                cout << "A user with ID " << newID << " already exists.\n";
                break;
            }

            string newName;
            cout << "Enter new user name: ";
            getline(cin, newName);

            users.push_back(User(newID, newName));
            cout << newName << " (ID: " << newID << ") was added.\n";

            // Persist immediately so the new user is saved right away and
            // becomes a viable option for issuing books.
            saveUsers(usersFile, users);
            break;
        }

        case 8:
        {
            int lateDays = readInt("Enter number of late days: ");
            if (lateDays == INPUT_EOF) {
                break;
            }
            cout << "Fine: $" << librarian.calculateFine(lateDays) << endl;
            break;
        }

        case 9:
            cout << "\nThank you for using the Library System.\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 9);

    // ---- Persist everything so the files match the current state ----
    cout << "\n--- SAVING ---\n";
    librarian.saveInventory(dataFile);
    saveUsers(usersFile, users);

    cout << "\n  THANK YOU FOR USING THE LIBRARY SYSTEM\n";
    return 0;
}
