#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct candy {
    string name;
    double price;
    int koldo;
    int crok;
    string place;
    candy* next;
};

candy* creatn(string n, double p, int q, int sl, string m) {
    candy* a = new candy;
    a->name = n; 
    a->price = p; 
    a->koldo = q;
    a->crok = sl; 
    a->place = m; 
    a->next = nullptr;
    return a;
}

void addn(candy*& b, string n, double p, int q, int sl, string m) {
    candy* a = creatn(n, p, q, sl, m);
    if (!b) b = a, b->next = b;
    else {
        candy* brem = b;
        while (brem->next != b) brem = brem->next;
        brem->next = a;
        a->next = b;
    }
    cout << "Элемент добавлен!";
}


void deleten(candy*& b, string naz) {
    if (!b) { cout << "Список пуст!"; return; }
    candy* tek = b, * prev = nullptr;
    do {
        if (tek->name == naz) {
            if (tek->next == tek) {
                delete tek;
                b = nullptr;
                cout << "Элемент удален. Список теперь пуст.";
                return;
            }

            if (tek == b) {
                candy* posled = b;
                while (posled->next != b) posled = posled->next;
                b = tek->next;
                posled->next = b;
            }
            else prev->next = tek->next;

            delete tek;
            cout << "Элемент '" << naz << "' удален!";
            return;
        }
        prev = tek;
        tek = tek->next;
    } while (tek != b);

    cout << "Элемент '" << naz << "' не найден!";
}



void sortprice(candy*& a) {
    if (!a || a->next == a) return;

    bool found;
    do {
        found = false;
        candy* tek = a;
        do {
            if (tek->next != a && tek->price > tek->next->price) {
                swap(tek->name, tek->next->name);
                swap(tek->price, tek->next->price);
                swap(tek->koldo, tek->next->koldo);
                swap(tek->crok, tek->next->crok);
                swap(tek->place, tek->next->place);
                found = true;
            }
            tek = tek->next;
        } while (tek->next != a);
    } while (found);
    cout << "Сортировка по цене выполнена!";
}

void sortcrok(candy*& a) {
    if (!a || a->next == a) return;

    bool found;
    do {
        found = false;
        candy* tek = a;
        do {
            if (tek->next != a && tek->crok > tek->next->crok) {
                swap(tek->name, tek->next->name);
                swap(tek->price, tek->next->price);
                swap(tek->koldo, tek->next->koldo);
                swap(tek->crok, tek->next->crok);
                swap(tek->place, tek->next->place);
                found = true;
            }
            tek = tek->next;
        } while (tek->next != a);
    } while (found);
    cout << "Сортировка по сроку хранения выполнена!";
}

void savefile(candy* a, string namefil) {
    ofstream file(namefil);
    if (!file) { cout << "Ошибка открытия файла!"; return; }

    if (!a) {
        file.close();
        cout << "Список пуст, создан пустой файл.";
        return;
    }

    candy* brem = a;
    int count = 0;
    do {
        file << brem->name << "\n" << brem->price << "\n"
            << brem->koldo << "\n" << brem->crok << "\n"
            << brem->place << "\n";
        brem = brem->next;
        count++;
    } while (brem != a);

    file.close();
    if (count > 0) cout << "Сохранено " << count << " элементов в файл '" << namefil;
    else cout << "Создан пустой файл '" << namefil ;
}

void loadfile(candy*& a, string namefil) {
    ifstream file(namefil);
    if (!file) {
        cout << "Ошибка открытия файла '" << namefil;
        return;
    }

    file.seekg(0, ios::end);
    if (file.tellg() == 0) {
        cout << "Файл '" << namefil << "' пуст";
        file.close();
        return;
    }
    file.seekg(0, ios::beg);


    while (a) deleten(a, a->name);

    string name, place;
    double price;
    int koldo, crok;
    int count = 0;

    while (getline(file, name)) {
        if (name.empty()) continue; 

        if (file >> price>> koldo >> crok) {
            file.ignore(); 
            getline(file, place);
            addn(a, name, price, koldo, crok, place);
            count++;
        }
        else {
            cout << "Ошибка чтения данных для элемента: " << name ;
            break;
        }
    }

    file.close();
    if (count > 0) cout << "Загружено " << count << " элементов из файла '" << namefil ;
    else cout << "Не удалось загрузить данные из файла '" << namefil ;
}

void ssfile(candy* a, string namefil, int ts) {
    if (!a) {
        cout << "Список пуст, нечего сортировать!";

 
        ofstream emptyFile(namefil);
        if (emptyFile) {
            emptyFile.close();
            cout << "Создан пустой файл '" << namefil << "'";
        }
        return;
    }

    candy* sf = nullptr;
    candy* brem = a;

    do {
        addn(sf, brem->name, brem->price,
            brem->koldo, brem->crok, brem->place);
        brem = brem->next;
    } while (brem != a);

    if (ts == 1) sortprice(sf);
    else if (ts == 2) sortcrok(sf);

    ofstream file(namefil);
    if (!file) { cout << "Ошибка открытия файла!"; return; }

    brem = sf;
    int count = 0;
    do {
        file << brem->name << "\n" << brem->price << "\n"
            << brem->koldo << "\n" << brem->crok << "\n"
            << brem->place << "\n";
        brem = brem->next;
        count++;
    } while (brem != sf);

    file.close();

    while (sf) deleten(sf, sf->name);

    cout << "Отсортированный список (" << (ts == 1 ? "по цене" : "по сроку хранения")
        << ") сохранен в файл '" << namefil << "' (" << count << " элементов)";
}

