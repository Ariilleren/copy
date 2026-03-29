#include <iostream>
#include <random>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    cout << endl;   
    int a[n][m];
    int b[n][m];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            a[i][j] = rand()%100;
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;   
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            b[i][j] = a[n-1-i][j];
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << b[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}