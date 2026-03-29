#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Tovar {
    string name;
    double price;
    int kolvo;
    int srok;
    string proizvod;
    Tovar* next;
};

Tovar* Dobavit(string n, double pr, int k, int s, string proiz) {
    Tovar* t = new Tovar;
    t->name = n;
    t->price = pr;
    t->kolvo = k;
    t->srok = s;
    t->proizvod = proiz;
    t->next = nullptr;
    return t;
}

void addn(Tovar*& b, string n, double p, int q, int sl, string m) {
    Tovar* a = Dobavit(n, p, q, sl, m);
    if (!b) {
        b = a;
        b->next = b;
    }
    else {
        Tovar* cur = b;
        while (cur->next != b) cur = cur->next;
        cur->next = a;
        a->next = b;
    }
    cout << "Элемент добавлен\n";
}

void Show(Tovar* b) {
    if (!b) {
        cout << "Список пуст!\n";
        return;
    }
    Tovar* cur = b;
    int index = 1;
    cout << "| № | Наименование | Цена | Кол-во | Срок | Производитель |\n";
    do {
        cout << "| " << index++ << " | " << cur->name << " | " << cur->price  << " | " << cur->kolvo << " | " << cur->srok  << " | " << cur->proizvod << " |\n";
        cur = cur->next;
    } while (cur != b);
}

void DeletePoNazv(Tovar*& b, string naz) {
    if (!b) {
        cout << "Список пуст";
        return;
    }
    Tovar* cur = b;
    Tovar* prev = nullptr;
    do {
        if (cur->name == naz) {
            if (cur->next == cur) {
                delete cur;
                b = nullptr;
                cout << "Элемент удален.\n";
                return;
            }
            if (cur == b) {
                Tovar* last = b;
                while (last->next != b) last = last->next;
                b = cur->next;
                last->next = b;
            }
            else {
                prev->next = cur->next;
            }
            delete cur;
            cout << "Элемент удален\n";
            return;
        }
        prev = cur;
        cur = cur->next;
    } while (cur != b);
    cout << "Элемент не найден"<< endl;
}

void EditElement(Tovar*& b) {
    if (!b) {
        cout << "Список пуст!\n";
        return;
    }
    
    Show(b); 
    int index;
    cout << "Введите номер элемента для редактирования: ";
    cin >> index;

    Tovar* cur = b;
    int count = 1;

    do {
        if (count == index) {
            cout << "\nРедактирование элемента: " << cur->name << "\n";
            cout << "1. Наименование: " << cur->name << "\n";
            cout << "2. Цена: " << cur->price << "\n";
            cout << "3. Количество: " << cur->kolvo << "\n";
            cout << "4. Срок хранения: " << cur->srok << "\n";
            cout << "5. Производитель: " << cur->proizvod << "\n";
            cout << "6. Отмена редактирования\n";
            
            int choice;
            cout << "Выберите поле для редактирования (1-6): ";
            cin >> choice;
            cin.ignore();
            
            switch(choice) {
                case 1: {
                    cout << "Введите новое наименование: ";
                    getline(cin, cur->name);
                    cout << "Наименование изменено\n";
                    break;
                }
                case 2: {
                    cout << "Введите новую цену: ";
                    cin >> cur->price;
                    cout << "Цена изменена\n";
                    break;
                }
                case 3: {
                    cout << "Введите новое количество: ";
                    cin >> cur->kolvo;
                    cout << "Количество изменено\n";
                    break;
                }
                case 4: {
                    cout << "Введите новый срок хранения: ";
                    cin >> cur->srok;
                    cout << "Срок хранения изменен!\n";
                    break;
                }
                case 5: {
                    cout << "Введите нового производителя: ";
                    //cin.ignore();
                    getline(cin, cur->proizvod);
                    cout << "Производитель изменен\n";
                    break;
                }
                case 6: {
                    cout << "Редактирование отменено.\n";
                    break;
                }
                default: {
                    cout << "Неверный выбор\n";
                    break;
                }
            }
            return;
        }
        count++;
        cur = cur->next;
    } while (cur != b);
    
    cout << "Элемент с номером " << index << " не найден\n";
}

