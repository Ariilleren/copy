#include <iostream>
#include <string>
using namespace std;

class Building {
    private:
        string type;
        string proizv;
        string color;
        int id;

    public:
        Building(string t = "", string p = "", string c = "", int id = 0) 
            : type(t), proizv(p), color(c), id(id) {}
        
        void output() const {
            cout << "тип: " << type << endl;
            cout << "производитель: " << proizv << endl;
            cout << "цвет: " << color << endl;
            cout << "id: " << id << endl;
        }
        
        int getId() const { return id; }
        void setType(const string& t) { type = t; }
        void setProizv(const string& p) { proizv = p; }
        void setColor(const string& c) { color = c; }
        void setId(int newId) { id = newId; }
        
        ~Building() {}
};

template <typename T>
class Queue {
    private:
        struct Node {
            T data;              
            Node* next;          
            Node(const T& t) : data(t), next(nullptr) {}
        };
        Node* head;  
        Node* tail;  
        
    public:
        Queue() : head(nullptr), tail(nullptr) {}
        ~Queue() {
            while (head != nullptr) {
                pop();
            }
        }
        void push(const T& t) {
            Node* newNode = new Node(t); 
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;  
            }
            cout << "Готово" << endl;
            cout << endl;
        }
        
        void pop() {
            Node* temp = head;        
            head = head->next;        
            if (head == nullptr) {    
                tail = nullptr;
            }  
            delete temp;              
            cout << "Готово" << endl;
            cout << endl;
        }
        
        void display() const {
            Node* current = head;
            cout << endl;
            cout << "Очередь" << endl;
            while (current != nullptr) {
                current->data.output();
                current = current->next;
                cout << endl;
            }
        }
};

int main() {
    Queue<Building> bQueue;
    bQueue.push(Building("Жилой дом", "Стройтрест", "Белый", 1));
    bQueue.push(Building("Офис", "БизнесСтрой", "Серый", 2));
    int ch = 1;

    while (ch != 0) {
        cout << "1. Добавить элемент в очередь" << endl;
        cout << "2. Удалить первый элемент" << endl;
        cout << "3. Показать всю очередь" << endl;
        cout << "0. Выход" << endl;
        cin >> ch;
        cin.ignore();

        switch (ch) {
            case 1: {  
                string type, proizv, color;
                int id;
                cout << endl;
                cout << "Введите тип здания: ";
                getline(cin, type);
                cout << "Введите производителя: ";
                getline(cin, proizv);
                cout << "Введите цвет: ";
                getline(cin, color);
                cout << "Введите id: ";
                cin >> id;
                cout << endl;
                bQueue.push(Building(type, proizv, color, id));
                break;
            }
            
            case 2: { 
                bQueue.pop();
                break;
            }
            
            case 3: { 
                bQueue.display();
                break;
            }
            case 0: {  
                cout << "\nПрограмма завершена." << endl;
                break;
            }
            
            default: {
                cout << "Неверный выбор" << endl;
                break;
            }
        }
    }
    return 0;
}