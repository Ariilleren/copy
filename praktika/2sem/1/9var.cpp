#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <sstream>
using namespace std;

class Building {
    private:
        string type;
        string proizv;
        string color;
        int id;
    public:
        Building(string t, string p, string c, int id);
        
        void output() const {
            cout << "тип: " << type << endl;
            cout << "производитель: " << proizv << endl;
            cout << "цвет: " << color << endl;
            cout << "id: " << id << endl;
        }
        void save(ofstream& file) const {
            file << type << endl;
            file << proizv << endl;
            file << color << endl;
            file << id << endl;
        }
        bool load(ifstream& file) {
            if (getline(file, type) && 
                getline(file, proizv) && 
                getline(file, color) && 
                file >> id) {
                file.ignore();
                return true;
            }
            return false;
        }
        ~Building() {};
};

Building::Building(string t, string p, string c, int id1) {
    type = t;
    proizv = p;
    color = c;
    id = id1;
}

void load(list<Building>& BUILD, const string& filename) {
    ifstream file(filename);
    BUILD.clear();
    string t, p, c;
    int id;
    
    while (getline(file, t)) {
        if (!getline(file, p)) break;
        if (!getline(file, c)) break;
        if (!(file >> id)) break;
        file.ignore();
        
        BUILD.push_back(Building(t, p, c, id));
    }
    file.close();
}

void save(const list<Building>& BUILD, const string& filename) {
    ofstream file(filename);
    for (const auto& building : BUILD) {
        building.save(file);
    }
    file.close();
    cout << "Пока" << endl;
}

int main(){
    list<Building> BUILD = list<Building>();
    const string filename = "b.txt";
    load(BUILD, filename);
    int ch;
    do{
        cout << "\n1. добавить новое здание" << endl;
        cout << "2. показать все" << endl;
        cout << "3. выход с сохранением" << endl;
        cin >> ch;
        cin.ignore();
        switch(ch){
            case 1: {
                string t, p, c;
                int d;
                cout << "тип: ";
                getline(cin, t);
                cout << "производитель: ";
                getline(cin, p);
                cout << "цвет: ";
                getline(cin, c);
                cout << "id: ";
                cin >> d;
                cin.ignore();
                Building nb(t, p, c, d);
                BUILD.push_back(nb);
                cout << "👍" << endl;
                break;
            }
            case 2:{
                int a = 1;
                for (list<Building>::iterator it = BUILD.begin(); it != BUILD.end(); ++it) {
                    cout << "\n🏠 " << a++ << ":" << endl;
                    it->output();  
                }
                break;
            }
            case 3: {
                save(BUILD, filename);
                break;
            }
            default:
                cout << "Неправильная цифра" << endl;
        }
    } while (ch != 3);
    return 0;
}