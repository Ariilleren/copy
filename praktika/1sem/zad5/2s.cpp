#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

struct str {
    char* data;
};

// Убрали перегрузку оператора >>, будем читать обычным способом

int rewrite(vector<str*> strings) {
    fstream file;
    file.open("strings.txt", ios::out | ios::binary);
    
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи" << endl;
        return 1;
    }
    
    file.seekp(0, ios::beg);  // Используем ios::beg
    
    for (int i = 0; i < strings.size(); i++) {  // Обычный цикл for
        if (strings[i] != NULL && strings[i]->data != NULL) {
            int length = strlen(strings[i]->data);  // Используем int
            file.write((char*)&length, sizeof(length));  // Простое приведение типа
            file.write(strings[i]->data, length);
        }
    }
    
    int endMarker = 0;  // Используем int
    file.write((char*)&endMarker, sizeof(endMarker));
    
    file.close();
    return 0;
}

int add_str(vector<str*> &strings, const string &newString, int logicalIndex) {
    if (logicalIndex < 0 || logicalIndex > strings.size()) {  // Исправили оператор
        cout << "Ошибка: неверный логический индекс " << logicalIndex 
             << ". Допустимый диапазон: 0-" << strings.size() << endl;
        return -1;
    }
    
    str* newRecord = new str;
    newRecord->data = new char[newString.length() + 1];
    strcpy(newRecord->data, newString.c_str());
    
    strings.insert(strings.begin() + logicalIndex, newRecord);
    rewrite(strings);
    
    cout << "Строка добавлена на позицию " << logicalIndex << endl;
    return 0;
}

void del_strings(vector<str*> &strings) {
    for (int i = 0; i < strings.size(); i++) {  // Обычный цикл for
        if (strings[i] != NULL) {
            delete[] strings[i]->data;
            delete strings[i];
        }
    }
    strings.clear();
}

int main() {
    fstream file;
    vector<str*> strings;
    
    // Чтение файла
    file.open("strings.txt", ios::in | ios::binary);
    
    if (file.is_open()) {
        while (true) {
            int length;  // Используем int вместо size_t
            file.read((char*)&length, sizeof(length));
            
            if (length == 0 || file.eof()) {  // Исправили оператор
                break;
            }
            
            str* record = new str;
            record->data = new char[length + 1];
            file.read(record->data, length);
            record->data[length] = '\0';
            
            strings.push_back(record);
        }
        file.close();
    } else {
        cout << "Файл не найден. Будет создан новый." << endl;
    }
    
    cout << "\nВсего загружено строк: " << strings.size() << endl;
    
    cout << "\nДля добавления строки по индексу введите 1\n"
         << "Для вывода всех строк введите 2\n"
         << "Для сохранения и выхода введите 0\n";
    
    int choice; 
    cin >> choice;
    cin.ignore();
    
    while (choice != 0) {
        switch (choice) {
        case 1: {
            string newString;
            int index;
            
            cout << "Введите новую строку: ";
            getline(cin, newString);
            
            cout << "Введите логический номер для вставки (0-" << strings.size() << "): ";
            cin >> index;
            cin.ignore();
            
            add_str(strings, newString, index);
            
            cout << "\nТекущий список строк:" << endl;
            for (int i = 0; i < strings.size(); i++) {  // Обычный цикл for
                cout << "[" << i << "]: " << strings[i]->data << endl;
            }
            
            cout << "\nДля добавления строки по индексу введите 1\n"
                 << "Для вывода всех строк введите 2\n"
                 << "Для сохранения и выхода введите 0\n";
            cin >> choice;
            cin.ignore();
            break;
        }
        case 2: {
            cout << "\nСписок всех строк:\n" << endl;
            for (int i = 0; i < strings.size(); i++) {  // Обычный цикл for
                cout << "[" << i << "]: " << strings[i]->data << endl;
            }
            cout << "Всего строк: " << strings.size() << endl;
            
            cout << "\nДля добавления строки по индексу введите 1\n"
                 << "Для вывода всех строк введите 2\n"
                 << "Для сохранения и выхода введите 0\n";
            cin >> choice;
            cin.ignore();
            break;
        }
        case 0:
            rewrite(strings);
            del_strings(strings);
            cout << "Данные сохранены. Выход из программы." << endl;
            break;  // Убрали exit(0), используем break
        default:
            cout << "Неверное значение" << endl;
            cout << "\nДля добавления строки по индексу введите 1\n"
                 << "Для вывода всех строк введите 2\n"
                 << "Для сохранения и выхода введите 0\n";
            cin >> choice;
            cin.ignore();
        }
        
        if (choice != 0) {
            cout << "\nДля добавления строки по индексу введите 1\n"
                 << "Для вывода всех строк введите 2\n"
                 << "Для сохранения и выхода введите 0\n";
            cin >> choice;
            cin.ignore();
        }
    }
    
    rewrite(strings);
    del_strings(strings);
    
    return 0;
}