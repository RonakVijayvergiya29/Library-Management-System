#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>
#include <iomanip>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

class BookNotFoundException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Book not found in catalog.";
    }
};

class InvalidInputException : public std::exception {
    string msg;
public:
    InvalidInputException(const string& m) : msg(m) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class LibraryItem {
protected:
    string title;
    int itemID;
public:

    inline int getItemID() const { return itemID; }

    LibraryItem(const string& t = "", int id = 0) : title(t), itemID(id) {
    
    }


    LibraryItem(const LibraryItem& other) : title(other.title), itemID(other.itemID) {}

    
    virtual ~LibraryItem() {}

    void setTitle(const string& t) {
        
        this->title = t;
    }

    string getTitle() const { return title; }

    
    virtual double calculateFine(int daysOverdue) const = 0;

    
    virtual string serialize() const = 0;
    virtual string getType() const = 0;
};


class Book : public LibraryItem {
private:
    string author;
    int pages;
public:

    Book(const string& t = "", int id = 0, const string& a = "", int p = 0)
        : LibraryItem(t, id), author(a), pages(p) {}

    
    Book(const Book& other)
        : LibraryItem(other), author(other.author), pages(other.pages) {}

    ~Book() override {}

    double calculateFine(int daysOverdue) const override {
    
        return daysOverdue * 0.50;
    }


    bool operator==(const Book& rhs) const {
        return this->itemID == rhs.itemID;
    }

    string getAuthor() const { return author; }
    int getPages() const { return pages; }

    string serialize() const override {
        std::ostringstream oss;
        oss << "BOOK|" << itemID << "|" << title << "|" << author << "|" << pages;
        return oss.str();
    }

    string getType() const override { return "BOOK"; }
};

class Journal : public LibraryItem {
private:
    int volume;
    int issue;
public:
    Journal(const string& t = "", int id = 0, int vol = 0, int iss = 0)
        : LibraryItem(t, id), volume(vol), issue(iss) {}

    Journal(const Journal& other)
        : LibraryItem(other), volume(other.volume), issue(other.issue) {}

    ~Journal() override {}

    double calculateFine(int daysOverdue) const override {
    
        return daysOverdue * 1.00;
    }

    string serialize() const override {
        std::ostringstream oss;
        oss << "JOURNAL|" << itemID << "|" << title << "|" << volume << "|" << issue;
        return oss.str();
    }

    string getType() const override { return "JOURNAL"; }
};

vector<LibraryItem*> catalog;

LibraryItem* createBook(const string& title, int id, const string& author, int pages) {
    return new Book(title, id, author, pages);
}

LibraryItem* createJournal(const string& title, int id, int volume, int issue) {
    return new Journal(title, id, volume, issue);
}
LibraryItem* search(int id) {
    for (LibraryItem* item : catalog) {
        if (item->getItemID() == id) return item;
    }
    
    throw BookNotFoundException();
}

LibraryItem* search(const string& title) {
    for (LibraryItem* item : catalog) {
        if (item->getTitle() == title) return item;
    }
    throw BookNotFoundException();
}


void saveCatalog(const string& filename) {
    std::ofstream ofs(filename, std::ios::out);
    if (!ofs) {
        throw InvalidInputException("Failed to open file for writing: " + filename);
    }
    for (LibraryItem* item : catalog) {
        ofs << item->serialize() << "\n";
    }
    ofs.close();
}

void loadCatalog(const string& filename) {
    std::ifstream ifs(filename, std::ios::in);
    if (!ifs) {
        
        return;
    }
    string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        string token;
        std::getline(iss, token, '|');
        if (token == "BOOK") {
            string idS, title, author, pagesS;
            std::getline(iss, idS, '|');
            std::getline(iss, title, '|');
            std::getline(iss, author, '|');
            std::getline(iss, pagesS, '|');
            int id = std::stoi(idS);
            int pages = std::stoi(pagesS);
            catalog.push_back(createBook(title, id, author, pages));
        } else if (token == "JOURNAL") {
            string idS, title, volS, issS;
            std::getline(iss, idS, '|');
            std::getline(iss, title, '|');
            std::getline(iss, volS, '|');
            std::getline(iss, issS, '|');
            int id = std::stoi(idS);
            int vol = std::stoi(volS);
            int issue = std::stoi(issS);
            catalog.push_back(createJournal(title, id, vol, issue));
        }
    }
    ifs.close();
}


void printItem(const LibraryItem* item) {
    cout << "[" << item->getType() << "] ID: " << item->getItemID()
         << " Title: \"" << item->getTitle() << "\"\n";
}


int main() {
    const string catalogFile = "catalog.txt";

    try {
        
        cout << "Loading catalog from file (" << catalogFile << ") if it exists...\n";
        loadCatalog(catalogFile);
        cout << "Loaded " << catalog.size() << " items from file.\n\n";
    } catch (const std::exception& e) {
        cout << "Error loading catalog: " << e.what() << endl;
    }

    int choice = 0;
    while (choice != 5) {
        cout << "Library Catalog Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. Add Journal\n";
        cout << "3. Search by ID\n";
        cout << "4. Search by Title\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            if (choice == 1) {
                
                string title, author;
                int id, pages;
                cout << "Enter book title: ";
                cin.ignore();
                std::getline(cin, title);
                cout << "Enter author name: ";
                std::getline(cin, author);
                cout << "Enter book ID: ";
                cin >> id;
                cout << "Enter number of pages: ";
                cin >> pages;
                catalog.push_back(createBook(title, id, author, pages));
                cout << "Book added successfully!\n\n";
            } else if (choice == 2) {
                
                string title;
                int id, volume, issue;
                cout << "Enter journal title: ";
                cin.ignore();
                std::getline(cin, title);
                cout << "Enter journal ID: ";
                cin >> id;
                cout << "Enter volume number: ";
                cin >> volume;
                cout << "Enter issue number: ";
                cin >> issue;
                catalog.push_back(createJournal(title, id, volume, issue));
                cout << "Journal added successfully!\n\n";
            } else if (choice == 3) {
                
                int id;
                cout << "Enter item ID to search: ";
                cin >> id;
                LibraryItem* item = search(id);
                printItem(item);
                cout << "Fine for 5 days overdue: $" << std::fixed << std::setprecision(2)
                     << item->calculateFine(5) << "\n\n";
            } else if (choice == 4) {
                
                string title;
                cout << "Enter title to search: ";
                cin.ignore();
                std::getline(cin, title);
                LibraryItem* item = search(title);
                printItem(item);
                cout << "Fine for 3 days overdue: $" << std::fixed << std::setprecision(2)
                     << item->calculateFine(3) << "\n\n";
            } else if (choice == 5) {
                cout << "Exiting program. Saving catalog to file...\n";
                saveCatalog(catalogFile);
                cout << "Catalog saved. Goodbye!\n";
            } else {
                cout << "Invalid choice, please try again.\n\n";
            }
        } catch (const std::exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }


    for (LibraryItem* item : catalog) {
        delete item;
    }
    catalog.clear();

    return 0;

}
