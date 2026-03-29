#include <iostream>
#include <string>
#include <conio.h>
#include <algorithm> 
#include <vector>    
using namespace std;

class Book {
private: 
    string author;     
    string title;      
    string izd;   
    int year;         
    int pages;         
    
public:
    Book();  
 //   ~Book(); 
    void input();     
    void setAuthor(const string& a);
    void setTitle(const string& t);
    void setizd(const string& i);
    void setYear(int y);
    void setPages(int p);
    string getAuthor() const { return author; }
    string getTitle() const { return title; }
    string getizd() const { return izd; }
    int getYear() const { return year; }
    int getPages() const { return pages; }
    void show() const;  
};

Book::Book() : year(0), pages(0) {}

void Book::input() {
    cout << "автор: "; 
    getline(cin, author);
    cout << "названин: ";
    getline(cin, title);
    cout << "издательство: ";
    getline(cin, izd);
    cout << "год: ";
    cin >> year;
    cout << "кол-во страниц: ";
    cin >> pages;
    cin.ignore(); 
}

void Book::setAuthor(const string& a) {
    author = a;
}
void Book::setTitle(const string& t) {
    title = t;
}
void Book::setizd(const string& p) {
    izd = p;
}
void Book::setYear(int y) {
    year = y;
}
void Book::setPages(int p) {
    pages = p;
}

void Book::show() const {
    cout << "автор: " << author << endl;
    cout << "название: " << title << endl;
    cout << "издательство: " << izd << endl;
    cout << "год: " << year << endl;
    cout << "количество страниц: " << pages << endl;
}

bool srbook(const Book& a, const Book& b) {
    if (a.getAuthor() != b.getAuthor()) {
        return a.getAuthor() < b.getAuthor();
    }
    return a.getTitle() < b.getTitle();
}

void a(Book* BOOKS, int n) {
    string author;
    cout << "\nупорядоченный список книг зад автора (а)" << endl;
    cout << "автор: ";
    getline(cin, author);
    
    vector<Book> fbooks;
    
    for (int i = 0; i < n; i++) {
        const string& bookAuthor = BOOKS[i].getAuthor();
        if (bookAuthor.find(author) != string::npos) {
            fbooks.push_back(BOOKS[i]);
        }
    }
    sort(fbooks.begin(), fbooks.end(),  srbook);
    cout << "\nкниг автора " << author <<"   " <<fbooks.size() << endl;
    for (const auto& book : fbooks) {
        book.show();
        cout << endl;
    }
    cout << endl;
}

void b(Book* BOOKS, int n) {
    string izd;
    cout << "\n книги издательства (б)" << endl;
    cout << "название издательства: ";
    getline(cin, izd);
    
    for (int i = 0; i < n; i++) {
        if (BOOKS[i].getizd() == izd) {
            BOOKS[i].show();
        }
        cout << endl;
    }
    cout << endl;
}

void v(Book* BOOKS, int n) {
    int year;
    cout << "\n книги после зад года (в)" << endl;
    cout << "год: ";
    cin >> year;
    cin.ignore(); 
    cout << endl;
    for (int i = 0; i < n; i++) {
        if (BOOKS[i].getYear() > year) {
            BOOKS[i].show();
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    Book* BOOKS;
    int n;
    cout << "количество книг: ";
    cin >> n;
    cin.ignore(); 
    
    BOOKS = new Book[n];
    for (int i = 0; i < n; i++) {
        cout << "\nкнига " << i+1 << ":";
        BOOKS[i].input();
    }
    
    cout << "\n" << endl;
    for (int i = 0; i < n; i++) {
        cout << "\nкнига " << i+1 << ":";
        BOOKS[i].show();
    }
    cout << endl;


    while(true){
        int ch;
        cout << "\n a-1. \n б-2. \n в-3. \n" << endl;
        cin >> ch;
        cin.ignore();
        switch (ch){
        case 1:
            a(BOOKS, n);
            break;
        case 2:
            b(BOOKS, n);
            break;
        case 3:
            v(BOOKS, n);
            break;
        default:
            break;
        }
    }

    delete[] BOOKS;
    return 0;
}