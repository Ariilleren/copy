#include <iostream>
#include <string>
#include <cctype>

using namespace std;


int main() {
    string text;
    cout << "Текст: ";
    getline(cin, text);
    
    char symbol;
    cout << "Символ: ";
    cin >> symbol;
    
    string result;
    
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] != symbol) {
            result += text[i];
        }
    }
    
    cout << "Результат: " << result << endl;

    
    return 0;
}