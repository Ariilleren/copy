#include <iostream>
#include <fstream>
using namespace std;

struct Athlete
{
    string lastName;
    int number;
    int points;
};

int main()
{
    Athlete athletes[100];
    int count = 0;
    
    // Создание начальных 10 спортсменов (исправлено: было 2, теперь 10)
    cout << "Введите данные 10 спортсменов\n";
    for (int i = 0; i < 10; i++)
    {
        cout << "Спортсмен #" << i + 1 << ":\n";
        
        cout << "Фамилия: ";
        cin >> athletes[count].lastName;
        
        cout << "Номер: ";
        cin >> athletes[count].number;
        
        cout << "Очки: ";
        cin >> athletes[count].points;
        
        count++;
        cout << endl;
    }
    
    // Запись в файл
    ofstream file("athletes.dat", ios::binary);
    file.write((char*)&count, sizeof(count));
    for (int i = 0; i < count; i++)
    {
        int len = athletes[i].lastName.length();
        file.write((char*)&len, sizeof(len));
        file.write(athletes[i].lastName.c_str(), len);
        file.write((char*)&athletes[i].number, sizeof(athletes[i].number));
        file.write((char*)&athletes[i].points, sizeof(athletes[i].points));
    }
    file.close();
    
    // Чтение из файла
    ifstream in("athletes.dat", ios::binary);
    int fileCount;
    in.read((char*)&fileCount, sizeof(fileCount));
    count = fileCount;
    
    for (int i = 0; i < count; i++)
    {
        int len;
        in.read((char*)&len, sizeof(len));
        
        athletes[i].lastName.resize(len);
        in.read(&athletes[i].lastName[0], len);
        
        in.read((char*)&athletes[i].number, sizeof(athletes[i].number));
        in.read((char*)&athletes[i].points, sizeof(athletes[i].points));
    }
    in.close();
    
    int choice;
    cout << "0 - выход\n1 - добавить\n2 - удалить худшего\n3 - вывод списка\n";
    cin >> choice;
    cin.ignore();
    
    while (choice != 0)
    {   
        switch (choice)  // Исправлено: было choise, теперь choice
        {
        case 1:{
            cout << "Фамилия: ";
            cin >> athletes[count].lastName;
                
            cout << "Номер: ";
            cin >> athletes[count].number;
                
            cout << "Очки: ";
            cin >> athletes[count].points;
                
            count++;
                
            // Обновление файла
            ofstream file("athletes.dat", ios::binary);
            file.write((char*)&count, sizeof(count));
            for (int i = 0; i < count; i++){
                int len = athletes[i].lastName.length();
                file.write((char*)&len, sizeof(len));
                file.write(athletes[i].lastName.c_str(), len);
                file.write((char*)&athletes[i].number, sizeof(athletes[i].number));
                file.write((char*)&athletes[i].points, sizeof(athletes[i].points));
            }
            file.close();
                
            cout << "Спортсмен добавлен\n";
            break;
        }
        case 2:{
            if (count == 0) {
                cout << "Список спортсменов пуст\n";
                break;
            }
            
            int minIndex = 0;
            for (int i = 1; i < count; i++){
                if (athletes[i].points < athletes[minIndex].points){
                    minIndex = i;
                }
            }
                
            cout << "Удален: " << athletes[minIndex].lastName 
                 << " (очки: " << athletes[minIndex].points << ")\n";
                
            // Сдвигаем элементы
            for (int i = minIndex; i < count - 1; i++)
            {
                athletes[i] = athletes[i + 1];
            }
            count--;
                
            // Обновление файла
            ofstream file("athletes.dat", ios::binary);
            file.write((char*)&count, sizeof(count));
            for (int i = 0; i < count; i++)
            {
                int len = athletes[i].lastName.length();
                file.write((char*)&len, sizeof(len));
                file.write(athletes[i].lastName.c_str(), len);
                file.write((char*)&athletes[i].number, sizeof(athletes[i].number));
                file.write((char*)&athletes[i].points, sizeof(athletes[i].points));
            }
            file.close();
            break;  // Добавлен break
        }
        case 3:{  // Добавлен case 3
            cout << "Список спортсменов:\n";
            cout << "Фамилия\t\tНомер\tОчки\n";
            for (int i = 0; i < count; i++)
            {
                cout << athletes[i].lastName << "\t\t"
                     << athletes[i].number << "\t"
                     << athletes[i].points << endl;
            }
            break;
        }
        default:
            cout << "Неверная команда\n";
            break;
        }
        
        cout << "\n0 - выход\n1 - добавить\n2 - удалить худшего\n3 - вывод списка\n";
        cin >> choice;
        cin.ignore();  // Очистка буфера ввода
    }
    
    return 0;
}