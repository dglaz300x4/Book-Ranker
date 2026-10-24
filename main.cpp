#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

int getMenuInput(){
    int selection = 0;
    std::cin >> selection;
    return selection;
}


class Book {
    private:
        std::string title;
        std::string author;
        std::string genre;
        std::string description;
        std::string publisher;
        std::string releaseDate;
        int rating;

    public:
    // CONSTRUCTORS
        Book(){ // Default Constructor
            std::string notAvailable = "N/A";
            int defaultRating = -1;

            this->setTitle(notAvailable);
            this->setAuthor(notAvailable);
            this->setGenre(notAvailable);
            this->setDescription(notAvailable);
            this->setPublisher(notAvailable);
            this->setReleaseDate(notAvailable);
            this->setRating(defaultRating);
        }

        Book(Book *copy){ // Copy constructor
            this->title = copy->getTitle();
            this->author = copy->getAuthor();
            this->genre = copy->getGenre();
            this->description = copy->getDescription();
            this->publisher = copy->getPublisher();
            this->releaseDate = copy->getReleaseDate();
            this->rating = copy->getRating();
        }

    // GETTERS
        std::string getTitle(){ // Returns the title of the book
            return this->title;
        }

        std::string getAuthor(){ // Returns the author of the book
            return this->author;
        }

        std::string getGenre(){ // Return the genre(s) of the book
            return this->genre;
        }

        std::string getDescription(){ // Returns the description
            return this->description;
        }

        std::string getPublisher(){ // Returns the publisher
            return this->publisher;
        }

        std::string getReleaseDate(){ // Returns the releaseDate
            return this->releaseDate;
        }

        int getRating(){ // Returns the books rating
            return this->rating;
        }

    // SETTERS
        void setTitle(std::string title){ // Sets the title of the book
            this->title = title;
        }

        void setAuthor(std::string author){ // Sets the author of the book
            this->author = author;
        }

        void setGenre(std::string genre){ // Sets the genre(s) of the book
            this->genre = genre;
        }

        void setDescription(std::string description){ // Sets the description
            this->description = description;
        }

        void setPublisher(std::string publisher){ // Sets the publisher
            this->publisher = publisher;
        }

        void setReleaseDate(std::string releaseDate){ // Sets the releaseDate
            this->releaseDate = releaseDate;
        }

        void setRating(int rating){ // Sets the books rating
            this->rating = rating;
        }
};

class Library {
    private:
        std::vector<Book> books; // Vector of all of the books
        int bookCount; // holds the number of books in the library
    public:
    // CONSTRUCTORS
        Library(){
            bookCount = 0;
        }
    // GETTERS
        std::vector<Book> getBooksVector(){ // Returns the books in the library as a vector
            return this->books;
        }

        int getBookCount(){ // Returns the book count
            return this->bookCount;
        }

    // SETTERS
        void setBooks(std::vector<Book> books){ // Sets the books vector
            this->books = books;
            this->bookCount = books.size();
        }

    // FUNCTIONS
        void clearLibrary(){ // Clears the books saved
            books.clear();
        }

        void addBook(Book newBook){ // Adds a new book to the library
            books.push_back(newBook);
            ++bookCount;
        }

        void removeBook(int index){ // Remove a book given its index
            --bookCount;
            int lastBook = books.size()-1;

            if (index != lastBook){ // Resorts the vector to move the indexed book to the last position to be removed
                Book tempBook = books[index];

                for (int book = index; book < lastBook; ++book){
                    books[book] = books[book+1];
                }

                books[lastBook] = tempBook;
            }

            books.pop_back();
        }

        void editBook(int index, Book updateBook) { // Edit a book given its index
            this->books[index] = updateBook;
        }
};

class Menus {
    private:
        Library savedLibrary;

        std::string ratingScore(int rating) {
            std::string displayedRating;

            if (rating < 0) {
                displayedRating = "No Rating";
            }
            else {
                displayedRating = std::to_string(rating) + "/5";
            }
            return displayedRating;
        }

        void displayBookInfo(Book bookInfo){
            std::cout << bookInfo.getTitle() << ' ' << this->ratingScore(bookInfo.getRating()) << '\n';
            std::cout << bookInfo.getAuthor() << '\n';
            std::cout << bookInfo.getGenre() << '\n';
            std::cout << bookInfo.getDescription() << '\n';
            std::cout << "Publisher: " << bookInfo.getPublisher() << '\t' << bookInfo.getReleaseDate() << '\n';
        }

        void displayBookInfoList(std::vector<Book> saved, int bookCount){
            std::cout << "=============================\n";
            for (int i = 0; i < bookCount; ++i) {
                std::cout << i+1 << ' ' <<  saved[i].getTitle() << " Rating: " << this->ratingScore(saved[i].getRating()) << "\n   " << saved[i].getAuthor() << '\n';
            }
            std::cout << "=============================\n";
        }