void dislist(candy* a) {
    if (!a) { cout << "Список пуст!"; return; }

    candy* brem = a;
    int index = 1;
    cout << "Наименование            Цена за 100г   Количество   Срок хранения   Производитель    \n";
    do {
        printf("%-3d  %-22s %-14.2f %-12d %-15d %-18s \n",
            index++, brem->name.c_str(), brem->price,
            brem->koldo, brem->crok, brem->place.c_str());
        brem = brem->next;
    } while (brem != a);
  
}

void add(candy*& a) {
    string name, place;
    double price;
    int kolbo, crok;

    cout << "Введите данные:";
    cout << "Наименование: ";
    cin.ignore();
    getline(cin, name);

    cout << "Стоимость за 100г: ";
    while (!(cin >> price) || price < 0) {
        cout << "Ошибка! Введите корректную цену: ";
        cin.clear();
        while (cin.get() != '\n') {} 
    }

    cout << "Количество на складе: ";
    while (!(cin >> kolbo) || kolbo < 0) {
        cout << "Ошибка! Введите корректное количество: ";
        cin.clear();
        while (cin.get() != '\n') {} 
    }

    cout << "Срок хранения (дней): ";
    while (!(cin >> crok) || crok < 0) {
        cout << "Ошибка! Введите корректный срок хранения: ";
        cin.clear();
        while (cin.get() != '\n') {} 
    }

    cout << "Производитель: ";
    cin.ignore();
    getline(cin, place);

    addn(a, name, price, kolbo, crok, place);
}

void menu() {
    cout << "             МЕНЮ УПРАВЛЕНИЯ СПИСКОМ\n";
    cout << "1.  Добавить элемент\n";
    cout << "2.  Удалить элемент\n";
    cout << "3.  Редактировать элемент\n";  
    cout << "4.  Показать список\n";
    cout << "5.  Сортировать по цене\n";
    cout << "6.  Сортировать по сроку хранения\n";
    cout << "7.  Сохранить в файл\n";
    cout << "8.  Загрузить из файла\n";
    cout << "9.  Сохранить отсортированный список (по цене)\n";
    cout << "10. Сохранить отсортированный список (по сроку хранения)\n";
    cout << "11. Очистить список\n";
    cout << "12. Добавить тестовые данные\n";
    cout << "0.  Выход\n";
    cout << "Выбор: ";
}

