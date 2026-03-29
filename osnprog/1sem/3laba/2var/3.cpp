#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
    int n;
    cout << "n: " << endl;
    cin >> n;
    cout << endl;

    srand(time(0));
    int mat[n][n];
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            mat[i][j] = rand()%100;
            cout << mat[i][j] << "     ";
        }
        cout << endl;
    }
    cout << endl;

    //главная
    int maxs = -1;
    for (int k = -(n-1); k <= (n-1); k++){
        int sum = 0;
        for (int i = 0; i < n; i++){
            int j = i+k;
            if (j >=0 && j < n){
                sum += mat[i][j];
            }
        }

        if ((sum > maxs) && (k !=0)){
            maxs = sum;
        }
        //cout << "Диагональ k=" << k << ", сумма=" << sum << endl;
    }

    int mins = 999999;
    for (int k = 0; k <= 2*(n-1); k++){
        int sum = 0;
        for (int i = 0; i< n; i++){
            int j = k-i;
            if (j>= 0 && j < n){
                sum += mat[i][j];
            }
        }
        if (sum < mins){
            mins = sum;
        }
    }
    cout << maxs << endl << mins;
    return 0;
}