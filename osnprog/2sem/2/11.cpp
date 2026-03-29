#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class StackNode {
private:
    double data;
    StackNode* next;
public:
    StackNode(double value) : data(value), next(nullptr) {}
    friend class StackMemory;
    friend class StackFile;
};

class StackMemory {
private:
    StackNode* top;
public:
    StackMemory() : top(nullptr) {}
    ~StackMemory() { clear(); }
    bool isEmpty() const { return top == nullptr; }
    void push(double value) {
        StackNode* newNode = new StackNode(value);
        newNode->next = top;
        top = newNode;
    }
    double pop() {
        if (isEmpty()) throw runtime_error("Стек пуст");
        StackNode* temp = top;
        double value = temp->data;
        top = top->next;
        delete temp;
        return value;
    }
    double peek() {
        if (isEmpty()) throw runtime_error("Стек пуст");
        return top->data;
    }
    void clear() { while (!isEmpty()) pop(); }
};

class StackFile {
private:
    string filename;
public:
    StackFile(const string& fname) : filename(fname) {
        ofstream file(filename, ios::trunc);
        file.close();
    }
    bool isEmpty() {
        ifstream file(filename);
        bool empty = file.peek() == ifstream::traits_type::eof();
        file.close();
        return empty;
    }
    void push(double value) {
        ofstream file(filename, ios::app);
        file << value << endl;
        file.close();
    }
    double pop() {
        if (isEmpty()) throw runtime_error("Стек пуст");
        
        ifstream inFile(filename);
        ofstream tempFile("temp.txt");
        vector<double> values;
        double val;
        
        while (inFile >> val) {
            values.push_back(val);
        }
        inFile.close();
        
        if (values.empty()) throw runtime_error("Нет данных в файле");
        
        double lastValue = values.back();
        values.pop_back();
        
        for (double v : values) {
            tempFile << v << endl;
        }
        tempFile.close();
        
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        
        return lastValue;
    }
    double peek() {
        if (isEmpty()) throw runtime_error("Стек пуст");
        
        ifstream inFile(filename);
        double val, last;
        while (inFile >> val) {
            last = val;
        }
        inFile.close();
        return last;
    }
    void clear() {
        ofstream file(filename, ios::trunc);
        file.close();
    }
};

class SeriesProcessor {
private:
    int storageType;
    StackMemory* stackMem;
    StackFile* stackFile;
    
    bool isStackEmpty() {
        return storageType == 1 ? stackMem->isEmpty() : stackFile->isEmpty();
    }
    void pushToStack(double value) {
        if (storageType == 1) stackMem->push(value);
        else stackFile->push(value);
    }
    double popFromStack() {
        return storageType == 1 ? stackMem->pop() : stackFile->pop();
    }
    double peekFromStack() {
        return storageType == 1 ? stackMem->peek() : stackFile->peek();
    }
    void clearStack() {
        if (storageType == 1) stackMem->clear();
        else stackFile->clear();
    }
    
public:
    SeriesProcessor(int type, const string& filename = "stack_data.txt") : storageType(type) {
        if (type == 1) stackMem = new StackMemory();
        else stackFile = new StackFile(filename);
    }
    ~SeriesProcessor() {
        if (stackMem) {
            delete stackMem;
            stackMem = nullptr;
        }
        if (stackFile) {
            delete stackFile;
            stackFile = nullptr;
        }
    }
    
    // Поиск возрастающих серий и вывод их в обратном порядке
    vector<vector<double>> findSeriesReverse(const vector<double>& seq) {
        vector<vector<double>> series;
        vector<double> currentSeries;
        
        if (seq.empty()) return series;
        
        currentSeries.push_back(seq[0]);
        
        for (size_t i = 1; i < seq.size(); i++) {
            if (seq[i] > seq[i-1]) {
                currentSeries.push_back(seq[i]);
            } else {
                // Используем стек для разворота серии
                clearStack();
                for (double val : currentSeries) {
                    pushToStack(val);
                }
                
                vector<double> reversedSeries;
                while (!isStackEmpty()) {
                    reversedSeries.push_back(popFromStack());
                }
                series.push_back(reversedSeries);
                
                currentSeries.clear();
                currentSeries.push_back(seq[i]);
            }
        }
        
        // Обрабатываем последнюю серию
        if (!currentSeries.empty()) {
            clearStack();
            for (double val : currentSeries) {
                pushToStack(val);
            }
            
            vector<double> reversedSeries;
            while (!isStackEmpty()) {
                reversedSeries.push_back(popFromStack());
            }
            series.push_back(reversedSeries);
        }
        
        return series;
    }
    
