#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

int main() {
    queue<double> q;

    for (double i = -100.99; i <= 60.99; i += 0.01) {
        q.push(i);
    }
    queue<double> copy_q = q;

    
    while (!copy_q.empty()) {
        double num = copy_q.front();
        if (abs(num) > 75.5) {
            cout << num << " ";
        }
        copy_q.pop();
    }   
    return 0;
}