void cllist(candy*& a) {
    if (!a) { cout << "Список уже пуст!\n"; return; }

    int count = 0;
    while (a) {
        deleten(a, a->name);
        count++;
    }
    cout << "Удалено " << count << " элементов. Список очищен.\n";
}
void edit(candy* a, string name) {
    if (!a) {                            
        cout << "Список пуст!";
        return;
    }

    candy* tek = a;                      
    bool found = false;                      

    do {                                     
        if (tek->name == name) {
            found = true;                   
            break;
        }
        tek = tek->next;
    } while (tek != a);

    if (!found) {                            
        cout << "Элемент '" << name << "' не найден в списке!";
        return;
    }

   
    cout << "\n=== РЕДАКТИРОВАНИЕ ЭЛЕМЕНТА ===";
    cout << "\nТекущие данные:";
    cout << "\nНаименование: " << tek->name;
    cout << "\nЦена за 100г: " << tek->price;
    cout << "\nКоличество на складе: " << tek->koldo;
    cout << "\nСрок хранения (дней): " << tek->crok;
    cout << "\nПроизводитель: " << tek->place;

    int choice;                             
    cout << "\n\nВыберите поле для редактирования:";
    cout << "\n1. Цена за 100г";
    cout << "\n2. Количество на складе";
    cout << "\n3. Срок хранения";
    cout << "\n4. Производитель";
    cout << "\n5. Редактировать все поля";
    cout << "\n0. Отмена";
    cout << "\nВыбор: ";
    cin >> choice;

    switch (choice) {
    case 1: {                           
        double newprice;
        cout << "Текущая цена: " << tek->price;
        cout << "\nВведите новую цену: ";
        while (!(cin >> newprice) || newprice < 0) {
            cout << "Ошибка! Введите корректную цену (>= 0): ";
            cin.clear();
            while (cin.get() != '\n') {}
        }
        tek->price = newprice;          
        cout << "Цена успешно изменена!";
        break;
    }

    case 2: {                          
        int newkolbo;
        cout << "Текущее количество: " << tek->koldo;
        cout << "\nВведите новое количество: ";
        while (!(cin >> newkolbo) || newkolbo < 0) {
            cout << "Ошибка! Введите корректное количество (>= 0): ";
            cin.clear();
            while (cin.get() != '\n') {}
        }
        tek->koldo = newkolbo;       
        cout << "Количество успешно изменено!";
        break;
    }

    case 3: {                            
        int newcrok;
        cout << "Текущий срок хранения: " << tek->crok << " дней";
        cout << "\nВведите новый срок хранения: ";
        while (!(cin >> newcrok) || newcrok < 0) {
            cout << "Ошибка! Введите корректный срок (>= 0): ";
            cin.clear();
            while (cin.get() != '\n') {}
        }
        tek->crok = newcrok;       
        cout << "Срок хранения успешно изменен!";
        break;
    }

    case 4: {                            
        string newplace;
        cout << "Текущий производитель: " << tek->place;
        cout << "\nВведите нового производителя: ";
        cin.ignore();                    
        getline(cin, newplace);   
        tek->place = newplace;   
        cout << "Производитель успешно изменен!";
        break;
    }

    case 5: {                            
        cout << "\n=== РЕДАКТИРОВАНИЕ ВСЕХ ПОЛЕЙ ===";

       
        double newprice;
        cout << "\nТекущая цена: " << tek->price;
        cout << "\nВведите новую цену: ";
        while (!(cin >> newprice) || newprice < 0) {
            cout << "Ошибка! Введите корректную цену (>= 0): ";
            cin.clear();
            while (cin.get() != '\n') {}
        }
        tek->price = newprice;

        
        int newkolbo;
        cout << "\nТекущее количество: " << tek->koldo;
        cout << "\nВведите новое количество: ";
        while (!(cin >> newkolbo) || newkolbo < 0) {
            cout << "Ошибка! Введите корректное количество (>= 0): ";
            cin.clear();
            while (cin.get() != '\n') {}
        }
        tek->koldo = newkolbo;

        
        int newcrok;
        cout << "\nТекущий срок хранения: " << tek->crok << " дней";
        cout << "\nВведите новый срок хранения: ";
        while (!(cin >> newcrok) || newcrok < 0) {
            cout << "Ошибка! Введите корректный срок (>= 0): ";
            cin.clear();
            while (cin.get() != '\n') {}
        }
        tek->crok = newcrok;

        
        string newplace;
        cout << "\nТекущийпроизводитель: " << tek->place;
        cout << "\nВведите нового производителя: ";
        cin.ignore();
        getline(cin, newplace);
        tek->place = newplace;

        cout << "\nВсе поля успешно обновлены!";
        break;
    }

    case 0:                             
        cout << "Редактирование отменено.";
        break;

    default:                             
        cout << "Неверный выбор! Редактирование отменено.";
        break;
    }
}

void addtest(candy*& a) {
    addn(a, "Шоколад молочный", 120.50, 150, 365, "Рот Фронт");
    addn(a, "Печенье овсяное", 85.30, 200, 90, "Яшкино");
    addn(a, "Конфеты шоколадные", 210.00, 100, 180, "Бабаевский");
    addn(a, "Вафли с шоколадом", 95.00, 300, 120, "Красный Октябрь");
    addn(a, "Мармелад фруктовый", 65.75, 180, 60, "Фрутте");
    cout << "Добавлено 5 тестовых записей!\n";
}

int main() {
    setlocale(LC_ALL, "RU");
    candy* a = nullptr;
    int choice;
    string filename, name;

    do {
        menu();
        cin >> choice;

        switch (choice) {
        case 1:
            add(a);
            break;

        case 2:
            if (!a) cout << "Список пуст!\n";
            else {
                cout << "Введите наименование для удаления: ";
                cin.ignore();
                getline(cin, name);
                deleten(a, name);
            }
            break;

        case 3:  
            if (!a) cout << "Список пуст!\n";
            else {
                cout << "Введите наименование для редактирования: ";
                cin.ignore();
                getline(cin, name);
                edit(a, name);
            }
            break;

        case 4:
            dislist(a);
            break;

        case 5:
            sortprice(a);
            dislist(a);
            break;

        case 6:
            sortcrok(a);
            dislist(a);
            break;

        case 7:
            cout << "Введите имя файла для сохранения: ";
            cin >> filename;
            savefile(a, filename);
            break;

        case 8:
            cout << "Введите имя файла для загрузки: ";
            cin >> filename;
            loadfile(a, filename);
            break;

        case 9:
            cout << "Введите имя файла для сохранения: ";
            cin >> filename;
            ssfile(a, filename, 1);
            break;

        case 10:
            cout << "Введите имя файла для сохранения: ";
            cin >> filename;
            ssfile(a, filename, 2);
            break;

        case 11:
            cllist(a);
            break;

        case 12:
            addtest(a);
            break;

        case 0:
            cout << "Выход из программы...\n";
            break;

        default:
            cout << "Неверный выбор! Попробуйте снова.\n";
        }

        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";   
            cin.ignore();
            cin.get();
        }

    } while (choice != 0);

    cllist(a);

    return 0;
}