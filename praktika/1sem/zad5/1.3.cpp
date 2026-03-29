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

    // 1. СОЗДАНИЕ ФАЙЛА С 10 ЗАПИСЯМИ
    cout << "=== СОЗДАНИЕ ФАЙЛА С 10 КОМАНДАМИ ===\n";
    
    ofstream outfile("teams.dat", ios::binary | ios::out);
    if (!outfile) {
        cout << "Ошибка создания файла!" << endl;
        return 1;
    }
    
    for (int i = 0; i < 10; i++) {
        Team team;
        cout << "\nКоманда №" << i+1 << ":\n";
        
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
        outfile.write((char*)&nameLen, sizeof(nameLen));
        outfile.write(team.name.c_str(), nameLen);
        
        outfile.write((char*)&team.points, sizeof(team.points));
        
        int captainLen = team.captain.length();
        outfile.write((char*)&captainLen, sizeof(captainLen));
        outfile.write(team.captain.c_str(), captainLen);
        
        teams.push_back(team);
    }
    outfile.close();
    
    // 2. ПРОСМОТР ФАЙЛА
    cout << "\n\n=== СОДЕРЖИМОЕ ФАЙЛА ===\n";
    
    ifstream infile("teams.dat", ios::binary | ios::in);
    if (!infile) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }
    
    teams.clear();
    
    while (true) {
        Team team;
        int nameLen;
        
        infile.read((char*)&nameLen, sizeof(nameLen));
        if (infile.eof()) break;
        
        char* nameBuf = new char[nameLen + 1];
        infile.read(nameBuf, nameLen);
        nameBuf[nameLen] = '\0';
        team.name = nameBuf;
        delete[] nameBuf;
        
        infile.read((char*)&team.points, sizeof(team.points));
        
        int captainLen;
        infile.read((char*)&captainLen, sizeof(captainLen));
        char* captainBuf = new char[captainLen + 1];
        infile.read(captainBuf, captainLen);
        captainBuf[captainLen] = '\0';
        team.captain = captainBuf;
        delete[] captainBuf;
        
        teams.push_back(team);
        cout << team.name << ", " << team.points << ", " << team.captain << endl;
    }
    
    infile.close();
    
    //ДОБАВЛЕНИЕ НОВОго
    cout << "\n=== ДОБАВЛЕНИЕ ===\n";
    
    cout << "добавить? (y/n): ";
    string choice;
    getline(cin, choice);
    
    if (choice == "y" || choice == "Y") {
        Team newTeam;
        
        cout << "\nНазвание новой команды: ";
        getline(cin, newTeam.name);
        
        cout << "Очки: ";
        string pointsStr;
        getline(cin, pointsStr);
        stringstream ss(pointsStr);
        ss >> newTeam.points;
        
        cout << "Капитан: ";
        getline(cin, newTeam.captain);
        
        ofstream appendFile("teams.dat", ios::binary | ios::app);
        
        int nameLen = newTeam.name.length();
        appendFile.write((char*)&nameLen, sizeof(nameLen));
        appendFile.write(newTeam.name.c_str(), nameLen);
        
        appendFile.write((char*)&newTeam.points, sizeof(newTeam.points));
        
        int captainLen = newTeam.captain.length();
        appendFile.write((char*)&captainLen, sizeof(captainLen));
        appendFile.write(newTeam.captain.c_str(), captainLen);
        
        appendFile.close();
        
        teams.push_back(newTeam);
        cout << "Новая команда добавлена!\n";
    }
    
    // 4. ВЫВОД В ПОРЯДКЕ НАБРАННЫХ МЕСТ (сортировка пузырьком)
    cout << "\n=== РЕЗУЛЬТАТЫ В ПОРЯДКЕ МЕСТ ===\n";
    
    // Сортировка пузырьком по убыванию очков
    for (size_t i = 0; i < teams.size(); i++) {
        for (size_t j = i + 1; j < teams.size(); j++) {
            if (teams[i].points < teams[j].points) {
                // Меняем местами
                Team temp = teams[i];
                teams[i] = teams[j];
                teams[j] = temp;
            }
        }
    }
    
    cout << "Место\tКоманда\t\tОчки\tКапитан\n";
    for (size_t i = 0; i < teams.size(); i++) {
        cout << i+1 << "\t" << teams[i].name << "\t\t" 
             << teams[i].points << "\t" << teams[i].captain << endl;
    }
    
    return 0;
}