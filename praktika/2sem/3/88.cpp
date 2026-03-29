#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  
using namespace std;

class GardenTree {
private:
    static int nextId;  
    int id;                   
    
protected:
    int age;
    bool bearsFruit;           
    
public:
    GardenTree(int treeAge, bool fruit) : age(treeAge), bearsFruit(fruit) {
        id = nextId++;
    }
    virtual ~GardenTree() {}
    int getId() const { return id; }
    int getAge() const { return age; }
    bool getBearsFruit() const { return bearsFruit; }
    void setAge(int newAge) { age = newAge; }
    void setBearsFruit(bool fruit) { bearsFruit = fruit; }
    virtual void show() const {
        cout << "Дерево #" << id 
             << ", возраст: " << age << " лет"
             << ", плодоносит: " << (bearsFruit ? "да" : "нет");
    }
    virtual bool needTransplant() const = 0;
    virtual GardenTree* clone() const = 0;
};

int GardenTree::nextId = 1;
class AppleTree : public GardenTree {
public:
    AppleTree(int age, bool fruit) : GardenTree(age, fruit) {}
    
    void show() const override {
        GardenTree::show();
        cout << " (Яблоня)" << endl;
    }
    bool needTransplant() const override {
        if (age > 15) return true;
        if (age > 5 && !bearsFruit) return true;
        return false;
    }
    GardenTree* clone() const override {
        return new AppleTree(age, bearsFruit);
    }
};
class CherryTree : public GardenTree {
public:
    CherryTree(int age, bool fruit) : GardenTree(age, fruit) {} 
    void show() const override {
        GardenTree::show();
        cout << " (Вишня)" << endl;
    }
    bool needTransplant() const override {
        if (age > 10 && !bearsFruit) return true;
        if (age > 20) return true;
        return false;
    }
    GardenTree* clone() const override {
        return new CherryTree(age, bearsFruit);
    }
};
class PearTree : public GardenTree {
public:
    PearTree(int age, bool fruit) : GardenTree(age, fruit) {}
    void show() const override {
        GardenTree::show();
        cout << " (Груша)" << endl;
    }
    bool needTransplant() const override {
        if (age > 8 && !bearsFruit) return true;
        if (age > 25) return true;
        return false;
    }
    GardenTree* clone() const override {
        return new PearTree(age, bearsFruit);
    }
};
void clearGarden(vector<GardenTree*>& garden) {
    for (GardenTree* tree : garden) {
        delete tree;
    }
    garden.clear();
}
void showAllTrees(const vector<GardenTree*>& garden) {
    cout << "\n=== СОСТАВ САДА ===\n";
    for (const auto& tree : garden) {
        tree->show();
    }
}
void analyzeGarden(const vector<GardenTree*>& garden) { 
    cout << "\n=== АНАЛИЗ ПЕРЕСАДОК ===\n";
    int transplantCount = 0;
    for (const auto& tree : garden) {
        tree->show();
        if (tree->needTransplant()) {
            cout << "   >>> НУЖНА ПЕРЕСАДКА! <<<" << endl;
            transplantCount++;
        } else {
            cout << "   Пересадка не требуется." << endl;
        }
    }
}
void addTree(vector<GardenTree*>& garden) {
    int type, age;
    char fruitChar;
    bool fruit;
    cout << "\n=== ДОБАВЛЕНИЕ ДЕРЕВА ===\n";
    cout << "Выберите тип дерева:\n";
    cout << "1 - Яблоня\n";
    cout << "2 - Вишня\n";
    cout << "3 - Груша\n";
    cout << "Ваш выбор: ";
    cin >> type;
    
    cout << "Введите возраст дерева (лет): ";
    cin >> age;
    cout << "Плодоносит? (y/n): ";
    cin >> fruitChar;
    fruit = (fruitChar == 'y' || fruitChar == 'Y');
    
    switch (type) {
        case 1:
            garden.push_back(new AppleTree(age, fruit));
            break;
        case 2:
            garden.push_back(new CherryTree(age, fruit));
            break;
        case 3:
            garden.push_back(new PearTree(age, fruit));
            break;
        default:
            cout << "\nНеверный выбор!\n";
    }
    cout << "\nДерево добавлено!\n";
}

int main() {
    vector<GardenTree*> garden;
    int choice;
    do {
        cout << "\n========================================\n";
        cout << "   САДОВЫЙ КАЛЬКУЛЯТОР ПЕРЕСАДОК\n";
        cout << "========================================\n";
        cout << "1. Добавить дерево\n";
        cout << "2. Показать все деревья\n";
        cout << "3. Анализ необходимости пересадки\n";
        cout << "0. Выход\n";
        cin >> choice;
        
        switch (choice) {
            case 1:
                addTree(garden);
                break;
            case 2:
                showAllTrees(garden);
                break;
            case 3:
                analyzeGarden(garden);
                break;

            case 0:
                cout << "\nВыход из программы...\n";
                break;
            default:
                cout << "\nНеверный выбор! Попробуйте снова.\n";
        }
        cin.clear();  
        cin.ignore();
    } while (choice != 0);

    clearGarden(garden);
    return 0;
}