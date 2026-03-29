#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct str {
    string data; 
};

istream& operator>>(istream &is, str &record) {
    getline(is, record.data);
    return is;
}

int rewrite(vector<str>& strings) {
    fstream file("strings.txt", ios::out | ios::binary | ios::trunc);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return -1;
    }
    
    for (const auto& str_record : strings) {
        size_t length = str_record.data.length();
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(str_record.data.c_str(), length);
    }
    
    size_t endMarker = 0;
    file.write(reinterpret_cast<const char*>(&endMarker), sizeof(endMarker));
    
    return 0;
}

int add_str(vector<str>& strings, const string &newString, int logicalIndex) {
    if (logicalIndex < 0 || logicalIndex > strings.size()) {
        cout << "Ошибка: неверный логический индекс " << logicalIndex 
             << ". Допустимый диапазон: 0-" << strings.size() << endl;
        return -1;
    }
    
    str newRecord;
    newRecord.data = newString;
    
    strings.insert(strings.begin() + logicalIndex, newRecord);
    
    if (rewrite(strings) != 0) {
        cout << "Ошибка при сохранении в файл!" << endl;
        return -1;
    }
    
    cout << "Строка добавлена на позицию " << logicalIndex << endl;
    return 0;
}

int load_strings(vector<str>& strings) {
    ifstream file("strings.txt", ios::in | ios::binary);
    
    if (!file.is_open()) {
        return 0;
    }
    
    while (true) {
        size_t length;
        file.read(reinterpret_cast<char*>(&length), sizeof(length));
        
        if (length == 0 || file.eof()) {
            break;
        }
        
        if (!file) {
            cerr << "Ошибка чтения длины строки из файла!" << endl;
            return -1;
        }
        
        str record;
        record.data.resize(length);
        file.read(&record.data[0], length);
        
        if (!file) {
            cerr << "Ошибка чтения строки из файла!" << endl;
            return -1;
        }
        
        strings.push_back(record);
    }
    
    return strings.size();
}

void print_menu() {
    cout << "\nМеню:\n"
         << "1 - Добавить строку по индексу\n"
         << "2 - Вывести все строки\n"
         << "0 - Сохранить и выйти\n"
         << "Выберите действие: ";
}

int main() {
    vector<str> strings;  // Теперь вектор объектов, а не указателей
    
    // Загрузка строк из файла
    int loadedCount = load_strings(strings);
    if (loadedCount < 0) {
        cerr << "Ошибка при загрузке файла!" << endl;
        return 1;
    }
    
    cout << "\nВсего загружено строк: " << strings.size() << endl;
    
    int choice;
    print_menu();
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
            
            if (add_str(strings, newString, index) == 0) {
                cout << "\nТекущий список строк:" << endl;
                for (size_t i = 0; i < strings.size(); i++) {
                    cout << "[" << i << "]: " << strings[i].data << endl;
                }
            }
            
            print_menu();
            cin >> choice;
            cin.ignore();
            break;
        }
        case 2: {
            cout << "\nСписок всех строк:\n" << endl;
            if (strings.empty()) {
                cout << "Список строк пуст." << endl;
            } else {
                for (size_t i = 0; i < strings.size(); i++) {
                    cout << "[" << i << "]: " << strings[i].data << endl;
                }
            }
            cout << "Всего строк: " << strings.size() << endl;
            
            print_menu();
            cin >> choice;
            cin.ignore();
            break;
        }
        case 0:
            break;
        default:
            cout << "Неверное значение!" << endl;
            print_menu();
            cin >> choice;
            cin.ignore();
        }
    }
    
    // Сохраняем перед выходом
    if (rewrite(strings) != 0) {
        cerr << "Ошибка при сохранении данных!" << endl;
        return 1;
    }
    
    cout << "Данные сохранены. Выход из программы." << endl;
    
    return 0;
}

