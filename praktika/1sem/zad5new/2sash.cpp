#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void getLineByNumber(string filename, int lineNumber) {
    ifstream in(filename);
    string line;
    int currentLine = 0;
    bool found = false;

    while (getline(in, line)) {
        currentLine++;
        if (currentLine == lineNumber) {
            cout << "Строка " << lineNumber << ": " << line << endl;
            found = true;
            break;
        }
    }
    in.close();
}

void printFile(string filename) {
    ifstream in(filename);
    string line;
    int lineNumber = 0;
    while (getline(in, line)) {
        cout << (lineNumber+1) << ". " << line << endl;
        lineNumber++;
    }
    in.close();
}

int main() {
    string filename = "strings.txt";

    ofstream out(filename);
    out << "string\nint\nbool\nfloat\ndouble" << endl;
    out.close();

    cout << "Содержимое файла:" << endl;
    printFile(filename);
    
    int searchLine;
    cout << "\nВведите номер строки для вывода (1-5): ";
    cin >> searchLine;

    getLineByNumber(filename, searchLine);
    
    return 0;
}