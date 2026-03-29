#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct tovar {
    char name[50];
    float cost;
    int count;
    int srok;
    char proizvoditel[50];
    tovar* next;
};
struct list {
    tovar* head;
    tovar* tail;
    int size;
};
void constr_list(list &l) {
    l.head = NULL;
    l.tail = NULL;
    l.size = 0;
}
bool chk_empty(list l) {
    return (l.head == NULL);
}
void tovar_in(list &l) { //добавление
    tovar* t = new tovar();
    cout << "Введите наименование товара: ";
    cin.ignore();
    cin.getline(t->name, 50);
    
    cout << "Введите стоимость товара: ";
    cin >> t->cost;
    
    cout << "Введите количество на складе: ";
    cin >> t->count;
    
    cout << "Введите срок хранения (в днях): ";
    cin >> t->srok;
    
    cout << "Введите производителя: ";
    cin.ignore();
    cin.getline(t->proizvoditel, 50);
    
    t->next = NULL;
    
    if (chk_empty(l))
        l.head = t;
    else
        l.tail->next = t;
        
    l.tail = t;
    l.tail->next = l.head; // Делаем кольцо
    l.size++;
}

// По аналогии с теорией: поиск товара
tovar* search(list l, char *n) {
    if (chk_empty(l))
        return NULL;
        
    tovar* start = l.head;
    
    do {
        if (!strcmp(l.head->name, n))
            return l.head;
        l.head = l.head->next;
    } while (l.head != start);
    
    return NULL;
}

// По аналогии с теорией: удаление товара
void tovar_del(list &l, tovar* t) {
    if (chk_empty(l) || t == NULL)
        return;
    
    if (t == l.head) {
        if (l.head == l.tail) { // Один элемент
            l.head = NULL;
            l.tail = NULL;
        } else {
            l.head = t->next;
            l.tail->next = l.head;
        }
        delete t;
        l.size--;
        return;
    }
    
    tovar* r = new tovar();
    r = l.head;
    
    while (r->next != t && r->next != l.head)
        r = r->next;
        
    if (r->next == t) {
        r->next = t->next;
        if (t == l.tail)
            l.tail = r;
        delete t;
        l.size--;
    }
}

// По аналогии с теорией: изменение товара
void tovar_edit(tovar &t, float new_cost, int new_count, int new_srok, char* new_proiz) {
    t.cost = new_cost;
    t.count = new_count;
    t.srok = new_srok;
    strcpy_s(t.proizvoditel, 50, new_proiz);
}

// Запись в файл (новое требование)
void write_to_file(list l, const char* filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }
    
    if (chk_empty(l)) {
        file.close();
        return;
    }
    
    tovar* start = l.head;
    
    do {
        file << l.head->name << endl;
        file << l.head->cost << endl;
        file << l.head->count << endl;
        file << l.head->srok << endl;
        file << l.head->proizvoditel << endl;
        
        l.head = l.head->next;
    } while (l.head != start);
    
    file.close();
}

// Выгрузка из файла (новое требование)
void load_from_file(list &l, const char* filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Файл не найден!" << endl;
        return;
    }
    
    // Очищаем существующий список
    while (!chk_empty(l)) {
        tovar_del(l, l.head);
    }
    
    while (!file.eof()) {
        tovar* t = new tovar();
        
        file.getline(t->name, 50);
        if (strlen(t->name) == 0) {
            delete t;
            break;
        }
        
        file >> t->cost;
        file >> t->count;
        file >> t->srok;
        file.ignore();
        file.getline(t->proizvoditel, 50);
        
        t->next = NULL;
        
        if (chk_empty(l)) {
            l.head = t;
            l.tail = t;
            t->next = l.head;
        } else {
            l.tail->next = t;
            l.tail = t;
            t->next = l.head;
        }
        
        l.size++;
    }
    
    file.close();
}

// Сортировка по наименованию
void sort_by_name(list &l) {
    if (chk_empty(l) || l.size < 2)
        return;
    bool swapped;
    
    do {
        swapped = false;
        tovar* current = l.head;
        tovar* prev = NULL;
        
        do {
            tovar* next = current->next;
            
            if (next != l.head && strcmp(current->name, next->name) > 0) {
                // Меняем местами данные
                tovar temp = *current;
                
                strcpy_s(current->name, 50, next->name);
                current->cost = next->cost;
                current->count = next->count;
                current->srok = next->srok;
                strcpy_s(current->proizvoditel, 50, next->proizvoditel);
                
                strcpy_s(next->name, 50, temp.name);
                next->cost = temp.cost;
                next->count = temp.count;
                next->srok = temp.srok;
                strcpy_s(next->proizvoditel, 50, temp.proizvoditel);
                
                swapped = true;
            }
            
            prev = current;
            current = next;
        } while (current != l.head);
        
    } while (swapped);
}

