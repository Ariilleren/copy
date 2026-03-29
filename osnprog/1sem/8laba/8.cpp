#include <iostream>
#include <list>
#include <cmath>
#include <random>
using namespace std;

int main() {
    list<double> l;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<>  dis(30.99, 70.99);

    for (int i = 0; i < 15; i++) {
        l.push_back(dis(gen));
    }
    list<double> copy_l = l;
    
    while (!copy_l.empty()) {
        double numD = copy_l.front();
        int numI = numD;
        if (numI % 2 ==0) { 
            cout << numI << " ";
        }
        copy_l.pop_front();
    }   
    return 0;
}