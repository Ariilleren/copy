#include <iostream>
#include <random>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    cout << endl;
    
    int mat[n][m];
    int sum[m];
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            mat[i][j] = rand()%100;
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    for (int j = 0; j < m; j++){
        sum[j] = 0;
        for (int i = 0; i < n; i++){
            sum[j] += mat[i][j];
        }
        cout << sum[j] << " ";
    }
    cout << endl;
    
    int max_sum = sum[0];
    int m = 0;
    for (int j = 0; j < m; j++){
        if (sum[j] > max_sum){
            max_sum = sum[j];
            m = (j+1);
        }
    } 
    cout << m << endl;
    return 0;
}