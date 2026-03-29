#include <iostream>
using namespace std;

int main() {
    double a,b,c;
    cin >> a>>b>>c;
    if (a+b>c && a+c>b && b+c > a){
        double p = a+b+c;
        cout << p << endl;
    } else {
        cout << "не существует" << endl;
    }
    return 0;
}
