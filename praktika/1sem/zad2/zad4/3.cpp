#include <iostream>
#include <random>

using namespace std;

int main(){
    int mat[3][3];
    
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            mat[i][j] = rand()%100;
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    int max = mat[0][0];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (mat[i][j] > max){
                max = mat[i][j];
            }
        }
    }
    
    cout << max << endl;
    return 0;
}