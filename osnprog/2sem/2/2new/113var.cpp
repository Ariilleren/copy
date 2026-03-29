#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class StackNode {
private:
    char data;
    StackNode* next;
public:
    StackNode(char value) : data(value), next(nullptr) {}
    friend class StackMemory;
    friend class StackFile;
};

class StackMemory {
private:
    StackNode* top;
    int cnt;
public:
    StackMemory() : top(nullptr), cnt(0) {}
    ~StackMemory() { clear(); }
    void push(char val) {
        StackNode* n = new StackNode(val);
        n->next = top;
        top = n;
        cnt++;
    }
    char pop() {
        if (!top) throw runtime_error("Пусто");
        char val = top->data;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        cnt--;
        return val;
    }
    
    bool empty() { return !top; }
    int count() { return cnt; }
    void clear() { while (top) pop(); }
    
    void save(const string& f) {
        ofstream out(f);
        for (StackNode* cur = top; cur; cur = cur->next) out << cur->data << endl;
    }
    
    void load(const string& f) {
        clear();
        ifstream in(f);
        string line;
        while (getline(in, line)) if (!line.empty()) push(line[0]);
    }
    
    void print() {
        for (StackNode* cur = top; cur; cur = cur->next) cout << cur->data << " ";
        cout << endl;
    }
};

class StackFile {
    string file;
    int cnt;
    void update() {
        ifstream in(file);
        string line;
        cnt = 0;
        while (getline(in, line)) if (!line.empty()) cnt++;
    }
public:
    StackFile(const string& f) : file(f), cnt(0) { ofstream out(file, ios::trunc); }
    
    void push(char val) {
        ofstream out(file, ios::app);
        out << val << endl;
        cnt++;
    }
    
    char pop() {
        ifstream in(file);
        ofstream tmp("tmp.txt");
        string line, last;
        while (getline(in, line)) if (!line.empty()) last = line;
        in.close();
        in.open(file);
        while (getline(in, line)) if (line != last) tmp << line << endl;
        remove(file.c_str());
        rename("tmp.txt", file.c_str());
        cnt--;
        return last[0];
    }
    
    bool empty() {
        ifstream in(file);
        return in.peek() == EOF;
    }
    
    int count() { update(); return cnt; }
    void clear() { ofstream out(file, ios::trunc); cnt = 0; }
    void save(const string& b) { ifstream src(file); ofstream dst(b); dst << src.rdbuf(); }
    void load(const string& b) { ifstream src(b); ofstream dst(file); dst << src.rdbuf(); update(); }
    
    void print() {
        ifstream in(file);
        string line;
        while (getline(in, line)) if (!line.empty()) cout << line[0] << " ";
        cout << endl;
    }
};

class Processor {
    int mode;
    StackMemory *m1, *m2;
    StackFile *f1, *f2;
    string b1, b2;
    
    void op(int n, string cmd, char val = 0) {
        if (mode == 1) {
            StackMemory* s = n == 1 ? m1 : m2;
            if (cmd == "push") s->push(val);
            else if (cmd == "clear") s->clear();
            else if (cmd == "save") s->save(n == 1 ? b1 : b2);
            else if (cmd == "load") s->load(n == 1 ? b1 : b2);
        } else {
            StackFile* s = n == 1 ? f1 : f2;
            if (cmd == "push") s->push(val);
            else if (cmd == "clear") s->clear();
            else if (cmd == "save") s->save(n == 1 ? b1 : b2);
            else if (cmd == "load") s->load(n == 1 ? b1 : b2);
        }
    }
    
    char popStack(int stackNum) {
        if (mode == 1) {
            return stackNum == 1 ? m1->pop() : m2->pop();
        } else {
            return stackNum == 1 ? f1->pop() : f2->pop();
        }
    }
    
    int cnt(int stackNum) { 
        return mode == 1 ? (stackNum == 1 ? m1->count() : m2->count()) : (stackNum == 1 ? f1->count() : f2->count()); 
    }
    
    bool empty(int stackNum) { 
        return mode == 1 ? (stackNum == 1 ? m1->empty() : m2->empty()) : (stackNum == 1 ? f1->empty() : f2->empty()); 
    }
    
    void print(int stackNum) { 
        cout << "Стек " << stackNum << ": ";
        if (mode == 1) (stackNum == 1 ? m1 : m2)->print();
        else (stackNum == 1 ? f1 : f2)->print();
    }
    
