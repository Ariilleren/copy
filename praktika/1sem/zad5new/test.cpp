#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    int kolvo = 5; 
    ifstream file("data.txt");
    ofstream idx("idx.txt");
    idx << kolvo << endl;

    for (int i = 0; i < kolvo; i++) {
        int pos = file.tellg();
        idx << pos << endl; 
        
        string line;
        getline(file, line); 
    }
    
    file.close();
    idx.close();

    ifstream idxRead("idx.txt");
    int count;
    idxRead >> count;
    
    int positions[kolvo];
    for (int i = 0; i < count; i++) {
        idxRead >> positions[i];
    }
    idxRead.close(); 

    int lineNumber;
    cout << "номер строки для чтения (1-" << count << "): ";
    cin >> lineNumber;

    ifstream dataFile("data.txt");
        
    dataFile.seekg(positions[lineNumber-1]);
   
    string line;
    if (getline(dataFile, line)) {
        cout << "Строка " << lineNumber << ": " << line << endl;
    }
    dataFile.close();
    return 0;
    
}