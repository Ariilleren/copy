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
    cout << "Элемент добавлен";
}

void Show(Tovar* b) {
    if (!b) {
        cout << "Список пуст!\n";
        return;
    }   
    Tovar* cur = b;
    cout << "| Наименование | Цена | Количество | Срок | Производитель |\n";
    do {
        cout << "| " << cur->name << " | " << cur->price << " | " << cur->kolvo << " | " << cur->srok << " | " << cur->proizvod << " |\n";
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
            if (cur->next == cur) { //Ед элемент
                delete cur;
                b = nullptr;
                cout << "Элемент удален.\n";
                return;
            }
            if (cur == b) { //первый элемент
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
void SortPoNazv(Tovar*& b) {
    if (!b || b->next == b) return;
    bool found;
    do {
        found = false;
        Tovar* cur = b; 
        do {
            if (cur->next != b && cur->name > cur->next->name) {
                swap(cur->name, cur->next->name);
                swap(cur->price, cur->next->price);
                swap(cur->kolvo, cur->next->kolvo);
                swap(cur->srok, cur->next->srok);
                swap(cur->proizvod, cur->next->proizvod);
                found = true;
            }
            cur = cur->next;
        } while (cur->next != b); 
    } while (found);   
    cout << "Сортировка по наименованию выполнена\n";
}

void SortPoSroku(Tovar*& b) {
    if (!b || b->next == b) return;
    bool found;
    do {
        found = false;
        Tovar* cur = b; 
        do {
            if (cur->next != b && cur->srok > cur->next->srok) {
                swap(cur->name, cur->next->name);
                swap(cur->price, cur->next->price);
                swap(cur->kolvo, cur->next->kolvo);
                swap(cur->srok, cur->next->srok);
                swap(cur->proizvod, cur->next->proizvod);
                found = true;
            }
            cur = cur->next;
        } while (cur->next != b);
    } while (found);   
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
    if (!out) {
        cout << "Ошибка\n";
        return;
    }
    
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
    cout << "Данные сохранены в файл " << "\n";
}
int main() {
    Tovar* b = nullptr;
    string fileName;
    cout << "Введите имя файла -> ";
    cin >> fileName;
//    cin.ignore();

    ifstream inp(fileName);
    if (inp.is_open()) {
        string name, proizvod;
        double price;
        int kolvo, srok;

        while (inp >> name >> price >> kolvo >> srok >> proizvod) {
            addn(b, name, price, kolvo, srok, proizvod);
        }
        inp.close();
        cout << "Данные загружены из файла " << "\n";
    }   
    
    else {
        cout << "Файл не найден. создан новый список.\n";
    }
    int choice;
    
    while (choice != 6) {
        cout << "\nМеню:\n";
        cout << "1. Вывод всех товаров\n";
        cout << "2. Сортировка по наименованию\n";
        cout << "3. Сортировка по сроку хранения\n";
        cout << "4. Добавить товар\n";
        cout << "5. Удалить товар\n";
        cout << "6. Выход из программы\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();
        
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
                getline(cin, name);
                cout << "Введите стоимость: ";
                cin >> price;
                cout << "Введите количество: ";
                cin >> kolvo;
                cout << "Введите срок хранения: ";
                cin >> srok;
                cin.ignore();
                cout << "Введите производителя: ";
                getline(cin, proizvod);
                
                addn(b, name, price, kolvo, srok, proizvod);
                cout << "Товар добавлен!\n";
                break;
            }   
            case 5: { 
                cout << "\nУдаление товара\n";
                string nazvanie;
                cout << "Введите наименование товара для удаления: ";
                getline(cin, nazvanie);
                DeletePoNazv(b, nazvanie);
                break;
            }
            case 6: {
                cout << "\nВыход из программы\n";
                saveToFile(fileName, b);
                break;
            }
            default: {
                cout << "\nОшибка! Введите число от 1 до 6.\n";
                break;
            }
        }
    } 
    ClearList(b);
    return 0;
}