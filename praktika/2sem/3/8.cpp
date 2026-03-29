// Создать базовый класс «Садовое дерево» и производные классы
// «Яблоня», «Вишня», «Груша» и др. С помощью конструктора автоматически
// установить номер каждого дерева. Принять решение о пересадке каждого
// дерева в зависимости от возраста и плодоношения.

#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Базовый класс "Садовое дерево"
class GardenTree {
private:
    static int nextId;          // Статический счётчик для генерации номеров
    int id;                     // Уникальный номер дерева
    
protected:
    int age;                    // Возраст в годах
    bool bearsFruit;            // Плодоносит ли дерево
    
public:
    // Конструктор: автоматически устанавливает номер
    GardenTree(int treeAge, bool fruit) : age(treeAge), bearsFruit(fruit) {
        id = nextId++;
    }
    
    // Виртуальный деструктор (важно для полиморфизма)
    virtual ~GardenTree() {}
    
    // Геттеры
    int getId() const { return id; }
    int getAge() const { return age; }
    bool getBearsFruit() const { return bearsFruit; }
    
    // Сеттеры
    void setAge(int newAge) { age = newAge; }
    void setBearsFruit(bool fruit) { bearsFruit = fruit; }
    
    // Виртуальный метод вывода информации
    virtual void show() const {
        std::cout << "Дерево #" << id 
                  << ", возраст: " << age << " лет"
                  << ", плодоносит: " << (bearsFruit ? "да" : "нет");
    }
    
    // Чисто виртуальная функция - решение о пересадке
    // Каждый вид дерева определяет свои критерии
    virtual bool needTransplant() const = 0;
};

// Инициализация статической переменной
int GardenTree::nextId = 1;

// ========== ПРОИЗВОДНЫЕ КЛАССЫ ==========

// 1. Яблоня
class AppleTree : public GardenTree {
public:
    AppleTree(int age, bool fruit) : GardenTree(age, fruit) {}
    
    void show() const override {
        GardenTree::show();
        std::cout << " (Яблоня)" << std::endl;
    }
    
    bool needTransplant() const override {
        // Яблоню пересаживаем, если:
        // - возраст больше 15 лет, ИЛИ
        // - дерево старше 5 лет и не плодоносит
        if (age > 15) {
            return true;
        }
        if (age > 5 && !bearsFruit) {
            return true;
        }
        return false;
    }
};

// 2. Вишня
class CherryTree : public GardenTree {
public:
    CherryTree(int age, bool fruit) : GardenTree(age, fruit) {}
    
    void show() const override {
        GardenTree::show();
        std::cout << " (Вишня)" << std::endl;
    }
    
    bool needTransplant() const override {
        // Вишню пересаживаем, если:
        // - возраст больше 10 лет И не плодоносит
        if (age > 10 && !bearsFruit) {
            return true;
        }
        // - возраст больше 20 лет (старая вишня)
        if (age > 20) {
            return true;
        }
        return false;
    }
};

// 3. Груша
class PearTree : public GardenTree {
public:
    PearTree(int age, bool fruit) : GardenTree(age, fruit) {}
    
    void show() const override {
        GardenTree::show();
        std::cout << " (Груша)" << std::endl;
    }
    
    bool needTransplant() const override {
        // Грушу пересаживаем, если:
        // - возраст больше 8 лет И не плодоносит
        if (age > 8 && !bearsFruit) {
            return true;
        }
        // - возраст больше 25 лет
        if (age > 25) {
            return true;
        }
        return false;
    }
};

// 4. Дополнительный класс - Слива (для демонстрации расширяемости)
class PlumTree : public GardenTree {
public:
    PlumTree(int age, bool fruit) : GardenTree(age, fruit) {}
    
    void show() const override {
        GardenTree::show();
        std::cout << " (Слива)" << std::endl;
    }
    
    bool needTransplant() const override {
        // Сливу пересаживаем, если:
        // - возраст больше 12 лет И не плодоносит
        if (age > 12 && !bearsFruit) {
            return true;
        }
        return false;
    }
};