void SortPoNazv(Tovar*& b) {
    if (!b || b->next == b) return;
    
    bool swapped;
    do {
        swapped = false;
        Tovar* cur = b; 
        do {
            if (cur->next != b && cur->name > cur->next->name) {
                swap(cur->name, cur->next->name);
                swap(cur->price, cur->next->price);
                swap(cur->kolvo, cur->next->kolvo);
                swap(cur->srok, cur->next->srok);
                swap(cur->proizvod, cur->next->proizvod);
                swapped = true;
            }
            cur = cur->next;
        } while (cur->next != b); 
    } while (swapped);   
    cout << "Сортировка по наименованию выполнена\n";
}

void SortPoSroku(Tovar*& b) {
    if (!b || b->next == b) return;
    
    bool swapped;
    do {
        swapped = false;
        Tovar* cur = b; 
        do {
            if (cur->next != b && cur->srok > cur->next->srok) {
                swap(cur->name, cur->next->name);
                swap(cur->price, cur->next->price);
                swap(cur->kolvo, cur->next->kolvo);
                swap(cur->srok, cur->next->srok);
                swap(cur->proizvod, cur->next->proizvod);
                swapped = true;
            }
            cur = cur->next;
        } while (cur->next != b);
    } while (swapped);   
    cout << "Сортировка по сроку хранения выполнена\n";
}

void ClearList(Tovar*& b) {
    if (!b) return;
    
    Tovar* cur = b;
    Tovar* nextNode;
    
    do {
        nextNode = cur->next;
        delete cur;
        cur = nextNode;
    } while (cur != b);
    
    b = nullptr;
}

void saveToFile(const string& filename, Tovar* b) {
    ofstream out(filename);
    if (!b) {
        out.close();
        return;
    }
    Tovar* cur = b;
    do {
        out << cur->name << " " << cur->price << " "
            << cur->kolvo << " " << cur->srok << " "
            << cur->proizvod << "\n";
        cur = cur->next;
    } while (cur != b);
    
    out.close();
    cout << "Данные сохранены в файл " << filename << "\n";
}

int main() {
    Tovar* b = nullptr;
    
    string fileName;
    cout << "Введите имя файла -> ";
    cin >> fileName;
    
    ifstream inp(fileName);
    if (inp.is_open()) {
        string name, proizvod;
        double price;
        int kolvo, srok;
        
        while (inp >> name >> price >> kolvo >> srok >> proizvod) {
            addn(b, name, price, kolvo, srok, proizvod);
        }
        inp.close();
        cout << "Данные загружены из файла " << fileName << "\n";
    } else {
        cout << "Файл не найден. Будет создан новый список.\n";
    }
    
    int choice = 0;
    
    while (choice != 7) {

        cout << "1 Вывод товаров\n";
        cout << "2 Сортировка по наименованию\n";
        cout << "3 Сортировка по сроку хранения\n";
        cout << "4 Добавить товар\n";
        cout << "5 Удалить товар\n";
        cout << "6 Редактировать товар\n";
        cout << "7 Выход из программы\n";
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                cout << "\nВсе товары:\n";
                Show(b);
                break;
            } 
            case 2: {
                cout << "\nСортировка по наименованию\n";
                SortPoNazv(b);
                Show(b);
                break;
            }
            case 3: {
                cout << "\nСортировка по сроку хранения\n";
                SortPoSroku(b);
                Show(b);  
                break;
            } 
            case 4: {
                cout << "\nДобавление товара\n";
                string name, proizvod;
                double price;
                int kolvo, srok;
                
                cout << "Введите наименование: ";
                cin >> name;
                cout << "Введите стоимость: ";
                cin >> price;
                cout << "Введите количество: ";
                cin >> kolvo;
                cout << "Введите срок хранения: ";
                cin >> srok;
                cout << "Введите производителя: ";
                cin >> proizvod;
                
                addn(b, name, price, kolvo, srok, proizvod);
                cout << "Товар добавлен!\n";
                break;
            }   
            case 5: { 
                cout << "\nУдаление товара\n";
                string nazvanie;
                cout << "Введите наименование товара для удаления: ";
                cin >> nazvanie;
                DeletePoNazv(b, nazvanie);
                break;
            }
            case 6: {
                cout << "\nРедактирование товара\n";
                EditElement(b);
                break;
            }
            case 7: {
                cout << "\nВыход из программы\n";
                saveToFile(fileName, b);
                break;
            }
            default: {
                cout << "\nОшибка! Введите число от 1 до 7.\n";
                break;
            }
        }
    }
    
    ClearList(b);
    return 0;
}