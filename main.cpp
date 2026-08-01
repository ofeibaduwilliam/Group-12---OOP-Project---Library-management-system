#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
class Book { //this is the book class
private:
    string title;
    string author;
    int bookID;
    bool isAvailable;

public: // a constructor 
    Book(int ID, string bookAuthor, string bookTitle) {
        bookID = ID;
        author = bookAuthor;
        title = bookTitle;
        isAvailable = true;
    }// getters
    string getTitle() {
        return title;
    }
    string getAuthor() {
        return author;
    }
    int getBookID() {
        return bookID;
    }
    bool getAvailability() {
        return isAvailable;
    }
    void setAvailability(bool status) {
        isAvailable = status;
    }
    // to display book information
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
    }
}; 
class User { //this is the user class 
private:
    int userID;
    string name;
    vector<int> borrowedBooks;

public:
//this is a constructor
    User(int id, string userName) {
        userID = id;
        name = userName;
    }

    // Getters
    int getUserID() {
        return userID;
    }
    string getName() {
        return name;
    }

    // to borrow a book
    void borrowBook(int bookID) {
        borrowedBooks.push_back(bookID);
    }
    // to return a book
    void returnBook(int bookID) {
    for (int i = 0; i < borrowedBooks.size(); i++) {

   if (borrowedBooks[i] == bookID) {

     borrowedBooks.erase(
      borrowedBooks.begin() + i
      );
     cout << "Book returned successfully.\n";
   return;
            }
        }
    cout << "This user did not borrow that book.\n";
    }
    // to display user information
    void displayUser() {
      cout << "\nUser ID: " << userID;
        cout << "\nName: " << name;
        cout << "\nNumber of borrowed books: "
             << borrowedBooks.size() << endl;
    }
};
class Librarian { //this is the librarian class 
private:
    int librarianID;
    string name;
    vector<Book> inventory;

public:
    // Constructor
    Librarian(int id, string librarianName) {
        librarianID = id;
        name = librarianName;
    }
    // to add a book
    void addBook(Book book) {
        inventory.push_back(book);
        cout << book.getTitle()
     << " was added to the library.\n";
    }

    // to display inventory
    void displayInventory() {
        cout << "\n LIBRARY INVENTORY n";
        for (int i = 0; i < inventory.size(); i++) {
          inventory[i].displayBook();
        }
    }
    //  to issue a book
    void issueBook(User& user, int bookID) {

    for (int i = 0; i < inventory.size(); i++) {
     if (inventory[i].getBookID() == bookID) {
         if (inventory[i].getAvailability()) {
      inventory[i].setAvailability(false);
     user.borrowBook(bookID);
      cout << "\nBook issued successfully.\n";
        }
       else {
         cout << "\nThis book is unavailable.\n";
         }
   return;        }
    }
        cout << "\nBook not found.\n";
    }
    void returnBook(User& user, int bookID) {
    for (int i = 0; i < inventory.size(); i++) {
     if (inventory[i].getBookID() == bookID) {
         inventory[i].setAvailability(true);
        user.returnBook(bookID);
           return;
        }
        }
        cout << "\nBook not found.\n";
    }
    double calculateFine(int lateDays) {
        double finePerDay = 2.0;
        if (lateDays <= 0) {
            return 0;
        }
       return lateDays * finePerDay;
    }
};

int main() {

    cout << "  WELCOME TO THE LIBRARY MANAGEMENT SYSTEM";
    
    // 1. Create a Librarian
    Librarian librarian(1, "Mr. William Smith");
    cout << "\nLibrarian: " << librarian.getName() << " (ID: " << librarian.getLibrarianID() << ")\n";
    
    // 2. Add Books to the Library
    cout << "\n--- ADDING BOOKS TO LIBRARY ---\n";
    Book book1(101, "George Orwell", "1984");
    Book book2(102, "Harper Lee", "To Kill a Mockingbird");
    Book book3(103, "J.R.R. Tolkien", "The Hobbit");
    Book book4(104, "F. Scott Fitzgerald", "The Great Gatsby");
    Book book5(105, "J.K. Rowling", "Harry Potter and the Philosopher's Stone");
    
    librarian.addBook(book1);  
    librarian.addBook(book2);  
    librarian.addBook(book3);  
    librarian.addBook(book4);  
    librarian.addBook(book5);  
    
    // 3. Display All Books in Inventory
    librarian.displayInventory();  
    // 4. Create Users
    cout << "\n--- CREATING USERS ---\n";
    User user1(201, "Alice Johnson");
    User user2(202, "Bob Williams");
    User user3(203, "Charlie Brown");
    
    cout << "User 1: " << user1.getName() << " (ID: " << user1.getUserID() << ")\n";
    cout << "User 2: " << user2.getName() << " (ID: " << user2.getUserID() << ")\n";
    cout << "User 3: " << user3.getName() << " (ID: " << user3.getUserID() << ")\n";
    
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
    
    // 10. Calculate Late Fees
    cout << "\n--- LATE FEE CALCULATION ---\n";
    
    int lateDays = 5;
    double fine = librarian.calculateFine(lateDays);
    cout << "Fine for " << lateDays << " late days: $" << fine << endl;
    
    lateDays = 0;
    fine = librarian.calculateFine(lateDays);
    cout << "Fine for " << lateDays << " late days: $" << fine << " (No fine for on-time return)\n";
    
    cout << "  THANK YOU FOR USING THE LIBRARY SYSTEM";
   
    
    return 0;
}
