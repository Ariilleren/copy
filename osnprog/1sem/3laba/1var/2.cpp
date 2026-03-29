#include <iostream> 
using namespace std;

int main(){
    int n;
    cout << "введите n: "<< endl;
    cin >> n;

    int a[n];
    cout << "введите n чисел : " << endl;
    for (int i = 0; i < n; i++){
        int num;
        cin >> num;
        a[i] = num;
    }
    cout << endl;
    cout << "массив a: " << endl;
    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    int mat[n][n];
    for (int i=0; i<n; i++){
        for (int j = 0; j<n; j++){
            mat[n][n] = a[(i+j)%n];
            cout << mat[n][n] << "   ";
        }
        cout << endl;
    }

    return 0;
}