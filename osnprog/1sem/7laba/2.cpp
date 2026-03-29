#include <iostream>
#include "lib2.h"
using namespace std;

int main(){
    int a; int b; int c;
    cout << "введите a: ";
    cin >> a;
    cout << "введите b: ";
    cin >> b;
    cout << "введите c: ";
    cin >> c;
    cout << "ответ: " << sum(a, b, c) << endl;
    return 0;
}