// ========== ФУНКЦИЯ ДЛЯ ПОДСЧЁТА ПЕРЕСАДОК ==========
void analyzeGarden(const std::vector<std::unique_ptr<GardenTree>>& garden) {
    std::cout << "\n=== АНАЛИЗ САДА ===\n";
    int transplantCount = 0;
    
    for (const auto& tree : garden) {
        tree->show();
        if (tree->needTransplant()) {
            std::cout << "   >>> НУЖНА ПЕРЕСАДКА! <<<" << std::endl;
            transplantCount++;
        } else {
            std::cout << "   Пересадка не требуется." << std::endl;
        }
    }
    
    std::cout << "\nВсего деревьев: " << garden.size() 
              << ", требуется пересадка: " << transplantCount << std::endl;
}

// ========== ГЛАВНАЯ ФУНКЦИЯ ==========
int main() {
    // Создаём сад (массив умных указателей на базовый класс)
    std::vector<std::unique_ptr<GardenTree>> garden;
    
    // Добавляем деревья разных видов с разными параметрами
    
    // Яблони
    garden.push_back(std::make_unique<AppleTree>(3, true));   // молодая, плодоносит
    garden.push_back(std::make_unique<AppleTree>(10, true));  // взрослая, плодоносит
    garden.push_back(std::make_unique<AppleTree>(18, true));  // старая, но плодоносит -> пересадка
    garden.push_back(std::make_unique<AppleTree>(7, false));  // не плодоносит -> пересадка
    
    // Вишни
    garden.push_back(std::make_unique<CherryTree>(4, true));   // молодая
    garden.push_back(std::make_unique<CherryTree>(12, false)); // не плодоносит, старше 10 -> пересадка
    garden.push_back(std::make_unique<CherryTree>(22, true));  // очень старая -> пересадка
    garden.push_back(std::make_unique<CherryTree>(8, true));   // нормальная
    
    // Груши
    garden.push_back(std::make_unique<PearTree>(5, true));     // молодая
    garden.push_back(std::make_unique<PearTree>(10, false));   // не плодоносит, старше 8 -> пересадка
    garden.push_back(std::make_unique<PearTree>(30, true));    // очень старая -> пересадка
    
    // Сливы (дополнительный класс)
    garden.push_back(std::make_unique<PlumTree>(6, true));     // нормальная
    garden.push_back(std::make_unique<PlumTree>(15, false));   // не плодоносит, старше 12 -> пересадка
    
    // Выводим информацию о саде
    std::cout << "=== СОСТАВ САДА ===\n";
    for (const auto& tree : garden) {
        tree->show();
    }
    
    // Анализируем необходимость пересадок
    analyzeGarden(garden);
    
    // Дополнительно: моделирование изменения состояния деревьев
    std::cout << "\n=== МОДЕЛИРОВАНИЕ ИЗМЕНЕНИЙ ===\n";
    std::cout << "Через 2 года:\n";
    
    // Создаём новый вектор для изменённых деревьев
    std::vector<std::unique_ptr<GardenTree>> gardenFuture;
    
    // Копируем деревья с обновлёнными параметрами
    for (const auto& tree : garden) {
        int newAge = tree->getAge() + 2;
        // Простая симуляция: если дереву больше 15 лет, может перестать плодоносить
        bool stillFruits = tree->getBearsFruit();
        if (newAge > 15 && tree->getBearsFruit()) {
            // 30% вероятность, что перестанет плодоносить (для демонстрации)
            stillFruits = (newAge % 3 != 0);
        }
        
        // Создаём дерево того же типа с новыми параметрами
        if (dynamic_cast<AppleTree*>(tree.get())) {
            gardenFuture.push_back(std::make_unique<AppleTree>(newAge, stillFruits));
        } else if (dynamic_cast<CherryTree*>(tree.get())) {
            gardenFuture.push_back(std::make_unique<CherryTree>(newAge, stillFruits));
        } else if (dynamic_cast<PearTree*>(tree.get())) {
            gardenFuture.push_back(std::make_unique<PearTree>(newAge, stillFruits));
        } else if (dynamic_cast<PlumTree*>(tree.get())) {
            gardenFuture.push_back(std::make_unique<PlumTree>(newAge, stillFruits));
        }
    }
    
    analyzeGarden(gardenFuture);
    
    return 0;
}