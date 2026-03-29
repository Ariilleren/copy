#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void add(string filename, string newStr, int position) {
    int count = 0;
    string temp;
    
    ifstream fin(filename);
    while (getline(fin, temp)) {
        count++;
    }
    fin.close();
    
    string** lines = new string*[count + 1];
    
    fin.open(filename);
    for (int i = 0; i < count; i++) {
        getline(fin, temp);
        lines[i] = new string(temp);
    }
    fin.close();
    
    for (int i = count; i > position; i--) {
        lines[i] = lines[i - 1];
    }
    
    lines[position] = new string(newStr);
    count++;
    
    ofstream out(filename);
    for (int i = 0; i < count; i++) {
        out << *lines[i] << endl;
    }
    out.close();
}

void printFile(string filename) { //вывод
    ifstream fin(filename);
    string line;
    int lineNumber = 0;
    while (getline(fin, line)) {
        cout << (lineNumber+1) << ". " << line << endl;
        lineNumber++;
    }
    fin.close();
}

int main() {
    string filename = "strings.txt";
    
    /*string words[] = {"string", "int", "bool", "float", "double"};
    int numb = 0;
    for (string i : words){
    add(filename, i, numb);
    numb++;}*/
    
    int lineCount = 0;
    string temp;
    ifstream countFile(filename);
    while (getline(countFile, temp)) lineCount++;
    countFile.close();
    printFile(filename);
    
    string nstr;
    int pos;
    cout << "Введите строку для добавления: ";
    cin >> nstr;
    cout << "Введите позицию для вставки (0-" << lineCount << "): ";
    cin >> pos;
    
    add(filename, nstr, pos-1);
    printFile(filename);
    
    return 0;
}