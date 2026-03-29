#include <iostream>
#include <random>
#include <cmath>
using namespace std;

int main(){
    int n,m;
    cin >> m >> n;
    cout << endl;

    int a[n][m];
    int c[m]; //характеристики

    for (int i = 0; i<n; i++){
        for (int j = 0; j<m;j++){
            a[i][j] = rand()%100 - 50;
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (int j = 0; j<m; j++){
        c[j]=0;
        for (int i = 0; i<n; i++){
            if (a[i][j]<0 && a[i][j] %2 !=0){
                c[j] += abs(a[i][j]);
            }
        }
        cout << "Характеристика столбца "<< j+1 << ": " << c[j]<< endl;
    }
    cout << endl;

    for (int j = 0; j < m-1; j++){
        for (int k = 0; k < m-1-j; k++){
            if (c[k] > c[k+1]){
                int temp_char = c[k];
                c[k] = c[k+1];
                c[k+1] = temp_char;
                
                for (int i = 0; i < n; i++){
                    int temp = a[i][k];
                    a[i][k] = a[i][k+1];
                    a[i][k+1] = temp;
                }
            }
        }
    }
    
    cout << "Отсортированная матрица:" << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}
