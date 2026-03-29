#include <iostream>
using namespace std;

int main(){
    int mas[10];
    int p = 0;

    for (int i = 0; i<10; i++) {
        cin >> mas[i];
    }
    for (int i = 0; i<10; i++){
        cout << mas[i] << " ";
    }
    cout << endl;

    for (int i = 0; i<10; i++) {
        if (mas[i]%3==0){
            p+=mas[i];
        }
    }
    cout << p << endl;
    return 0;
}
