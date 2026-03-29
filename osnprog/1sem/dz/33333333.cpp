#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> s;
    
    cout << "=== РАБОТА СО СТЕКОМ ===" << endl;
    
    // 1. Добавление элементов
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    
    cout << "После добавления 10, 20, 30, 40:" << endl;
    cout << "Размер стека: " << s.size() << endl;
    
    // 2. Просмотр вершины
    cout << "Вершина стека: " << s.top() << endl;
    
    // 3. Удаление
    s.pop();
    cout << "\nПосле pop():" << endl;
    cout << "Вершина: " << s.top() << endl;
    cout << "Размер: " << s.size() << endl;
    
    // 4. Извлечение всех элементов
    cout << "\nИзвлекаем все элементы:" << endl;
    while (!s.empty()) {
        cout << "Вершина: " << s.top() << " | ";
        s.pop();
        cout << "Размер после pop: " << s.size() << endl;
    }
    
    // 5. Проверка на пустоту
    cout << "\nСтек пустой? " << (s.empty() ? "Да" : "Нет") << endl;
    
    return 0;
}