#include <iostream>
#include <string>
#include <conio.h>
#include <algorithm>  
#include <vector>    
using namespace std;

class Book {
    string author;      
    string title;       
    string izd;   
    int year;          
    int pages;         
    
public:
    Book();             // конструктор по умолчанию
    void input();       // метод для ввода данных
    void setAuthor(const string& a);
    void setTitle(const string& t);
    void setizd(const string& p);
    void setYear(int y);
    void setPages(int p);
    
    string getAuthor() const { return author; }
    string getTitle() const { return title; }
    string getizd() const { return izd; }
    int getYear() const { return year; }
    int getPages() const { return pages; }
    
    void show() const;  
};

void Book::input() {
    cout << "\n=== Ввод данных о книге ===" << endl;
    cout << "Автор (Фамилия И.О.): "; 
    getline(cin, author); 
    cout << "Название книги: ";
    getline(cin, title);
    cout << "Издательство: ";
    getline(cin, izd);
    cout << "Год издания: ";
    cin >> year;
    cout << "Количество страниц: ";
    cin >> pages;
    cin.ignore(); 
}

// Методы set с использованием const string&
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

// Метод show
void Book::show() const {
    cout << "\n==============================" << endl;
    cout << "Автор: " << author << endl;
    cout << "Название: " << title << endl;
    cout << "Издательство: " << izd << endl;
    cout << "Год издания: " << year << endl;
    cout << "Количество страниц: " << pages << endl;
}

bool compareBooks(const Book& a, const Book& b) {
    // Сначала сравниваем по автору
    if (a.getAuthor() != b.getAuthor()) {
        return a.getAuthor() < b.getAuthor();
    }
    // Если авторы одинаковые, сравниваем по названию
    return a.getTitle() < b.getTitle();
}

// а) Упорядоченный по алфавиту список книг заданного автора
void listBooksByAuthor(Book* listBooks, int n) {
    string author;
    cout << "\n=== Поиск книг по автору ===" << endl;
    cout << "Введите фамилию автора: ";
    getline(cin, author);
    
    // Вектор для хранения найденных книг
    vector<Book> foundBooks;
    
    // Ищем книги данного автора
    for (int i = 0; i < n; i++) {
        const string& bookAuthor = listBooks[i].getAuthor();
        // Проверяем, содержит ли автор введенную фамилию
        // find ищет подстроку в строке
        if (bookAuthor.find(author) != string::npos) {
            foundBooks.push_back(listBooks[i]);
        }
    }
    
    if (foundBooks.empty()) {
        cout << "Книг автора \"" << author << "\" не найдено." << endl;
    } else {
        // Сортируем найденные книги
        sort(foundBooks.begin(), foundBooks.end(), compareBooks);
        
        cout << "\n=== Найдено " << foundBooks.size() 
             << " книг автора \"" << author << "\" ===" << endl;
        for (const auto& book : foundBooks) {
            book.show();
        }
    }
}

// б) Список книг, выпущенных заданным издательством
void listBooksByizd(Book* listBooks, int n) {
    string izd;
    cout << "\n=== Поиск книг по издательству ===" << endl;
    cout << "Введите название издательства: ";
    getline(cin, izd);
    
    cout << "\n=== Книги издательства \"" << izd << "\" ===" << endl;
    bool found = false;
    
    for (int i = 0; i < n; i++) {
        if (listBooks[i].getizd() == izd) {
            listBooks[i].show();
            found = true;
        }
    }
    
    if (!found) {
        cout << "Книг издательства \"" << izd << "\" не найдено." << endl;
    }
}

// в) Список книг, выпущенных после заданного года
void listBooksAfterYear(Book* listBooks, int n) {
    int year;
    cout << "\n=== Поиск книг после заданного года ===" << endl;
    cout << "Введите год: ";
    cin >> year;
    cin.ignore(); // очистка буфера
    
    cout << "\n=== Книги, выпущенные после " << year << " года ===" << endl;
    bool found = false;
    
    for (int i = 0; i < n; i++) {
        if (listBooks[i].getYear() > year) {
            listBooks[i].show();
            found = true;
        }
    }
    
    if (!found) {
        cout << "Книг, выпущенных после " << year << " года, не найдено." << endl;
    }
}

// Основная функция
int main() {
    setlocale(LC_ALL, "Russian");
    
    Book* listBooks;
    int n;
    
    cout << "=== Учет книг в библиотеке ===" << endl;
    cout << "Введите количество книг: ";
    cin >> n;
    cin.ignore(); // очистка буфера после ввода числа
    
    // Создаем динамический массив объектов Book
    listBooks = new Book[n];
    
    // Вводим данные для каждой книги
    for (int i = 0; i < n; i++) {
        cout << "\nКнига №" << i+1 << ":";
        listBooks[i].input();
    }
    
    cout << "\n=== Введенные книги ===" << endl;
    for (int i = 0; i < n; i++) {
        cout << "\nКнига №" << i+1 << ":";
        listBooks[i].show();
    }
    
    // Выполняем выборки
    listBooksByAuthor(listBooks, n);
    listBooksByizd(listBooks, n);
    listBooksAfterYear(listBooks, n);
    
    // Освобождаем память
    delete[] listBooks;
    
    cout << "\nНажмите любую клавишу для выхода...";
    while(!kbhit()); // Проверяет наличие ввода с клавиатуры
    
    return 0;
}
