#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

struct el {
    int inf;
    el* next;
};
el *p, *q, *n;

// создания стека;
void stack() {
    p = nullptr;
    int v;
    cout << "элементы стека (0 - конец):" << endl;
    while (true) {
        cin >> v;
        if (v == 0) break;
        q = new el;
        q->inf = v;
        q->next = p;
        p = q;
    }
    n = p; 
    cout << "Текущий стек: ";
    el* cur = n;
    while (cur != nullptr) {
        cout << cur->inf << " ";
        cur = cur->next;
    }
    cout << endl;
}

//создания очереди;
void queue() {
    p = nullptr;
    el* last = nullptr;
    int v;
    cout << "элементы (0 - конец):" << endl;
    while (true) {
        cin >> v;
        if (v == 0) break;
        q = new el;
        q->inf = v;
        q->next = nullptr;
        if (p == nullptr) {
            p = q;
            last = q;
        } else {
            last->next = q;
            last = q;
        }
    }
    n = p;

    cout << "Текущая очередь: ";
    el* cur = n;
    while (cur != nullptr) {
        cout << cur->inf << " ";
        cur = cur->next;
    }
    cout << endl;
}

// Функция для вывода текущего списка (стека/очереди)
void showcur() {
    cout << "Текущий список: ";
    el* cur = n;
    while (cur != nullptr) {
        cout << cur->inf << " ";
        cur = cur->next;
    }
    cout << endl;
}

//прохода по списку;
void walk() {
    el* cur = n;
    cout << "Список: ";
    while (cur != nullptr) {
        cout << cur->inf << " ";
        cur = cur->next;
    }
    cout << endl;
}

//удаления из списка по ключу;
void del(int key) {
    if (n == nullptr) {
        cout << "Список пуст, нечего удалять" << endl;
        return;
    }
    
    el* cur = n;
    el* prev = nullptr;
    bool found = false;
    
    while (cur != nullptr) {
        if (cur->inf == key) {
            found = true;
            if (prev == nullptr) {
                n = cur->next;
                delete cur;
                cur = n;
            } else {
                prev->next = cur->next;
                delete cur;
                cur = prev->next;
            }
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
    if (found) {
        cout << "Элементы со значением " << key << " удалены" << endl;
    } else {
        cout << "Элемент со значением " << key << " не найден" << endl;
    }
    showcur();
}

//добавления элемента за ключевым в список;
void insert(int key, int newv) {
    el* cur = n;
    bool found = false;
    
    while (cur != nullptr) {
        if (cur->inf == key) {
            found = true;
            q = new el;
            q->inf = newv;
            q->next = cur->next;
            cur->next = q;
            cur = q->next;
        } else {
            cur = cur->next;
        }
    }
    
    if (found) {
        cout << "Элемент " << newv << " добавлен после " << key << endl;
    } else {
        cout << "Ключ " << key << " не найден" << endl;
    }
    showcur();
}

//формирования частотного словаря исходные данные в текстовом файле;
void slovar(const string& filename) {
    ifstream file(filename);
    
    map<string, int> freq;
    string word;
    while (file >> word) {
        freq[word]++;
    }
    file.close();
    
    cout << "Частотный словарь:" << endl;
    for (const auto& pair : freq) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

//формирование самоупорядычивающегося списка исходные данные в бинарном файле.
void krutoilist(const string& filename) {
    ifstream file(filename, ios::binary);

    p = nullptr;
    int v;
    int count = 0;
    while (file.read(reinterpret_cast<char*>(&v), sizeof(int))) {
        q = new el;
        q->inf = v;
        q->next = p;
        p = q;
        count++;
    }
    file.close();
    n = p;
    
    cout << "Создан самоупорядочивающийся список из " << count << " элементов" << endl;
    showcur();
}

/*void test(const string& filename) {
    ofstream file(filename, ios::binary);
    int testData[] = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    for (int i = 0; i < 9; i++) {
        file.write(reinterpret_cast<const char*>(&testData[i]), sizeof(int));
    }
    file.close();
}*/

int main() {
    setlocale(LC_ALL, "Russian");
    int ch;
    do {
        cout << "1. Создать стек" << endl;
        cout << "2. Создать очередь" << endl;
        cout << "3. Показать текущий список" << endl;
        cout << "4. Проход по списку" << endl;
        cout << "5. Удалить по ключу" << endl;
        cout << "6. Добавить после ключа" << endl;
        cout << "7. Частотный словарь из текстового файла" << endl;
        cout << "8. Самоупорядочивающийся список из бинарного файла" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> ch;
        
        switch (ch) {
            case 1:
                stack();
                break;
            case 2:
                queue();
                break;
            case 3:
                showcur();
                break;
            case 4:
                walk();
                break;
            case 5: {
                int key;
                cout << "Введите ключ для удаления: ";
                cin >> key;
                del(key);
                break;
            }
            case 6: {
                int key, val;
                cout << "Введите ключ и новое значение: ";
                cin >> key >> val;
                insert(key, val);
                break;
            }
            case 7: {
                string filename;
                cout << "Введите имя текстового файла: ";
                cin >> filename;
                slovar(filename);
                break;
            }
            case 8: {
                string filename;
                cout << "Введите имя бинарного файла: ";
                cin >> filename;
                // test(filename);
                krutoilist(filename);
                break;
            }
            case 0:
                cout << "Программа завершена" << endl;
                break;
            default:
                cout << "Неверный выбор, попробуйте снова" << endl;
        }
    } while (ch != 0);
    
    while (n != nullptr) {
        el* temp = n;
        n = n->next;
        delete temp;
    }
    
    return 0;
}