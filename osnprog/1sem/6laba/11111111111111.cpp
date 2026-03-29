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

    ofstream file("athletes.txt");
    file << count << endl;  // количество
    for (int i = 0; i < count; i++)
    {
        file << athletes[i].lastName << endl;
        file << athletes[i].number << endl;
        file << athletes[i].points << endl;
    }
    file.close();
    
    //из файла
    ifstream in("athletes.txt");
    in >> count;
    in.ignore();
    for (int i = 0; i < count; i++)
    {
        getline(in, athletes[i].lastName);
        in.ignore();
        in >> athletes[i].number;
        in.ignore();
        in >> athletes[i].points;
        in.ignore();
    }
    in.close();
    
    int choice;
    cout << "0 - выход\n1 - добавить\n2 - удалить худшего\n3 - вывод списка\n";
    cin >> choice;
    cin.ignore();
    
    while (choice != 0)
    {   
        switch (choice)
        {
        case 1:{
            cout << "Фамилия: ";
            cin >> athletes[count].lastName;   
            cout << "Номер: ";
            cin >> athletes[count].number; 
            cout << "Очки: ";
            cin >> athletes[count].points; 
            count++;
            ofstream file("athletes.txt");
            file << count << endl;
            for (int i = 0; i < count; i++) {
                file << athletes[i].lastName << endl;
                file << athletes[i].number << endl;
                file << athletes[i].points << endl;
            }
            file.close();       
            cout << "Спортсмен добавлен\n";
            break;
        }
        case 2:{
            int minIndex = 0;
            for (int i = 1; i < count; i++) {
                if (athletes[i].points < athletes[minIndex].points) {
                    minIndex = i;
                }
            }
            cout << "Удален худший спортсмен: " << athletes[minIndex].lastName;
            // сдвиг
            for (int i = minIndex; i < count - 1; i++) {
                athletes[i] = athletes[i + 1];
            }
            count--; 
            ofstream file("athletes.txt");
            file << count << endl;
            for (int i = 0; i < count; i++) {
                file << athletes[i].lastName << endl;
                file << athletes[i].number << endl;
                file << athletes[i].points << endl;
            }
            file.close();
            break;  
        }
        case 3:{  
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
    }
    return 0;
}