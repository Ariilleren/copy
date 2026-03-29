#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class StackNode {
private:
    char data;
    StackNode* next;
public:
    StackNode(char value) : data(value), next(nullptr) {}
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
    void push(char value) {
        StackNode* newNode = new StackNode(value);
        newNode->next = top;
        top = newNode;
    }
    char pop() {
        if (isEmpty()) throw runtime_error("Stack empty");
        StackNode* temp = top;
        char value = temp->data;
        top = top->next;
        delete temp;
        return value;
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
    void push(char value) {
        ofstream file(filename, ios::app);
        file << value << endl;
        file.close();
    }
    char pop() {
        if (isEmpty()) throw runtime_error("Stack empty");
        ifstream inFile(filename);
        ofstream tempFile("temp.txt");
        string line, lastValue;
        while (getline(inFile, line)) if (!line.empty()) lastValue = line;
        inFile.close();
        inFile.open(filename);
        while (getline(inFile, line)) if (line != lastValue) tempFile << line << endl;
        inFile.close();
        tempFile.close();
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        return lastValue[0];
    }
    void clear() {
        ofstream file(filename, ios::trunc);
        file.close();
    }
};

class BracketChecker {
private:
    int storageType;
    StackMemory* stackMem;
    StackFile* stackFile;
    
    bool isStackEmpty() {
        return storageType == 1 ? stackMem->isEmpty() : stackFile->isEmpty();
    }
    void pushToStack(char value) {
        if (storageType == 1) stackMem->push(value);
        else stackFile->push(value);
    }
    char popFromStack() {
        return storageType == 1 ? stackMem->pop() : stackFile->pop();
    }
    void clearStack() {
        if (storageType == 1) stackMem->clear();
        else stackFile->clear();
    }
    
public:
    BracketChecker(int type, const string& filename = "stack_data.txt") : storageType(type) {
        if (type == 1) stackMem = new StackMemory();
        else stackFile = new StackFile(filename);
    }
    ~BracketChecker() {
        if (stackMem) delete stackMem;
        if (stackFile) delete stackFile;
    }
    
    bool checkBrackets(const string& expr) {
        clearStack();
        for (char ch : expr) {
            if (ch == '(' || ch == '[' || ch == '{') pushToStack(ch);
            else if (ch == ')' || ch == ']' || ch == '}') {
                if (isStackEmpty()) return false;
                char last = popFromStack();
                if ((ch == ')' && last != '(') || (ch == ']' && last != '[') || (ch == '}' && last != '{'))
                    return false;
            }
        }
        return isStackEmpty();
    }
    
    string inputFromKeyboard() {
        string expr;
        cout << "Enter expression: ";
        getline(cin, expr);
        return expr;
    }
    
    string inputFromFile(const string& fname) {
        ifstream file(fname);
        if (!file.is_open()) throw runtime_error("Cannot open file");
        string expr;
        getline(file, expr);
        file.close();
        return expr;
    }
    
    void printResult(const string& expr, bool valid) {
        cout << "\n====================\n";
        cout << "Expression: " << expr << "\nResult: " << (valid ? "CORRECT" : "INCORRECT") << "\n";
        cout << "====================\n";
    }
};

int main() {
    int choice, inputChoice;
    string expr, filename;
    bool result;
    
    ofstream("input_correct.txt") << "{[()]}([]){}\n";
    ofstream("input_incorrect.txt") << "({[}])\n";
    
    while (true) {
        cout << "\nMENU:\n1. Check (memory)\n2. Check (file)\n3. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
            case 2: {
                BracketChecker checker(choice);
                
                cout << "\nINPUT METHOD:\n1. Keyboard\n2. File\nChoice: ";
                cin >> inputChoice;
                cin.ignore();
                
                switch(inputChoice) {
                    case 1:
                        expr = checker.inputFromKeyboard();
                        break;
                    case 2:
                        cout << "Filename: ";
                        getline(cin, filename);
                        try {
                            expr = checker.inputFromFile(filename);
                        } catch (const exception& e) {
                            cout << "Error: " << e.what() << endl;
                            continue;
                        }
                        break;
                    default:
                        cout << "Invalid input choice!\n";
                        continue;
                }
                
                result = checker.checkBrackets(expr);
                checker.printResult(expr, result);
                break;
            }
            case 0:
                exit(0);
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}