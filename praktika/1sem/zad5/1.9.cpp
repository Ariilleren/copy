#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Team {
    string name;
    int points;
    string captain;
};

int main() {
    vector<Team> teams;
    fstream file;
    
    // Создание файла и запись 10 записей
    file.open("teams.dat", ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "ошибка" << endl;
        return 1;
    }
    
    cout << "введите данные 3 команд\n";
    
    for (int i = 0; i < 3; i++) {
        Team team;
        cout << "команда #" << i+1 << ":\n";
        cout << "название: ";
        getline(cin, team.name);
        
        cout << "очки: ";
        string pointsStr;
        getline(cin, pointsStr);
        stringstream ss(pointsStr);
        ss >> team.points;
        
        cout << "капитан: ";
        getline(cin, team.captain);
        
        // Для записи string в бинарный файл нужно записать размер и саму строку
        int nameSize = team.name.size();
        file.write((char*)&nameSize, sizeof(nameSize));
        file.write(team.name.c_str(), nameSize);

        file.write((char*)&team.points, sizeof(team.points));

        int captainSize = team.captain.size();
        file.write((char*)&captainSize, sizeof(captainSize));
        file.write(team.captain.c_str(), captainSize);

        teams.push_back(team);
        cout << endl;
    }
    file.close();
    
    // ПРОСМОТР 
    cout << "содержимое файла:\n";
    
    file.open("teams.dat", ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "ошибка" << endl;
        return 1;
    }
    
    // очищаем вектор для повторного чтения
    teams.clear();
    
    // переходим в начало файла
    file.seekg(0, ios::beg);
    
    // читаем все записи
    while (true) {
        Team team;
        
        // Читаем название команды
        int nameSize;
        file.read((char*)&nameSize, sizeof(nameSize));
        if (file.eof()) break;
        
        char* nameBuffer = new char[nameSize + 1];
        file.read(nameBuffer, nameSize);
        nameBuffer[nameSize] = '\0';
        team.name = nameBuffer;
        delete[] nameBuffer;
        
        // Читаем очки
        file.read((char*)&team.points, sizeof(team.points));
        
        // Читаем капитана
        int captainSize;
        file.read((char*)&captainSize, sizeof(captainSize));
        
        char* captainBuffer = new char[captainSize + 1];
        file.read(captainBuffer, captainSize);
        captainBuffer[captainSize] = '\0';
        team.captain = captainBuffer;
        delete[] captainBuffer;
        
        if (file) { // проверяем, успешно ли прочитали
            teams.push_back(team);
            cout << team.name << ", " << team.points << ", " << team.captain << endl;
        }
    }
    
    if (file.eof()) {
        file.clear();
    }
    file.close();
    
    // Очищаем буфер ввода перед чтением выбора
    cin.ignore();
    
    int choice;
    cout << "Для выхода из программы введите 0\n"
         << "Для вывода команд в порядке очков введите 1\n"
         << "Для добавления команды введите 2\n";
    cin >> choice;

    while (choice != 0) {    
        switch (choice) {
            case 1: {
                // Сортировка команд по очкам (по убыванию)
                for (int i = 0; i < teams.size(); i++) {
                    for (int j = i + 1; j < teams.size(); j++) {
                        if (teams[i].points < teams[j].points) {
                            Team temp = teams[i];
                            teams[i] = teams[j];
                            teams[j] = temp;
                        }
                    }
                }
                cout << "место\tкоманда\t\tочки\tкапитан\n";
                for (int i = 0; i < teams.size(); i++) {
                    cout << i+1 << "\t" << teams[i].name << "\t\t" 
                         << teams[i].points << "\t" << teams[i].captain << endl;
                }
                break;
            }
            
            case 2: { 
                // Очищаем буфер перед чтением строк
                cin.ignore();
                
                Team newTeam;
                cout << "название: ";
                getline(cin, newTeam.name);
                
                cout << "очки: ";
                string pointsStr;
                getline(cin, pointsStr);
                stringstream ss(pointsStr);
                ss >> newTeam.points;
                
                cout << "капитан: ";
                getline(cin, newTeam.captain);
                
                // открываем файл для добавления в конец
                file.open("teams.dat", ios::out | ios::app | ios::binary);
                if (!file.is_open()) {
                    cout << "ошибка открытия файла для добавления" << endl;
                    return 1;
                }
                
                // Записываем название команды
                int nameSize = newTeam.name.size();
                file.write((char*)&nameSize, sizeof(nameSize));
                file.write(newTeam.name.c_str(), nameSize);
                
                // Записываем очки
                file.write((char*)&newTeam.points, sizeof(newTeam.points));
                
                // Записываем капитана
                int captainSize = newTeam.captain.size();
                file.write((char*)&captainSize, sizeof(captainSize));
                file.write(newTeam.captain.c_str(), captainSize);
                
                file.close();
                teams.push_back(newTeam);
                cout << "новая команда добавлена\n";
                break;
            }
            
            default: {
                cout << "Введена неверная команда\nДопустимые значения 0-2\n";
                break;
            }
        }
        
        // Выводим меню снова
        cout << "\nДля вывода команд в порядке очков введите 1\n"
             << "Для добавления команды введите 2\n"
             << "Для выхода из программы введите 0\n";
        cin >> choice;
    }

    return 0;
}