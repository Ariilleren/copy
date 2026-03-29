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
    Athlete athletes[15];
    int c = 0;
    cout << "Введите данные 10 спортсменов\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "Спортсмен #" << i + 1 << ":\n";  
        cout << "Фамилия: ";
        cin >> athletes[c].lastName;
        cout << "Номер: ";
        cin >> athletes[c].number;
        cout << "Очки: ";
        cin >> athletes[c].points;
        c++;
        cout << endl;
    }

    ofstream file("athletes.txt");
    file << c << endl;  // количество
    for (int i = 0; i < c; i++)
    {
        file << athletes[i].lastName << endl;
        file << athletes[i].number << endl;
        file << athletes[i].points << endl;
    }
    file.close();
    /*ifstream in("athletes.txt");
    in >> c;
    for (int i = 0; i < c; i++)
    {
        in >> athletes[i].lastName;    
        in >> athletes[i].number;     
        in >> athletes[i].points;
    }
    in.close();*/
    
    int choice;
    cout << "0 - выход\n1 - добавить\n2 - вывести в порятке мест\n3 - вывод списка\n";
    cin >> choice;
    cin.ignore();
    
    while (choice != 0)
    {   
        switch (choice)
        {
        case 1:{
            cout << "Фамилия: ";
            cin >> athletes[c].lastName;   
            cout << "Номер: ";
            cin >> athletes[c].number; 
            cout << "Очки: ";
            cin >> athletes[c].points; 
            c++;
            ofstream file("athletes.txt");
            file << c << endl;
            for (int i = 0; i < c; i++) {
                file << athletes[i].lastName << endl;
                file << athletes[i].number << endl;
                file << athletes[i].points << endl;
            }
            file.close();       
            cout << "Спортсмен добавлен\n";
            break;
        }
        case 2:{
            Athlete sortedAthletes[100];
            for (int i = 0; i < c; i++) {
                sortedAthletes[i] = athletes[i];
            }
            
            for (int i = 0; i < c - 1; i++) {
                for (int j = 0; j < c - i - 1; j++) {
                    if (sortedAthletes[j].points < sortedAthletes[j + 1].points) {
                        Athlete temp = sortedAthletes[j];
                        sortedAthletes[j] = sortedAthletes[j + 1];
                        sortedAthletes[j + 1] = temp;
                    }
                }
            }  
            cout << "Список спортсменов по набранным местам:\n";
            cout << "Место\tФамилия\t\tНомер\tОчки\n";
            for (int i = 0; i < c; i++) {
                cout << i + 1 << "\t"
                    << sortedAthletes[i].lastName << "\t\t"
                    << sortedAthletes[i].number << "\t"
                    << sortedAthletes[i].points << endl;
            }
            break;
        }
        default:
            cout << "Неверная команда\n";
            break;
        } 
        cout << "\n0 - выход\n1 - добавить\n2 - список по номерам мест\n3 - вывод списка\n";
        cin >> choice;
    }
    return 0;
}