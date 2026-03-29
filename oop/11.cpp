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
    el* cur = n;
    el* prev = nullptr;
    
    while (cur != nullptr) {
        if (cur->inf == key) {
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
}

//добавления элемента за ключевым в список;
void insert(int key, int newv) {
    el* cur = n;
    while (cur != nullptr) {
        if (cur->inf == key) {
            q = new el;
            q->inf = newv;
            q->next = cur->next;
            cur->next = q;
            cur = q->next;
        } else {
            cur = cur->next;
        }
    }
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
    while (file.read(reinterpret_cast<char*>(&v), sizeof(int))) {
        //каждый новый элемент становится головой
        q = new el;
        q->inf = v;
        q->next = p;
        p = q;
    }
    file.close();
    n = p;
    cout << "все" << endl;
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
        cout << "\nМеню:\n";
        cout << "1. Создать стек\n";
        cout << "2. Создать очередь\n";
        cout << "3. Проход по списку\n";
        cout << "4. Удалить по ключу\n";
        cout << "5. Добавить после ключа\n";
        cout << "6. Частотный словарь из текстового файла\n";
        cout << "7. Самоупорядочивающийся список из бинарного файла\n";
        cout << "0. Выход\n";
        cin >> ch;
        switch (ch) {
            case 1:
                stack();
                break;
            case 2:
                queue();
                break;
            case 3:
                walk();
                break;
            case 4: {
                int key;
                cout << "ключ: ";
                cin >> key;
                del(key);
                break;
            }
            case 5: {
                int key, val;
                cout << "ключ и новое значение: ";
                cin >> key >> val;
                insert(key, val);
                break;
            }
            case 6: {
                string filename;
                cout << "имя файла: ";
                cin >> filename;
                slovar(filename);
                break;
            }
            case 7: {
                string filename;
                cout << "имя файла: ";
                cin >> filename;
             //   test(filename);
                krutoilist(filename);
                break;
            }
        }
    } while (ch != 0);
    return 0;
}