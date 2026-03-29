#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
using namespace std;

// Функция для загрузки строки по логическому номеру
string loadStringByIndex(const char* filename, int index) {
    fstream file;
    file.open(filename, ios::in | ios::binary);
    
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для чтения" << endl;
        return "";
    }
    
    // Читаем размерность массива указателей
    int arraySize;
    file.read((char*)&arraySize, sizeof(arraySize));
    
    // Проверяем корректность индекса
    if (index < 0 || index >= arraySize) {
        cout << "Ошибка: индекс " << index << " вне диапазона [0, " << arraySize-1 << "]" << endl;
        file.close();
        return "";
    }
    
    // Читаем позицию указателя для заданного индекса
    long pointerPosition;
    file.seekg(sizeof(int) + index * sizeof(long), ios::beg);
    file.read((char*)&pointerPosition, sizeof(pointerPosition));
    
    // Переходим к позиции строки
    file.seekg(pointerPosition, ios::beg);
    
    // Читаем размер строки
    int stringSize;
    file.read((char*)&stringSize, sizeof(stringSize));
    
    // Читаем саму строку
    char* buffer = new char[stringSize + 1];
    file.read(buffer, stringSize);
    buffer[stringSize] = '\0';
    
    string result = buffer;
    delete[] buffer;
    
    file.close();
    return result;
}

int main() {
    fstream file;
    
    // 1. СОЗДАНИЕ ФАЙЛА С МАССИВОМ УКАЗАТЕЛЕЙ НА СТРОКИ
    cout << "Создание файла с массивом указателей на строки\n";
    
    // Массив строк (записи переменной длины)
    vector<string> strings = {
        "Первая строка в файле",
        "Вторая запись переменной длины",
        "Третья строка с данными",
        "Четвертая текстовая запись",
        "Пятая и последняя строка в массиве"
    };
    
    int arraySize = strings.size(); // Размерность массива указателей
    
    file.open("strings.dat", ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "Ошибка создания файла" << endl;
        return 1;
    }
    
    // 1. Записываем размерность массива указателей
    file.write((char*)&arraySize, sizeof(arraySize));
    
    // 2. Резервируем место для массива указателей
    // Сначала записываем нули, потом вернемся и заполним
    vector<long> pointers(arraySize, 0);
    for (int i = 0; i < arraySize; i++) {
        file.write((char*)&pointers[i], sizeof(long));
    }
    
    // 3. Записываем строки и сохраняем их позиции
    for (int i = 0; i < arraySize; i++) {
        // Сохраняем текущую позицию (это позиция строки)
        long stringPosition = file.tellp();
        
        // Записываем строку
        int stringSize = strings[i].size();
        file.write((char*)&stringSize, sizeof(stringSize));
        file.write(strings[i].c_str(), stringSize);
        
        // Сохраняем позицию строки в массиве
        pointers[i] = stringPosition;
    }
    
    // 4. Возвращаемся и записываем правильные указатели
    file.seekp(sizeof(int), ios::beg); // Пропускаем размерность массива
    for (int i = 0; i < arraySize; i++) {
        file.write((char*)&pointers[i], sizeof(long));
    }
    
    file.close();
    
    cout << "Файл создан. Размерность массива указателей: " << arraySize << endl;
    
    // 2. ПРОСМОТР СОДЕРЖИМОГО ФАЙЛА
    cout << "\nСодержимое файла:\n";
    
    file.open("strings.dat", ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для чтения" << endl;
        return 1;
    }
    
    // Читаем размерность массива
    int readArraySize;
    file.read((char*)&readArraySize, sizeof(readArraySize));
    cout << "Размерность массива указателей: " << readArraySize << endl;
    
    // Читаем и выводим указатели
    cout << "Массив указателей:\n";
    for (int i = 0; i < readArraySize; i++) {
        long pointer;
        file.read((char*)&pointer, sizeof(long));
        cout << "  Указатель[" << i << "] = " << pointer << endl;
    }
    
    // Читаем и выводим строки
    cout << "\nСтроки в файле:\n";
    while (!file.eof()) {
        int stringSize;
        file.read((char*)&stringSize, sizeof(stringSize));
        
        if (file.eof()) break;
        
        char* buffer = new char[stringSize + 1];
        file.read(buffer, stringSize);
        buffer[stringSize] = '\0';
        
        cout << "  Длина: " << stringSize << ", Строка: " << buffer << endl;
        
        delete[] buffer;
    }
    
    if (file.eof()) {
        file.clear();
    }
    file.close();
    
    // 3. ТЕСТИРОВАНИЕ ФУНКЦИИ ЗАГРУЗКИ СТРОКИ ПО ЛОГИЧЕСКОМУ НОМЕРУ
    cout << "\nТестирование функции загрузки строки по логическому номеру:\n";
    
    // Загружаем несколько строк по индексу
    for (int i = 0; i < arraySize; i++) {
        string loadedString = loadStringByIndex("strings.dat", i);
        cout << "Строка [" << i << "]: " << loadedString << endl;
    }
    
    // Тестируем неверные индексы
    cout << "\nТестирование неверных индексов:\n";
    string invalid1 = loadStringByIndex("strings.dat", -1);
    string invalid2 = loadStringByIndex("strings.dat", arraySize);
    string invalid3 = loadStringByIndex("strings.dat", 100);
    
    // 4. ИНТЕРАКТИВНЫЙ РЕЖИМ
    cout << "\nИнтерактивный режим загрузки строк:\n";
    cout << "Введите индекс строки для загрузки (0-" << arraySize-1 << "): ";
    
    int choice;
    string choiceStr;
    getline(cin, choiceStr);
    stringstream ss(choiceStr);
    ss >> choice;
    
    while (choice >= 0 && choice < arraySize) {
        string loadedString = loadStringByIndex("strings.dat", choice);
        if (!loadedString.empty()) {
            cout << "Загруженная строка [" << choice << "]: " << loadedString << endl;
        }
        
        cout << "\nВведите следующий индекс (или отрицательное число для выхода): ";
        getline(cin, choiceStr);
        stringstream ss2(choiceStr);
        ss2 >> choice;
    }
    
    cout << "Программа завершена.\n";
    
    return 0;
}