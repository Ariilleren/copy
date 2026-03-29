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
    if (!b) b = a, b->next = b;
    else {
        Tovar* brem = b;
        while (brem->next != b) brem = brem->next;
        brem->next = a;
        a->next = b;
    }
    cout << "Элемент добавлен!";
}


void DeletePoNazv(Tovar*&b, string naz) {
    if (!b){
        cout << "Список пуст";
        return
        ;
    }
    Tovar* tek = b, * prev = nullptr;
    do {
        if (tek->name == naz){
            if (tek->next ==tek) {
            delete tek;
            b = nullptr;
            cout << "Эллемент удален.";
            return;
            }
            if (tek = b){
                Tovar* posl = b;
                while (posl->next != b) posl = posl->next;
                b = tek->next;
                posl->next = b;
            }
            else prev->next = tek->next;
            delete tek;
            cout << "Элемент удален";
            return;
        }
        prev = tek;
        tek = tek->next;
    } while (tek != b);
    cout << "Элемент не найден"<< endl;
}


void SortPoNazv(Tovar*& b) {
    bool found;
    do{
        found = false;
        Tovar* tek = b; 
        do {
            if (tek->next != b && tek->name > tek->next->name) {
                swap(tek->name, tek->next->name);
                swap(tek->price, tek->next->price);
                swap(tek->kolvo, tek->next->kolvo);
                swap(tek->srok, tek->next->srok);
                swap(tek->proizvod, tek->next->proizvod);
                found = true;
            }
            tek = tek->next;
        } while (tek->next != b); 
    } while (found);   
    cout << "Сортировка по наименованию выполнена!\n";
}


void sortcrok(Tovar*& b) {
    if (!b || b->next == b) return;

    bool found;
    do {
        found = false;
        Tovar* tek = b;
        do {
            if (tek->next != b && tek->srok > tek->next->srok) {
                swap(tek->name, tek->next->name);
                swap(tek->price, tek->next->price);
                swap(tek->kolvo, tek->next->kolvo);
                swap(tek->srok, tek->next->srok);
                swap(tek->proizvod, tek->next->proizvod);
                found = true;
            }
            tek = tek->next;
        } while (tek->next != b);
    } while (found);
    cout << "Сортировка по сроку хранения выполнена!";
}
void SortPoSroku(Tovar*& b) {
    bool found;
    Tovar* b = b->tek; 
    do {
        found = false;
        Tovar* tek = b; 
        do {
            if (tek->next != b && tek->srok > tek->next->srok) {
                swap(tek->name, tek->next->name);
                swap(tek->price, tek->next->price);
                swap(tek->kolvo, tek->next->kolvo);
                swap(tek->srok, tek->next->srok);
                swap(tek->proizvod, tek->next->proizvod);
                found = true;
            }
            tek = tek->next;
        } while (tek->next != b);
        
    } while (found);   
    cout << "Сортировка по сроку хранения выполнена!\n";
}

void ClearList(Tovar* b) { //?
    if (b->tek == nullptr) {
        delete b;
        return;
    }
    b->next = nullptr;
    Tovar* tek = b->tek;
    while (tek != nullptr) {
        Tovar* next = tek->next;
        delete tek;
        tek = next;
    }
    delete b;
}

int main() {
    Tovar* b = new Tovar;
    b->head = nullptr;
    b->tail = nullptr;
    
    char fileName[20];
    cout << "Введите имя файла -> ";
    cin >> fileName;
    cin.ignore(); 

    ifstream inp(fileName);
        string name, price, kolvo, srok, proizvod;
        while (getline(inp, name, ' ') && 
               getline(inp, price, ' ') &&
               getline(inp, kolvo, ' ') &&
               getline(inp, srok, ' ') && 
               getline(inp, proizvod)) {
            Dobavit(name, price, kolvo, srok, proizvod, Spisok);
        }
        inp.close();
        cout << "\nДанные загружены"<< "\n";
    int choice = -1;
    
    while (choice != 5) {
        cout << "\n1.Вывод всех товаров\n2.Сортировка по наименованию\n3.Сортировка по сроку хранения\n4.Добавить товар\n5.Выход из программы\n" << endl;
        cin >> choice;
        cin.ignore(); 
        switch(choice) {
            case 1: {
                cout << "\nВсе товары\n";
                Show(b);
                break;
            } 
            case 2: {
                cout << "\nСортировка по наименованию\n";
                SortPoNazv(Spisok);
                Show(Spisok);
                break;
            }
            case 3: {
                cout << "\nСортировка по сроку хранения\n";
                SortPoSroku(Spisok);
                Show(Spisok);  
                break;
            } 
            case 4: {
                cout << "\nДобавление товара\n";
                string name, price, kolvo, srok, proizvod;
                cout << "Введите наименование: ";
                getline(cin, name);
                cout << "Введите стоимость: ";
                getline(cin, price);
                cout << "Введите количество: ";
                getline(cin, kolvo);
                cout << "Введите срок хранения: ";
                getline(cin, srok);
                cout << "Введите производителя: ";
                getline(cin, proizvod);   
                Dobavit(name, price, kolvo, srok, proizvod, Spisok);
                cout << "Товар добавлен!\n";
                break;
            }   
            case 5: { 
                cout << "\nУдаление товара\n";
                string nazvanie;
                cout << "Введите наименование товара для удаления: ";
                getline(cin, nazvanie);
                DeletePoNazv(Spisok, nazvanie);
                break;
            }
            case 6: {
                cout << "\nВыход из программы\n";
                // save(fileName, Spisok);
            }
            default: {
                cout << "\nОшибка! Введите число от 1 до 5.\n";
                break;
            }
        }
    }
    ClearList(Spisok);
    return 0;
}