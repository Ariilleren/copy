#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Athlete {
    string lastName;
    int number;
    int points;
};

int main() {
    vector<Athlete> athletes;
    fstream file;
    
    // Создание файла и запись 10 записей
    file.open("athletes.dat", ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "ошибка" << endl;
        return 1;
    }
    
    cout << "введите данные 10 спортсменов\n";
    
    for (int i = 0; i < 1; i++) {
        Athlete athlete;
        cout << "спортсмен #" << i+1 << ":\n";
        
        cout << "фамилия: ";
        getline(cin, athlete.lastName);
        
        cout << "номер: ";
        string numberStr;
        getline(cin, numberStr);
        stringstream ss1(numberStr);
        ss1 >> athlete.number;
        
        cout << "очки: ";
        string pointsStr;
        getline(cin, pointsStr);
        stringstream ss2(pointsStr);
        ss2 >> athlete.points;
        
        // Записываем фамилию
        int lastNameSize = athlete.lastName.size();
        file.write((char*)&lastNameSize, sizeof(lastNameSize));
        file.write(athlete.lastName.c_str(), lastNameSize);
        
        // номер
        file.write((char*)&athlete.number, sizeof(athlete.number));
        
        // очки
        file.write((char*)&athlete.points, sizeof(athlete.points));
        
        athletes.push_back(athlete);
        
        cout << endl;
    }
    file.close();
    
    int choice;
    cout << "Для выхода из программы введите 0\n"
         << "Для добавления новой информации введите 1\n"
         << "Для удаления человека с наименьшим кол-вом очков введите 2\n"
         << "Для вывода списка введите 3\n";
    cin >> choice;
    cin.ignore(); // Очищаем буфер после cin >>

    while (choice != 0) {
        switch (choice) {
            case 1: {
                Athlete newAthlete;
                cout << "фамилия: ";
                getline(cin, newAthlete.lastName);
                
                cout << "номер: ";
                string numberStr;
                getline(cin, numberStr);
                stringstream ss1(numberStr);
                ss1 >> newAthlete.number;
                
                cout << "очки: ";
                string pointsStr;
                getline(cin, pointsStr);
                stringstream ss2(pointsStr);
                ss2 >> newAthlete.points;
                
                // открываем файл для добавления в конец
                file.open("athletes.dat", ios::out | ios::app | ios::binary);
                if (!file.is_open()) {
                    cout << "ошибка открытия файла для добавления" << endl;
                    return 1;
                }
                
                // Записываем фамилию
                int lastNameSize = newAthlete.lastName.size();
                file.write((char*)&lastNameSize, sizeof(lastNameSize));
                file.write(newAthlete.lastName.c_str(), lastNameSize);
                
                // Записываем номер
                file.write((char*)&newAthlete.number, sizeof(newAthlete.number));
                
                // Записываем очки
                file.write((char*)&newAthlete.points, sizeof(newAthlete.points));
                
                file.close();
                
                athletes.push_back(newAthlete);
                cout << "новый спортсмен добавлен\n";
                break;
            }
            case 2: {
                if (athletes.empty()) {
                    cout << "список пуст, нечего удалять\n";
                    break;
                }
                
                int minIndex = 0;
                int minPoints = athletes[0].points;
                
                for (int i = 1; i < athletes.size(); i++) {
                    if (athletes[i].points < minPoints) {
                        minPoints = athletes[i].points;
                        minIndex = i;
                    }
                }
                
                cout << "удаляем спортсмена: " << athletes[minIndex].lastName 
                     << ", номер: " << athletes[minIndex].number 
                     << ", очки: " << athletes[minIndex].points << endl;
                
                // Удаляем из вектора
                athletes.erase(athletes.begin() + minIndex);
                
                // Перезаписываем файл без удаленного спортсмена
                file.open("athletes.dat", ios::out | ios::binary);
                if (!file.is_open()) {
                    cout << "ошибка открытия файла для перезаписи" << endl;
                    return 1;
                }
                
                for (int i = 0; i < athletes.size(); i++) {
                    // Записываем фамилию
                    int lastNameSize = athletes[i].lastName.size();
                    file.write((char*)&lastNameSize, sizeof(lastNameSize));
                    file.write(athletes[i].lastName.c_str(), lastNameSize);
                    
                    // Записываем номер
                    file.write((char*)&athletes[i].number, sizeof(athletes[i].number));
                    
                    // Записываем очки
                    file.write((char*)&athletes[i].points, sizeof(athletes[i].points));
                } 
                file.close();
                cout << "спортсмен удален. осталось спортсменов: " << athletes.size() << endl;
                break;
            }
            case 3: {
                if (athletes.empty()) {
                    cout << "список пуст\n";
                    break;
                }
                
                // Сортировка по очкам (по убыванию)
                for (int i = 0; i < athletes.size(); i++) {
                    for (int j = i + 1; j < athletes.size(); j++) {
                        if (athletes[i].points < athletes[j].points) {
                            Athlete temp = athletes[i];
                            athletes[i] = athletes[j];
                            athletes[j] = temp;
                        }
                    }
                }
                
                cout << "место\tфамилия\t\tномер\tочки\n";
                for (int i = 0; i < athletes.size(); i++) {
                    cout << i+1 << "\t" << athletes[i].lastName << "\t\t" 
                         << athletes[i].number << "\t" << athletes[i].points << endl;
                }
                break;
            }
            default: {
                cout << "Введена неверная команда\nДопустимые значения 0-3\n";
                break;
            }
        }
        
        // ПОВТОРНЫЙ ЗАПРОС ВЫБОРА (этого не было!)
        cout << "\nДля выхода из программы введите 0\n"
             << "Для добавления новой информации введите 1\n"
             << "Для удаления человека с наименьшим кол-вом очков введите 2\n"
             << "Для вывода списка введите 3\n";
        cin >> choice;
        cin.ignore(); // Очищаем буфер после cin >>
    }
    
    cout << "Программа завершена.\n";
    return 0;
}