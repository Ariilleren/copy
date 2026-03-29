#include <iostream>
#include <list>
#include <cmath>

using namespace std;

int main() {
    list<double> l;

    for (double i = 30.99; i <= 70.99; i += 0.01) {
        l.push_back(i);
    }
    list<double> copy_l = l;

    
    while (!copy_l.empty()) {
        double num = copy_l.front();
        if (fmod(num, 2.0) < 0.000001) { ////????
            cout << num << " ";
        }
        copy_l.pop_front();
    }   
    return 0;
}