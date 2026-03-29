#include <iostream>
#include <fstream>
#include <string>
#include <vector> 
using namespace std;

string filename;
int position;

void print(string filename){
    ifstream fin(filename);
    string line;
    int lineNum = 0;
    while (getline(fin,line)) {
        cout << line << endl;
        lineNum++;
    }
    fin.close();
}

int main() {
    string filename = "text.txt"; //исходный
    
    ifstream fin(filename); 
    int count = 0;
    string temp;
    while (getline(fin, temp)) {
        count++;
    }
    fin.close();

    string* lines = new string[count];

    fin.open(filename);
    for (int i = 0; i < count; i++) {
        getline(fin, lines[i]);
    }
    fin.close();

    ofstream f2("sorted.txt");

    // cout << "Строки в обратном порядке:" << endl;
    for (int i = count - 1; i >= 0; i--) {
        f2 << lines[i] << "\n";
    }
    f2.close();
    ifstream f2_r("sorted.txt");
    for (int i = count - 1; i >= 0; i--) {
        string temp;
        getline(f2_r, temp);
        cout << temp << endl;
    }
    f2.close();
       
    delete[] lines;
    return 0;
}