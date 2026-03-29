#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>

using namespace std;

struct Team {
    string name;
    int points;
    string captain;
};

int main() {
    vector<Team> teams;
    
    // Создание файла с 10 записями
    ofstream outFile("teams.dat", ios::binary | ios::out);
    if (!outFile) {
        cout << "Ошибка создания файла!" << endl;
        return 1;
    }
    
    cout << "Введите данные 10 команд:\n";
    for (int i = 0; i < 10; i++) {
        Team team;
        cout << "Команда #" << i+1 << ":\n";
        cout << "Название: "; 
        getline(cin, team.name);
        cout << "Очки: ";
        string pointsStr;
        getline(cin, pointsStr);
        stringstream ss(pointsStr);
        ss >> team.points;
        cout << "Капитан: ";
        getline(cin, team.captain);
        
        // Запись в файл
        int nameLen = team.name.length();
        outFile.write((char*)&nameLen, sizeof(nameLen));
        outFile.write(team.name.c_str(), nameLen);
        
        outFile.write((char*)&team.points, sizeof(team.points));
        
        int captainLen = team.captain.length();
        outFile.write((char*)&captainLen, sizeof(captainLen));
        outFile.write(team.captain.c_str(), captainLen);
        
        teams.push_back(team);
        cout << endl;
    }
    outFile.close();
    
    // Просмотр файла
    cout << "Содержимое файла:\n";
    ifstream inFile("teams.dat", ios::binary | ios::in);
    if (!inFile) {
        cout << "Ошибка открытия файла для чтения!" << endl;
        return 1;
    }
    
    teams.clear();
    inFile.seekg(0); // Переходим в начало файла
    
    while (inFile) {
        Team team;
        int nameLen;
        
        // Чтение названия команды
        inFile.read((char*)&nameLen, sizeof(nameLen));
        if (inFile.eof()) break;
        
        char* nameBuf = new char[nameLen + 1];
        inFile.read(nameBuf, nameLen);
        nameBuf[nameLen] = '\0';
        team.name = nameBuf;
        delete[] nameBuf;
        
        // Чтение очков
        inFile.read((char*)&team.points, sizeof(team.points));
        
        // Чтение капитана
        int captainLen;
        inFile.read((char*)&captainLen, sizeof(captainLen));
        char* captainBuf = new char[captainLen + 1];
        inFile.read(captainBuf, captainLen);
        captainBuf[captainLen] = '\0';
        team.captain = captainBuf;
        delete[] captainBuf;
        
        if (inFile) {
            teams.push_back(team);
            cout << team.name << ", " << team.points << ", " << team.captain << endl;
        }
    }
    
    if (inFile.eof()) {
        inFile.clear(); // Очищаем флаг конца файла
    }
    inFile.close();
    cout << endl;
    
    // Добавление новой информации
    cout << "Добавить новую команду? (y/n): ";
    string choice;
    getline(cin, choice);
    
    if (choice == "y" || choice == "Y") {
        ofstream appendFile("teams.dat", ios::binary | ios::app);
        if (!appendFile) {
            cout << "Ошибка открытия файла для добавления!" << endl;
            return 1;
        }
        
        Team newTeam;
        cout << "Название новой команды: ";
        getline(cin, newTeam.name);
        cout << "Очки: ";
        string pointsStr;
        getline(cin, pointsStr);
        stringstream ss(pointsStr);
        ss >> newTeam.points;
        cout << "Капитан: ";
        getline(cin, newTeam.captain);
        
        // Запись новой команды в конец файла
        int nameLen = newTeam.name.length();
        appendFile.write((char*)&nameLen, sizeof(nameLen));
        appendFile.write(newTeam.name.c_str(), nameLen);
        
        appendFile.write((char*)&newTeam.points, sizeof(newTeam.points));
        
        int captainLen = newTeam.captain.length();
        appendFile.write((char*)&captainLen, sizeof(captainLen));
        appendFile.write(newTeam.captain.c_str(), captainLen);
        
        appendFile.close();
        teams.push_back(newTeam);
    }
    
    // Перечитываем все данные из файла для сортировки
    teams.clear();
    inFile.open("teams.dat", ios::binary | ios::in);
    if (!inFile) {
        cout << "Ошибка открытия файла для чтения!" << endl;
        return 1;
    }
    
    inFile.seekg(0); // Переходим в начало файла
    
    while (inFile) {
        Team team;
        int nameLen;
        
        inFile.read((char*)&nameLen, sizeof(nameLen));
        if (inFile.eof()) break;
        
        char* nameBuf = new char[nameLen + 1];
        inFile.read(nameBuf, nameLen);
        nameBuf[nameLen] = '\0';
        team.name = nameBuf;
        delete[] nameBuf;
        
        inFile.read((char*)&team.points, sizeof(team.points));
        
        int captainLen;
        inFile.read((char*)&captainLen, sizeof(captainLen));
        char* captainBuf = new char[captainLen + 1];
        inFile.read(captainBuf, captainLen);
        captainBuf[captainLen] = '\0';
        team.captain = captainBuf;
        delete[] captainBuf;
        
        if (inFile) {
            teams.push_back(team);
        }
    }
    
    if (inFile.eof()) {
        inFile.clear();
    }
    inFile.close();
    
    // Сортировка по очкам (в порядке убывания) - пузырьковая сортировка
    for (size_t i = 0; i < teams.size(); i++) {
        for (size_t j = i + 1; j < teams.size(); j++) {
            if (teams[i].points < teams[j].points) {
                Team temp = teams[i];
                teams[i] = teams[j];
                teams[j] = temp;
            }
        }
    }
    
    // Вывод в порядке набранных мест
    cout << "\nРезультаты в порядке мест:\n";
    cout << "Место\tКоманда\t\tОчки\tКапитан\n";
    for (size_t i = 0; i < teams.size(); i++) {
        cout << i+1 << "\t" << teams[i].name << "\t\t" 
             << teams[i].points << "\t" << teams[i].captain << endl;
    }
    
    return 0;
}