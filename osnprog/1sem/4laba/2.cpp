#include <iostream>
#include <cctype>

using namespace std;

struct digit_arrays {
    char* even_digits; //ук массив четных
    char* odd_digits; //нечетных
    int even_count = 0;
    int odd_count = 0;
};

int main() {
    const int MAX_CHARS = 80;
    char* input_str = new char[MAX_CHARS + 1];
    
    cout << "Введите строку (максимум 80 символов):\n";
    cin.getline(input_str, MAX_CHARS + 1);
    
    digit_arrays arrays;
    
    // Первый проход - подсчет цифр
    char* ptr = input_str;
    while (*ptr != '\0') {
        if (isdigit(*ptr)) {
            int digit = *ptr - '0';
            if (digit == 0 || digit % 2 == 0) {
                arrays.even_count++;
            } else {
                arrays.odd_count++;
            }
        }
        ptr++;
    }
    
    // Выделение памяти для массивов
    arrays.even_digits = new char[arrays.even_count + 1];
    arrays.odd_digits = new char[arrays.odd_count + 1];
    
    // Второй проход - заполнение массивов
    ptr = input_str;
    int even_index = 0, odd_index = 0;
    
    while (*ptr != '\0') {
        if (isdigit(*ptr)) {
            int digit = *ptr - '0';
            if (digit == 0 || digit % 2 == 0) {
                arrays.even_digits[even_index] = *ptr;
                even_index++;
            } else {
                arrays.odd_digits[odd_index] = *ptr;
                odd_index++;
            }
        }
        ptr++;
    }
    
    // Завершаем строки
    arrays.even_digits[arrays.even_count] = '\0';
    arrays.odd_digits[arrays.odd_count] = '\0';
    
    // Вывод результатов
    if (arrays.even_count > 0) {
        cout << "Четные цифры: ";
        for (int i = 0; i < arrays.even_count; i++) {
            cout << arrays.even_digits[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Четные цифры отсутствуют" << endl;
    }
    
    if (arrays.odd_count > 0) {
        cout << "Нечетные цифры: ";
        for (int i = 0; i < arrays.odd_count; i++) {
            cout << arrays.odd_digits[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Нечетные цифры отсутствуют" << endl;
    }
    
    // Освобождение памяти
    delete[] input_str;
    delete[] arrays.even_digits;
    delete[] arrays.odd_digits;
    
    return 0;
}