    void inputFromKeyboard(int stackNum) {
        cout << "Введите символы для стека " << stackNum << ": ";
        string s; 
        getline(cin, s);
        op(stackNum, "clear");
        for (char c : s) op(stackNum, "push", c);
    }
    
    void inputFromFile(int stackNum) {
        string f; 
        cout << "Имя файла для стека " << stackNum << ": "; 
        getline(cin, f);
        ifstream in(f);
        // if (!in.is_open()) throw runtime_error("Не удалось открыть файл");
        op(stackNum, "clear");
        string line;
        while (getline(in, line)) {
            for (char c : line) {
                if (!isspace(c)) op(stackNum, "push", c);
            }
        }
    }
    
public:
    Processor(int m, string bk1 = "b1.txt", string bk2 = "b2.txt") : mode(m), b1(bk1), b2(bk2) {
        if (mode == 1) { m1 = new StackMemory(); m2 = new StackMemory(); f1 = f2 = nullptr; }
        else { f1 = new StackFile("s1.txt"); f2 = new StackFile("s2.txt"); m1 = m2 = nullptr; }
    }
    ~Processor() {
        if (m1) delete m1; if (m2) delete m2;
        if (f1) delete f1; if (f2) delete f2;
    }
    void inputStacks() {
        cout << "\n ввод для обоих стеков:\n";
        cout << "1 - с клавиатуры\n";
        cout << "2 - из файла\n";
        cout << "Ваш выбор: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        if (choice == 1) {
            inputFromKeyboard(1);
            inputFromKeyboard(2);
        } 
        else if (choice == 2) {
            inputFromFile(1);
            inputFromFile(2);
        }
    }
    
    void save() { 
    op(1, "save"); 
    op(2, "save"); 
    cout << "Сохранено\n"; 
}

void restore() { 
    op(1, "load"); 
    op(2, "load"); 
    cout << "Восстановлено\n"; 
}

int total() { 
    return cnt(1) + cnt(2); 
}

void demo() {
    int choice;
    do {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
        cout << "1. Показать состояние стеков\n";
        cout << "2. Работа со стеком 1\n";
        cout << "3. Работа со стеком 2\n";
        cout << "5. Восстановить состояние\n";
        cout << "6. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                info();
                break;
                
            case 2:
                stackMenu(1);
                break;
                
            case 3:
                stackMenu(2);
                break;
                
            case 4:
                save();
                break;
                
            case 5:
                restore();
                break;
                
            case 6:
                cout << "Выход из программы\n";
                break;
                
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while(choice != 6);
}

void stackMenu(int stackNum) {
    int choice;
    do {
        cout << "\n=== РАБОТА СО СТЕКОМ " << stackNum << " ===\n";
        cout << "Текущее состояние: ";
        print(stackNum);
        cout << "\n1. Добавить элемент\n";
        cout << "2. Удалить элемент\n";
        cout << "3. Вернуться в главное меню\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: {
                char val;
                cout << "Введите символ для добавления: ";
                cin.get(val);
                cin.ignore();
                op(stackNum, "push", val);
                cout << "Элемент '" << val << "' добавлен в стек " << stackNum << endl;
                break;
            }
            
            case 2: {
                try {
                    if (empty(stackNum)) {
                        cout << "Стек " << stackNum << " пуст. Невозможно удалить элемент.\n";
                    } else {
                        char c = popStack(stackNum);
                        cout << "Из стека " << stackNum << " удален элемент: " << c << endl;
                    }
                } catch (const exception& e) {
                    cout << "Ошибка при удалении: " << e.what() << endl;
                }
                break;
            }
            
            case 3:
                cout << "Возврат в главное меню\n";
                break;
                
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while(choice != 3);
}

void info() {
    cout << "\n=== СОСТОЯНИЕ ===\nРежим: " << (mode == 1 ? "память" : "файл") << endl;
    print(1); 
    print(2); 
    cout << "Всего: " << total() << endl;
}
};

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        int mode; 
        cout << "1-память, 2-файл: "; 
        cin >> mode; 
        cin.ignore();
        
        Processor p(mode);
        
        p.inputStacks();
        
        p.info();
        p.demo();
        
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    return 0;
}