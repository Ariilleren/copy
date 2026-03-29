#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

// Структура элемента списка
struct el {
    int inf;
    el* next;
};

el *p, *q, *n;

// 1. Создание стека (LIFO)
void createStack() {
    p = nullptr;
    int value;
    cout << "Введите элементы стека (0 - конец ввода):" << endl;
    while (true) {
        cin >> value;
        if (value == 0) break;
        q = new el;
        q->inf = value;
        q->next = p;
        p = q;
    }
    n = p; // сохраняем начало
}

// 2. Создание очереди (FIFO)
void createQueue() {
    p = nullptr;
    el* last = nullptr;
    int value;
    cout << "Введите элементы очереди (0 - конец ввода):" << endl;
    while (true) {
        cin >> value;
        if (value == 0) break;
        q = new el;
        q->inf = value;
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

// 3. Проход по списку с выводом
void traverseList() {
    el* current = n;
    cout << "Список: ";
    while (current != nullptr) {
        cout << current->inf << " ";
        current = current->next;
    }
    cout << endl;
}

// 4. Удаление из списка по ключу
void deleteByKey(int key) {
    el* current = n;
    el* prev = nullptr;
    
    while (current != nullptr) {
        if (current->inf == key) {
            if (prev == nullptr) {
                // Удаляем первый элемент
                n = current->next;
                delete current;
                current = n;
            } else {
                prev->next = current->next;
                delete current;
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// 5. Добавление элемента за ключевым
void insertAfterKey(int key, int newValue) {
    el* current = n;
    while (current != nullptr) {
        if (current->inf == key) {
            q = new el;
            q->inf = newValue;
            q->next = current->next;
            current->next = q;
            current = q->next;
        } else {
            current = current->next;
        }
    }
}

// 6. Формирование частотного словаря из текстового файла
void createFrequencyDictionary(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return;
    }
    
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

// 7. Формирование самоупорядочивающегося списка из бинарного файла
void createSelfOrderingList(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Не удалось открыть бинарный файл" << endl;
        return;
    }
    
    p = nullptr;
    int value;
    while (file.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        // Самоупорядочивание: каждый новый элемент становится головой
        q = new el;
        q->inf = value;
        q->next = p;
        p = q;
    }
    file.close();
    n = p;
    cout << "Самоупорядочивающийся список сформирован" << endl;
}

// Вспомогательная функция для записи тестовых данных в бинарный файл
void writeBinaryTestFile(const string& filename) {
    ofstream file(filename, ios::binary);
    int testData[] = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    for (int i = 0; i < 9; i++) {
        file.write(reinterpret_cast<const char*>(&testData[i]), sizeof(int));
    }
    file.close();
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    int choice;
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
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                createStack();
                break;
            case 2:
                createQueue();
                break;
            case 3:
                traverseList();
                break;
            case 4: {
                int key;
                cout << "Введите ключ для удаления: ";
                cin >> key;
                deleteByKey(key);
                break;
            }
            case 5: {
                int key, val;
                cout << "Введите ключ и новое значение: ";
                cin >> key >> val;
                insertAfterKey(key, val);
                break;
            }
            case 6: {
                string filename;
                cout << "Введите имя текстового файла: ";
                cin >> filename;
                createFrequencyDictionary(filename);
                break;
            }
            case 7: {
                string filename;
                cout << "Введите имя бинарного файла: ";
                cin >> filename;
                // Для теста создаем бинарный файл, если его нет
                writeBinaryTestFile(filename);
                createSelfOrderingList(filename);
                break;
            }
        }
    } while (choice != 0);
    
    return 0;
}