#include <iostream>
#include <string>

using namespace std;

int main() {
    string text;
    cout << "Текст: ";
    getline(cin, text);
    
    char symbol;
    cout << "Символ: ";
    cin >> symbol;
    cin.ignore(); 
    
    string substring;
    cout << "Подстрока: ";
    getline(cin, substring);
    
    string result;
    bool inserted = false;
    
    for (int i = 0; i < text.length(); ++i) {
        result += text[i];
        
        if (!inserted && text[i] == symbol) {
            result += substring;
            inserted = true;
        }
    }
    cout << "Результат: " << result << endl;   
    return 0;
}