// Запись отсортированного списка в отдельный файл
void write_sorted_to_file(list l, const char* filename, bool by_name = true) {
    // Создаем копию для сортировки
    list sorted;
    constr_list(sorted);
    
    if (!chk_empty(l)) {
        tovar* start = l.head;
        
        do {
            tovar* t = new tovar();
            strcpy_s(t->name, 50, l.head->name);
            t->cost = l.head->cost;
            t->count = l.head->count;
            t->srok = l.head->srok;
            strcpy_s(t->proizvoditel, 50, l.head->proizvoditel);
            
            if (chk_empty(sorted)) {
                sorted.head = t;
                sorted.tail = t;
                t->next = sorted.head;
            } else {
                sorted.tail->next = t;
                sorted.tail = t;
                t->next = sorted.head;
            }
            
            sorted.size++;
            l.head = l.head->next;
        } while (l.head != start);
    }
    
    // Сортируем копию
    if (by_name)
        sort_by_name(sorted);
    
    // Записываем в файл
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }
    
    file << "Отсортированный список товаров:" << endl;
    file << "================================" << endl;
    
    if (!chk_empty(sorted)) {
        tovar* start = sorted.head;
        int count = 1;
        
        do {
            file << "Товар #" << count << ":" << endl;
            file << "  Наименование: " << sorted.head->name << endl;
            file << "  Стоимость: " << sorted.head->cost << endl;
            file << "  Количество: " << sorted.head->count << endl;
            file << "  Срок хранения: " << sorted.head->srok << " дней" << endl;
            file << "  Производитель: " << sorted.head->proizvoditel << endl;
            file << "-------------------" << endl;
            
            sorted.head = sorted.head->next;
            count++;
        } while (sorted.head != start);
    }
    
    file.close();
}

// Вывод списка на экран
void show_list(list l) {
    if (chk_empty(l)) {
        cout << "Список пуст!" << endl;
        return;
    }
    
    tovar* start = l.head;
    int count = 1;
    
    cout << "\n=== Список товаров ===" << endl;
    
    do {
        cout << "Товар #" << count << ":" << endl;
        cout << "  Наименование: " << l.head->name << endl;
        cout << "  Стоимость: " << l.head->cost << endl;
        cout << "  Количество: " << l.head->count << endl;
        cout << "  Срок хранения: " << l.head->srok << " дней" << endl;
        cout << "  Производитель: " << l.head->proizvoditel << endl;
        cout << "-------------------" << endl;
        
        l.head = l.head->next;
        count++;
    } while (l.head != start);
    
    cout << "Всего товаров: " << l.size << endl;
}
int main() {
    list vars; // Динамический список
    constr_list(vars); // Создаем пустой список
    int choice;
    char search_name[50];
    
    do {
        cout << "\n=== Меню списка товаров ===" << endl;
        cout << "1. Добавить товар" << endl;
        cout << "2. Показать все товары" << endl;
        cout << "3. Найти товар" << endl;
        cout << "4. Удалить товар" << endl;
        cout << "5. Сохранить в файл (tovari.txt)" << endl;
        cout << "6. Загрузить из файла (tovari.txt)" << endl;
        cout << "7. Сохранить отсортированный список (sorted.txt)" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                tovar_in(vars);
                break;          
            case 2:
                show_list(vars);
                break;               
            case 3:
                cout << "Введите наименование для поиска: ";
                cin.ignore();
                cin.getline(search_name, 50);               
                {
                    tovar* found = search(vars, search_name);
                    if (found)
                        cout << "Найден: " << found->name << " (стоимость: " << found->cost << ")" << endl;
                    else
                        cout << "Товар не найден!" << endl;
                }
                break;    
            case 4:
                cout << "Введите наименование для удаления: ";
                cin.ignore();
                cin.getline(search_name, 50); 
                {
                    tovar* found = search(vars, search_name);
                    if (found) {
                        tovar_del(vars, found);
                        cout << "Товар удален!" << endl;
                    } else {
                        cout << "Товар не найден!" << endl;
                    }
                }
                break;   
            case 5:
                write_to_file(vars, "tovari.txt");
                break;   
            case 6:
                load_from_file(vars, "tovari.txt");
                break;  
            case 7:
                write_sorted_to_file(vars, "sorted.txt");
                cout << "Отсортированный список сохранен в sorted.txt" << endl;
                break;    
            case 0:
                cout << "Выход из программы..." << endl;
                break;   
            default:
                cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);
    return 0;
}