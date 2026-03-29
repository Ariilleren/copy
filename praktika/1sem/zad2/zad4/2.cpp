#include <iostream>
using namespace std;

int main(){
    int mas[10];

    for (int i = 0; i < 10; i++) {
        cin >> mas[i];
    }

    for (int i = 0; i < 10; i++) {
        if ((i+1) % 2 == 0) {
            cout << mas[i] << " ";
        }
    }
    
    for (int i = 0; i < 10; i++) {
        if ((i+1) % 2 != 0) {
            cout << mas[i] << " ";
        }
    }
    cout << endl;
    
    return 0;
}
