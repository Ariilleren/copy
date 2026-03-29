#include <iostream>
#include <cctype>

using namespace std;

int main() {
    int MAX_CHARS = 80;
    
    string str;
    char *symbols = new char[MAX_CHARS];
    cout << "Введите текст:\n";
    getline(cin, str);

    int count = 0;
    for (int i = 0; i < str.length() && count < MAX_CHARS; i++) {
        symbols[count] = str[i];
        count++;
    }

    int even_count = 0;
    int odd_count = 0;

    for (int i = 0; i < count; i++) {
        if (isdigit(symbols[i])) {
            int num = (int)symbols[i] - '0';
            if (num % 2 == 0) {
                even_count++;
            } else {
                odd_count++;
            }
        }
    }

    int *even_nums = new int[even_count];
    int *odd_nums = new int[odd_count];
    int even_index = 0;
    int odd_index = 0;

    for (int i = 0; i < count; i++) {
        if (isdigit(symbols[i])) {
            int num = (int)symbols[i] - '0';
            if (num % 2 == 0) {
                even_nums[even_index] = num;
                even_index++;
            } else {
                odd_nums[odd_index] = num;
                odd_index++;
            }
        }
    }

    if (even_count > 0) {
        cout << "Четные цифры:\n{ ";
        for (int i = 0; i < even_count; i++) {
            cout << even_nums[i] << " ";
        }
        cout << "}" << endl;
    } else {
        cout << "Четные цифры отсутствуют" << endl;
    }

    if (odd_count > 0) {
        cout << "Нечетные цифры:\n{ ";
        for (int i = 0; i < odd_count; i++) {
            cout << odd_nums[i] << " ";
        }
        cout << "}" << endl;
    } else {
        cout << "Нечетные цифры отсутствуют" << endl;
    }

    delete[] symbols;
    delete[] even_nums;
    delete[] odd_nums;

    return 0;
}