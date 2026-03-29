#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Tovar {
    string nazvanie;
    float stoimost;
    int kolichestvo;
    string srok_hraneniya;
    string proizvoditel;
    Tovar* Head, * Tail, * Next;
};

void Dobavit(string nazvanie, string stoimost, string kolichestvo, string srok_hraneniya, string proizvoditel, Tovar*& Spisok) {
    Tovar* temp = new Tovar;
    temp->nazvanie = nazvanie;
    temp->stoimost = std::stoi(stoimost);
    temp->kolichestvo = std::stoi(kolichestvo);
    temp->srok_hraneniya = srok_hraneniya;
    temp->proizvoditel = proizvoditel;
    Tovar* Head = Spisok->Head;
    
    if (Head == NULL) {
        Spisok->Head = temp;
        Spisok->Tail = temp;
        temp->Next = temp;
    }
    else {
        Tovar* Tail = Spisok->Tail;
        Tail->Next = temp;
        temp->Next = Head;
        Spisok->Tail = temp;
    }
}

void Show(Tovar* Spisok) {
    cout << "Наименование\tСтоимость\tКол-во\tСрок\t\tПроизводитель\n"; 
    Tovar* temp = Spisok->Head;
    do {
        cout << temp->nazvanie << "\t\t" 
             << temp->stoimost << "\t\t"
             << temp->kolichestvo << "\t"
             << temp->srok_hraneniya << "\t"
             << temp->proizvoditel << endl;
        temp = temp->Next;
    } while (temp != Spisok->Head);
    
}
int Dlina(Tovar* Spisok) {
    int dlina = 0;
    Tovar* temp = Spisok->Head;
    do {
        dlina++;
        temp = temp->Next;
    } while (temp != Spisok->Head);
    return dlina;
}

void Zapisat(string fileName, Tovar* Spisok) {
    ofstream myfile;
    myfile.open(fileName);
    
    if (Spisok->Head != NULL) {
        Tovar* temp = Spisok->Head;
        do {
            myfile << temp->nazvanie << " " << temp->stoimost << " " 
                   << temp->kolichestvo << " " << temp->srok_hraneniya << " "
                   << temp->proizvoditel << "\n";
            temp = temp->Next;
        } while (temp != Spisok->Head);
    }
    
    myfile.close();
}

Tovar* SortirovkaPoNazvaniu(Tovar* Spisok) {
    int dlina = Dlina(Spisok);
    
    Tovar* arr = new Tovar[dlina];
    Tovar* temp = Spisok->Head;
    
    for (int i = 0; i < dlina; i++) {
        arr[i] = *temp;
        temp = temp->Next;
    }
    
    for (int i = 0; i < dlina - 1; i++) {
        for (int j = 0; j < dlina - i - 1; j++) {
            if (arr[j].nazvanie > arr[j + 1].nazvanie) {
                Tovar temp_t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp_t;
            }
        }
    }
    
    Tovar* SpisokNazvanie = new Tovar;
    SpisokNazvanie->Head = NULL;
    SpisokNazvanie->Tail = NULL;
    
    for (int j = 0; j < dlina; j++) {
        Dobavit(
            arr[j].nazvanie,
            to_string(arr[j].stoimost),
            to_string(arr[j].kolichestvo),
            arr[j].srok_hraneniya,
            arr[j].proizvoditel,
            SpisokNazvanie
        );
    }
    
    delete[] arr;
    return SpisokNazvanie;
}