        Book editBookInfo(Book displayedBook){
            Book newBook = displayedBook;

            int selection = -1;
            int newRating;

            std::string inputString;

            while (selection != 9) {
                system("clear");
                std::cout << "ADD A NEW BOOK\n";
                std::cout << "=============================\n";
                std::cout << "1 TITLE: " << newBook.getTitle() << '\n';
                std::cout << "2 AUTHOR: " << newBook.getAuthor() << '\n';
                std::cout << "3 GENRE: " << newBook.getGenre() << '\n';
                std::cout << "4 DESCRIPTION: " << newBook.getDescription() << '\n';
                std::cout << "5 PUBLISHER: " << newBook.getPublisher() << '\n';
                std::cout << "6 RELEASE DATE: " << newBook.getReleaseDate() << '\n';
                std::cout << "7 RATING: " << this->ratingScore(newBook.getRating()) << '\n';
                std::cout << "8 SAVE & EXIT\n";
                std::cout << "9 EXIT\n";
                std::cout << "=============================\n";
                std::cout << "SELECT AN ITEM TO CHANGE IT (TITLE AND AUTHOR MUST NOT BE N/A): ";
                selection = getMenuInput();
                std::cout << '\n';

                switch (selection) {
                    case 1:
                        std::cout << "ENTER A NEW TITLE: ";
                        std::cin.ignore();
                        std::getline(std::cin, inputString);
                        newBook.setTitle(inputString);
                        break;
                    case 2:
                        std::cout << "ENTER A NEW AUTHOR: ";
                        std::cin.ignore();
                        std::getline(std::cin, inputString);
                        newBook.setAuthor(inputString);
                        break;
                    case 3:
                        std::cout << "ENTER A NEW GENRE: ";
                        std::cin.ignore();
                        std::getline(std::cin, inputString);
                        newBook.setGenre(inputString);
                        break;
                    case 4:
                        std::cout << "ENTER A NEW DESCRIPTION: ";
                        std::cin.ignore();
                        std::getline(std::cin, inputString);
                        newBook.setDescription(inputString);
                        break;
                    case 5:
                        std::cout << "ENTER A NEW PUBLISHER: ";
                        std::cin.ignore();
                        std::getline(std::cin, inputString);
                        newBook.setPublisher(inputString);
                        break;
                    case 6:
                        std::cout << "ENTER A NEW RELEASE DATE: ";
                        std::cin.ignore();
                        std::getline(std::cin, inputString);
                        newBook.setReleaseDate(inputString);
                        break;
                    case 7:
                        std::cout << "ENTER A NEW RATING (0-5): "; std::cin >> newRating;
                        newBook.setRating(newRating);
                        break;
                    case 8:

                        if ((newBook.getTitle() != "N/A" || newBook.getTitle() != "") && (newBook.getAuthor() != "N/A" || newBook.getAuthor() != "")){
                            std::cout << "SAVING " << newBook.getTitle() << " (PRESS ENTER TO CONTINUE)";
                            selection = 9; // Changes selection to 9 to exit loop
                            displayedBook = newBook;
                        }
                        else {
                            std::cout << "YOUR TITLE OR AUTHOR IS INVALID (PRESS ENTER TO CONTINUE)";
                        }
                        std::cin.ignore();
                        std::cin.get();
                        break;
                    case 9:
                        break;
                    default:
                        std::cout << "THAT WAS NOT A VALID INPUT (PRESS ENTER TO CONTINUE)";
                        std::cin.ignore();
                        std::cin.get();
                        break;
                }
            }

            return displayedBook;
        }

    public:

        void mainMenu(){ // Display Main menu
            system("clear");
            std::cout << "=============================\n";
            std::cout << "WELCOME TO YOUR LOCAL LIBRARY\n  1. VIEW YOUR BOOKS\n  2. ADD A NEW BOOK\n  3. EDIT AN EXISTING BOOK\n  0. EXIT\n";
            std::cout << "=============================\n";
        }

        void viewBooksMenu(){ // View all books
            int selection = -1;
            int bookCount = this->savedLibrary.getBookCount();
            std::vector<Book> saved = this->savedLibrary.getBooksVector();

            while (selection != 0) {
                system("clear");
                std::cout << "SELECT A BOOK TO VIEW MORE (OR 0 TO EXIT)\n";
                displayBookInfoList(saved, bookCount);
                std::cin >> selection;

                if (selection != 0 && selection <= bookCount) {
                    system("clear");
                    std::cout << "=============================\n";
                    this->displayBookInfo(saved[selection-1]);
                    std::cout << "=============================\n";

                    std::cout << "(PRESS ENTER TO CONTINUE)";
                    std::cin.ignore();
                    std::cin.get();
                }

            }
        }

        void editBookMenu(){
            Book updateBook;

            int selection = -1;
            std::vector<Book> saved = this->savedLibrary.getBooksVector();
            int bookCount = this->savedLibrary.getBookCount();

            displayBookInfoList(saved, bookCount);

            std::cout << "SELECT THE BOOK YOU WISH TO EDIT: "; std::cin >> selection;

            if ()

            editBookInfo(updateBook);
        }

        void addNewBook(){ // Adds a new book to the library
            Book newBook;

            newBook = editBookInfo(newBook);

            this->savedLibrary.addBook(newBook);
        };
};


int main(){
    Menus display;
    int selection = -1;

    while(selection != 0) {
        system("clear");
        display.mainMenu();
        selection = getMenuInput();
        system("clear");
        switch (selection) {
            case 1:
                display.viewBooksMenu();
                break;
            case 2:
                display.addNewBook();
                break;
            case 3:
                display.editBookMenu();
                break;
        }
    }

    return 0;
}