    // Поиск возрастающих серий и вывод их в том же порядке
    vector<vector<double>> findSeriesSameOrder(const vector<double>& seq) {
        vector<vector<double>> series;
        vector<double> currentSeries;
        
        if (seq.empty()) return series;
        
        currentSeries.push_back(seq[0]);
        
        for (size_t i = 1; i < seq.size(); i++) {
            if (seq[i] > seq[i-1]) {
                currentSeries.push_back(seq[i]);
            } else {
                series.push_back(currentSeries);
                currentSeries.clear();
                currentSeries.push_back(seq[i]);
            }
        }
        
        // Добавляем последнюю серию
        if (!currentSeries.empty()) {
            series.push_back(currentSeries);
        }
        
        return series;
    }
    
    vector<double> inputFromKeyboard() {
        vector<double> sequence;
        int n;
        
        cout << "Введите количество элементов: ";
        cin >> n;
        
        cout << "Введите " << n << " действительных чисел:\n";
        for (int i = 0; i < n; i++) {
            double val;
            cin >> val;
            sequence.push_back(val);
        }
        cin.ignore();
        
        return sequence;
    }
    
    vector<double> inputFromFile(const string& fname) {
        ifstream file(fname);
        if (!file.is_open()) throw runtime_error("Не удалось открыть файл");
        
        vector<double> sequence;
        double val;
        
        while (file >> val) {
            sequence.push_back(val);
        }
        file.close();
        
        if (sequence.empty()) throw runtime_error("Файл пуст");
        
        return sequence;
    }
    
    void printSeries(const vector<vector<double>>& series, const string& title) {
        cout << "\n" << title << ":\n";
        cout << "====================\n";
        for (size_t i = 0; i < series.size(); i++) {
            cout << "Серия " << i+1 << ": ";
            for (double val : series[i]) {
                cout << val << " ";
            }
            cout << "\n";
        }
        cout << "====================\n";
    }
};

int main() {
    int choice, inputChoice, modeChoice;
    string filename;
    vector<double> sequence;
    
    // Создаем тестовые файлы
    ofstream("seq1.txt") << "1 3 5 2 4 6 1 3 5 7\n";
    ofstream("seq2.txt") << "5.5 6.7 8.9 3.4 5.6 7.8 2.1 4.3 6.5\n";
    
    while (true) {
        cout << "\nГЛАВНОЕ МЕНЮ:\n";
        cout << "1. Обработать последовательность (стек в памяти)\n";
        cout << "2. Обработать последовательность (стек в файле)\n";
        cout << "3. Выход\n";
        cout << "Выбор: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
            case 2: {
                SeriesProcessor processor(choice);
                
                cout << "\nВЫБОР ВВОДА:\n";
                cout << "1. С клавиатуры\n";
                cout << "2. Из файла\n";
                cout << "Выбор: ";
                cin >> inputChoice;
                
                if (inputChoice == 1) {
                    sequence = processor.inputFromKeyboard();
                } else if (inputChoice == 2) {
                    cout << "Имя файла: ";
                    cin >> filename;
                    try {
                        sequence = processor.inputFromFile(filename);
                        cout << "Последовательность из файла: ";
                        for (double val : sequence) {
                            cout << val << " ";
                        }
                        cout << endl;
                    } catch (const exception& e) {
                        cout << "Ошибка: " << e.what() << endl;
                        continue;
                    }
                } else {
                    cout << "Неверный выбор!\n";
                    continue;
                }
                
                cout << "\nРЕЖИМ ВЫВОДА:\n";
                cout << "1. Серии в обратном порядке\n";
                cout << "2. Серии в том же порядке\n";
                cout << "Выбор: ";
                cin >> modeChoice;
                
                try {
                    if (modeChoice == 1) {
                        vector<vector<double>> result = processor.findSeriesReverse(sequence);
                        processor.printSeries(result, "ВОЗРАСТАЮЩИЕ СЕРИИ (В ОБРАТНОМ ПОРЯДКЕ)");
                    } else if (modeChoice == 2) {
                        vector<vector<double>> result = processor.findSeriesSameOrder(sequence);
                        processor.printSeries(result, "ВОЗРАСТАЮЩИЕ СЕРИИ (В ТОМ ЖЕ ПОРЯДКЕ)");
                    } else {
                        cout << "Неверный режим вывода!\n";
                    }
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << endl;
                }
                break;
            }
            case 3:
                cout << "Программа завершена.\n";
                return 0;
            default:
                cout << "Неверный выбор! Попробуйте снова.\n";
        }
    }
}