Tovar* SortirovkaPoSroku(Tovar* Spisok) {
    int dlina = Dlina(Spisok);
    
    Tovar* arr = new Tovar[dlina];
    Tovar* temp = Spisok->Head;
    
    for (int i = 0; i < dlina; i++) {
        arr[i] = *temp;
        temp = temp->Next;
    }
    
    for (int i = 0; i < dlina - 1; i++) {
        for (int j = 0; j < dlina - i - 1; j++) {
            if (arr[j].srok_hraneniya > arr[j + 1].srok_hraneniya) {
                Tovar temp_t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp_t;
            }
        }
    }
    
    Tovar* SpisokSrok = new Tovar;
    SpisokSrok->Head = NULL;
    SpisokSrok->Tail = NULL;
    
    for (int j = 0; j < dlina; j++) {
        Dobavit(
            arr[j].nazvanie,
            to_string(arr[j].stoimost),
            to_string(arr[j].kolichestvo),
            arr[j].srok_hraneniya,
            arr[j].proizvoditel,
            SpisokSrok
        );
    }
    
    delete[] arr;
    return SpisokSrok;
}


int main() {
    Tovar* Spisok = new Tovar;
    Spisok->Head = NULL;
    Spisok->Tail = NULL;
    
    char fileName[50];
    cout << "Введите имя файла -> ";
    cin >> fileName;
    cin.ignore(1000, '\n'); // Очистка буфера после cin
    
    // Открытие файла для чтения
    ifstream inp(fileName);
    if (!inp.is_open()) {
        cout << "Ошибка открытия файла " << fileName << "!" << endl;
        return 1;
    }
    
    string nazvanie, stoimost, kolichestvo, srok_hraneniya, proizvoditel;
    // Чтение из файла с использованием getline для строк с пробелами
    while (getline(inp, nazvanie, ' ') && 
           getline(inp, stoimost, ' ') &&
           getline(inp, kolichestvo, ' ') &&
           getline(inp, srok_hraneniya, ' ') &&
           getline(inp, proizvoditel)) {
        Dobavit(nazvanie, stoimost, kolichestvo, srok_hraneniya, proizvoditel, Spisok);
    }
    inp.close();
    
    cout << "\nДанные успешно загружены из файла: " << fileName << "\n";
    
    int choice = -1;
    Tovar* sortedList = NULL;
    
    while (choice != 5) {
        cout << "\n1.Вывод всех товаров\n2.Сортировка по наименованию\n3.Сортировка по сроку хранения\n4.Добавить товар\n5.Выход из программы" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore(1000, '\n'); // Очистка буфера после ввода числа
        
        switch(choice) {
            case 1: {
                cout << "\nТовары\n";
                Show(Spisok);
                break;
            }
              
            case 2: {
                cout << "\nСортировка по наименованию\n";
                if (sortedList != NULL) {
                    delete sortedList;
                }
                sortedList = SortirovkaPoNazvaniu(Spisok);
                Show(sortedList);
                break;
            }
            
            case 3: {
                cout << "\nСортировка по сроку хранения\n";
                if (sortedList != NULL) {
                    delete sortedList;
                }
                sortedList = SortirovkaPoSroku(Spisok);
                Show(sortedList);
                break;
            }
                
            case 4: {
                cout << "\nДобавление товара\n";
                cout << "Введите наименование: ";
                getline(cin, nazvanie);
                cout << "Введите стоимость: ";
                getline(cin, stoimost);
                cout << "Введите количество: ";
                getline(cin, kolichestvo);
                cout << "Введите срок хранения: ";
                getline(cin, srok_hraneniya);
                cout << "Введите производителя: ";
                getline(cin, proizvoditel);
                
                Dobavit(nazvanie, stoimost, kolichestvo, srok_hraneniya, proizvoditel, Spisok);
                cout << "Товар добавлен!\n";
                
                // Показываем обновленный список
                cout << "\nОбновленный список товаров:\n";
                Show(Spisok);
                break;
            }
                
            case 5: {
                cout << "\nВыход из программы...\n";
                break;
            }
            
            default: {
                cout << "\nОшибка! Введите число от 1 до 5.\n";
                break;
            }
        }
    }
    
    // Очистка памяти
    if (sortedList != NULL) {
        delete sortedList;
    }
    delete Spisok;
    
    return 0;
}